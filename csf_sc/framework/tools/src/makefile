include $(HOME)/run/framework/tools/env.mk

LIBS=-L$(SYS_LIBS) -L$(ORA_LIB)  -L$(XML_LIB)

all:s_public_InitShm s_public_DelShm s_public_GetShm s_public_GetPasswd s_public_GetMemAccept clxml abc #redo s_public_GetRedo cl32 cl32toyx cl32test
# Invoke tuxedo compiler

OBJ_PUBLIC=s_public.o
COMPILE= $(BUILD_CLIENT) -v -w -f "$(OBJ_PUBLIC)  -L$(LIBDIR) -lDesMac "

COMPILE1= $(BUILD_CLIENT) -v -w

######################################
s_public_InitShm: $(OBJ_PUBLIC) s_public_InitShm.o
	$(COMPILE)  -f s_public_InitShm.o -o $(BINDIR)/s_public_InitShm

s_public_DelShm: $(OBJ_PUBLIC) s_public_DelShm.o
	$(COMPILE)  -f s_public_DelShm.o -o $(BINDIR)/s_public_DelShm

s_public_GetShm: $(OBJ_PUBLIC) s_public_GetShm.o
	$(COMPILE)  -f s_public_GetShm.o -o $(BINDIR)/s_public_GetShm

s_public_GetPasswd: $(OBJ_PUBLIC) s_public_GetPasswd.o
	$(COMPILE)  -f s_public_GetPasswd.o -o $(BINDIR)/s_public_GetPasswd

s_public_GetMemAccept: $(OBJ_PUBLIC) s_public_GetMemAccept.o
	$(COMPILE)  -f s_public_GetMemAccept.o -o $(BINDIR)/s_public_GetMemAccept


s_public_GetRedo: $(OBJ_PUBLIC) s_public_GetRedo.o
	$(COMPILE)  -f s_public_GetRedo.o -o $(BINDIR)/s_public_GetRedo

des: desende.o
	$(CPP_COMP) -o $(BINDIR)/$@ $? $(INCLUDE) $(CFLAGS) $(LFLAGS) $(LIBS) -L$(LIBDIR) -lcfg -lpublog -lDesMac

clxml:  clxml.o
	$(COMPILE1) -f $? -o $(BINDIR)/$@

cl32:  cl32.o
	$(COMPILE) -f $? -o $(BINDIR)/$@

autoBC:autoBC.cpp
	$(CPP_COMP) -o $@ $? $(INCLUDE) $(CFLAGS) $(LFLAGS) $(LIBS)

abc=ansysql.o abc.o cfg.o
abc1: $(abc)
	$(CPP_COMP) -o $@ $(abc) $(INCLUDE) $(CFLAGS) $(LFLAGS) $(LIBS) -L$(HOME)/run/solib -lpublog

