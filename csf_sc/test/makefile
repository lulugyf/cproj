all: rtest

include $(HOME)/run/framework/tools/env.mk


OBJS_STATIC=rPubFunc.o

librPubFunc.so:$(OBJS_STATIC)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS_STATIC)
	mv $@ $(WORK_LIB_DIR)

LIBS= -L$(ORA_LIB) -L$(TUX_LIB) -L$(WORKDIR)/solib -llogutype -lcfg -lpublog -lrule -lBusi -lutype -lDesMac -lfilter -ltuxadp -lBaseTree -llogfunc
rtest: rtest.o
	$(CPP_COMP) $(CPPFLAGS) -o $@ $? $(LIBS)
	
GCC=gcc

pjson: pjson.o
 $(GCC) -o $@ $? -lcurl
