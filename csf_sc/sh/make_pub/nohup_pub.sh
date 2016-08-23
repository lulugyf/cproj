cat /dev/null > $HOME/run/sh/make_pub/make_pub.txt

nohup sh $HOME/run/sh/make_pub/make_pub.sh 2>&1 >> $HOME/run/sh/make_pub/make_pub.txt &

