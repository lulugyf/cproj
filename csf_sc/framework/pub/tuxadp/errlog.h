/*
 * errlog.h
 *
 *  Created on: 2013-6-19
 *      Author: guanyf
 */

#ifndef ERRLOG_H_
#define ERRLOG_H_

/*错误日志记录文件, 使用了全局变量, 线程不安全

配置在文件  $CRM_CFG 中, 如果 STORE_PATH 没有配置, 则完全不记录
[ERRLOG]
STORE_PATH=/path/to/logfile   存储日志文件的路径
STORE_SUCC_FLAG=0           是否记录成功调用， 1-是 0-否
DBLABEL=$label               入库进程使用的数据库连接标签
 */

void errlog_begin(const char *svc_name, const char *inputstr);

void errlog_end(long errid, long retcode, const char *outputstr);

// 产生一个随机的errid数字， 8位数字， 短时间内尽量不重复
int errlog_generrid();


int errlog_loadIntoDB(int *running, int interval);

/*
表结构（暂为月表）：
create table bs_csf_errlog_$yyyymm
(
	service_name varchar(64),
	op_time date,
	begin_time char(17),
	time_cost number(8),
	errid number(8),
	server_ip varchar(64),
	client_ip varchar(64),
	contact_id varchar(25),
	phone_no varchar(100),
	op_code varchar(8),
	login_no varchar(8),
	ret_code number(6),
	ret_msg varchar(128),
	detail_msg varchar(128),
	input varchar(4000),
	output varchar(4000)
);

insert into bs_csf_errlog_%s ("
			"service_name, op_time, begin_time, time_cost, errid,"
			"server_ip, client_ip, contact_id, phone_no, op_code,"
			"login_no, ret_code, ret_msg, detail_msg,"
			"input, output"
			")"
			 "values( :svc_name<char[65]>, to_date(:op_time<char[15]>, 'yyyymmddhh24miss') , :begin_time<char[18]>, :time_cost<int>, :errid<int>,"
			 ":server_ip<char[65]>, :client_ip<char[65]>, :contact_id<char[26]>, :phone_no<char[100]>, :op_code<char[9]>,"
			 ":login_no<char[9]>, :ret_code<int>, :ret_msg<char[129]>, :detail_msg<char[129]>,"
			 ":input<char[4001]>, :output<char[4001]>"
			 ")

 */

/**
 * @brief 避免sql语句在前台展示出来
 * @param serviceName 调用的服务名
 * @param retMsg  服务返回错误信息
 */
void checkDetailMsgWithSQL(const char *serviceName, char *retMsg);

#endif /* ERRLOG_H_ */
