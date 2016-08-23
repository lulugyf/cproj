

输出内容的权限过滤配置方法：

工号权限级别	用户授权	关键字段处理模式
1	1	完全展示
1	0	模糊化
0	x	模糊化


procedure_id:  6000 
popedom_code:  4600  object_id: 4600

bs_DataObjItem_dict.OBJECT_CLASS must be 2
bs_Popedom_dict.POPEDOM_TYPE must be '02'

insert into bs_procedure_dict values(6000, 1000, 'sQDual', '测试关键字段过滤')
insert into bs_DataObjItem_dict (POPEDOM_CODE, SECURITY_LEVEL, OBJECT_ID, PARENT_OBJECT_ID, OBJECT_CLASS, DB_OBJECT_TYPE, DB_OBJECT_OWNER, DB_OBJECT_NAME, DATA_DOMAIN, DATA_TYPE, DATA_LENGTH, DATA_PRECISION, OBJECT_DESC, ENCRYPT_LEVEL)
  values (4600, 1, 4600, -1, 2, 'COLUMN', 'DBCUSTADM', 'POPEDOM_TYPE', 'USER', 'CHAR', 0, 0, 'SDFSDF', 1);

insert into bs_FuncDataItem_rel(procedure_id, object_id, alias_name) values(6000, 4600, 'TODAY');
insert into bs_LoginPopedom_rel (LOGIN_NO, POPEDOM_CODE, SELECT_PRIVS, UPDATE_PRIVS, INSERT_PRIVS, DELETE_PRIVS, RELA_TYPE, BEGIN_DATE, END_DATE, GRANT_LOGIN, OP_TIME, AUTH_NUM, AUTH_REASON, GRANTABLE, FAVOUR_RATE)
  values ('kmkc00', 4600, 1, 1, 1, 1, '1', to_date('21-05-2008 09:58:57', 'dd-mm-yyyy hh24:mi:ss'), to_date('30-01-2099', 'dd-mm-yyyy'), 'kaaa50', to_date('21-05-2008 09:58:57', 'dd-mm-yyyy hh24:mi:ss'), null, '', '', 0.00);

## 两个测试， kmkc00 工号有权限， kmkc01 无权限，会被模糊化
clxml sQDual '{"ROOT":{"REQUEST_INFO":{"OPR_INFO":{"LOGIN_NO":"kmkc00"}, "PHONE_NO":"13835013681"}}}'

clxml sQDual '{"ROOT":{"REQUEST_INFO":{"OPR_INFO":{"LOGIN_NO":"kmkc01"}, "PHONE_NO":"13835013681"}}}'


### 测试结合用户验证方式的敏感信息过滤
export VALIDATE_PATH=REQUEST_INFO.OPR_INFO.VALIDATE_TYPE
clxml sQDual '{"ROOT":{"REQUEST_INFO":{"OPR_INFO":{"LOGIN_NO":"kmkc00", "VALIDATE_TYPE":0}}}}'












select distinct b.ALIAS_NAME, c.POPEDOM_CODE 
                  from bs_procedure_dict a, bs_FuncDataItem_rel b, bs_DataObjItem_dict c 
                  where a.PROCEDURE_ID=b.PROCEDURE_ID and b.OBJECT_ID=c.OBJECT_ID 
                  and c.OBJECT_CLASS=2 and a.PROCEDURE_NAME='sQDual'

bs_Popedom_dict.POPEDOM_TYPE

select a.POPEDOM_CODE from bs_LoginPopedom_rel a ,bs_Popedom_dict b  
where ((a.RELA_TYPE='0' and a.SELECT_PRIVS=1) or (a.RELA_TYPE='1' and a.SELECT_PRIVS=0))
                           and sysdate between a.BEGIN_DATE 
and a.END_DATE and b.POPEDOM_CODE=10007
 and b.POPEDOM_CODE=a.POPEDOM_CODE  and b.POPEDOM_TYPE='02'
             and b.USE_FLAG='Y'                 and a.LOGIN_NO='kmkc01'

select b.POPEDOM_CODE,b.SELECT_PRIVS from bs_LoginRole_rel a ,bs_RolePdom_rel b, bs_Popedom_dict c ,bs_ROLE_dict d
where a.ROLE_CODE=b.ROLE_CODE
and a.ROLE_CODE=d.ROLE_CODE and  d.USE_FLAG='Y'
and sysdate between a.BEGIN_DATE   and a.END_DATE and b.POPEDOM_CODE=10007
  and b.POPEDOM_CODE=c.POPEDOM_CODE 
 and c.POPEDOM_TYPE='02'            and a.login_no='kmkc01'
 
 
select a.POPEDOM_CODE from bs_LoginPopedom_rel a ,bs_Popedom_dict b
                         where ((a.RELA_TYPE='0' and a.SELECT_PRIVS=0) or (a.RELA_TYPE='1' and a.SELECT_PRIVS=1)) 
 and sysdate between a.BEGIN_DATE 
 and a.END_DATE and b.POPEDOM_CODE=10007
  and b.POPEDOM_CODE=a.POPEDOM_CODE
 and b.POPEDOM_TYPE='02'  and b.USE_FLAG='Y'  and a.LOGIN_NO='kmkc01'
 
 
 
 

select * from bs_procedure_dict where procedure_name='sQDual'
select * from bs_FuncDataItem_rel for update
select * from bs_DataObjItem_dict where object_id=4600 for update

select * from bs_LoginPopedom_rel where login_no='kmkc00'
select * from bs_Popedom_dict where popedom_type='02'

procedure_id:  6000 
popedom_code:  4600  object_id: 4600

insert into bs_procedure_dict values(6000, 1000, 'sQDual', '测试关键字段过滤')
insert into bs_DataObjItem_dict (POPEDOM_CODE, SECURITY_LEVEL, OBJECT_ID, PARENT_OBJECT_ID, OBJECT_CLASS, DB_OBJECT_TYPE, DB_OBJECT_OWNER, DB_OBJECT_NAME, DATA_DOMAIN, DATA_TYPE, DATA_LENGTH, DATA_PRECISION, OBJECT_DESC, ENCRYPT_LEVEL)
values (4600, 1, 4600, -1, 2, 'COLUMN', 'DBCUSTADM', 'POPEDOM_TYPE', 'USER', 'CHAR', 0, 0, 'SDFSDF', 1);

insert into bs_FuncDataItem_rel(procedure_id, object_id, alias_name) values(6000, 4600, 'TODAY');
insert into bs_LoginPopedom_rel (LOGIN_NO, POPEDOM_CODE, SELECT_PRIVS, UPDATE_PRIVS, INSERT_PRIVS, DELETE_PRIVS, RELA_TYPE, BEGIN_DATE, END_DATE, GRANT_LOGIN, OP_TIME, AUTH_NUM, AUTH_REASON, GRANTABLE, FAVOUR_RATE)
values ('kmkc00', 4600, 1, 1, 1, 1, '1', to_date('21-05-2008 09:58:57', 'dd-mm-yyyy hh24:mi:ss'), to_date('30-01-2099', 'dd-mm-yyyy'), 'kaaa50', to_date('21-05-2008 09:58:57', 'dd-mm-yyyy hh24:mi:ss'), null, '', '', 0.00);

select * from bs_LoginPopedom_rel where rownum<2

