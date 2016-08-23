include $(HOME)/run/framework/tools/env.mk

a:libCallESBApi.so

OBJS=pCallESBApi.o pCallESBWS.o   esb_cli/libesbgsoap.a

libCallESBApi.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS)
	cp -rf $@ $(WORK_LIB_DIR)

esb_cli/libesbgsoap.a:
	cd esb_cli && sh b.sh




clean:
	rm -f *.o *.lis


t1: t1.o 
	$(CPP_COMP) -o $@  $(CPPFLAGS) $? -L$(BOSS_LIB) -L$(ORA_LIB) -L$(XML_LIB) -L$(TUX_LIB)
