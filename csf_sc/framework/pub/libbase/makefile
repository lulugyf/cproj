include $(HOME)/run/framework/tools/env.mk

a:libBaseTree.so

OBJS= pubInclude.o publicM.o  pubTongli.o  publicBaseFunc.o
libBaseTree.so:$(OBJS)
	    $(C_COMP) $(CFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS)  
		mv $@ $(WORK_LIB_DIR)

