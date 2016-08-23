include $(HOME)/run/framework/tools/env.mk


INCLUDE=-I. \
	-I$(ZLIB_INCL) -I$(DBUG_INCL) -I$(LIBSYS_INCL)


a:libClsys.so clean

OBJ1= CLSemaphore.o CLArray.o CLAse.o CLBit.o CLBitmap.o CLCrc32.o CLList.o \
	CLMd5.o CLQsort.o CLQuery.o CLRbtree.o CLSha1.o CLString.o \
	CLThreadPool.o CLThreadRwLock.o CLShm.o CLMsgQueue.o

libClsys.so:$(OBJ1)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJ1)
	mv $@ $(WORK_LIB_DIR)

