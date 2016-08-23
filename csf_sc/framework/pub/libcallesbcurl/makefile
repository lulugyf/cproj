.SUFFIXES: .pc .cpp .c .o

CINC=${_SOLIB_FLAG} -DCALL_ESB_DEBUG -I${HOME}/run/framework/pub/utype -I./curl_home/include -I.
CLIB=-L./curl_home/lib -lcurl ${ICONV_LIBS} ${_MY_EXTEND_LIBS}

sx:libCallESBWS.so
sc:libCallESBApi.so
test:test.o
testcpp:testcpp.o
yx:libesbgsoap.so


libCallESBWS.so:pCallESBWS.o  httpcustomheader.o
	$(_CC)  $(CINC) -o $@ $? $(CLIB)

libCallESBApi.so:pCallESBApi.o  pCallESBWS.o httpcustomheader.o
	$(_CC)  $(CINC) -o $@ $? $(CLIB)
libesbgsoap.so:httpcustomheader.o
	$(_CC)  $(CINC) -o $@ $? $(CLIB)

test:httpcustomheader.o
	$(_CC)  $(CINC) -o $@ $? $(CLIB)

testso:testso.o 
	$(_CC) -o $@ $?  -L. -lesbgsoap

.c.o:
	echo "Compiling the $<"
	$(_CC) -c $(CINC) $<
.cpp.o:
	echo "Compiling the $<"
	$(_CC) -c $(CINC) $<
clean:
	rm -rf *.o *.so test
