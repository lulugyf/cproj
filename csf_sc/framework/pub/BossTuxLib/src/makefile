include $(HOME)/run/framework/tools/env.mk

INCLUDE=-I. \
	-I$(ZLIB_INCL) -I$(DBUG_INCL) -I$(LIBSYS_INCL) -I$(BOSSLIB_INCL) \
	-I$(UTYPE_INCL) -I$(BOSSTUXLIB_INCL) \
	-I$(XML_INCL) -I$(TUX_INCL) \
	-I$(ORA_INCL1) -I$(ORA_INCL2) -I$(ORA_INCL3)


a:libBossTux.so

OBJ1=CLTux.o CLDomErrorHandler.o CLTuxParam.o CLBusiFuncMgr.o

libBossTux.so:$(OBJ1)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJ1)
	mv $@ $(WORK_LIB_DIR)

