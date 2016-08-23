CurrPath=`pwd`
echo $cppcompile
echo $1 $2
cppcompile -progtype=$1  -pdepso=yes  -dbstr=dbrun/dbrun@crmnga -towner=dbrun -esc=/crmnga/run/sh/EscFuncFile.txt -path=$CurrPath $2
