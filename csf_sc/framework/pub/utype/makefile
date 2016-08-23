include $(HOME)/run/framework/tools/env.mk

a:libutype.so

OBJS=utype.o xs.o utype_json.o jsonc/libjsonc.a
libutype.so:$(OBJS)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS)
	mv $@ $(WORK_LIB_DIR)

jsonc/libjsonc.a:
	cd jsonc && make a

um:utypetst.o
	$(CPP_COMP) -o $(BINDIR)/$@ $? $(INCLUDE) $(CPPFLAGS) $(LFLAGS) -L$(BOSS_LIB)

t1: t1.o
	$(CPP_COMP) $(CPPFLAGS) -o $@ $? -L$(WORKDIR)/solib -lutype

t2: t2.o
	$(CPP_COMP) $(CPPFLAGS) -o $@ $? -L$(WORKDIR)/solib -lutype
	
convert: convert.o
	$(CPP_COMP) $(CPPFLAGS) -o $@ $? -L$(WORKDIR)/solib -lutype

jsontest: jsontest.o
	$(CPP_COMP) -o $@ $? -L./jsonc -ljsonc

clean1:
	rm -f *.o jsontest
