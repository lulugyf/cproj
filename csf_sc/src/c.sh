clxml sQDual "<r></r>"
clxml sQDual "{}"

clxml sTest1 '{"ROOT":{"col1":1} }'
clxml sTest1 '{"ROOT":{"HEADER":{"DB_ID":"b1"}, "BODY":{"col1":1} } }'
clxml sTest1 '{"ROOT":{"HEADER":{"DB_ID":"a1"}, "BODY":{"col1":1} } }'

#测试 在服务中调用 AssMutiConnWork 函数， 原AssMutiConnWork已经更名为 AssMutiConnWork_old
clxml sMulTest '{"ROOT":{"col1":2} }'
clxml sTest1 '{"ROOT":{"col1":2} }'

#这个是修改了 AssMutiConnWork 函数为调用远程服务的测试
clxml sMulTest '{"ROOT":{"HEADER":{"DB_ID":"a1","POOL_ID":"11","CHANNEL_ID":"02"}, "BODY":{"col1":2, "PHONE_NO":"15799881753"} }}'


