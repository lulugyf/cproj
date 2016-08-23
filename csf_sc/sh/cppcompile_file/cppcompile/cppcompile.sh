CurrPath=`pwd`
echo $cppcompile
echo $1
/crmcb/work/lgz/cppcompile/cppcompile -progtype=so  -pdepso=yes -dbstr=dbrun/dbrun@crma -towner=dbrun -esc=/crmcb/run/sh/EscFuncFile.txt -path=$CurrPath $1
