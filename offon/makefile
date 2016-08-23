CFLAGS= -I. -I$(ORACLE_HOME)/precomp/public -I$(ORACLE_HOME)/rdbms/public -I../gyf/cutil/include

CC=gcc -m64 -g
#CC=cc -xarch=v9

LFLAGS=-L$(ORACLE_HOME)/lib -lclntsh -lm  -lpthread -lsocket -lnsl
PROCPLSFLAGS=include=../gyf/cutil/include include=./

userid=offon/opr_offon292@offondb
PRECOMP= $(ORACLE_HOME)/bin/proc DYNAMIC=ANSI USERID=$(userid) sqlcheck=SEMANTICS LINE=TRUE define=_PROC_

CPROPS=-L../gyf/cutil/lib -lcprops64 -lgyftool64
GYFLIB=-L../gyf/cutil/lib -lgyftool64

.SUFFIXES: .pc .c .o

all: offon_manager offon_entry

des2pro: des2pro.o check.o des2.o
	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS)

#offon_manager: offon_manager.o testdir.o db_func.o daemon.o util.o des2.o check.o file_func.o util_str.o dul_util.o util_tcp.o

offon_manager: offon_manager.o testdir.o db_func.o util.o des2.o check.o file_func.o dul_util.o daemon.o util.o util_tcp.o
	$(CC) -o $@ $^ $(LFLAGS)

OBJ_entry=offon_entry1.o testdir.o db_func.o daemon.o sigtool.o util.o util_tcp.o util_str.o des2.o check.o
offon_entry:$(OBJ_entry)
	$(CC) -o $@ $(OBJ_entry) $(LFLAGS)

#OBJ11=offon_entry.o testdir.o db_func.o util.o des2.o check.o file_func.o dul_util.o
#offon_entry:$(OBJ11)
#	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS) $(GYFLIB)
#	cp $@ bin/

q_check: q_check.o db_func.o util.o des2.o check.o
	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS)
	cp $@ bin/

offon_fordb=offon_fordb.o testdir.o db_func.o util.o des2.o check.o file_func.o dul_util.o
offon_fordb:$(offon_fordb)
	$(CC) -o $@ $(offon_fordb) $(LFLAGS) $(CFLAGS) $(GYFLIB)
	cp $@ bin/

dul_syn_recv=dul_syn_recv.o db_func.o daemon.o util.o des2.o check.o dul_util.o file_func.o
dul_syn_recv:$(dul_syn_recv)
	$(CC) -o $@ $(dul_syn_recv) $(LFLAGS) $(CFLAGS) $(CPROPS) -lrt
	cp $@ bin/

#dul_syn_recv.c:dul_syn_recv.pc
#	$(PRECOMP) THREADS=YES $? $(PROCPLSFLAGS) 

offon_rongzai:$(OBJ12)
	$(CC) -o $@ $(OBJ12) $(LFLAGS) $(CFLAGS)
	mv offon_rongzai ../bin

offon_query:$(OBJ21)
	$(CC) -o $@ $(OBJ21) $(LFLAGS) $(CFLAGS)
	mv offon_query ../bin

offon_alcatel:$(OBJ31)
	$(CC) -o $@ $(OBJ31) $(LFLAGS) $(CFLAGS)
	mv offon_alcatel ../bin

offon_nokia:$(OBJ41)
	$(CC) -o $@ $(OBJ41) $(LFLAGS) $(CFLAGS)
	mv $@ ../bin

offon_hlr: offon_hlr.o util.o des2.o check.o db_func.o daemon.o testdir.o util_tcp.o
	$(CC) -o $@ $^ $(LFLAGS) $(GYFLIB)
	cp $@ bin/

offon_nokia_mml: offon_nokia_mml.o testdir.o util.o query_parse.o des.o des2.o check.o
	$(CC) -o $@ $^ $(GYFLIB) -lxnet

offon_ericsson: offon_ericsson.o testdir.o util.o des2.o check.o query_parse.o
	$(CC) -o $@ $^ $(GYFLIB) -lxnet

offon_ericssonph: offon_ericssonph.o testdir.o util.o des2.o check.o query_parse.o
	$(CC) -o $@ $^ $(GYFLIB) -lxnet

offon_siemens_cu:$(OBJ61)
	$(CC) -o $@ $? $(LFLAGS) $(CFLAGS)
#	mv $@ ../bin

offon_siemens_Q3:$(OBJ62)
	$(CC) -o $@ $? $(LFLAGS) $(CFLAGS)
	mv $@ ../bin

offon_siemens_Q3_SR11:$(OBJ63)
	$(CC) -o $@ $? $(LFLAGS) $(CFLAGS)
	mv $@ ../bin

offon_huawei:$(OBJ71)
	$(CC) -o $@ $? $(LFLAGS) $(CFLAGS)
	mv $@ ../bin

offon_huawei_3G: offon_huawei_3G.o testdir.o util.o des2.o check.o query_parse.o daemon.o db_func.o
	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS)

offon_zte:$(OBJ81)
	$(CC) -o $@ $? $(LFLAGS) $(CFLAGS)
	mv $@ ../bin

OBJzte=offon_zte_3G.o testdir.o db_func.o daemon.o sigtool.o util_str.o util.o des2.o check.o scapi.o util_tcp.o
offon_zte_3G: $(OBJzte)
	$(CC) -o $@ $(OBJzte) $(LFLAGS) $(CFLAGS)

fetch_cmd:$(OBJ91)
	$(CC) -o $@ $(OBJ91) $(LFLAGS) $(CFLAGS)
	mv fetch_cmd ../bin

offon_ora_put:$(OBJ92)
	$(CC) -o $@ $? $(LFLAGS) $(CFLAGS)
	mv $@ ../bin

offon_oracle_put:$(OBJ93)
	$(CC) -o $@ $? $(LFLAGS) $(CFLAGS)
	mv $@ ../bin

fetch_cmd_one: fetch_cmd_one.o db_func.o util.o des2.o check.o file_func.o dul_util.o
	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS) $(GYFLIB)
	cp $@ bin/

fetch_cmd_one111: fetch_cmd_one111.o db_func.o util.o des2.o check.o file_func.o dul_util.o
	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS) $(GYFLIB)

mopen_ericsson: mopen_ericsson.o db_func.o util.o des2.o check.o
	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS) $(GYFLIB)
	cp $@ ../bin

mopen_siemensQ3: mopen_siemensQ3.o db_func.o util.o des2.o check.o
	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS) $(GYFLIB)
	cp $@ ../bin

dul_shmtool: dul_shmtool.o db_func.o dul_util.o util.o des2.o check.o
	$(CC) -o $@ $^ $(LFLAGS) $(CFLAGS)
	cp $@ ../bin

CRBOBJ=crb.o util_str.o util_logs.o
crb: $(CRBOBJ)
	$(CC) -o $@ $(CRBOBJ) $(LFLAGS) $(CFLAGS)

VPMNOBJ=vpmn.o util_str.o util_logs.o
vpmn: $(VPMNOBJ)
	$(CC) -o $@ $(VPMNOBJ) $(LFLAGS) $(CFLAGS)

TOHISOBJ=tohis.o util_str.o util_logs.o
tohis: $(TOHISOBJ)
	$(CC) -o $@ $(TOHISOBJ) $(LFLAGS) $(CFLAGS)

FBATCH=fetch_cmd_batch.o daemon.o util_tcp.o db_func.o util.o des2.o check.o dul_util.o file_func.o
fetch_cmd_batch: $(FBATCH)
	$(CC) -o $@ $(FBATCH) $(LFLAGS) $(CFLAGS) $(GYFLIB)
	cp $@ bin/

XHZW=fetch_cmd_xhzw.o daemon.o   util.o  db_func.o dul_util.o des2.o check.o  file_func.o
fetch_cmd_xhzw: $(XHZW)
	$(CC) -o $@ $(XHZW) $(LFLAGS) $(CFLAGS) $(GYFLIB)
	cp $@ bin/

RBATCH=rcv_batch.o util_tcp.o util_str.o daemon.o boss_hlr_diff.o
rcv_batch: $(RBATCH)
	$(CC) -o $@ $(RBATCH) $(LFLAGS) $(CFLAGS)
	ps -ef|grep rcv_batch|grep -v grep|grep -v make|cut -c9-15|xargs kill
	sleep 1
	./rcv_batch -Fcrmoprdb.cfg -L9888

RBOSSHLRDIFF=boss_hlr_diff.o util_tcp.o util_str.o daemon.o
boss_hlr_diff: $(RBOSSHLRDIFF)
	$(CC) -o $@ $(RBOSSHLRDIFF) $(LFLAGS) $(CFLAGS)

file_shmtool: shmtest.o file_func.o util_str.o util_tcp.o
	$(CC) -o $@ $^ -lxnet
	cp $@ ../bin

des_11: des_11.o des.o
	$(CC) -o $@ $^

zmae: zmae.o des.o
	$(CC) -o $@ $^

%.c: %.pc
	$(PRECOMP) $(PROCPLSFLAGS) $?

%.o: %.c
	@echo " Compiling the $<"
	$(CC)  -c  $(CFLAGS) $<

db_func.c:db_func.pc
	$(PRECOMP) db_func.pc $(PROCPLSFLAGS) 

offon_entry.c:offon_entry.pc
	$(PRECOMP) offon_entry.pc $(PROCPLSFLAGS) 

offon_rongzai.c:offon_rongzai.pc
	$(PRECOMP) offon_rongzai.pc $(PROCPLSFLAGS) 

fetch_cmd.c:fetch_cmd.pc
	$(PRECOMP) fetch_cmd.pc $(PROCPLSFLAGS) 

offon_ora_put.c:offon_ora_put.pc
	$(PRECOMP) offon_ora_put.pc $(PROCPLSFLAGS) 

offon_oracle_put.c:offon_oracle_put.pc
	$(PRECOMP) offon_oracle_put.pc $(PROCPLSFLAGS) 

fetch_cmd_one.c:fetch_cmd_one.pc
	$(PRECOMP) fetch_cmd_one.pc $(PROCPLSFLAGS) 
	cp fetch_cmd_one ../bin/fetch_cmd_one_TEST
fetch_cmd_batch.c:fetch_cmd_batch.pc
	$(PRECOMP) fetch_cmd_batch.pc $(PROCPLSFLAGS) 

fetch_cmd_xhzw.c:fetch_cmd_xhzw.pc
	$(PRECOMP) fetch_cmd_xhzw.pc $(PROCPLSFLAGS)

#rcv_batch.c:rcv_batch.pc
#	$(PRECOMP) rcv_batch.pc $(PROCPLSFLAGS) 

clean:
	rm -f *.o
	rm -f db_func.c offon_entry.c offon_rongzai.c offon_ora_put.c offon_oracle_put.c fetch_cmd_one.c fetch_cmd.c 
	rm -f *.lis

move:
	mv offon_manager ../bin
	mv offon_entry ../bin
	mv offon_rongzai ../bin
	mv offon_alcatel ../bin
	mv offon_nokia ../bin
	mv offon_ericsson ../bin
	mv offon_siemens_cu ../bin
	mv offon_query ../bin
	mv fetch_cmd ../bin
	mv fetch_cmd_one ../bin
	mv offon_ora_put ../bin
