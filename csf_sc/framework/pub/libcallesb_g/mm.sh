while [ 1 ]
do
	#ps aux |  grep test| grep -v grep 
    ps -eo pid,vsz,args | grep pCallESBApi | grep -v grep
	sleep 1
done

