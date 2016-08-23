. ~/.profile


cd ~/run/log

ls -l|grep -v "ULOG"|grep -v "total"| awk ' { if($5!=0) print $NF } ' | while read file
do
cat /dev/null > $file
cat /dev/null > $file
cat /dev/null > $file
cat /dev/null > $file
cat /dev/null > $file   
done
