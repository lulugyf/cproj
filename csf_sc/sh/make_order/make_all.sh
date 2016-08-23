####make orderBC
cd $HOME/run/framework/src/public/bc/order
pwd
make clean
make liborderBC.so



cd $HOME/run/framework/src/border/libbordererr
pwd
make clean
make a
cd $HOME/run/framework/src/border/libborder
pwd
make clean
make a
cd $HOME/run/framework/src/border/libstorder
pwd
make clean
make a
cd $HOME/run/framework/src/border/libbgcfg
pwd
make clean
make a
cd $HOME/run/framework/src/border/libbodisp
pwd
make clean
make a
cd $HOME/run/framework/src/border/libbordercfg
pwd
make clean
make a
cd $HOME/run/framework/src/border/libborderoffon
pwd
make clean
make a
cd $HOME/run/framework/src/border/libborderrule
pwd
make clean
make a
cd $HOME/run/framework/src/border/libborderext
pwd
make clean
make a
cd $HOME/run/framework/src/border/libborderqry
pwd
make clean
make a
cd $HOME/run/framework/src/border/libborderfreebill
pwd
make clean
make a
cd $HOME/run/framework/src/border/libborderdeal
pwd
make clean
make a
cd $HOME/run/framework/src/border/libborderdisp
pwd
make clean
make a
cd $HOME/run/framework/src/border/crontab/boadmin
pwd
make clean
make a
cd $HOME/run/framework/src/border/crontab/bodispatch
pwd
make clean
make a
cd $HOME/run/framework/src/border/crontab/boworker
pwd
make clean
make a
cd $HOME/run/framework/src/border/libborderexchange
pwd
make clean
make a
cd $HOME/run/framework/src/border/libbordertransfer
pwd
make clean
make a
cd $HOME/run/framework/src/border/libborderappfunc
pwd
make clean
make a


####make data_syn
cd $HOME/run/framework/src/border/interface/ifOrder2Spms/cfileNew; make libcrm2spms.so
cd $HOME/run/framework/src/border/interface/ifOrder2Spms/cfileNew; make libdatamodel.so
cd $HOME/run/framework/src/border/interface/ifDataSyn/cfile; cpmk datasyn.cpp
