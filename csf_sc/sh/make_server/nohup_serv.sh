
cat /dev/null > $HOME/run/sh/make_server/make_server.txt

nohup sh $HOME/run/sh/make_server/make_server.sh 2>&1 >> $HOME/run/sh/make_server/make_server.txt &
