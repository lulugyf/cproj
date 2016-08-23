include $(HOME)/run/framework/tools/env.mk

a: libbossshm.a
OBJ1= publicShm.o publicF.o publicP.o publicS.o publicT.o
libbossshm.a:$(OBJ1)
	#$(AR) libbossshm.a $(OBJ1)
	ar -X64 -rv libbossshm.a $(OBJ1)
	mv $@ $(WORK_LIB_DIR)
	

