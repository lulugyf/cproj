clxml sQDual "<r></r>"
clxml sQDual "{}"

clxml sTest1 '{"ROOT":{"col1":1} }'
clxml sTest1 '{"ROOT":{"HEADER":{"DB_ID":"b1"}, "BODY":{"col1":1} } }'
clxml sTest1 '{"ROOT":{"HEADER":{"DB_ID":"a1"}, "BODY":{"col1":1} } }'

#���� �ڷ����е��� AssMutiConnWork ������ ԭAssMutiConnWork�Ѿ�����Ϊ AssMutiConnWork_old
clxml sMulTest '{"ROOT":{"col1":2} }'
clxml sTest1 '{"ROOT":{"col1":2} }'

#������޸��� AssMutiConnWork ����Ϊ����Զ�̷���Ĳ���
clxml sMulTest '{"ROOT":{"HEADER":{"DB_ID":"a1","POOL_ID":"11","CHANNEL_ID":"02"}, "BODY":{"col1":2, "PHONE_NO":"15799881753"} }}'


