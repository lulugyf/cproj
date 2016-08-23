xlc++_r -q64 -g -brtl -qnolibansi -U__STR__ -qcpluscmt -ma -D_THREAD_SAFE -DAIX -D_USEDCI -D__BIGMSGQUEUE_ENABLED -DPLATFORM_TYPE=PLATFORM_TYPE_AIX -DMACHINE_WORD=64 -lhmu  -I. -I$HOME/run/framework/pub/liblogutype  -I$HOME/run/framework/pub/tuxadp -I$HOME/run/framework/pub/router -I$HOME/run/framework/pub/publog -I$HOME/run/framework/pub/filter -I$HOME/run/framework/pub/rule -I$HOME/run/framework/pub/utype  -I$HOME/run/framework/pub/libdbug -I$HOME/run/framework/pub/liblogfunc -I$HOME/run/framework/pub/libsys -I$HOME/run/framework/pub/BossLib/include -I$HOME/run/framework/pub/BossTuxLib/include -I$HOME/run/framework/src/border/include  -I$HOME/run/framework/pub/zlib -I$HOME/run/imdb/dci/include/ -I$HOME/run/framework/src/zdb/libzdb -I$HOME/run/framework/src/zdb/libzdbclient -I$HOME/run/framework/src/zdb/libzdbserver  -I$HOME/run/framework/include -I$HOME/run/public/include -I$HOME/run/xerces/include -I/tuxedo10/tuxedo10gR3/include  -I/ora10g/app/product/10.2.0/precomp/public -I/ora10g/app/product/10.2.0/rdbms/public -I/ora10g/app/product/10.2.0/rdbms/demo -I$HOME/work/inc_all/ -I$HOME/run/framework/pub/liblogfunc -I/usr/vacpp/include  -c RRouteInfo.cpp -o RRouteInfo.o



buildserver -v -s sRouteInfo,sQSysDT   -o RRouteInfo -f "RRouteInfo.o" -l "-L/crmpdpp/csf/run/solib -L/crmpdpp/csf/run/solib -ltuxadp  -lfilter -lrouter -lrule  -lrule  -lBaseTree  -llogutype -lutype -lcfg -lpublog -lDesMac -lBusi  -L/crmpdpp/csf/run/imdb/dci/liba/ -ldci -L$ORACLE_HOME/lib -lclntsh  -L$TUXDIR/lib -ltux -lbuft -lfml -lfml32 -lengine"


cp -rf RRouteInfo /crmpdpp/csf/run/bin
