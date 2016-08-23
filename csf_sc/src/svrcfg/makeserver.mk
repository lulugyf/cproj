include $(WORKDIR)/framework/tools/env.mk


LIBS_NOORDER=-L$(WORK_LIB)  -L$(WORK_LIB) -L$(BOSS_LIB) -L$(XML_LIB) -L$(TUX_LIB) -L$(ORA_LIB)   
LIBS_ORDER= -L$(BORDER_SO_LIB) -L$(ORDER_LIB) -L$(WORK_LIB)   -L$(BOSS_LIB) -L$(XML_LIB) -L$(TUX_LIB) -L$(ORA_LIB)
LIBS_CSF=-L$(WORK_LIB_DIR)  -ltuxadp -llogutype -lcfg -lpublog -lrule -lBusi -lBossSys -llogfunc -lBaseTree -lDesMac -lfilter -ldbug -lCallESBApi -lutype
LIBS_SVR=$(LIBS_CSF) -L$(TUX_LIB) -L$(ORA_LIB) -L$(XML_LIB) 

NOORDER:$(OBJSVR)
	$(BUILD_SERVER) $(SVS) -o $(SRV_NAME) -f "$(DEP)" -l "$(LIBS_NOORDER)"
	#tmshutdown -s $(SRV_NAME)
	mv $(SRV_NAME) $(BOSS_BIN)
	#tmboot -s $(SRV_NAME)

SERVER: $(SRV_NAME).o
	CC="$(CPP_COMP)" $(BUILD_SERVER) $(SVS) -o $(SRV_NAME) -f "$(DEP)" -l "$(LIBS_SVR)"
	#tmshutdown -s $(SRV_NAME)
	mv $(SRV_NAME) $(BOSS_BIN)
	#tmboot -s $(SRV_NAME)