
# 安徽应急系统双库函数切换脚本
# 在需要做切换的tuxedo实例下， 修改配置文件 run/cfg/crm.cfg 或者 $CRM_CFG 的文件， 增加
# [BASEENV]
# EMERGENCY_FILE=/absolute/path/to/a/file

# 配置指向的文件所在目录， 需当前用户可写入， 该文件存在则进入应急模式， 否则为普通模式

# 脚本保存在需要进行切换的tuxedo实例的 run/shell/目录中， 
# 运行方法（tuxedo主机上本地运行）： 
#   开启应急模式： ConvertEmergFunc.sh Y
#   关闭应急模式： ConvertEmergFunc.sh N

if [ -r "$CRM_CFG" ]; then
   cfgfile = "$CRM_CFG"
else
   if [ -r "$WORKDIR/cfg/crm.cfg" ]; then
      cfgfile = "$WORKDIR/cfg/crm.cfg"
   else
      echo "can not found cfgfile"
      exit
   fi
fi


tagfile = `grep EMERGENCY_FILE $cfgfile|awk '{FS="="}{print $2}'`


if [ "$1" = "Y" ]; then
  echo "" >$tagfile
else
  rm $tagfile
fi
