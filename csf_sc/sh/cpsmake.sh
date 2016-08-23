##CPP文件列表。
FirstCppFile=""
CppFileList=""
ProgType=""
#######builder bc bp server liupengc #######

#### get "sh cppcompile.sh bc_bp_server.cpp lib str" ###
#### 入参个数 1 个, bc or bp or server name
get_cps_lib()
{
        my_date=`date +%Y%m%d%H%M%S`
        lib_result_file=$FirstCppFile"_"${my_date}
        sh cppcompile.sh $ProgType $CppFileList > $lib_result_file 2>&1
        link_lib_str=`get_lib_str $lib_result_file`
        rm -rf $lib_result_file
        echo $link_lib_str
}

#### get "sh cppcompile.sh bc_bp_server.cpp lib str" ###
#### 入参个数 1 个, bc or bp or server name
get_cps_libforexe()
{
        my_date=`date +%Y%m%d%H%M%S`
        lib_result_file=$FirstCppFile"_"${my_date}
        sh cppcompileforexe.sh $CppFileList > $lib_result_file 2>&1
        link_lib_str=`get_lib_str $lib_result_file`
        rm -rf $lib_result_file
        echo $link_lib_str
}


#### 编译 单个 bc 和 bp 的函数
#### 入参个数: 1
#### in_para : bc or bp 名字
build_bc_bp_single()
{
        my_date=`date +%Y%m%d%H%M%S`
        bc_bp_full_name=$1   # 传入的 bc or bp 名字: eg :  cQTimeAgeLimit.cpp
        makefile_name="makefile_"${bc_bp_full_name}_${my_date}
        bc_bp_name=`echo $bc_bp_full_name|cut -f 1 -d .`
        target_name="lib"${bc_bp_name}".so"

        #cppcompile_result=`sh cppcompile.sh $bc_bp_full_name`   #获取脚本的执行结果
        #link_lib_str=`echo $cppcompile_result|awk '{i=index($0,":"); j=index($0,"Success"); print substr($0,i+1,j-i-1)}'` # 提取 bc 或者 bp 的依赖文件
        #link_lib_str=`get_cps_lib`

        my_date=`date +%Y%m%d%H%M%S`
        lib_result_file=$FirstCppFile"_"${my_date}
        sh cppcompile.sh $ProgType $CppFileList > $lib_result_file 2>&1
        link_lib_str=`get_lib_str $lib_result_file`
        returnCode=$?
        rm -rf $lib_result_file
#       echo $link_lib_str
#       makedep=`echo $link_lib_str|grep "ChangedDependSo:YES"|wc -l`
#       if [ "$makedep" -eq "0" ]
#       then
#               link_lib_str=`echo $link_lib_str|sed "s/ChangedDependSo:NO//g"`
#       else
#               link_lib_str=`echo $link_lib_str|sed "s/ChangedDependSo:YES//g"`
#       fi

        echo "ssssss"$returnCode
        link_lib_str_len=${#link_lib_str} #获取字符串长度的变量
        link_lib_str_all=""
        WORK_LIB_DIR=${HOME}/run/solib

        if [ $link_lib_str_len  -lt 3 ]  # 形成 后缀拼接在makefile文件中
        then
                link_lib_str_all=""
        else
                link_lib_str_all="-L${WORK_LIB_DIR} ${link_lib_str}"
        fi

		makefile_str=
		echo "===>   ${WORK_LIB_DIR}/lib${bc_bp_name}.so"
        if [ -f ${WORK_LIB_DIR}/lib${bc_bp_name}.so ]; then
        	makefile_str="include \$(HOME)/run/framework/tools/env.mk.new\nlib${bc_bp_name}.so:${bc_bp_name}.o\n\t\$(CPP_COMP) \$(CPPFLAGS) \$(INCLUDE) \$(DYNLIBFLAGS) -o \$@ ${bc_bp_name}.o -L\$(ORA_LIB)  -L\$(TUX_LIB) ${link_lib_str_all}\n\t mv ${WORK_LIB_DIR}/lib${bc_bp_name}.so ${WORK_LIB_DIR}/solib_old/lib${bc_bp_name}.so.${my_date};  mv \$@ ${WORK_LIB_DIR}"  # 注意此处只是将 .so 文件强制复制到 solib 文件夹中
        else
        	makefile_str="include \$(HOME)/run/framework/tools/env.mk.new\nlib${bc_bp_name}.so:${bc_bp_name}.o\n\t\$(CPP_COMP) \$(CPPFLAGS) \$(INCLUDE) \$(DYNLIBFLAGS) -o \$@ ${bc_bp_name}.o -L\$(ORA_LIB)  -L\$(TUX_LIB) ${link_lib_str_all}\n\t mv \$@ ${WORK_LIB_DIR}"  # 注意此处只是将 .so 文件强制复制到 solib 文件夹中
        fi
        echo $makefile_str > $makefile_name
        make -f $makefile_name $target_name
        rm -rf $makefile_name

        if [ "$returnCode" -eq "100" ]
        then
                echo "依赖文件无需变更。"
        elif [ "$returnCode" -eq "101" ]
        then
                echo ""
                echo "文件内容变更，依赖于本动态库的其他文件需要编译，请使用“depmk”命令重新编译！"
        else
                echo "解析程序报错了！"
        fi
}


#### 编译 整个目录下的 bc 和 bp 的函数
#### 入参个数: 0
build_bc_bp_all()
{
        ls_flags=" -t *.cpp"  # ls 指令的选项, 默认是按照字母顺序排序; -t : 文件的修改时间排序; -r : 逆序; 默认优先编译先修改的; 切记不要添加 -l 选项; 不要在alias设置 alias ls='ls -l'

        ls ${ls_flags} | while read file_name
        do
                CppFileList=$file_name
                FirstCppFile=$file_name
                build_bc_bp_single $file_name
        done

}

#### 编译单个 server
build_server_single()
{
        my_date=`date +%Y%m%d%H%M%S`
        server_full_name=$1   # 传入的 server 的 cpp名字, 里面包含多个server: eg :  RPubGetSeq.cpp
        makefile_name="makefile_"${server_full_name}_${my_date}
        server_name=`echo $server_full_name|cut -f 1 -d .`
        #cppcompile_result=`sh cppcompile.sh ${server_full_name}`   #获取脚本的执行结果

        #echo "$server_full_name  $makefile_name  $cppcompile_result "
        #link_lib_str=`echo ${cppcompile_result}|awk '{i=index($0,":"); j=index($0,"Success"); print substr($0,i+1,j-i-1)}'` # 提取 server 的依赖文库文件
        link_lib_str=`get_cps_lib`
        link_lib_str_len=${#link_lib_str} #获取字符串长度的变量
        link_lib_str_all=""
        WORK_LIB_DIR=${HOME}/run/solib

        if [ $link_lib_str_len  -lt 3 ]  # 形成后缀拼接在makefile文件中
        then
                link_lib_str_all=""
        else
                link_lib_str_all="-L${WORK_LIB_DIR} ${link_lib_str}"
        fi
        echo "#########  $server_name"
        dep_content=`cat ${server_name}.dep`
        service_list=`grep void ${server_name}.cpp | tr -s "(" " " | awk '{if($5=="TPSVCINFO") {printf("-s %s ", $4)}}'`
        ####makefile_str="include \$(HOME)/run/framework/tools/env.mk.new\n${server_name}:${dep_content}\n\t\$(BUILD_SERVER) ${service_list} -o ${server_name} -f\"\$?\" -l \"-L\$(COMMON_LIB) -L\$(XML_LIB) -L\$(TUX_LIB) -L\$(SYS_LIBS) -L\$(ORA_LIB) ${link_lib_str_all}\"\n\ttmshutdown -s ${server_name}; mv \$@ \${BOSS_BIN};tmboot -s ${server_name}"  # 注意此处只是将server文件强制复制到 bin 文件夹中
        
        ####临时调整为编译不启动进程
        makefile_str="include \$(HOME)/run/framework/tools/env.mk.new\n${server_name}:${dep_content}\n\t\$(BUILD_SERVER) ${service_list} -o ${server_name} -f\"\$?\" -l \"-L\$(COMMON_LIB) -L\$(XML_LIB) -L\$(TUX_LIB) -L\$(SYS_LIBS) -L\$(ORA_LIB) ${link_lib_str_all}\"\n\tmv \$@ \${BOSS_BIN}"  

	####makefile_str="include \$(HOME)/run/framework/tools/env.mk.new\n${server_name}:${dep_content}\n\t\$(BUILD_SERVER) ${service_list} -o ${server_name} -f\"\$?\" -l \" ${link_lib_str_all} -L\$(COMMON_LIB) -L\$(XML_LIB) -L\$(TUX_LIB) -L\$(SYS_LIBS) -L\$(ORA_LIB) \"\n\tmv \$@ \${BOSS_BIN}"
        
        echo $makefile_str > $makefile_name
        make -f $makefile_name $server_name
        rm -rf $makefile_name
}

#### 编译 整个目录下的 server 的函数
#### 入参个数: 0
build_server_all()
{
        ls_flags=" -t R*.cpp"  # ls 指令的选项, 默认是按照字母顺序排序; -t : 文件的修改时间排序; -r : 逆序; 默认优先编译先修改的; 切记不要添加 -l 选项; 不要在alias设置 alias ls='ls -l'

        ls ${ls_flags} | while read file_name
        do
                CppFileList=$file_name
                FirstCppFile=$file_name
                build_server_single $file_name
        done

}

#### 编译可执行程序
build_exec()
{
        my_date=`date +%Y%m%d%H%M%S`
        exec_name=$1   # 可执行程序名称。
        makefile_name="makefile_"${exec_name}_${my_date}

        link_lib_str=`get_cps_libforexe`
#       echo "$link_lib_str"
        link_lib_str_len=${#link_lib_str} #获取字符串长度的变量
        link_lib_str_all=""
        WORK_LIB_DIR=${HOME}/run/solib

        if [ $link_lib_str_len  -lt 3 ]  # 形成后缀拼接在makefile文件中
        then
                link_lib_str_all=""
        else
                link_lib_str_all="-L${WORK_LIB_DIR} ${link_lib_str}"
        fi
        echo "#########"
        dep_content=`echo "$CppFileList"| sed "s/.cpp/.o/g"`
        makefile_str="include \$(HOME)/run/framework/tools/env.mk.new\n${exec_name}:${dep_content}\n\t\$(CPP_COMP) \$(CPPFLAGS) -o \$@ ${dep_content} -L\$(EXEC_COMMON_LIB) -L\$(XML_LIB) -L\$(ORA_LIB) -L\$(TUX_LIB) ${link_lib_str_all}"  # 注意此处只是将server文件强制复制到 bin 文件夹中
        echo $makefile_str > $makefile_name
        echo "${makefile_str}"
        make -f $makefile_name $exec_name
        rm -rf $makefile_name
}

############## main ##############
##################################
#脚本的 4 种用法如下:
# usage: xx.sh 0 cQTimeAgeLimit.cpp  表示编译单个bc or bp;
# usage: xx.sh 0 all                 表示编译当前目录下所有的bc or bp
# usage: xx.sh 1 RRouteInfo.cpp      表示编译单个server
# usage: xx.sh 1 all                 表示编译当前目录下所有的server
#使用脚本的时候,请先进入到bc or bp 的目录中去;

usage()
{
        echo "脚本的 5 种用法如下:"
        echo "usage: xx.sh 0 cQTimeAgeLimit.cpp  表示编译单个bc or bp"
        echo "usage: xx.sh 0 all                 表示编译当前目录下所有的bc or bp"
        echo "usage: xx.sh 1 RRouteInfo.cpp      表示编译单个server"
        echo "usage: xx.sh 1 all                 表示编译当前目录下所有的server"
        echo "usage: xx.sh 2 ExecFileName file1 file2 ...      用于编译可执行文件"
}

if [ $# -lt 2 ]
then
        usage;
fi

if [ "$1" = "0" -o "$1" = "1" ] # 编译 BC BP SERVER
then
        CppFileList=$2
        FirstCppFile=$2
        if [ "$#" != "2" ]; then
                usage;
        fi
        
        if [ "$1" = "0" ]       # 编译 BC BP
        then
                ProgType="so"
                if [ "$2" = "all" ] #编译所有的
                then
                        echo "build_bc_bp_all"
                        build_bc_bp_all

                else
                        echo "build_bc_bp_single"
                        build_bc_bp_single $2
                fi
        else    # 编译 SERVER
                ProgType="service"
                if [ "$2" = "all" ] #编译所有的
                then
                        echo "build_server_all"
                        build_server_all
                else
                        echo "build_server_single"
                        build_server_single $2
                fi
        fi
elif [ "$1" = "2" ]     #编译可执行程序
then
        ProgType="exec"
        if [ $# -lt 3 ]
        then
                usage;
        else
                FirstCppFile=$3
                CppFileList=`echo "$*"| sed "s/^2//g"`
                CppFileList=`echo $CppFileList|awk '{i=index($0, $1);j=length($1);print substr($0, i+j)}'`
                echo "CppFileList=$CppFileList"
                build_exec $2
        fi
else
        usage;
fi

