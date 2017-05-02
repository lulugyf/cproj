CFLAGS= -I. -I../include/ -I./cprops/ -I$(ORACLE_HOME)/precomp/public -I$(ORACLE_HOME)/rdbms/public -I$(ORACLE_HOME)/rdbms/demo -I$(ORACLE_HOME)/plsql/public -I$(ORACLE_HOME)/network/public

CC=cc -g -q64 -qnolibansi -qproto -U__STR__ -D_PRINT_LOG_

LFLAGS= -L../lib -lcprops -L$(ORACLE_HOME)/lib -lclntsh -lpthread -L/sap/ServiceActivation/lua-5.1.4/src -llua  -lm

ORADIR=$(ORACLE_HOME)
ORAINCL = $(ORADIR)/precomp/public
PROCFLAGS =include=${ORAINCL} include=${ORADIR}/include

PRECOMP= $(ORACLE_HOME)/bin/proc

.SUFFIXES: .pc .c .o

OBJ01=cms_parse.o testdir.o db_func.o daemon.o sigtool.o util.o
OBJ02=cms_writeback.o testdir.o db_func.o daemon.o sigtool.o util.o

all:cms_parse cms_writeback clean

cms_parse:$(OBJ01)
	echo " Compiling the $@"
	$(CC) -o $@ $(OBJ01) $(LFLAGS) $(CFLAGS)
	cp -rf $@ ../bin
	cp $@ ../testbin

cms_writeback:$(OBJ02)
	echo " Compiling the $@"
	$(CC) -o $@ $(OBJ02) $(LFLAGS) $(CFLAGS)
	cp -rf $@ ../bin

.cp.c:
	echo " Compiling the $<"
	$(PRECOMP) $(PROCFLAGS) $<

.c.o:
	@echo " Compiling the $<"
	$(CC)  -c  $(CFLAGS) $(LFLAGS) $<

db_func.c:db_func.pc
	@echo " Compiling the $<"
	$(PRECOMP) db_func.pc $(PROCPLSFLAGS)

clean:
	rm -f *.o
	rm -f db_func.c
	rm -f *.lis
