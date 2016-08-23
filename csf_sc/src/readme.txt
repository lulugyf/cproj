
create table csf1(col1 int, col2 varchar2(60));
insert into csf1 values(100, 'hello world');

clxml sTest1 '{"col1":100}'
clxml sTestx '{"col1":100}'