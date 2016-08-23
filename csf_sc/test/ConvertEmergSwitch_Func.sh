
# ����Ӧ��ϵͳ˫�⺯���л��ű�
# ����Ҫ���л���tuxedoʵ���£� �޸������ļ� run/cfg/crm.cfg ���� $CRM_CFG ���ļ��� ����
# [BASEENV]
# EMERGENCY_FILE=/absolute/path/to/a/file

# ����ָ����ļ�����Ŀ¼�� �赱ǰ�û���д�룬 ���ļ����������Ӧ��ģʽ�� ����Ϊ��ͨģʽ

# �ű���������Ҫ�����л���tuxedoʵ���� run/shell/Ŀ¼�У� 
# ���з�����tuxedo�����ϱ������У��� 
#   ����Ӧ��ģʽ�� ConvertEmergFunc.sh Y
#   �ر�Ӧ��ģʽ�� ConvertEmergFunc.sh N

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
