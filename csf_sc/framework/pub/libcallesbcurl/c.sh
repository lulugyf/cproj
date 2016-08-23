rm -rf *.so core* *.o dlopen_test curl_home

PLAT=`uname -s`

case $PLAT in
"SunOS")
    #export PLATFORM="solaris"
    #export _CC='gcc -m64'
    #export _AR='ar -rv'
    #export SUNLIBS='-lsocket -lnsl '
    #export _RANLIB='ranlib '
    export PLATFORM="solaris"
    export _CC='CC -features=extensions -xarch=v9'
    export _AR='ar -rv'
    export SUNLIBS='-lsocket -lnsl '
    export _RANLIB='ranlib '
    export _MY_EXTEND_LIBS=' -lsocket -lnsl -lrt '
    cp -rf ./curl_home_sun  curl_home
;;
"AIX")
    export PLATFORM=aix
    export _CC='xlC_r -g -q64 -brtl ' 
    export _AR='ar -X64 -rv'
    export _SOLIB_FLAG=' -G '
    export ICONV_LIBS=' -liconv '
    cp -rf ./curl_home_ibm  curl_home
    #export  __TUX__LIBS=' ${TUXDIR}/lib/wstpinit.o  -L${TUXDIR}/lib -lwsc -lbuft -lwsc  -lgpnet  -lfml -lfml32 -lengine  -lpthread '
    #export _RANLIB='ranlib -X32_64 '
;;
"Linux")
    export PLATFORM=linux
    export _CC='g++ -g -m64 -fpic ' 
    #ICONV_LIBS=' -liconv '
    export _AR='ar  -rv'
    export _SOLIB_FLAG=' -shared '
    #export  __TUX__LIBS=' -L${TUXDIR}/lib   -lwsc -lbuft -lwsc  -lgpnet  -lfml -lfml32 -lengine  -ldl -lpthread '
    #export _RANLIB='ranlib  '
    export _MY_EXTEND_LIBS=' -lrt '
    cp -rf ./curl_home_linux curl_home
;;
"HP-UX")
    export PLATFORM=hp
    export _CC='aCC -g +DD64 -Ag++  -DHP_UX ' 
    #export _CC='cc    -g +DD64 -Ae  '
    #export _CC='gcc -mlp64  -g '
    export  _AR='ar  -rv '
    export  _SOLIB_FLAG=' -b '
    cp -rf ./curl_home_hp curl_home
;;
esac


rm -rf *.so *.o test testso

#山西营销使用的库
#make sx
#四川所有部门使用的库
#make sc
#营销统一开发环境使用的库不推荐使用
make yx
#编译测试测试程序
make test
make testso



