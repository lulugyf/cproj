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

#ɽ����������� libCallESBWS.so
#Ŀǰɽ������ʹ�õ������, �����Ҫ��ſ�����ע��
#${_CC} -DCALL_ESB_DEBUG -I${HOME}/run/framework/pub/utype -I./curl_home/include  ${_SOLIB_FLAG} -o libCallESBWS.so   pCallESBWS.cpp  httpcustomheader.c ./curl_home/lib/libcurl.a   ${ICONV_LIBS}
#retcode=`echo $?`
#if [ ${retcode} -ne 0 ] ; then
#    echo "���� libCallESBWS.so ʧ�� "
#    exit 9999
#fi

#�Ĵ�����ʹ�õ� libCallESBApi.so 
#�Ĵ�����ͨ���ؽ��е���, ������Ĵ���ſ������ע��
${_CC} -DCALL_ESB_DEBUG -I${HOME}/run/framework/pub/utype -I./curl_home/include  ${_SOLIB_FLAG} -o libCallESBApi.so  pCallESBApi.cpp pCallESBWS.cpp httpcustomheader.c ./curl_home/lib/libcurl.a   ${ICONV_LIBS}
retcode=`echo $?`
if [ ${retcode} -ne 0 ] ; then
    echo "���� libCallESBApi.so ʧ�� "
    exit 9999
fi


#�ṩ��Ӫ��ֱ��ʹ�õ�api��so: libesbgsoap.so
#����ͳһ��������,�ṩ��Ӫ��ʹ�õĿ�,
#����ڱ����Ŀ��������Ͽ��Էſ������ע��
#${_CC}  -I./curl_home/include  ${_SOLIB_FLAG} -o libesbgsoap.so   httpcustomheader.c ./curl_home/lib/libcurl.a   ${ICONV_LIBS}
#retcode=`echo $?`
#if [ ${retcode} -ne 0 ] ; then
#    echo "���� libesbgsoap.so ʧ�� "
#    exit 9999
#fi

#һ���򵥵Ĵ�C:test.c���Գ���
#${_CC} -o dlopen_test dlopen_test.cpp -ldl -L$HOME/run/solib  -lutype
#cp -rf libCallESBWS.so $HOME/run/solib  
${_CC}  -DLIUPENGC_CURL_TEST  -I./curl_home/include -o test test.c httpcustomheader.c -L./curl_home/lib -lcurl ${ICONV_LIBS} ${_MY_EXTEND_LIBS}
retcode=`echo $?`
if [ ${retcode} -ne 0 ] ; then
    echo "���� test ʧ�� "
    exit 9999
fi



#�����ɵ�.so����testso����;
#һ���򵥵Ĵ�cpp�Ļ���.so�Ĳ��Գ���:testso.cpp���Գ���
#${_CC}  -DLIUPENGC_CURL_TEST  -I./curl_home/include -o testso testso.cpp  -L. -lesbgsoap ${ICONV_LIBS} ${_MY_EXTEND_LIBS}
#retcode=`echo $?`
#if [ ${retcode} -ne 0 ] ; then
#    echo "���� testso ʧ�� "
#    exit 9999
#fi
