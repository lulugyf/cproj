#!/usr/bin/env python
#coding=gbk
import sys
import os
import yaml


def genFile(svc, cppfile, extra):
    f = file(cppfile, 'w')
    f.write('#include "allBCP.h"\n')
    if extra is not None:
        f.write(extra)
        f.write('\n')

    svclist = []
    for line in svc:
        vs = line.split()
        if len(vs) < 4:
            continue
        svcname, bpname, dblabel, conntype = vs[:4]
        # 因为默认 allBCP.h 中已经有所有 bc/bp的函数申明， 因此， 这里的函数申明先去掉 2013-8-16
        if bpname.startswith('(C)'):
            bpname = bpname[3:].strip()
            #f.write('extern "C" utype* %s(const utype * inParam,TCtrlInfo *errInfo);\n'%bpname)
        else:
            #f.write('utype* %s(const utype * inParam,TCtrlInfo *errInfo);\n'%bpname)
            pass
        f.write('extern "C" void %s(TPSVCINFO *transb){\n'%svcname)
        if len(vs) > 4 and vs[4] == '1':
            f.write('  tuxadp1(transb->name, transb, %s, "%s", %s, %s);\n}\n'%(
                                    dblabel, bpname, bpname, conntype))
        else:
            f.write('  tuxadp(transb->name, transb, %s, "%s", %s, %s);\n}\n'%(
                                    dblabel, bpname, bpname, conntype))
        svclist.append('-s')
        svclist.append(svcname)
    f.close()
    return " ".join(svclist)

def main(svrname):
    if not os.path.exists('build'):
        os.mkdir('build')
    print "SERVER:", svrname
    cfg = yaml.load(file(svrname + '.yaml'))
    #svc, lib = loadcf(svrname + '.yaml')
    svclist = genFile(cfg['SERVICE'], 'build/%s.cpp'%svrname, cfg.get('EXTRA', None))
    lib = cfg.get('LIBS')
    if lib is None: lib = []
    lib.insert(0, svrname+".o")
    liblist = " ".join(lib)
    
    print 'svclist', svclist
    print 'liblist', liblist
    
    #make -f ${HOME}/run/framework/tools/svc.mk ORDER SRV_NAME=${SRV_NAME} DEP="${DEP}" SVS="${SVS}"
    os.chdir('build')
    cmd = 'make -f ../makeserver.mk SERVER SRV_NAME="%s" DEP="%s" SVS="%s"'%(
        svrname, liblist, svclist)
    print cmd
    os.system(cmd)

if __name__ == '__main__':
    if len(sys.argv[1]) < 2:
        print "Usage:\n  "+sys.argv[0] + " <servername1[ servername2[ servername3...]]>\n\n"
    else:
        for svrname in sys.argv[1:]:
            main(svrname)
