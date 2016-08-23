LASTNUM=`grep -n "#endif" pubBCP.h |tail -1 |awk -F: '{print $1}'`
echo $LASTNUM

sed "${LASTNUM}d" pubBCP.h > pubBCP.tmp
