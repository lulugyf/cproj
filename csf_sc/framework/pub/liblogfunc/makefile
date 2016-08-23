include $(HOME)/run/framework/tools/env.mk

a:liblogfunc.so

OBJS=LogFunc.o tuxadpcall.o
liblogfunc.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS)
	mv $@ $(WORK_LIB_DIR)
clean:
	rm -f *.o *.lis
