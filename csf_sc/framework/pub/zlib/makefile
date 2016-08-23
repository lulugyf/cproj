include $(HOME)/run/framework/tools/env.mk

INCLUDE=-I. \
	-I$(ZLIB_INCL)

a:libzlib.so clean


OBJ1= adler32.o compress.o crc32.o deflate.o  gzio.o infback.o \
	inffast.o inflate.o inftrees.o  trees.o uncompr.o zutil.o

libzlib.so:$(OBJ1)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJ1)
	mv $@ $(WORK_LIB_DIR)

