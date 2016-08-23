ps -ef | grep -v grep | grep rsp | grep data | awk '{print $2}'|xargs kill -9
cc -o s s.c
nohup ./s ./rsp_xml.data  51900  >>./ws.log &
nohup ./s ./rsp_json.data 51901 >./rest.log &
