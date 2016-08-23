include $(HOME)/run/framework/tools/env.mk

a:libDBConn.so

OBJS=  publicDb.o
libDBConn.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS)
	mv $@ $(WORK_LIB_DIR)
