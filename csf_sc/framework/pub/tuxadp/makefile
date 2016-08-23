include $(HOME)/run/framework/tools/env.mk
newdate=`date +%Y%m%d%H%M%S`
a:libtuxadp.so

MAIN_VER=0
MINOR_VER=1

OBJS=tuxadp.o framework.o errlog.o errmng.o calltrace.o util_socket.o
#OBJS=tux.o adapter.o framework.o errlog.o 
libtuxadp.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(DYNLIBFLAGS) -o $@ $(OBJS) -L../../../local/lib -luuid -L$(WORK_LIB_DIR) -lzlib -llogfunc
	mv $@ $(WORK_LIB_DIR)

__libtuxadp.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -Wl,-soname,$@.$(MAIN_VER) -o $@.$(MAIN_VER).$(MINOR_VER) $(OBJS) -L$(WORK_LIB_DIR) -lzlib -llogfunc
	mv $@.$(MAIN_VER).$(MINOR_VER) $(WORK_LIB_DIR)
	rm -f $(WORK_LIB_DIR)/$@.$(MAIN_VER) $(WORK_LIB_DIR)/$@
	ln -s $(WORK_LIB_DIR)/$@.$(MAIN_VER).$(MINOR_VER) $(WORK_LIB_DIR)/$@.$(MAIN_VER)
	ln -s $(WORK_LIB_DIR)/$@.$(MAIN_VER) $(WORK_LIB_DIR)/$@

calltrace.o: calltrace.cpp
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) -I../../../local/include -c -o $@ $?
	
util_socket.o:util_socket.c
	$(C_COMP) $(CFLAGS) -c $? -o $@	

b: errlog_imp
#OBJ1=errlog.o errlog_imp.o framework.o
#errlog_imp: $(OBJ1)
#	$(CPP_COMP) $(CPPFLAGS) -o $@ $(OBJ1) -L$(WORKDIR)/solib -lcfg -lutype -lDesMac -lpublog -L$(ORA_LIB)
errlog_imp: errlog_imp.o
	CC="$(CPP_COMP)" buildserver -s __svc__ -f "$? -L$(WORKDIR)/solib -ltuxadp -lrule -llogutype -lfilter -lCallESBApi -lcfg -lutype -lDesMac -lpublog -L$(ORA_LIB) -lpthread -ldl" -o $@
	cp $@ ~/run/bin/

NGX_BOSS_LIB=$(WORK_LIB_DIR) -lDBConn -lbossshm -llogutype -lcfg -lpublog  -lrule -lBusi  -lutype -lBossSys -lClsys -ldbug  -lBaseTree -lDesMac -lfilter -lCallESBApi -llogfunc -lrouter	
c: ngxadp.so
OBJ2=ngx.o adapter.o framework.o errlog.o
ngxadp.so: $(OBJ2)
	$(CPP_COMP) $(CPPFLAGS) -shared -o $@ $(OBJ2) -ldl -L$(ORA_LIB) -L$(XML_LIB) -L$(NGX_BOSS_LIB)
	cp $@ $(HOME)/run/solib
