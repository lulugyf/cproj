#ifndef __PUB_H__
#define __PUB_H__
#define CENTER_GROUP_ID "10017"
#define SEQ_UR_UNI_VPMNNO 63


#include "framework.h"
#define LONG_CONN_TYPE 1
#define SHORT_CONN_TYPE 0
#define SEQ_UNI_KAUTNO       61      /*����ʺ�����*/
#define SEQ_UNI_AUTNO       62      /*vpmn�����ʺ�����*/
#define CUST_QRY_MAXCNT 50 /* ����֤����ѯ�ͻ������������ */


/*���к����Ͷ���*/
#define SEQ_CART_ID			1
#define SEQ_ORDER_ID		2
#define SEQ_ORDER_LINE_ID	3
#define SEQ_ORDER_CHG		4
#define SEQ_ORDER_LINE_CHG	5
#define SEQ_LOGIN_ACCEPT	6
#define SEQ_CUST_ID			7
#define SEQ_USER_ID			8
#define SEQ_CONTRACT_NO		9
#define SEQ_ORDER_LINE_SLA	10
#define SEQ_ORDER_LINE_BOOK	11
#define SEQ_ORDER_LINE_EXCP	12
#define SEQ_ORDER_LINE_EXEC	17
#define SEQ_UR_BILLMODE		28       /*13 ����ģʽ����*/
#define SEQ_UR_USERSTATE	29       /*14 �û�״̬����*/
#define SEQ_CT_CONTACTID	6       /*15 �ͻ���ϵ��Ϣ*/
#define SEQ_UR_ADDNBRID		27       /*16 ����ű�ʶ  */
#define SEQ_IA_CONTACTID	20		/*20 ͳһ�Ӵ��������� */
#define SEQ_CT_UNITID		1       /*18 ���ű���  */
#define SEQ_CT_GRPDEPTID	6       /*19 ���Ų��ű�ʶ  */
#define SEQ_CT_ADDRESSNO	6       /*20 ����ͨ��¼����  */
#define SEQ_AC_ACCTID		30       /*21 �����ʶ����*/
#define SEQ_CT_CUSTRELID	6       /*22 �ͻ���ϵ��ʶ  */
#define SEQ_CT_CONTACTID	6       /*23 ��ϵ��ʶ  */
#define SEQ_CT_SPCDAYNO	    6       /*24 �ؼ����ڱ�ʶ  */
#define SEQ_CT_BLACKCUST   60       /*Ƿ������  ����������*/

#define SEQ_PD_PRODPRCINSID	13	/*��Ʒ�ʷ�ʵ������*/
#define SEQ_PD_SVCINSID		18	/*����ʵ������*/
#define SEQ_UR_TEAMID  		14	/*��ʵ������*/
#define SEQ_UR_GROUPID	 	15 	/*Ⱥʵ������*/
#define SEQ_UR_MEMBERID	 	16	/*��Աʵ������*/
#define SEQ_UT_CUSTREL	 	6	/*�ͻ���ϵ����*/
#define SEQ_UR_AGREEMENT	6	/*��ͬ����*/
#define SEQ_OR_PREORDER	  	6	  /*Ԥ������ˮ-yangsong*/
#define SEQ_EVERY_PAGE	  	10	  /*ÿҳ��ʾ�ļ�¼��*/
#define SEQ_UR_IMPI	  		31	  /*ÿҳ��ʾ�ļ�¼��*/

#define SEQ_UR_TIETONGNO    65    /*��ͨADSL/LAN������Զ���������*/
#define SEQ_UR_IAGW1065702601	  		66	  /*ADC�ֻ�������������ֵ*/
#define SEQ_UR_IDCGRPOUTNO	  		67	  /*ͨ�õļ��Ž��������ֵ*/
#define SEQ_UR_GRPSX	  		68	  /*��Ѷͨ���������ֵ*/
#define SEQ_UR_GRPPRVVP	  		69	  /*vpmn���������ֵ*/
#define SEQ_UR_GRPVP	  		70	  /*ʡ��vpmn���������ֵ*/
#define SEQ_UR_BBOSSACCEPT	  		71	  /*ʡ��BBOSSһ��ͨ���������ֵ*/

#define BS_CHN_CODE "11"  		/* �Ӵ����������룺Ӫҵǰ̨ �ο�ia_chncode_dict 0��ͷ�ǰ��������ݲ����޸ģ����鲻��0��ͷ*/
#define INTERNET_CHN_CODE "02"  /* �Ӵ����������룺����Ӫҵ��*/
#define WAP_CHN_CODE "03"  		/* �Ӵ����������룺����Ӫҵ��*/
#define SMS_CHN_CODE "04"  		/* �Ӵ����������룺����Ӫҵ��*/
#define MACHINE_CHN_CODE "05"  	/* �Ӵ����������룺�����ն�*/
#define IVR_CHN_CODE "06"  		/* �Ӵ����������룺IVR*/
#define CALLER_CHN_CODE "17"  	/* �Ӵ����������룺10086�ͷ�*/
#define BBOSS_CHN_CODE "18"		/* �Ӵ����������룺bboss */
#define RADIUS_CHN_CODE "07" 	/* �Ӵ����������룺ʡ��RADIUSƽ̨ */

#define PD_MASTER_QUN "1007"  		/* Ⱥҵ��MASTER_SERV_ID*/
#define PD_MASTER_BRAND "1002"  	/* ���MASTER_SERV_ID*/

#define FINISH_FLAG         "N"        	/*��Ч״̬*/
#define EXP_DATE            "20991231" 	/*ʧЧʱ��*/
#define MAX_BILL_ORDER      99999999	/*Ĭ���˻��������ȼ�*/
#define FILE_PATH      "/run/file/ExtTxt/"	/*�ļ��Ĵ��·��*/
//A.B�༯�ű����ֶ�
#define GRP_A_B "|.���ſͻ�����.CUST_NAME|.���ſͻ���ַ.CUST_ADDRESS|.��ҵ����.TRADE_CODE_NAME|.�����ͨ�ŷ�֧��.COMMUNICATION_COSTS|.�в�ɲ���Ա��.MID_LEADER_NUM|.�쵼���ӳ�Ա��.LEADER_NUM|.��ҵԱ����.WORKER_AMOUNT|.�ƶ�3G�ֻ�����.MOBILE_NUM|.�ƶ�GSM�ֻ�����.MOBILE_GSM_NUM|.������������.WRITE_OFF_NUM|.��Ҫ�쵼������.LEAD_NAME|.��Ҫ�쵼�˵绰.LEAD_PHONE|.��Ҫ��ϵ������.CONTACT_NAME|.��Ҫ��ϵ�˵绰.CONTACT_PHONE|.С��ͨ�û���.SPIRIT_NUM|.����C���û���.TEL_NETC_NUM|.����3G�û���.TEL_3G_NUM|.��ͨG���û���.UNION_NETG_NUM|.��ͨ3G�û���.UNION_3G_NUM|.����ź�������.TEL_CONTENT|.����ͨ��������.UNION_CONTENT|.�ͻ�����Ϣ��������̶�.INFO_DEGREED|.�ͻ�ѡ�����Ӫ�̵���Ҫ����.CHOOSE_REASON|.�Ƿ�ǩԼ����.SIGN_TELECOM_FLAG|.�Ƿ�ǩԼ��ͨ.SIGN_UNICOM_FLAG|.��ǩԼ��������.SIGN_TELECOM_YEAR|.��ǩԼ��ͨ����.SIGN_UNICOM_YEAR|.�ͻ���������.MANAGER_NAME|.�ͻ�����绰.MANAGER_PHONE"
//C.D�༯�ű����ֶ�
#define GRP_C_D "|.���ſͻ�����.CUST_NAME|.���ſͻ���ַ.CUST_ADDRESS|.��ҵ����.TRADE_CODE_NAME|.��ҵԱ����.WORKER_AMOUNT|.�ƶ�3G�ֻ�����.MOBILE_NUM|.�ƶ�GSM�ֻ�����.MOBILE_GSM_NUM|.��Ҫ�쵼������.LEAD_NAME|.��Ҫ�쵼�˵绰.LEAD_PHONE|.��Ҫ��ϵ������.CONTACT_NAME|.��Ҫ��ϵ�˵绰.CONTACT_PHONE|.С��ͨ�û���.SPIRIT_NUM|.����C���û���.TEL_NETC_NUM|.����3G�û���.TEL_3G_NUM|.��ͨG���û���.UNION_NETG_NUM|.��ͨ3G�û���.UNION_3G_NUM|.�̶��绰������ͨ����.TELCOM_NUM"
#define BEGIN_CNTT_STATUS "N"     /* �Ӵ���ʼ״̬*/
#define FINISH_CNTT_STATUS "E"  /* �Ӵ����״̬*/
#endif

