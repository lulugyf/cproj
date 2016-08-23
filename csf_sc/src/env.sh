

PATH=/usr/bin:/etc:/usr/sbin:/usr/ucb:$HOMEDIR/bin:/usr/bin/X11:/sbin; export PATH

if [ -s "$MAIL" ]           # This is at Shell startup.  In normal
then echo "$MAILMSG"        # operation, the Shell checks
fi                          # periodically.

PS1='$LOGNAME:$PWD>'; export PS1
EDITOR=vi; export EDITOR;

HOMEDIR=/crmpdpp/csf/csf_sc; export HOMEDIR
#oracle
ORACLE_HOME=/ora10g/product/10.2.0; export ORACLE_HOME
NLS_LANG=American_America.zhs16gbk; export NLS_LANG
#export ORA_NLS33=$ORACLE_HOME/ocommon/nls/admin/data
export TNS_ADMIN=$HOMEDIR/run/tns

XERCESCROOT=$HOMEDIR/run/xerces ; export XERCESCROOT
LD_LIBRARY_PATH=$XERCESCROOT/lib:$ORACLE_HOME/lib:$/lib:/usr/lib:$ORACLE_HOME/rdbms/lib; export LD_LIBRARY_PATH
PATH=$HOMEDIR/work/test:$HOMEDIR/run/sh:$ORACLE_HOME/bin:/sbin:/bin:/usr/sbin:/usr/bin:/usr/ccs/bin:/usr/ucb:/etc:/usr/openwin/bin:/usr/dt/bin:/usr/sfw/bin:/usr/sfw/sbin:$HOMEDIR/run/framework/tools/:/usr/vac/bin:/usr/vacpp/bin:$HOMEDIR/run/bin:/usr/java6/bin:$PATH:$HOMEDIR/run/crontab/bin; export PATH


. /tuxedo10/tuxedo10gR3/tux.env
TUXCONFIG=$HOMEDIR/run/cfg/tuxconfig; export TUXCONFIG
BDMCONFIG=$HOMEDIR/run/cfg/bdmconfig; export BDMCONFIG

export DCI_HOME=$HOMEDIR/run/imdb
export HOME=$HOMEDIR

LANG=C; export LANG
WORKDIR=$HOMEDIR/run; export WORKDIR
L4C_CFG=$HOMEDIR/run/cfg/l4c.cfg; export L4C_CFG
#L4C_CFG=$HOMEDIR/run/cfg/crm.cfg; export L4C_CFG
CRM_CFG=$HOMEDIR/run/cfg/crm.cfg; export CRM_CFG

export COMMAGENT=$WORKDIR/cfg/commagent
export PROGRAM_ID=10.109.1.119
export LOG_DIR=$HOMEDIR/run/crontab/log
export CFGDIR=$HOMEDIR/run/crontab/cfg
export XML_CFG_FILE=$CFGDIR/cfg.xml
export RPTAPPCFG=$HOMEDIR/run/framework/src/rpt/cfg/wfapp.cfg
export RPTSHCFG=$HOMEDIR/run/framework/src/rpt/cfg/sh.cfg
export RPTDIR=$HOMEDIR/run/framework/src/rpt 
export LOG_FUNC_CFG=$HOMEDIR/run/cfg/logfunc.cfg
export PWDCFG=$WORKDIR/cfg/pwd.cfg
export PD_XML_CFG=$HOMEDIR/run/framework/src/prodmng/crontab/cfg/cfg.xml
export PD_LOGDIR=$HOMEDIR/run/crontab/log
export TMP_FILE_PATH=$HOMEDIR/run/framework/src/ordersvc/crontab/file
export LOGCFG=$HOMEDIR/run/framework/src/custsvc/crontab/cfg/SynCfg.cfg
export SYNCFG=$HOMEDIR/run/framework/src/custsvc/crontab/cfg/SynCfg.cfg

WSNADDR=//127.0.0.1:9901; export WSNADDR
DCI_HOMEDIR=$HOMEDIR/run/imdb; export DCI_HOMEDIR
DBSUFFIX="A1"; export DBSUFFIX
OTL_INFO="off"; export OTL_INFO
PATH=$PATH:$DCI_HOMEDIR/bin; export PATH
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$DCI_HOMEDIR/dci/lib:$HOMEDIR/run/solib; export LD_LIBRARY_PATH
BOSS_SYNLIB_DIR=$HOMEDIR/run/solib; export BOSS_SYNLIB_DIR
SHLIB_PATH=$DCI_HOMEDIR/dci/lib:$SHLIB_PATH; export SHLIB_PATH
CUSTVIEW_SYNDL_PATH_NAME=$HOMEDIR/run/solib/libsyncustview.so; export CUSTVIEW_SYNDL_PATH_NAME
BILLSVERVERCONFIG=$HOMEDIR/run/cfg/.paybillsvc.cfg; export BILLSVERVERCONFIG
BOSSCONFIG=$HOMEDIR/run/cfg/.bossconfig; export BOSSCONFIG
DISTCONFIG=$HOMEDIR/run/cfg/.distribution.cfg; export DISTCONFIG
PASSWORDCONFIG=$HOMEDIR/run/cfg/pwd.cfg; export PASSWORDCONFIG
#ulimit -n 65535

###################################################################
##lugz:C++ compile setting
###C++ compile setting
export XCC="g++ -m64  -g -fPIC -D_USEDCI  -DPLATFORM_TYPE=PLATFORM_TYPE_LINUX -D__BIGMSGQUEUE_ENABLED  -DMACHINE_WORD=64"
export CC="gcc -m64 -g -fPIC -D_THREAD_SAFE  -DPLATFORM_TYPE=PLATFORM_TYPE_LINUX -D_USEDCI -D__BIGMSGQUEUE_ENABLED  -DMACHINE_WORD=64"
export PLATFORM_TYPE=PLATFORM_TYPE_LINUX

export LIBPATH=$LIBPATH:$LD_LIBRARY_PATH

