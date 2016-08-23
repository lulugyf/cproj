include $(HOME)/run/framework/tools/env.mk

a: libcipher.so
OBJS=cipher.o
libcipher.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS)
	mv $@ $(WORK_LIB_DIR)
