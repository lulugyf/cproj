include $(HOME)/run/framework/tools/env.mk

INCLUDE=-I. \
	-I$(ZLIB_INCL) -I$(DBUG_INCL) -I$(LIBSYS_INCL) -I$(BOSSLIB_INCL) \
	-I$(XML_INCL) \
	-I$(ORA_INCL1) -I$(ORA_INCL2) -I$(ORA_INCL3)


a:libBossSys.so clean

OBJ1=CLBase.o CLRecordSet.o CLCommand.o db.o CLDbDriver.o CLDriver.o CLError.o CLException.o CLFile.o CLLayer.o CLRule.o CLShmDriver.o CLRight.o CLDomain.o

libBossSys.so:$(OBJ1)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJ1)
	mv $@ $(WORK_LIB_DIR)


