##CPP�ļ��б�
FirstCppFile=""
CppFileList=""
ProgType=""
#######builder bc bp server liupengc #######

#### get "sh cppcompile.sh bc_bp_server.cpp lib str" ###
#### ��θ��� 1 ��, bc or bp or server name
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
#### ��θ��� 1 ��, bc or bp or server name
get_cps_libforexe()
{
        my_date=`date +%Y%m%d%H%M%S`
        lib_result_file=$FirstCppFile"_"${my_date}
        sh cppcompileforexe.sh $CppFileList > $lib_result_file 2>&1
        link_lib_str=`get_lib_str $lib_result_file`
        rm -rf $lib_result_file
        echo $link_lib_str
}


#### ���� ���� bc �� bp �ĺ���
#### ��θ���: 1
#### in_para : bc or bp ����
build_bc_bp_single()
{
        my_date=`date +%Y%m%d%H%M%S`
        bc_bp_full_name=$1   # ����� bc or bp ����: eg :  cQTimeAgeLimit.cpp
        makefile_name="makefile_"${bc_bp_full_name}_${my_date}
        bc_bp_name=`echo $bc_bp_full_name|cut -f 1 -d .`
        target_name="lib"${bc_bp_name}".so"

        #cppcompile_result=`sh cppcompile.sh $bc_bp_full_name`   #��ȡ�ű���ִ�н��
        #link_lib_str=`echo $cppcompile_result|awk '{i=index($0,":"); j=index($0,"Success"); print substr($0,i+1,j-i-1)}'` # ��ȡ bc ���� bp �������ļ�
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
        link_lib_str_len=${#link_lib_str} #��ȡ�ַ������ȵı���
        link_lib_str_all=""
        WORK_LIB_DIR=${HOME}/run/solib

        if [ $link_lib_str_len  -lt 3 ]  # �γ� ��׺ƴ����makefile�ļ���
        then
                link_lib_str_all=""
        else
                link_lib_str_all="-L${WORK_LIB_DIR} ${link_lib_str}"
        fi

		makefile_str=
		echo "===>   ${WORK_LIB_DIR}/lib${bc_bp_name}.so"
        if [ -f ${WORK_LIB_DIR}/lib${bc_bp_name}.so ]; then
        	makefile_str="include \$(HOME)/run/framework/tools/env.mk.new\nlib${bc_bp_name}.so:${bc_bp_name}.o\n\t\$(CPP_COMP) \$(CPPFLAGS) \$(INCLUDE) \$(DYNLIBFLAGS) -o \$@ ${bc_bp_name}.o -L\$(ORA_LIB)  -L\$(TUX_LIB) ${link_lib_str_all}\n\t mv ${WORK_LIB_DIR}/lib${bc_bp_name}.so ${WORK_LIB_DIR}/solib_old/lib${bc_bp_name}.so.${my_date};  mv \$@ ${WORK_LIB_DIR}"  # ע��˴�ֻ�ǽ� .so �ļ�ǿ�Ƹ��Ƶ� solib �ļ�����
        else
        	makefile_str="include \$(HOME)/run/framework/tools/env.mk.new\nlib${bc_bp_name}.so:${bc_bp_name}.o\n\t\$(CPP_COMP) \$(CPPFLAGS) \$(INCLUDE) \$(DYNLIBFLAGS) -o \$@ ${bc_bp_name}.o -L\$(ORA_LIB)  -L\$(TUX_LIB) ${link_lib_str_all}\n\t mv \$@ ${WORK_LIB_DIR}"  # ע��˴�ֻ�ǽ� .so �ļ�ǿ�Ƹ��Ƶ� solib �ļ�����
        fi
        echo $makefile_str > $makefile_name
        make -f $makefile_name $target_name
        rm -rf $makefile_name

        if [ "$returnCode" -eq "100" ]
        then
                echo "�����ļ���������"
        elif [ "$returnCode" -eq "101" ]
        then
                echo ""
                echo "�ļ����ݱ���������ڱ���̬��������ļ���Ҫ���룬��ʹ�á�depmk���������±��룡"
        else
                echo "�������򱨴��ˣ�"
        fi
}


#### ���� ����Ŀ¼�µ� bc �� bp �ĺ���
#### ��θ���: 0
build_bc_bp_all()
{
        ls_flags=" -t *.cpp"  # ls ָ���ѡ��, Ĭ���ǰ�����ĸ˳������; -t : �ļ����޸�ʱ������; -r : ����; Ĭ�����ȱ������޸ĵ�; �мǲ�Ҫ��� -l ѡ��; ��Ҫ��alias���� alias ls='ls -l'

        ls ${ls_flags} | while read file_name
        do
                CppFileList=$file_name
                FirstCppFile=$file_name
                build_bc_bp_single $file_name
        done

}

#### ���뵥�� server
build_server_single()
{
        my_date=`date +%Y%m%d%H%M%S`
        server_full_name=$1   # ����� server �� cpp����, ����������server: eg :  RPubGetSeq.cpp
        makefile_name="makefile_"${server_full_name}_${my_date}
        server_name=`echo $server_full_name|cut -f 1 -d .`
        #cppcompile_result=`sh cppcompile.sh ${server_full_name}`   #��ȡ�ű���ִ�н��

        #echo "$server_full_name  $makefile_name  $cppcompile_result "
        #link_lib_str=`echo ${cppcompile_result}|awk '{i=index($0,":"); j=index($0,"Success"); print substr($0,i+1,j-i-1)}'` # ��ȡ server �������Ŀ��ļ�
        link_lib_str=`get_cps_lib`
        link_lib_str_len=${#link_lib_str} #��ȡ�ַ������ȵı���
        link_lib_str_all=""
        WORK_LIB_DIR=${HOME}/run/solib

        if [ $link_lib_str_len  -lt 3 ]  # �γɺ�׺ƴ����makefile�ļ���
        then
                link_lib_str_all=""
        else
                link_lib_str_all="-L${WORK_LIB_DIR} ${link_lib_str}"
        fi
        echo "#########  $server_name"
        dep_content=`cat ${server_name}.dep`
        service_list=`grep void ${server_name}.cpp | tr -s "(" " " | awk '{if($5=="TPSVCINFO") {printf("-s %s ", $4)}}'`
        ####makefile_str="include \$(HOME)/run/framework/tools/env.mk.new\n${server_name}:${dep_content}\n\t\$(BUILD_SERVER) ${service_list} -o ${server_name} -f\"\$?\" -l \"-L\$(COMMON_LIB) -L\$(XML_LIB) -L\$(TUX_LIB) -L\$(SYS_LIBS) -L\$(ORA_LIB) ${link_lib_str_all}\"\n\ttmshutdown -s ${server_name}; mv \$@ \${BOSS_BIN};tmboot -s ${server_name}"  # ע��˴�ֻ�ǽ�server�ļ�ǿ�Ƹ��Ƶ� bin �ļ�����
        
        ####��ʱ����Ϊ���벻��������
        makefile_str="include \$(HOME)/run/framework/tools/env.mk.new\n${server_name}:${dep_content}\n\t\$(BUILD_SERVER) ${service_list} -o ${server_name} -f\"\$?\" -l \"-L\$(COMMON_LIB) -L\$(XML_LIB) -L\$(TUX_LIB) -L\$(SYS_LIBS) -L\$(ORA_LIB) ${link_lib_str_all}\"\n\tmv \$@ \${BOSS_BIN}"  

	####makefile_str="include \$(HOME)/run/framework/tools/env.mk.new\n${server_name}:${dep_content}\n\t\$(BUILD_SERVER) ${service_list} -o ${server_name} -f\"\$?\" -l \" ${link_lib_str_all} -L\$(COMMON_LIB) -L\$(XML_LIB) -L\$(TUX_LIB) -L\$(SYS_LIBS) -L\$(ORA_LIB) \"\n\tmv \$@ \${BOSS_BIN}"
        
        echo $makefile_str > $makefile_name
        make -f $makefile_name $server_name
        rm -rf $makefile_name
}

#### ���� ����Ŀ¼�µ� server �ĺ���
#### ��θ���: 0
build_server_all()
{
        ls_flags=" -t R*.cpp"  # ls ָ���ѡ��, Ĭ���ǰ�����ĸ˳������; -t : �ļ����޸�ʱ������; -r : ����; Ĭ�����ȱ������޸ĵ�; �мǲ�Ҫ��� -l ѡ��; ��Ҫ��alias���� alias ls='ls -l'

        ls ${ls_flags} | while read file_name
        do
                CppFileList=$file_name
                FirstCppFile=$file_name
                build_server_single $file_name
        done

}

#### �����ִ�г���
build_exec()
{
        my_date=`date +%Y%m%d%H%M%S`
        exec_name=$1   # ��ִ�г������ơ�
        makefile_name="makefile_"${exec_name}_${my_date}

        link_lib_str=`get_cps_libforexe`
#       echo "$link_lib_str"
        link_lib_str_len=${#link_lib_str} #��ȡ�ַ������ȵı���
        link_lib_str_all=""
        WORK_LIB_DIR=${HOME}/run/solib

        if [ $link_lib_str_len  -lt 3 ]  # �γɺ�׺ƴ����makefile�ļ���
        then
                link_lib_str_all=""
        else
                link_lib_str_all="-L${WORK_LIB_DIR} ${link_lib_str}"
        fi
        echo "#########"
        dep_content=`echo "$CppFileList"| sed "s/.cpp/.o/g"`
        makefile_str="include \$(HOME)/run/framework/tools/env.mk.new\n${exec_name}:${dep_content}\n\t\$(CPP_COMP) \$(CPPFLAGS) -o \$@ ${dep_content} -L\$(EXEC_COMMON_LIB) -L\$(XML_LIB) -L\$(ORA_LIB) -L\$(TUX_LIB) ${link_lib_str_all}"  # ע��˴�ֻ�ǽ�server�ļ�ǿ�Ƹ��Ƶ� bin �ļ�����
        echo $makefile_str > $makefile_name
        echo "${makefile_str}"
        make -f $makefile_name $exec_name
        rm -rf $makefile_name
}

############## main ##############
##################################
#�ű��� 4 ���÷�����:
# usage: xx.sh 0 cQTimeAgeLimit.cpp  ��ʾ���뵥��bc or bp;
# usage: xx.sh 0 all                 ��ʾ���뵱ǰĿ¼�����е�bc or bp
# usage: xx.sh 1 RRouteInfo.cpp      ��ʾ���뵥��server
# usage: xx.sh 1 all                 ��ʾ���뵱ǰĿ¼�����е�server
#ʹ�ýű���ʱ��,���Ƚ��뵽bc or bp ��Ŀ¼��ȥ;

usage()
{
        echo "�ű��� 5 ���÷�����:"
        echo "usage: xx.sh 0 cQTimeAgeLimit.cpp  ��ʾ���뵥��bc or bp"
        echo "usage: xx.sh 0 all                 ��ʾ���뵱ǰĿ¼�����е�bc or bp"
        echo "usage: xx.sh 1 RRouteInfo.cpp      ��ʾ���뵥��server"
        echo "usage: xx.sh 1 all                 ��ʾ���뵱ǰĿ¼�����е�server"
        echo "usage: xx.sh 2 ExecFileName file1 file2 ...      ���ڱ����ִ���ļ�"
}

if [ $# -lt 2 ]
then
        usage;
fi

if [ "$1" = "0" -o "$1" = "1" ] # ���� BC BP SERVER
then
        CppFileList=$2
        FirstCppFile=$2
        if [ "$#" != "2" ]; then
                usage;
        fi
        
        if [ "$1" = "0" ]       # ���� BC BP
        then
                ProgType="so"
                if [ "$2" = "all" ] #�������е�
                then
                        echo "build_bc_bp_all"
                        build_bc_bp_all

                else
                        echo "build_bc_bp_single"
                        build_bc_bp_single $2
                fi
        else    # ���� SERVER
                ProgType="service"
                if [ "$2" = "all" ] #�������е�
                then
                        echo "build_server_all"
                        build_server_all
                else
                        echo "build_server_single"
                        build_server_single $2
                fi
        fi
elif [ "$1" = "2" ]     #�����ִ�г���
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

