#!/bin/sh
.SUFFIXES:.pc .cpp .cc .c .o

ORA_USERID=dbquery/dbquery@crmnga

SYS_INCL_C=/usr/include
SYS_INCL_CPP=/usr/vacpp/include
SYS_LIBS=/usr/lib

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
#WORK_LIB=$(WORK_LIB_DIR) -lordersvcBP  -lcustsvcBP  -lProdBP  -lMarketBP -lcustmngBP -lbasementBP -lProdOrderCfm -lscoreBP -l3966Cfm -l1100Finish -lcrm2spms -ldatasyn -lpubShare -lpubInterBoss -lpubInterRes -lpubInterWxwl -lpubInterWbqd -lpubInterFunc -lcustomerBC -luserBC -lahlocalBC -laccountBC -lproductBC -lmarketBC -lbasementBC -lorderBC -linteractionBC -lLG_bus -lcustviewBP -lcustviewBC -lpubInterWxwl -lobossBP -lobossBC -lChkBusiRule

#-L$(DCI_HOME)/dci/lib -ldci 
BOSS_LIB=$(WORK_LIB_DIR) -lDBConn -lbossshm  -ltuxadp -lCallESBApi -lCallESBWS -lcurl -lrouter -llogutype -lcfg -lpublog  -lrule -lBusi  -lutype -lBossSys -lClsys -ldbug -llogfunc  -lBaseTree -lDesMac -lfilter
#BOSS_LIB=$(WORK_LIB_DIR) -lDBConn -lbossshm -llogutype -lcfg10 -lpublog  -lrule -lBusi -lutype10 -lBossSys -lClsys -ldbug -lBaseTree -lDesMac  -lfilter -ltuxadp10 -L$(DCI_HOME)/dci/lib -ldci -lrouter -lBossPubService
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


#C_COMP=xlc_r
#CFLAGS=-q64 -g -brtl -qnolibansi -U__STR__ -qcpluscmt -ma -D_THREAD_SAFE -DAIX -D_USEDCI -D__BIGMSGQUEUE_ENABLED -DPLATFORM_TYPE=PLATFORM_TYPE_AIX -DMACHINE_WORD=64 -lhmu 

#CPP_COMP=xlc++_r
#CPPFLAGS=-q64 -g -brtl -qnolibansi -U__STR__ -qcpluscmt -ma -D_THREAD_SAFE -DAIX -D_USEDCI -D__BIGMSGQUEUE_ENABLED -DPLATFORM_TYPE=PLATFORM_TYPE_AIX -DMACHINE_WORD=64 -lhmu 

#DYNLIBFLAGS= -G

C_COMP=gcc -m64
CFLAGS=-g -fPIC  -DPLATFORM_TYPE=PLATFORM_TYPE_LINUX -D__BIGMSGQUEUE_ENABLED -DMACHINE_WORD=64

CPP_COMP=g++ -m64
CPPFLAGS=-g -fPIC -D_THREAD_SAFE  -DPLATFORM_TYPE=PLATFORM_TYPE_LINUX -D__BIGMSGQUEUE_ENABLED  -DMACHINE_WORD=64

DYNLIBFLAGS=-shared

PROC_COMP=$(ORA_HOME)/bin/proc code=cpp
PROCFLAGS=include=. include=$(BOSS_INCL) include=$(WORK_INCL) include=$(SYS_INCL_C) include=$(TUX_INCL) \
	include=$(ORA_INCL1) include=$(ORA_INCL2) include=$(ORA_INCL3) include=$(BOSSLIB_INCL) \
	USERID=$(ORA_USERID) SQLCHECK=FULL DYNAMIC=ANSI parse=none

BUILD_SERVER=$(TUX_HOME)/bin/buildserver -v
BUILD_CLIENT=$(TUX_HOME)/bin/buildclient

AR=ar -X64 -rv
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
	$(C_COMP) $(CFLAGS) $(INCLUDE) -I$(SYS_INCL_C)  -I$(SYS_INCL_CPP) -c $*.c
.cpp.o:
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) -I$(SYS_INCL_CPP)  -c $*.cpp
clean:
	rm -f *.o *.lis

