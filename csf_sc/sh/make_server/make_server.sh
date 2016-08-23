cat ./list_server |while read line
do
        curlpath=${HOME}/${line}
        echo ${curlpath}
        cd ${curlpath}
        ls_flags=" -t *.cpp"
        ls ${ls_flags}|while read cfile
        do
                folderpath=`echo ${line}|awk '{
                i=index($0,"server")
                if(i>0)
                {
                print "1"
                }
                else
                {
                print "0"
                }
                }'`
                filepath=`echo ${cfile}|awk '{print substr($0, 0, 1)}'`
                echo "${folderpath}"
                echo "${filepath}"
                
                if [ ${folderpath} = "0" ]
                then
                echo "here ccccc"
                        cpsmake.sh 0 $cfile
                else
                        if [ ${filepath} = "R" ]
                        then
                        echo "here R"
                                cpsmake.sh 1 $cfile
                        else
                        echo "here c or p"
                                cpsmake.sh 0 $cfile
                        fi
                fi
        done
done
