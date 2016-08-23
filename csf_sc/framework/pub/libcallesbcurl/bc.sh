CURL_HOME=`pwd`/curl_home
CURL_SRC=`pwd`/curl_src/curl-7.31.0
echo ${CURL_SRC}
echo ${CURL_HOME}
cd ${CURL_SRC}


###### sun 主机 可以通过 gcc 或者 cc进行编译;
#configure 'CC=gcc -g -m64 ' --disable-ldap  --prefix=${CURL_HOME}  --enable-shared=no --without-ssl --without-zlib --without-libidn
#configure 'CC=cc -xarch=v9 ' --disable-ldap  --prefix=${CURL_HOME}  --enable-shared=no --without-ssl --without-zlib --without-libidn

###### HP 主机 必须通过 gcc进行编译,否则无法通过;
# HP unix
#./configure 'CC=gcc -mlp64 ' --disable-ldap  --prefix=${CURL_HOME}  --enable-shared=no --without-ssl --without-zlib
# linux

###### IBM 主机的编译方法:
#./configure 'AR=ar -X64' 'CC=xlc_r -q64 -brtl ' 'NM=/usr/bin/nm -B -X64' '--prefix=${CURL_HOME}' '--enable-shared=no' '--without-ssl'"

######## linux 主机:
#./configure  'CC=gcc -g -m64 ' '--disable-ldap' '--prefix=${CURL_HOME}' '--enable-shared=no' '--without-ssl' '--without-zlib' '--without-libidn'



#make
#make install

## 172.21.1.30 esb/esb
#CONFIGURE_OPTIONS = " 'CC=gcc -mlp64 ' '--disable-ldap' '--prefix=/crmpdng/appnghcai/work/lpc/toyx_curl/curl_home' '--enable-shared=no' '--without-ssl' '--without-zlib' 'LDFLAGS=-L/crmpdng/appnghcai/Eai/pyhome/lib/python2.5/config'"

## 172.21.1.69 apphcai/apphcai
#CONFIGURE_OPTIONS = " 'AR=ar -X64' 'CC=xlc_r -q64 -brtl ' 'NM=/usr/bin/nm -B -X64' '--prefix=/crmpdpp/hcai/work/lpc/curl/curl_home' '--enable-shared=no' '--without-ssl'" 

## 172.21.0.117 anghcai/anghcai
#CONFIGURE_OPTIONS = " 'CC=gcc -mlp64 ' '--disable-ldap' '--prefix=/crmpdng/appnghcai/work/lpc/toyx_curl/curl_home'  '--enable-shared=no' '--without-ssl' '--without-zlib' 'LDFLAGS=-L/crmpdng/appnghcai/Eai/pyhome/lib/python2.5/config'"   

## 172.21.1.73 172.21.1.69
#CONFIGURE_OPTIONS = " 'CC=cc -xarch=v9 ' '--disable-ldap' '--prefix=/crmpdpp/hcai/work/lpc/toyx_curl/curl_home' '--enable-shared=no' '--without-ssl' '--without-zlib' '--without-libidn'"
