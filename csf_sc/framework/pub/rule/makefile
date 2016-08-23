
a:librule.so

include $(HOME)/run/framework/tools/env.mk


OBJS=  rule.o rulecheckall.o
librule.so:$(OBJS)  
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS)
	mv $@ $(WORK_LIB_DIR)
	
LIBS= -L$(ORA_LIB) -L$(TUX_LIB) -L$(WORKDIR)/solib -llogutype -lcfg -lpublog -lrule -lBusi -lutype -lDesMac -lfilter -ltuxadp -lBaseTree -llogfunc
OBJTEST=ruleck.o rulecheckall.o
ruleck: $(OBJTEST)
	$(CPP_COMP) $(CPPFLAGS) -o $@ $(OBJTEST) $(LIBS)
