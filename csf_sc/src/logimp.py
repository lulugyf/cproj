#!/usr/bin/env python
#coding=gbk

headlen = 8 + 64 + 17 + 14 + 14 + 10 + 10 + 14 + 14
'''
structlogdata{
    char tagstr[8];        //标识一组日志开始，固定字串 \n^ERRLG^
    char servicename[64];  //服务名称，长度不足前补空格
    char begintime[17];    //服务调用开始时间， 格式： yyyymmddHHMMSSsss
    char timecost[14];     //服务调用使用时间， 整数，单位： ms
    char processid[14];    //进程id
    char errid[10];       // 随机生成的错误id， 该值会插入到返回信息中使前台可以看到，可填入申告单便于快速定位错误信息
    char errcode[10];     // 业务返回错误代码， 0为成功
    char inputlen[14];     //10进制输入报文长度，长度不足前补空格
    char outputlen[14];    //10进制输出报文长度，长度不足前补空格
    char indata[atoi(inputlen)];        // 输入报文数据
    char outdata[atoi(outputlen)];      // 输出报文数据
};

service_name, op_time, begin_time, time_cost, errid,
    server_ip, client_ip, contact_id, phone_no, op_code,
    login_no, ret_code, ret_msg, detail_msg,
    input, output
'''

import struct
import os
import sys
import json
import socket
import ConfigParser
import cPickle as pickle
import time
import xml.etree.ElementTree as ET

import logging
from logging.handlers import TimedRotatingFileHandler

def initLogger():
    global logger
    logHandler = TimedRotatingFileHandler("imp.log",when="D")
    logFormatter = logging.Formatter('%(asctime)s %(message)s')
    logHandler.setFormatter( logFormatter )
    logger = logging.getLogger( 'logimp' )
    logger.addHandler( logHandler )
    logger.setLevel( logging.DEBUG )

def getmyip():
    myname = socket.getfqdn(socket.gethostname())
    myaddr = socket.gethostbyname(myname)
    return myaddr

def findFields(obj, dic, out):
    if len(dic) == 0:
        return
    if type(obj) != dict:
        return
    for k, v in obj.items():
        if type(v) == dict:
            findFields(v, dic, out)
        else:
            fn = dic.pop(k, None)
            if fn is None: continue
            out[fn] = v

def xml_addchild(level, el, obj):
    o = {}
    obj[el.tag] = o
    for child in el:
        text = child.text
        if text is not None:
            obj[child.tag] = text
        else:
            xml_addchild(level+1, child, o)

#把utype的xml串解析成dict对象, 没有管utype的类型， 值都按str处理
def parseUtypeXml(xmlstr, obj):
    if xmlstr.find('<?xml') >= 0:
        p = xmlstr.find('?>') + 2
        xmlstr = xmlstr[p:]
    print xmlstr
    root = ET.fromstring(xmlstr.encode("UTF-8"))
    level = 1
    xml_addchild(level, root, obj)

def readOneRecord(f):
    h = f.read(headlen)
    if h == '':
        return None
    (_, service_name, begin_time, time_cost, process_id,
        errid, ret_code, in_len, out_len) = struct.unpack('8s64s17s14s14s10s10s14s14s', h)
    input = f.read(int(in_len)).decode('gbk')
    output = f.read(int(out_len)).decode('gbk')
    
    p = input.find('{')
    if p < 0 or p > 10: #xml
        uin = {}
        parseUtypeXml(input, uin)
        #print '===', repr(uin)
        uout = {}
        parseUtypeXml(output, uout)
    else:
        uin = json.loads(input)
        uout = json.loads(output)
    
    out = {"service_name": service_name.strip(), "op_time": begin_time,
           "begin_time":begin_time, "time_cost":int(time_cost),
           "errid":int(errid), "ret_code":int(ret_code),
           "input":input, "output":output,
           "server_ip":myipaddr}
    
    dic = {"CONTACT_ID":"contact_id",
               "PHONE_NO":"phone_no",
               "OP_CODE":"op_code",
               "LOGIN_NO":"login_no",
               "ENDUSRIP":"client_ip" }
    findFields(uin, dic, out)
    for v in dic.values(): out[v] = ""
    
    dic = {"RETURN_MSG":"ret_msg", "DETAIL_MSG":"detail_msg"}
    findFields(uout, dic, out)
    for v in dic.values(): out[v] = ""

    return out

def readOneFile(fname, breakpoint):
    f = file(fname)
    pos = breakpoint.get(fname, 0L)
    if pos > 0:
        f.seek(pos)
    modified = False
    counter = 0;
    while True:
        obj = readOneRecord(f)
        if obj is None:
            break
        #TODO: save to mongodb
        csflog.insert(obj)
        
        modified = True
        counter += 1
        
    if not modified:
        #check if time passed, filename: 2013121610.29.log
        cur_hour = time.localtime().tm_hour
        file_hour = int(fname[8:10])
        if file_hour != cur_hour:
            logger.info("remove log: %s", fname)
            os.remove(fname)
            breakpoint.pop(fname, None)
            modified = True
    else:
        breakpoint[fname] = f.tell()
        logger.info("read %d record from %s", counter, fname)
    f.close()
    return modified
        

def scanpath():
    bkfile = ".breakpoint.dat"
    try:
        breakpoint = pickle.load(file(bkfile, "rb"))
    except:
        breakpoint = {}
    filelist = os.listdir('.')
    logger.info("scanning begin")
    for fname in filelist:
        if not (fname.startswith("20") and fname.endswith(".log") ):
            continue
        #logger.info("dealing file: %s", fname)
        try:
            modi = readOneFile(fname, breakpoint)
        except Exception,ex:
            logger.error("deal file %s failed: %s", fname, ex)
            return
        if modi:
            logger.debug("file: %s, breakpoint modified, save it", fname)
            pickle.dump(breakpoint, file(bkfile, "wb")) # 有断点变动，保存文件
    logger.info("scan finished")
    

def main():
    import pymongo
    
    global myipaddr
    global csflog
    
    initLogger()
    myipaddr = getmyip()
    cfgpath = "%s/run/cfg/crm.cfg"%os.environ['HOME']
    c = ConfigParser.RawConfigParser()
    c.read(cfgpath)
    logpath = c.get('ERRLOG', 'STORE_PATH')
    os.chdir(logpath)
    
    dblabel = c.get('ERRLOG', 'DBLABEL')
    while True:
        try:
            conn = pymongo.Connection(dblabel)
            csflog = conn.logs.csf
        except Exception,ex:
            logger.error("connect mongo:%s failed: %s", dblabel, ex)
            time.sleep(1.0)
            continue
        scanpath()
        try:
            conn.close()
        except Exception,ex:
            logger.error("close mongo failed: %s", ex)
        time.sleep(1.0)
    
def _test_():
    global myipaddr

    initLogger()
    myipaddr = getmyip()
    #f = file("d:/temp/session.log", "r")
    f = file("d:/temp/2013120609.24.log", "r")
    r = readOneRecord(f)
    f.close()
    print repr(r)
    
if __name__ == '__main__':
    _test_()
