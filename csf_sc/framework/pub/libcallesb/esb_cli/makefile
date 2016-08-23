.SUFFIXES: .pc .cpp .c .o
#CXX=gcc -g 
#CXXX=g++ -g
CINC= -I.
CLIB= -L./ -lesbgsoap
#AR=ar -rv

CXX=${_CC} 
AR=${_AR}
CXXX=${_CCC}
all: libesbgsoap.a
a: libesbgsoap.a 

OBJS=soapC.o soapClient.o httppost.o stdsoap2.o esb_cli.o
libesbgsoap.a:$(OBJS)
	$(AR) $@ $?
main1:main1.o
	$(CXXX)  -o $@  $?  $(CLIB)
	
main:main.o
	$(CXX)  -o $@  $?  $(CLIB) 
.cpp.o:
	echo "Compiling the $<"
	$(CXXX) -c $(CINC) $<
.c.o:
	echo "Compiling the $<"
	$(CXX) -c $(CINC) $<
clean:
	rm -f *.o core* *.a
### $< 第一个依赖文件的名称;
### $@ 目标的完成名称
### $? 所有的依赖文件
