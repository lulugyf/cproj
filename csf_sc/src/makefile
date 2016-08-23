all: libtestbp1.so libtestbp2.so


include $(WORKDIR)/framework/tools/env.mk


OBJS=cTest1.o cQDual.o cQUserInfoByPhoneNum.o pCustInfoByUrphno.o pDynSvc.o

libtestbp.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS) -L/crmtux1/run/solib/lcustviewBC
	echo "###############################################"
	mv $@ $(WORK_SO_DIR)
	echo "###############################################"

O1=cQDual.o cQTestUsr.o
libtestbp1.so: $(O1)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(O1)
#	upso.py $@
	mv $@ $(WORK_SO_DIR)

O2=pDynSvc.o cTest1.o
libtestbp2.so: $(O2)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(O2)
#	upso.py $@
	mv $@ $(WORK_SO_DIR)


WORK_LIB=$(WORK_LIB_DIR) -ltuxadp -llogutype -lpublog -lrouter -lDesMac -lrule -lBusi -lBaseTree  -lutype -lBossSys -lClsys -ldbug -lfilter -lm -lcfg 

LIBS=-L$(WORK_LIB) -L$(XML_LIB) -L$(TUX_LIB) -L$(ORA_LIB) -L$(SYS_LIBS)


 

RTest1: RTest1.o cQDual.o pDynSvc.o
	$(BUILD_SERVER) -s sQDual,sDynSvc  -o $@ -f "$^" -l "$(LIBS) "
	cp -rf $@ /tp/esb/csf/run/bin
	#tmshutdown -s $@;  mv $@ $(BOSS_BIN);  tmboot -s $@


RTest2: RTest2.o pCustInfoByUrphno.o cQUserInfoByPhoneNum.o 
	$(BUILD_SERVER) -s sCustInfoValid -o $@ -f "$^" -l "$(LIBS) "
	tmshutdown -s $@;  mv $@ $(BOSS_BIN);  tmboot -s $@


LIBS_CSF=-L$(WORK_LIB_DIR) -llogutype -lcfg -lpublog -lrule -lBusi  -lutype -lBossSys -llogfunc -lBaseTree -lDesMac -lfilter -ltuxadp -ldbug -lCallESBApi
LIBS_SVR=$(LIBS_CSF) -L$(TUX_LIB) -L$(ORA_LIB) -L$(XML_LIB) 
qTest1: qTest1.o
	$(CPP_COMP) $(CPPFLAGS) -o $@ $? $(LIBS_SVR) -L$(WORK_SO_DIR) -ltestbp1 -ltestbp2