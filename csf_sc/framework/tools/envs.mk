#!/bin/sh
.SUFFIXES:.pc .cpp .cc .c .o

ORA_USERID=dbcustopr/dbcustopr123@ahcrmatest

SYS_INCL_C=/usr/include
SYS_INCL_CPP=/usr/include
SYS_LIBS=/usr/lib/


ORA_HOME=$(ORACLE_HOME)
ORA_INCL1=$(ORA_HOME)/precomp/public
ORA_INCL2=$(ORA_HOME)/rdbms/public
ORA_INCL3=$(ORA_HOME)/rdbms/demo
ORA_LIB=$(ORA_HOME)/lib -lclntsh

TUX_HOME=$(TUXDIR)
TUX_INCL=$(TUX_HOME)/include
TUX_LIB=$(TUX_HOME)/lib -ltux -lbuft -lfml -lfml32 -lengine

XML_HOME=$(HOME)/xerces
XML_INCL=$(XML_HOME)/include
XML_LIB=$(XML_HOME)/lib -lxerces-c
WORK_LIB_DIR=$(HOME)/run/solib/
BOSS_BIN=$(HOME)/run/bin
BOSS_INCL=$(HOME)/run/public/include
WORK_SO_DIR=$(HOME)/run/solib
WORK_HOME=$(HOME)/run/framework
WORK_INCL=$(WORK_HOME)/include
ALL_INCL=$(HOME)/work/inc_all/
ORDER_LIB=$(WORK_LIB_DIR) 
WORK_LIB=$(WORK_LIB_DIR)    
BOSS_LIB=$(WORK_LIB_DIR)     -lDBConn    -llogutype   -lpublog  -lrule -lBusi  -lutype     
LIBDIR=$(WORK_LIB_DIR)
BINDIR=$(WORK_HOME)/tools


UTYPE_INCL=$(WORK_HOME)/pub/utype
RULE_INCL=$(WORK_HOME)/pub/rule
LIBLOGUTYPE_INCL=$(WORK_HOME)/pub/liblogutype
PUBLOG_INCL=$(WORK_HOME)/pub/publog
ROUTER_INCL=$(WORK_HOME)/pub/router
FILTER_INCL=$(WORK_HOME)/pub/filter
TUXADP_INCL=$(WORK_HOME)/pub/tuxadp
DBUG_INCL=$(WORK_HOME)/pub/libdbug
BOSSLIB_INCL=$(WORK_HOME)/pub/BossLib/include
LIBSYS_INCL=$(WORK_HOME)/pub/libsys
BOSSTUXLIB_INCL=$(WORK_HOME)/pub/BossTuxLib/include

#BORDERBP_INCL=$(WORK_HOME)/src/border/bp
#LIBORDER_BC_INCL=$(WORK_HOME)/src/border/bc
#LIBBORDER_INCL=$(WORK_HOME)/src/border/libborder
#BORDERERR_INCL=$(WORK_HOME)/src/border/libbordererr
#BORDERBASE_INCL=$(WORK_HOME)/src/border/libborderbase
LIBBORDER_INCL=$(WORK_HOME)/src/border/include

#LIBSTORDER_INCL=$(WORK_HOME)/src/border/libstorder
#LIBBGCFG_INCL=$(WORK_HOME)/src/border/libbgcfg
#LIBBODISP_INCL=$(WORK_HOME)/src/border/libbodisp
#LIBBODISPMGR_INCL=$(WORK_HOME)/src/border/libbodispmgr
BG_BIN_DIR=$(HOME)/run/crontab/bin
#BORDER_SO_LIB=$(HOME)/run/solib -lborder -lborderbase -lbordererr 
BORDER_SO_LIB=$(HOME)/run/solib -lborder

ZLIB_INCL=$(WORK_HOME)/pub/zlib
ZDB_INCL=$(WORK_HOME)/src/zdb/libzdb
ZDBCLIENT_INCL=$(WORK_HOME)/src/zdb/libzdbclient
ZDBSERVER_INCL=$(WORK_HOME)/src/zdb/libzdbserver
ZDB_BIN=$(HOME)/run/zdb/bin


C_COMP=/opt/SUNWspro/bin/cc -xcode=pic32
#CFLAGS=-m64 -mt -xc99 -g -DPLATFORM_TYPE=PLATFORM_TYPE_SOLARIS -D_PROCPATH="\"path/a.out\""
CFLAGS=-m64 -mt -g -D_USEDCI  -DPLATFORM_TYPE=PLATFORM_TYPE_SOLARIS -D_PROCPATH="\"path/a.out\""


CPP_COMP=/opt/SUNWspro/bin/CC -xcode=pic32
CPPFLAGS=-m64 -mt -D_USEDCI  -features=extensions -g -DPLATFORM_TYPE=PLATFORM_TYPE_SOLARIS -D_PROCPATH="\"path/a.out\""

DYNLIBFLAGS= -G 

PROC_COMP=$(ORA_HOME)/bin/proc code=cpp
PROCFLAGS=include=. include=$(BOSS_INCL) include=$(WORK_INCL) include=$(SYS_INCL_C) include=$(TUX_INCL) \
	include=$(ORA_INCL1) include=$(ORA_INCL2) include=$(ORA_INCL3) include=$(BOSSLIB_INCL) \
	USERID=$(ORA_USERID) SQLCHECK=FULL DYNAMIC=ANSI

BUILD_SERVER=$(TUX_HOME)/bin/buildserver -v
BUILD_CLIENT=$(TUX_HOME)/bin/buildclient

AR=ar -rv
#AR=$(CPP_COMP) -xar -o

INCLUDE=-I. -I$(LIBLOGUTYPE_INCL)  -I$(TUXADP_INCL) -I$(ROUTER_INCL) -I$(PUBLOG_INCL) -I$(FILTER_INCL)\
        -I$(RULE_INCL) -I$(UTYPE_INCL)  -I$(DBUG_INCL) \
        -I$(LIBSYS_INCL) -I$(BOSSLIB_INCL) -I$(BOSSTUXLIB_INCL) -I$(LIBBORDER_INCL) \
	-I$(ZLIB_INCL) -I$(DCI_HOME)/dci/include/\
	-I$(ZDB_INCL) -I$(ZDBCLIENT_INCL) -I$(ZDBSERVER_INCL) \
        -I$(WORK_INCL) -I$(BOSS_INCL) -I$(XML_INCL) -I$(TUX_INCL) \
        -I$(ORA_INCL1) -I$(ORA_INCL2) -I$(ORA_INCL3) -I$(ALL_INCL)

.pc.cpp:
	$(PROC_COMP) $(PROCFLAGS) iname=$< oname=$(<:.pc=.cpp)
.pc.o:
	$(PROC_COMP) $(PROCFLAGS) iname=$< oname=$(<:.pc=.cpp)
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE)   -c $(<:.pc=.cpp)
.c.o:
	$(C_COMP) $(CFLAGS) $(INCLUDE)   -c $*.c
.cpp.o:
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE)   -c $*.cpp
clean:
	rm -f *.o *.lis

