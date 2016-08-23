include $(HOME)/run/framework/tools/env.mk

a:libfilter.so clean

OBJS=filter.o
libfilter.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS)
	mv $@ $(WORK_LIB_DIR)

clean:
	rm -f *.o *.lis
	
