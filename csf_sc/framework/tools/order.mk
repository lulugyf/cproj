#!/bin/sh
.SUFFIXES:.pc .cpp .cc .c .o

ORA_USERID=dbrun/dbrun@crmb

SYS_INCL_C=/usr/include
#SYS_INCL_CPP=/usr/vacpp/include
#SYS_LIBS=/usr/lib
SYS_INCL_CPP=/usr/include/aCC_std/rw
#SYS_INCL_CPP=/usr/include/aCC
SYS_LIBS=/usr/lib/hpux64 -lstd_v2 -lCsup -lcl


ORA_HOME=$(ORACLE_HOME)
ORA_INCL1=$(ORA_HOME)/precomp/public
ORA_INCL2=$(ORA_HOME)/rdbms/public
ORA_INCL3=$(ORA_HOME)/rdbms/demo
ORA_LIB=$(ORA_HOME)/lib -lclntsh

TUX_HOME=$(TUXDIR)
TUX_INCL=$(TUX_HOME)/include
TUX_LIB=$(TUX_HOME)/lib -ltux -lbuft -lfml -lfml32 -lengine

XML_HOME=$(XERCESCROOT)
XML_INCL=$(XML_HOME)/include
XML_LIB=$(XML_HOME)/lib -lxerces-c

WORK_LIB_DIR=$(HOME)/run/solib
BOSS_BIN=$(HOME)/run/bin
BOSS_INCL=$(HOME)/run/public/include
WORK_SO_DIR=$(HOME)/run/solib
WORK_HOME=$(HOME)/run/framework
WORK_INCL=$(WORK_HOME)/include
ALL_INCL=$(HOME)/work/inc_all/
ORDER_LIB=$(WORK_LIB_DIR) -lstorder
WORK_LIB=$(WORK_LIB_DIR) -lorderBC -lLG_bus -lpPubFunction
BOSS_LIB=$(WORK_LIB_DIR) -lDBConn -lbossshm -llogutype -lcfg -lpublog  -lrule -lBusi  -lutype -lBossSys -lClsys -ldbug -llogfunc  -lBaseTree -lDesMac  -lfilter -ltuxadp -L$(DCI_HOME)/dci/lib  -ldci -lrouter
LIBDIR=$(WORK_LIB_DIR)
BINDIR=$(WORK_HOME)/tools


UTYPE_INCL=$(WORK_HOME)/pub/utype
RULE_INCL=$(WORK_HOME)/pub/rule
LIBLOGUTYPE_INCL=$(WORK_HOME)/pub/liblogutype
LIBLOGFUNC_INCL=$(WORK_HOME)/pub/liblogfunc
PUBLOG_INCL=$(WORK_HOME)/pub/publog
LIBLOGFUNC_INCL=$(WORK_HOME)/pub/liblogfunc
ROUTER_INCL=$(WORK_HOME)/pub/router
FILTER_INCL=$(WORK_HOME)/pub/filter
TUXADP_INCL=$(WORK_HOME)/pub/tuxadp
DBUG_INCL=$(WORK_HOME)/pub/libdbug
BOSSLIB_INCL=$(WORK_HOME)/pub/BossLib/include
LIBSYS_INCL=$(WORK_HOME)/pub/libsys
BOSSTUXLIB_INCL=$(WORK_HOME)/pub/BossTuxLib/include
LIBBORDER_INCL=$(WORK_HOME)/src/border/include


BG_BIN_DIR=$(HOME)/run/crontab/bin
BORDER_SO_LIB=$(HOME)/run/solib -lborder

ZLIB_INCL=$(WORK_HOME)/pub/zlib
ZDB_INCL=$(WORK_HOME)/src/zdb/libzdb
ZDBCLIENT_INCL=$(WORK_HOME)/src/zdb/libzdbclient
ZDBSERVER_INCL=$(WORK_HOME)/src/zdb/libzdbserver
ZDB_BIN=$(HOME)/run/zdb/bin

C_COMP=aCC
CFLAGS=+DD64 -g -Ae -D_REENTRANT -D_USEDCI -mt -w +z +Z -DPLATFORM_TYPE=PLATFORM_TYPE_HP -D_LVSETENABLE -DMACHINE_WORD=64 -D__BIGMSGQUEUE_ENABLED -D__HP_NO_STRING_OVERLOADS -D__USE_XOPEN_EXTENDED -D_XOPEN_SOURCE_EXTENDED -D_INCLUDE_POSIX4_SOURCE -D_HPUX_SOURCE -D_FEATURES_H -DPROVINCE_SX

CPP_COMP=aCC
CPPFLAGS=+DD64 -g -Ag++ -D_REENTRANT  -D_USEDCI  -mt -w +z +Z   -DPLATFORM_TYPE=PLATFORM_TYPE_HP -D_LVSETENABLE -DMACHINE_WORD=64 -D__BIGMSGQUEUE_ENABLED -D__HP_NO_STRING_OVERLOADS -D__USE_XOPEN_EXTENDED -D_XOPEN_SOURCE_EXTENDED -D_INCLUDE_POSIX4_SOURCE -D_HPUX_SOURCE -D_FEATURES_H -DPROVINCE_SX

DYNLIBFLAGS= -b

PROC_COMP=$(ORA_HOME)/bin/proc code=cpp
PROCFLAGS=include=. include=$(BOSS_INCL) include=$(WORK_INCL) include=$(SYS_INCL_C) include=$(TUX_INCL) \
	include=$(ORA_INCL1) include=$(ORA_INCL2) include=$(ORA_INCL3) include=$(BOSSLIB_INCL) \
	USERID=$(ORA_USERID) SQLCHECK=FULL DYNAMIC=ANSI parse=none

BUILD_SERVER=$(TUX_HOME)/bin/buildserver -v
BUILD_CLIENT=$(TUX_HOME)/bin/buildclient

AR=ar -rv
#AR=$(CPP_COMP) -xar -o

INCLUDE=-I. -I$(LIBLOGUTYPE_INCL)  -I$(TUXADP_INCL) -I$(ROUTER_INCL) -I$(PUBLOG_INCL) -I$(FILTER_INCL)\
        -I$(RULE_INCL) -I$(UTYPE_INCL)  -I$(DBUG_INCL) -I$(LIBLOGFUNC_INCL)\
        -I$(LIBSYS_INCL) -I$(BOSSLIB_INCL) -I$(BOSSTUXLIB_INCL) -I$(LIBBORDER_INCL) \
		-I$(ZLIB_INCL) -I$(DCI_HOME)/dci/include/\
		-I$(ZDB_INCL) -I$(ZDBCLIENT_INCL) -I$(ZDBSERVER_INCL) \
        -I$(WORK_INCL) -I$(BOSS_INCL) -I$(XML_INCL) -I$(TUX_INCL) \
        -I$(ORA_INCL1) -I$(ORA_INCL2) -I$(ORA_INCL3) -I$(ALL_INCL) -I$(LIBLOGFUNC_INCL)

.pc.cpp:
	$(PROC_COMP) $(PROCFLAGS) iname=$< oname=$(<:.pc=.cpp)
.pc.o:
	$(PROC_COMP) $(PROCFLAGS) iname=$< oname=$(<:.pc=.cpp)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) -I$(SYS_INCL_CPP)  -c $(<:.pc=.cpp)
.c.o:
	$(C_COMP) $(CFLAGS) $(INCLUDE) -I$(SYS_INCL_CPP) -I$(SYS_INCL_C) -c $*.c
.cpp.o:
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) -I$(SYS_INCL_CPP)  -c $*.cpp
clean:
	rm -f *.o *.lis

