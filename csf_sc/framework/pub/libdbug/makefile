include $(HOME)/run/framework/tools/env.mk

INCLUDE=-I. \
	-I$(ZLIB_INCL) -I$(DBUG_INCL)

a:libdbug.so clean

OBJ1=CLCriticalSection.o CLDbug.o CLDbugLibInit.o CLGlobalErrors.o \
	CLMalloc.o CLNumber.o CLThread.o CLThreadCond.o CLProcess.o

libdbug.so:$(OBJ1)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJ1)
	mv $@ $(WORK_LIB_DIR)


