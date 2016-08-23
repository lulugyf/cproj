include $(WORKDIR)/framework/tools/env.mk


LIBS_USE=-L$(XML_LIB) -L$(BOSS_LIB) -L$(ORA_LIB) -L$(SYS_LIBS) $(__DCI_LIB) -L$(WORKDIR)/solib $(DEPLIB)

CC=$(CPP_COMP) $(CPPFLAGS)

MYCOMPILE:$(DEP)
	$(BUILD_SERVER) $(SVS) -o $(SRV_NAME) -f "$?" -l "$(LIBS_USE)"
	tmshutdown -s $(SRV_NAME)
	mv $(SRV_NAME) $(BOSS_BIN)
	tmboot -s $(SRV_NAME)
