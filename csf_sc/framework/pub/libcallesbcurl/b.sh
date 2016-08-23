rm -rf *.so core* *.o dlopen_test curl_home

PLAT=`uname -s`

case $PLAT in
"SunOS")
    #export PLATFORM="solaris"
    #export _CC='gcc -m64'
    #export _AR='ar -rv'
    #export SUNLIBS='-lsocket -lnsl '
    #export _RANLIB='ranlib '
    PLATFORM="solaris"
    _CC='CC -features=extensions -xarch=v9'
    _AR='ar -rv'
    SUNLIBS='-lsocket -lnsl '
    _RANLIB='ranlib '
    _MY_EXTEND_LIBS=' -lsocket -lnsl -lrt '
    cp -rf ./curl_home_sun  curl_home
;;
"AIX")
    PLATFORM=aix
    _CC='xlC_r -g -q64 -brtl ' 
    _AR='ar -X64 -rv'
    _SOLIB_FLAG=' -G '
    ICONV_LIBS=' -liconv '
    cp -rf ./curl_home_ibm  curl_home
    #export  __TUX__LIBS=' ${TUXDIR}/lib/wstpinit.o  -L${TUXDIR}/lib -lwsc -lbuft -lwsc  -lgpnet  -lfml -lfml32 -lengine  -lpthread '
    #export _RANLIB='ranlib -X32_64 '
;;
"Linux")
    PLATFORM=linux
    _CC='g++ -g -m64 -fpic ' 
    #ICONV_LIBS=' -liconv '
    _AR='ar  -rv'
    _SOLIB_FLAG=' -shared '
    #export  __TUX__LIBS=' -L${TUXDIR}/lib   -lwsc -lbuft -lwsc  -lgpnet  -lfml -lfml32 -lengine  -ldl -lpthread '
    #export _RANLIB='ranlib  '
    _MY_EXTEND_LIBS=' -lrt '
    cp -rf ./curl_home_linux curl_home
;;
"HP-UX")
    PLATFORM=hp
    _CC='aCC -g +DD64 -Ag++  -DHP_UX ' 
    #export _CC='cc    -g +DD64 -Ae  '
    #export _CC='gcc -mlp64  -g '
    export  _AR='ar  -rv '
    export  _SOLIB_FLAG=' -b '
    cp -rf ./curl_home_hp curl_home
;;
esac


rm -rf *.so *.o
   
#${_CC} -DCALL_ESB_DEBUG -I${HOME}/run/framework/pub/utype -I./curl_home/include  ${_SOLIB_FLAG} -o libCallESBWS.so   pCallESBWS.cpp  httpcustomheader.c ./curl_home/lib/libcurl.a   ${ICONV_LIBS}
#${_CC} -DCALL_ESB_DEBUG -I${HOME}/run/framework/pub/utype -I./curl_home/include  ${_SOLIB_FLAG} -o libCallESBApi.so  pCallESBApi.cpp httpcustomheader.c ./curl_home/lib/libcurl.a   ${ICONV_LIBS}
#${_CC} -o dlopen_test dlopen_test.cpp -ldl -L$HOME/run/solib  -lutype
#cp -rf libCallESBWS.so $HOME/run/solib  
#${_CC}  -DLIUPENGC_CURL_TEST  -I./curl_home/include -o test test.c httpcustomheader.c -L./curl_home/lib -lcurl ${ICONV_LIBS} ${_MY_EXTEND_LIBS}

#山西环境编译的 libCallESBWS.so
#目前山西环境使用的这个库, 如果需要请放开如下注释
#${_CC} -DCALL_ESB_DEBUG -I${HOME}/run/framework/pub/utype -I./curl_home/include  ${_SOLIB_FLAG} -o libCallESBWS.so   pCallESBWS.cpp  httpcustomheader.c ./curl_home/lib/libcurl.a   ${ICONV_LIBS}
#retcode=`echo $?`
#if [ ${retcode} -ne 0 ] ; then
#    echo "编译 libCallESBWS.so 失败 "
#    exit 9999
#fi

#四川环境使用的 libCallESBApi.so 
#四川环境通过池进行调用, 如果在四川请放开下面的注释
${_CC} -DCALL_ESB_DEBUG -I${HOME}/run/framework/pub/utype -I./curl_home/include  ${_SOLIB_FLAG} -o libCallESBApi.so  pCallESBApi.cpp pCallESBWS.cpp httpcustomheader.c ./curl_home/lib/libcurl.a   ${ICONV_LIBS}
retcode=`echo $?`
if [ ${retcode} -ne 0 ] ; then
    echo "编译 libCallESBApi.so 失败 "
    exit 9999
fi


#提供给营销直接使用的api的so: libesbgsoap.so
#北京统一开发环境,提供给营销使用的库,
#如果在北京的开发环境上可以放开线面的注释
#${_CC}  -I./curl_home/include  ${_SOLIB_FLAG} -o libesbgsoap.so   httpcustomheader.c ./curl_home/lib/libcurl.a   ${ICONV_LIBS}
#retcode=`echo $?`
#if [ ${retcode} -ne 0 ] ; then
#    echo "编译 libesbgsoap.so 失败 "
#    exit 9999
#fi

#一个简单的纯C:test.c测试程序
#${_CC} -o dlopen_test dlopen_test.cpp -ldl -L$HOME/run/solib  -lutype
#cp -rf libCallESBWS.so $HOME/run/solib  
${_CC}  -DLIUPENGC_CURL_TEST  -I./curl_home/include -o test test.c httpcustomheader.c -L./curl_home/lib -lcurl ${ICONV_LIBS} ${_MY_EXTEND_LIBS}
retcode=`echo $?`
if [ ${retcode} -ne 0 ] ; then
    echo "编译 test 失败 "
    exit 9999
fi



#用生成的.so编译testso程序;
#一个简单的纯cpp的基于.so的测试程序:testso.cpp测试程序
#${_CC}  -DLIUPENGC_CURL_TEST  -I./curl_home/include -o testso testso.cpp  -L. -lesbgsoap ${ICONV_LIBS} ${_MY_EXTEND_LIBS}
#retcode=`echo $?`
#if [ ${retcode} -ne 0 ] ; then
#    echo "编译 testso 失败 "
#    exit 9999
#fi
