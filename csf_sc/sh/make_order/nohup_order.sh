cat /dev/null > $HOME/run/sh/make_order/make_all.txt
cat /dev/null > $HOME/run/sh/make_order/make_serv.txt

nohup sh $HOME/run/sh/make_order/make_all.sh 2>&1 >> $HOME/run/sh/make_order/make_all.txt &
nohup sh $HOME/run/sh/make_order/make_serv.sh 2>&1 >> $HOME/run/sh/make_order/make_serv.txt &

