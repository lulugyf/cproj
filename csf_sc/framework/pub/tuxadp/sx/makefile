include $(HOME)/run/framework/tools/env.mk

a:libtuxadp.so

OBJS=tuxadp.o calltrace.o util_socket.o errlog.o
libtuxadp.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS) -L$(WORK_LIB_DIR) -llogfunc
	mv $@ $(WORK_LIB_DIR)
