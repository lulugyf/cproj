#TUXDIR=/bea
LIBS= -L$(TUXDIR)/lib -lwsc -lbuft -lwsc  -lnws -lnwi -lnws -lfml -lfml32 -lgp  -lnsl -lsocket
CC=gcc
CPP=g++
INCLUDES=-I$(TUXDIR)/include -I../include -I/sybase/OCS-12_0/include
SYBLIB=-L/sybase/OCS-12_0/lib -lsybdb
TUXLIB=-L/bea/lib -lwsc -lbuft -lwsc -lnws -lnwi -lnws -lfml -lfml32 -lgp -lnsl -lsocket
PRECOMP=/sybase/OCS-12_0/bin/cpre

O=../o

#all: clear_dir proxy empty_file smpp hwHlr vpmndel smapcmd smapnew
#all: smap smpserv smapcmd smpserv_pkt smap_sc smap_sc_client
#all: proxy socks5
all: proxy_sel

proxy_sel: proxy_sel.o
	$(CC) -o $@ $^ -lws2_32

proxy: proxy.o util_tcp.o daemon.o
	$(CC) -o $@ $^ -lpthread -lws2_32

socks5: socks5.o
	$(CPP) -o $@ $^ -lpthread -lsocket -lnsl

tux.o: tux.c
	$(CC) -c -o $@ $? -I$(TUXDIR)/include

MboxServ: MboxServ.o tux.o daemon.o util_tcp.o
	$(CC) -o $@ $^ $(LIBS)


clear_dir:$O/clear_dir.o 
	$(CC) -o $@ $^ 


proxy_www: proxy_www.o
	$(CC) -o $@ $^ -lxnet -L../../cutil/lib -lgyftool
	ftp_put.sh 10.105.14.100 wwwwww kd9Dk20Dl_2 /export/home/wwwwww/balancer $@

cu1: $O/cu1.o $O/util_tcp.o
	$(CC) -o $@ $^ -lxnet

ca: $O/ca.o $O/util_tcp.o $O/daemon.o
	$(CC) -o $@ $^ -lxnet
	ftp_put.sh 10.105.220.212 offon offon /offon/bin $@

tconnect: $O/tconnect.o $O/util_tcp.o
	$(CC) -o $@ $^ -lsocket -lnsl -lpthread

empty_file:$O/empty_file.o
	$(CC) -o $@ $^

hwHlr: $O/hwHlr.o $O/util_tcp.o
	$(CC) -o $@ $^ -lsocket -lnsl

vpmndel: $O/vpmndel.o $O/util_tcp.o
	$(CC) -o $@ $^ -lxnet
	ftp_put.sh 10.105.2.239 zl zl /home/zl $@

smapcmd: $O/smapcmd.o $O/util_tcp.o $O/scapi.o $O/util_logs.o
	$(CC) -o $@ $^ -lxnet
	ftp_put.sh 10.105.2.184 zl smapzl123 /smap/zl/test $@

smap: $O/smap.o $O/scapi.o $O/util_tcp.o $O/daemon.o $O/util_regexp.o $O/util_logs.o \
   $O/smap_crb.o $O/smap_mt.o $O/smap_pps.o $O/smap_ncall.o $O/smap_onenm.o \
   $O/smap_charge.o
	$(CC) -o $@ $^ -lxnet -lpthread
	ftp_put.sh 10.105.2.184 zl zl /smap/zl/guanyf $@

smap_sc: $O/smap_sc.o $O/scapi.o $O/util_tcp.o $O/daemon.o $O/util_regexp.o $O/util_logs.o
	$(CC) -o $@ $^ -lxnet -lpthread
	ftp_put.sh 10.105.2.184 zl zl /smap/zl/guanyf $@

smap_sc_client: $O/smap_sc_client.o $O/util_tcp.o
	$(CC) -o $@ $^ -lxnet

smpserv: $O/smpserv.o $O/scapi.o $O/util_tcp.o $O/daemon.o $O/util_regexp.o $O/util_logs.o \
	$O/unixmsg.o
	$(CC) -o $@ $^ -lxnet
	ftp_put.sh 10.105.2.184 zl zl /smap/zl/smpserv $@

file_provider: $O/file_provider.o $O/util_tcp.o
	$(CC) -o $@ $^ -lxnet
	ftp_put.sh 10.105.2.29 bossapp bossapp /home/bossapp/dm9001/applications/iccweb $@

smpserv_pkt: $O/smpserv_pkt.o $O/util_tcp.o $O/scapi.o $O/daemon.o $O/util_regexp.o \
	 $O/util_logs.o $O/unixmsg.o $O/getRegion.o $O/tuxclnt.o
	$(CC) -o $@ $^  $(TUXLIB)
	ftp_put.sh 10.105.2.184 zl zl /smap/zl/smpserv $@

custClient: custClient.o util_tcp.o
	$(CC) -o $@ $^ -lxnet

rcmd: $O/rcmd.o $O/util_tcp.o $O/daemon.o $O/rcmdlib.o
	$(CC) -o $@ $^ -lxnet

t: $O/t.o $O/util_tcp.o $O/daemon.o
	$(CC) -o $@ $^ -lxnet

hash.o : hash.c
	$(CC) -D__TEST__ -c $? -o $@

hash: hash.o mempool.o
	$(CC) -o $@ $^

pp: $O/pp.o
pp: $O/pp.o
	$(CC) -o $@ $^

smtp1: smtp1.o
	$(CC) -o $@ $^ -L../../cutil/lib -lgyftool -lxnet

$O/%.o:%.c
	$(CC) -c $(INCLUDES) -fPIC -o $@ $?

%.o: %.c
	$(CC) -c $?

%.o: %.cpp
	$(CPP) -c $?

