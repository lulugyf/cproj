include $(HOME)/run/framework/tools/env.mk

a:libBusi.so  

OBJS=  publicBusi.o
libBusi.so:$(OBJS)  
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS)    -L$(TUX_LIB)
	mv $@ $(WORK_LIB_DIR)  
