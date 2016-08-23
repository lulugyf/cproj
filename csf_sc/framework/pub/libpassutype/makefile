include $(HOME)/run/framework/tools/env.mk

a: userpassutype

######################################
userpassutype: libpassutype.so
OBJS1=libpassutype.o
libpassutype.so:$(OBJS1)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $? 
	rm -f $(HOME)/run/solib/libpassutype.so
	mv $@ $(HOME)/run/solib
	@echo "### $@ created ###\n"

.cpp.o:
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) -I$(SYS_INCL_CPP) -c $*.cpp
