tmloadrepos -i mdr_simpapp.mif mdr_simpapp.repos
sh loadsalt
wsloadcf -y simpapp.dep
sh loadcfg

tmboot -y
tmwsdlgen -c simpapp.wsdf -y -o simpapp.wsdl


clxml stest "1"
export SALTCONFIG=/crmpdpp/csf/run/cfg/saltconfig
clxml sRouteInfo '<ROOT><ROUTE_TYPE type="int">10</ROUTE_TYPE><ROUTE_VALUE type="string">13655530123</ROUTE_VALUE></ROOT>'
