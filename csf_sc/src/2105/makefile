all:  lib2105pub.so lib2105.so


include $(WORKDIR)/framework/tools/env.mk

 
OBJS1=bc.o
lib2105pub.so: $(OBJS1)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS1)
	mv $@ $(WORK_SO_DIR)

OBJS2=p2105Cfm.o
lib2105.so: $(OBJS2)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJS2) -L$(WORK_SO_DIR)/ -l2105pub
	mv $@ $(WORK_SO_DIR)

