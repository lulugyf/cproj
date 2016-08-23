include $(HOME)/run/framework/tools/env.mk

a:libCallESBApi.so

OBJS=pCallESBApi.o esb_cli/libesbgsoap.a
libCallESBApi.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS)
	cp -rf $@ $(WORK_LIB_DIR)

esb_cli/libesbgsoap.a:
	cd esb_cli && sh b.sh
clean:
	rm -f *.o *.lis
