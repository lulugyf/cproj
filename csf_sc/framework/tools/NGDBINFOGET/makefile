#!/bin/sh
.SUFFIXES:.pc .cpp .cc .c .o

SYS_INCL_C=/usr/include
SYS_INCL_CPP=/usr/vacpp/include
SYS_LIBS=/usr/lib

BOSS_BIN_DIR=$(HOME)/run/bin
LIB_INCL=$(HOME)/run/framework/tools/NGDBINFOGET

WORK_LIB=-L$(HOME)/run/framework/tools/NGDBINFOGET libencrypt.o

C_COMP=xlc_r
CFLAGS=-q64 -g -brtl -qnolibansi -U__STR__ -qcpluscmt -ma -D_THREAD_SAFE -DAIX -D_USEDCI -D__BIGMSGQUEUE_ENABLED -DPLATFORM_TYPE=PLATFORM_TYPE_AIX -DMACHINE_WORD=64 -lhmu 

CPP_COMP=xlc++_r
CPPFLAGS=-q64 -g -brtl -qnolibansi -U__STR__ -qcpluscmt -ma -D_THREAD_SAFE -DAIX -D_USEDCI -D__BIGMSGQUEUE_ENABLED -DPLATFORM_TYPE=PLATFORM_TYPE_AIX -DMACHINE_WORD=64 -lhmu 

DYNLIBFLAGS= -G

AR=ar -X64 -rv

INCLUDE=-I. -I$(SYS_INCL_C) -I$(LIB_INCL)

a:NGDBINFOGET clean

OBJ1=NGDBINFOGET.o
NGDBINFOGET:$(OBJ1)
	$(C_COMP) $(CFLAGS) $(INCLUDE) -o $@ $(OBJ1) -L$(SYS_LIBS) -L$(WORK_LIB)
	mv $@ $(BOSS_BIN_DIR)

all: libencrypt
OBJ=libencrypt.o
libencrypt:$(OBJ)
	$(C_COMP) $(CFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(OBJ)

.c.o:
	$(C_COMP) $(CFLAGS) $(INCLUDE) -I$(SYS_INCL_C) -c $*.c
.cpp.o:
	$(C_COMP) $(CFLAGS) $(INCLUDE) -I$(SYS_INCL_C) -c $*.cpp
clean:
	rm -f *.o *.lis

