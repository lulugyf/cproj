API ʹ��˵����

Ŀǰ���𽫳���Ӧ��sun��������, �ܲ�������sun������������������!
�������� linux aix hp



���Ա��Ļ���:
1:����ESB�Ŀͻ���ϢУ��ӿ�:
1.1 webservice����
http://172.21.1.95:51900/esbWS/services/sCustInfoValid
1.1.1���Ա���:
<ROOT><PHONE_NO type="string">15799881753</PHONE_NO><TEST type="string">#####���Ĳ��ԣ�У���Ƿ���������֣�ESB��Ȼ͸�������Ǹı��˱��룬��Ҫ�ڷ������ݵ�ʱ���ַ���ת����UTF-8����#####</TEST></ROOT>
1.2 rest ����
http://192.168.0.11:51900/esbWS/rest/sCustInfoValid
1.2.1 ���Ա���
{"ROOT":{"HEADER":{"POOL_ID":"","DB_ID":"","ENV_ID":"","ROUTING":{"ROUTE_KEY":"","ROUTE_VALUE":""}},"BODY":{"PHONE_NO":"15799881753","TEST":"ESB��rest�����ʱ��,Ҳû�н���͸��,���뱨����Ҫ��UTF-8�ĸ�ʽ,���صı��Ĳ���Ҫ����UTF-8ת��,��Ҫ��WEB������к˶����Ĳ���"}}}

2:ֱ�ӵ���zhaojie�ṩ��wsdl:
http://172.21.0.122:21106/services/WsGetSaleAction?wsdl
��Ӧ�����е�url:
http://172.21.0.122:21106/services/WsGetSaleAction.WsGetSaleActionHttpEndpoint/
2.1 ������λ�ȡURL��ַ�ķ���
1):�����������:
http://172.21.0.122:21106/services/WsGetSaleAction?wsdl
2):�ҵ���һ��:
<wsdl:port name="WsGetSaleActionHttpSoap11Endpoint" binding="ns:WsGetSaleActionSoap11Binding"><soap:address location="http://172.21.0.122:21106/services/WsGetSaleAction.WsGetSaleActionHttpSoap11Endpoint/"/></wsdl:port>
location��ֵ����url�ĵ�ַ.
2.1.2 ���Ա���:
<?xml version="1.0" encoding="GBK" standalone="no" ?>
<ROOT>
	<COMMON_INFO>
		<PROVINCE_GROUP type="string">10011</PROVINCE_GROUP>
		<SESSION_ID type="string">23CGRBDMttwgBpsh6mSyTJqtggVc2pYLmGSVCLXF8ypG8L59jdGQ!-1625009959!1363248044628</SESSION_ID>
		<SER_NAME type="string"></SER_NAME >
		<ROUND_AUDIT type="string">Y</ROUND_AUDIT >
		<DEST_IP type="string">172.21.0.123</DEST_IP>
		<DEST_PORT type="string">11001</DEST_PORT>
		<SRC_PORT type="string">4567</SRC_PORT>
		<APP_NAME type="string">NGBOSS</APP_NAME>
		<APP_ID type="string">2000</APP_ID>
		<FROM_SYS type="string">BOSS</FROM_SYS>
	</COMMON_INFO>
	<REQUEST_INFO>
		<PHONE_NO type="string">13546799494</PHONE_NO>
		<ID_NO type="string">16310001001540</ID_NO>
		<BRAND_ID type="string">ys</BRAND_ID>
		<LOGIN_NO type="string">faaa48</LOGIN_NO>
		<REGION_CODE type="string">16</REGION_CODE>
		<CHANNEL_TYPE type="string">0</CHANNEL_TYPE>
		<GROUP_ID type="string">13765</GROUP_ID>
		<OP_CODE type="string">1147</OP_CODE>
		<BUSI_INFO type="string"></BUSI_INFO>
		<DISTRICT_CODE type="string">10145</DISTRICT_CODE>
		<FLAG type="string">4</FLAG>
		<CUST_FLAG type="string">0</CUST_FLAG>
		<RED_FLAG type="string">N</RED_FLAG>
		<BLACK_FLAG type="string">N</BLACK_FLAG>
		<ACT_CLASS type="string"></ACT_CLASS>
		<MARKOBJ_TYPE type="string">00</MARKOBJ_TYPE>
		<TMP_TEST type="string">#######���Ĳ���#######</TMP_TEST>
	</REQUEST_INFO>
</ROOT>


���ж�api��˵��:
@in: url webservice�����url��ַ,��λ�ȡ�������;
@in: conn_timeout ���ӳ�ʱʱ��;
@in: recv_timeout ���ܳ�ʱʱ��;
@in: inmsg        ���÷������α���
@in: need2utf     ��α����Ƿ���ҪתUTF-8����
@in: outmsg       ָ��ĵ�ַ,���ڱ�����񷵻ص���Ϣ,������ϢҲ��������;
@in: need2gbk     �����Ƿ�תΪ GBK����;

@out:  0��ʾ�ɹ�, �ɹ������� *outmsg �б���,ʹ�������free��,�����ڴ�й©;
     ��0��ʾʧ��, ʧ�ܱ����� *outmsg �б���,ʹ�������free��,�����ڴ�й©;

int call_esb_ws(char *url, int conn_timeout, int recv_timeout,
                      char *inmsg, int need2utf,char **outmsg, int need2gbk);
                      
                      
int call_esb_rest(char *url,int conn_timeout, int recv_timeout,
                      char *inmsg, int need2utf, char **outmsg, int need2gbk);

��ϸ�������뿴:

demo.cpp

demo.sh
#���÷��񼯳�ƽ̨������ webservice ���� �ͻ���ϢУ�����;
./demo 0 "http://172.21.1.95:51900/esbWS/services/sCustInfoValid" esba.txt
#���÷��񼯳�ƽ̨������ rest ���� �ͻ���ϢУ�����;
./demo 1 "http://172.21.1.95:51900/esbWS/rest/sCustInfoValid"    esbb.txt
#���� zhaojie �ṩ�� webservice ���� ;
./demo 0 "http://172.21.0.122:21106/services/WsGetSaleAction.WsGetSaleActionHttpEndpoint/" esbc.txt


usage: demo 0|1 url msg_filename
>>>>>: demo 0|1 ����: 0Ϊws����; 1Ϊrest����
>>>>>: demo url ����: urlΪws�������rest����ĵ�ַ
>>>>>: demo url ����: msg_filenameΪһ���ļ�����,��ŷ�����εı���



����ı��������:
Ŀǰ�����Ѿ��� Linux, AIX , HP �����ϲ���ͨ��,
��Ϊ�ܲ� Sun ����������, ����ֻ�ܱ���Ϊ32λ����,Ŀǰ�޷�����ͨ��, SUN��������,������ͨ����
����Ӧ����SUN����.


demo��ʵ������Ϊ:
mk.AIX  mk.CYGWIN_NT-6.1  mk.HP-UX  mk.Linux


����demo:
1): ���� esb_cli Ŀ¼�� ������;
2): ִ�� sh b.sh
3): sh demo.sh
ע�������κͳ��������Ƿ������������.





















