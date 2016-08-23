#!/usr/bin/env python

import sys
import os
import urllib2

sys.path.insert(0, "%s/bin/py"%os.environ.get("WORKDIR", ''))

import tuxedo.atmi as atmi
import json
import ConfigParser

'''
[CALL_ESB_API]
CHANNEL_ID=12
POOL_ID=11
POOL_ID.11=10.95.242.152:53000
'''        


class server:
    def __init__(self):
        self.esb_url = None
        
        config = ConfigParser.SafeConfigParser()
        config.read(os.environ['CRM_CFG'])
        self.channel_id = config.get('CALL_ESB_API', 'CHANNEL_ID')
        self.pool_id = config.get('CALL_ESB_API', 'POOL_ID')
        self.esb_addr = config.get('CALL_ESB_API', 'POOL_ID.'+self.pool_id)

    
    def jdump(self, obj):
        s = json.dumps(obj, encoding='gbk', ensure_ascii=False)
        return s.encode('gbk')
    def jload(self, s):
        return json.loads(s, 'gbk')

    def init(self, arg):
        atmi.tpadvertise('sMerge1')
    
    def fail(self, errcode, errmsg):
        o = { "ROOT": { "RETURN_CODE": 409007000+errcode,
                        "RETURN_MSG": errmsg, "USER_MSG": "",
                        "DETAIL_MSG": "", "PROMPT_MSG": "" } }
        return self.jdump(o)
    
    def callFromESB(self, svcname, data):
        #get from config
        url = "http://%s/esbWS/rest/%s"%(self.esb_addr, svcname)
        req = urllib2.Request(url)
        req.add_header('Content-Type', 'application/json')
        sdata = self.jdump(data)
        print sdata
        resp = urllib2.urlopen(req, sdata)
        rcode = resp.getcode()
        if rcode == 200:
            rdata = resp.read()
            print rdata
            return self.jload(rdata)
        else:
            raise Exception("call esb[%s] failed, http code[%d]"%(url, rcode))
    
    def sMerge1(self, arg):
        #print "calling service", self.svcname, 'from', self.cltid
        try:
            indata = self.jload(arg)
            header = indata['ROOT']['HEADER']
            body   = indata['ROOT']['BODY']
            phone_no = body.get('PHONE_NO', None)
            if phone_no is None:
                return self.fail(101, 'need PHONE_NO')
            login_no = body.get('LOGIN_NO', None)
            if login_no is None:
                return self.fail(102, 'need LOGIN_NO')
            
            outr = {}
            out = {"ROOT":outr}
            
            
            #call sSmsQryScL
            svc = "sSmsQryScL"
            pin = {"ROOT":{"HEADER":header, "BODY":{
                "OLD_SERVER":"sPubUsrMsgList",
                "PROVINCE_GROUP":"10008",
                "LOGIN_NO":login_no,
                "QUERY_TYPE":"",
                "PHONE_NO":phone_no,
                }}}
            pout1 = atmi.tpcall(svc, self.jdump(pin))
            pout1 = self.jload(pout1).get('ROOT', {})
            outr[svc] = pout1
            sim_no = None
            region_code = None
            if pout1.get('RETURN_CODE',-1) == 0:
                sim_no = pout1['OUT_DATA']['SIM_NO']
                region_code = str(pout1['OUT_DATA']['REGION_ID'])
            
            #call sQBaseInfo
            svc = "sQBaseInfo"
            pin = {"ROOT":{"HEADER":header, "BODY":{
                "PHONE_NO":phone_no,
                "QUERY_FLAG":"m",
                }}}
            pout2 = atmi.tpcall(svc, self.jdump(pin))
            pout2 = self.jload(pout2).get('ROOT', {})
            outr[svc] = pout2
            
            #call sQrySimDetInfo
            if sim_no is not None and region_code is not None:
                svc = "sQrySimDetInfo"
                pin = {"ROOT":{"HEADER":header, "BODY":{ "REQUEST_INFO": {
                    "SIM_NO": sim_no,
                    "LOGIN_NO": login_no,
                    "REGION_CODE": region_code,
                    }}} }
                pout3 = self.callFromESB(svc, pin)
                pout3 = pout3.get('ROOT', {})
                outr[svc] = pout3
            
        except Exception,ex:
            return self.fail(199, 'exception: '+str(ex))
        out['RETURN_CODE'] = 0
        out['RETURN_MSG'] = 'ok!'
        #return json.dumps(out, sort_keys=True, indent=2 * ' ', encoding='gbk')
        return self.jdump(out)
    
       
    def cleanup(self):
        pass


if __name__ == '__main__':
    #atmi.mainloop(sys.argv, server(), None)
    
    arg = '''{
   "ROOT":{
      "HEADER":{
         "CHANNEL_ID":"12",
         "POOL_ID":"11",
         "DB_ID": "c1",
         "ROUTING":{
            "ROUTE_TYPE":"10",
            "ROUTE_VALUE":"18783888332"
         }
      },
      "BODY":{
         "LOGIN_NO":"paa3i4",
         "PHONE_NO":"18783888332"
      }
   }
}'''
    s = server()
    print s.sMerge1(arg)

'''
REGION_CODE:27
PHONE_NO:18783888332
SIM_NO:898600E22212A9718557
       898600E22212A9718557

clxml sMerge1 '{
   "ROOT":{
      "HEADER":{
         "CHANNEL_ID":"12",
         "POOL_ID":"11",
         "DB_ID": "c1",
         "ROUTING":{
            "ROUTE_TYPE":"10",
            "ROUTE_VALUE":"18783888332"
         }
      },
      "BODY":{
         "LOGIN_NO":"paa3i4",
         "PHONE_NO":"18783888332"
      }
   }
}'
'''    