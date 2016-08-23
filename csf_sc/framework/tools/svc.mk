include $(HOME)/run/framework/tools/env.mk


LIBS_NOORDER=-L$(WORK_LIB) -L$(WORK_LIB)  -L$(BOSS_LIB) -L$(XML_LIB) -L$(TUX_LIB) -L$(ORA_LIB)   -L$(SYS_LIBS)
LIBS_ORDER= -L$(BORDER_SO_LIB) -L$(ORDER_LIB) -L$(WORK_LIB)   -L$(BOSS_LIB) -L$(XML_LIB) -L$(TUX_LIB) -L$(ORA_LIB) -L$(SYS_LIBS)


NOORDER:$(DEP)
	$(BUILD_SERVER) $(SVS) -o $(SRV_NAME) -f "$?" -l "$(LIBS_NOORDER)"
	tmshutdown -s $(SRV_NAME)
	mv $(SRV_NAME) $(BOSS_BIN)
	tmboot -s $(SRV_NAME)

ORDER:$(DEP)
	$(BUILD_SERVER) $(SVS) -o $(SRV_NAME) -f "$?" -l "$(LIBS_ORDER)"
	tmshutdown -s $(SRV_NAME)
	mv $(SRV_NAME) $(BOSS_BIN)
	tmboot -s $(SRV_NAME)
