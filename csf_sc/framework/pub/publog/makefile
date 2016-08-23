include $(HOME)/run/framework/tools/env.mk

a: libpublog.so
OBJS=log4c.o #pubLog.o 
libpublog.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS)
	mv $@ $(WORK_LIB_DIR)
