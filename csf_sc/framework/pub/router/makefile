include $(HOME)/run/framework/tools/env.mk

a:librouter.so clean

OBJS=router.o
librouter.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS) -L$(DCI_HOME)/dci/liba/ -ldci
	#mv $@ $(WORK_LIB_DIR)
	cp -rf $@ $(WORK_LIB_DIR)

clean:
	rm -f *.o *.lis
	
