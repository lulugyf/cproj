include $(HOME)/run/framework/tools/env.mk

a: libcfg.so
OBJS=getcfg.o
libcfg.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $?
	mv $@ $(WORK_LIB_DIR)

getdb: getdb.o getcfg.o
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE)  -o $(BINDIR)/$@ $? -L$(WORK_LIB_DIR) -lpublog -lDesMac

setmpwd: setmpwd.o getcfg.o
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE)  -o $(BINDIR)/$@ $? -L$(WORK_LIB_DIR) -lpublog -lDesMac

