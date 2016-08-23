
cd $HOME/run/framework/pub/BossLib/src
pwd 
make clean 
make a

cd $HOME/run/framework/pub/BossTuxLib/src
pwd 
make clean 
make a

cd $HOME/run/framework/pub/filter
pwd 
make clean 
make a

cd $HOME/run/framework/pub/libdbug
pwd 
make clean 
make a

cd $HOME/run/framework/pub/libsys
pwd 
make clean 
make a

cd $HOME/run/framework/pub/zlib
pwd 
make clean 
make a

cd $HOME/run/framework/pub/router
pwd 
make clean 
make a

cd $HOME/run/framework/pub/utype 
pwd 
make clean 
make a

cd $HOME/run/framework/pub/tuxadp 
pwd 
make clean 
make a

cd $HOME/run/framework/pub/rule
pwd 
make clean 
make a

cd $HOME/run/framework/pub/publog
pwd 
make clean 
make a

cd $HOME/run/framework/pub/libshm
pwd 
make clean 
make a

cd $HOME/run/framework/pub/libpassutype
pwd 
make clean 
make a

cd $HOME/run/framework/pub/liblogutype
pwd 
make clean 
make a

cd $HOME/run/framework/pub/libdbconn
pwd 
make clean 
make a

cd $HOME/run/framework/pub/libcfg
pwd 
make clean 
make a

cd $HOME/run/framework/pub/libbusi
pwd 
make clean 
make a

cd $HOME/run/framework/pub/libbase
pwd 
make clean 
make a

cd $HOME/run/framework/pub/liblogfunc
pwd
make clean
make a


####make libdes
cd $HOME/run/framework/pub/libdes
pwd
make clean
make libDesMac.so
chmod 755 libDesMac.so
mv libDesMac.so $HOME/run/solib


####make libLG_bus.so
cd $HOME/run/framework/src/intermng/bp/bus/src
pwd
make clean
make libLG_bus.so


####make zdb
cd $HOME/run/framework/src/zdb/libzdbserver; make a 
cd $HOME/run/framework/src/zdb/libzdbclient; make a 
cd $HOME/run/framework/src/zdb/libzdb; make a 
cd $HOME/run/framework/src/zdb/zdblistener; make a 
cd $HOME/run/framework/src/zdb/exportora; make a 
cd $HOME/run/framework/src/zdb/client_test; make a


