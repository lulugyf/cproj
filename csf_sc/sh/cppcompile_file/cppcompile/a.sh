bc_bp_name="tt.cpp"

#获取脚本的执行结果
cppcompile_result=`sh cppcompile.sh $bc_bp_name`

# 提取 bc 或者 bp 的依赖文件
link_lib_str = `echo $cppcompile_result|awk '{i=index($0,":"); j=index($0,"Success"); print substr($0,i+1,j-i-1)}'`
link_lib_str_len = ${#link_lib_str}
link_lib_str_all = ""
WORK_LIB_DIR=${HOME}/run/solib

if [ $link_lib_str_len  -lt 3 ]
then
	link_lib_str_all=""
else
	link_lib_str_all="-L${WORK_LIB_DIR} ${link_lib_str}"
fi

makefile_str="include \$(HOME)/run/framework/tools/env.mk.new
lib$(bc_bp_name).so:$(bc_bp_name).o
	$(CPP_COMP) $(CPPFLAGS) $(INCLUDE) $(DYNLIBFLAGS) -o $@ $(bc_bp_name).o ${link_lib_str_all}"
echo $makefile_str > test_makefile

