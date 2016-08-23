#!/usr/bin/env python

import sys
import glob
import os

def upso(soname):
	basedir = "%s/solib"%os.environ["WORKDIR"]
	fnames = glob.glob("%s/%s.*"%(basedir, soname))
	maxid = 0
	for f in fnames:
		p = f.rfind('.')
		if p < 0: continue
		cid = int(f[p+1:])
		if maxid < cid:
			maxid = cid
	symname = "%s/%s"%(basedir, soname)
	newfname = "%s/%s.%d"%(basedir, soname, maxid+1)
	
	os.rename(soname, newfname)
	try:
		os.remove(symname)
	except:
		pass
	os.symlink(newfname, symname)
	print "new file to %s.%d"%(soname, maxid+1)
	
if __name__ == '__main__':
	upso(sys.argv[1])
	