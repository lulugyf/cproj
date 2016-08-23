#coding=gbk
from __future__ import generators
import os
import sys
import threading
import time
import socket

runmode = "client"

def main ():
    if len(sys.argv) > 1 and sys.argv[1] == 'server':
        FileServer().start()
        return
    host, rpath = ("172.21.1.36", 7802), "/crmpdpp/csf/csf_sc/run"

    basedir = os.getcwd()
    print "current dir:", basedir
    flist = {}
    lock = threading.Lock()
    SendFiles(host, rpath, flist, lock).start()
    watch_path(basedir, flist, lock, True);


def recvn(sock, n):
    s = ""
    while n > 0:
        try:
            s1 = sock.recv(n)
        except Exception,x:
            print "recv failed[%s]"%x
            return None
        if len(s1) == 0:
            return None
        n -= len(s1)
        s = s + s1
    return s

class FileServer:
    def __init__(self):
        pass
    
    def start(self):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        sock.bind(('', 7801))
        sock.listen(5)
        while True:
            s, info = sock.accept()
            s.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
            
            try:
                self.doConnect(s)
            except:
                pass
            s.close()
            
    def doConnect(self, sock):
        # header 结构：   sfil(head length - 12 in format %08d)(remote file name);(local file name);(file length in hex bytes)(.... file data)
        h = recvn(sock, 12)
        if not h.startswith("sfil"):
            return
        hlen = int(h[4:])
        if hlen < 0:
            return
        head = recvn(sock, hlen)
        rfile, lfile, fsize_ = head.split(';')
        fsize = long(fsize_, 16)  #文件长度是16进制表示的
        
        try:
            if rfile.find('/') >= 0: #带路径的，需要先补全路径
                p = rfile.rfind('/')
                os.makedirs(rfile[0:p])
                
            f = file(rfile, "wb")
            sock.sendall('sfil000000040000')
        except : #失败则返回错误应答， 不再接收文件
            sock.sendall('sfil000000047777')
            print ""
            return
        try:
            while fsize > 0:
                l = min((fsize, 4096))
                data = recvn(sock, l)
                if data == '': continue
                f.write(data)
                fsize -= len(data)
        except:
            pass
        finally:
            f.close()

class SendFiles(threading.Thread):
    def __init__(self, host, rpath, flist, lock):
        threading.Thread.__init__(self)
        self.host = host
        self.rpath = rpath
        self.flist = flist
        self.lock = lock

    def run(self):
        while 1:
            time.sleep(2.0)
            self.lock.acquire()
            if len(self.flist) > 0:
                for fname in self.flist.keys():
                    rfile = self.rpath + "/" + fname
                    self.sendonefile(self.host, rfile, fname)
                    self.flist.pop(fname)
                    print "sendfile:", fname
            self.lock.release()
    def sendonefile(self, host, rfile, lfile):
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        sock.connect(host)
        fsize = os.stat(lfile).st_size
    
        s1 = "%s;%s;%x"%(rfile, lfile, fsize)
        s1 = s1.encode("gbk")
        s2 = "sfil%08d%s"%(len(s1), s1)
        sock.sendall(s2)
    
        s1 = recvn(sock, 12)
        slen = int(s1[4:])
        s2 = recvn(sock, slen)
        if s2 != '0000':
            print 'refuse ', s2, 'host', host, 'rfile', rfile, 'lfile', lfile
            sock.close()
            return
            #os.chdir(pwd)
        f = file(lfile, "rb")
        while fsize > 0:
            l = 4096
            if fsize < l:
                l = fsize
            s = f.read(4096)
            sock.sendall(s)
            fsize -= len(s)
        sock.close()
      



ACTIONS = {
  1 : "Created",
  2 : "Deleted",
  3 : "Updated",
  4 : "Renamed to something",
  5 : "Renamed from something"
}

def watch_path (path_to_watch, flist, lock, include_subdirectories=False):
    import win32file
    import win32con
    FILE_LIST_DIRECTORY = 0x0001
    hDir = win32file.CreateFile (
        path_to_watch,
        FILE_LIST_DIRECTORY,
        win32con.FILE_SHARE_READ | win32con.FILE_SHARE_WRITE,
        None,
        win32con.OPEN_EXISTING,
        win32con.FILE_FLAG_BACKUP_SEMANTICS,
        None
      )
    while 1:
        print 'waiting...'
        results = win32file.ReadDirectoryChangesW (
          hDir,
          1024,
          include_subdirectories,

           win32con.FILE_NOTIFY_CHANGE_LAST_WRITE,

          None,
          None
        )
          #win32con.FILE_NOTIFY_CHANGE_FILE_NAME | 
          # win32con.FILE_NOTIFY_CHANGE_DIR_NAME |
          # win32con.FILE_NOTIFY_CHANGE_ATTRIBUTES |
          # win32con.FILE_NOTIFY_CHANGE_SIZE |
          # win32con.FILE_NOTIFY_CHANGE_LAST_WRITE |
          # win32con.FILE_NOTIFY_CHANGE_SECURITY,
        lock.acquire()
        for action, fname in results:
            fname = fname.replace('\\', '/')
            p = fname.rfind('/') # ignore files that with . prefix.
            if p >= 0:
                if fname[p+1] == '.': continue
            if fname[0] == '.': continue
            
            full_filename = os.path.join (path_to_watch, fname)
            if not os.path.exists (full_filename):
                file_type = "<deleted>"
            elif os.path.isdir (full_filename):
                file_type = 'folder'
            else:
                file_type = 'file'
            print file_type, full_filename, ACTIONS.get (action, "Unknown")
            if file_type == "<deleted>" or file_type == "folder":
                continue

            if action == 1 or action == 3:
                flist[fname] = 1
        lock.release()

if __name__ == '__main__':
    main()
