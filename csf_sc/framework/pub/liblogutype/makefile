include $(HOME)/run/framework/tools/env.mk

a:liblogutype.so

OBJS=liblogutype.o
liblogutype.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS)
	mv $@ $(WORK_LIB_DIR)
