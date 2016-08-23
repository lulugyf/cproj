urrPath=`pwd`
echo $cppcompile
echo $1
cppcompile -progtype=exec -pdepso=yes -towner=tran -dbstr=dbrun/dbrun11A@crmatest -esc=$HOME/run/sh/EscFuncFile.txt -path=$CurrPath $*
