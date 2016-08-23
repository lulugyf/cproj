###### ESB 提供的ws服务；
#./demo 0 "http://172.21.1.30:51900/esbWS/services/sCustInfoValid" esba.txt
###### ESB 提供的ws服务；
#./demo 0 "http://172.21.1.30:51900/esbWS/services/sCustInfoValid" esbnew.txt
###### ESB 提供的rest服务；
./demo 1 "http://172.21.1.30:51900/esbWS/rest/sCustInfoValid"    esbb.txt
#./demo 1 "http://172.21.27.101:51900/esbWS/rest/sCustInfoValid"    esbb.txt

#./demo 0 "http://172.21.0.122:21106/services/WsGetSaleAction.WsGetSaleActionHttpEndpoint/" esbc.txt




#./demo 0 "http://127.0.0.1:51900/esbWS/services/sCustInfoValid" esba.txt
#./demo 1 "http://127.0.0.1:8089/esbWS/rest/sCustInfoValid"    esbb.txt
#./demo 0 "http://172.21.0.30:51300/esbWS/services/WsGetSaleAction/" esbc.txt
#./demo 0 "http://172.21.1.36:8016/services/WsGetSaleAction" error.txt



#调用自己模拟的 rest服务进行测试；
#./demo 1 "http://127.0.0.1:9999/services/WsGetSaleAction" esbnew.txt



