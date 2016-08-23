
cat /dev/null > $HOME/run/sh/make_public/make_public.txt

nohup sh $HOME/run/sh/make_public/make_public.sh 2>&1 >> $HOME/run/sh/make_public/make_public.txt &
