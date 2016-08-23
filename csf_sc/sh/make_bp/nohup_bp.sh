cat /dev/null > $HOME/run/sh/make_bp/make_bp1.txt
cat /dev/null > $HOME/run/sh/make_bp/make_bp2.txt

nohup sh $HOME/run/sh/make_bp/make_bp1.sh 2>&1 >> $HOME/run/sh/make_bp/make_bp1.txt &
nohup sh $HOME/run/sh/make_bp/make_bp2.sh 2>&1 >> $HOME/run/sh/make_bp/make_bp2.txt &

