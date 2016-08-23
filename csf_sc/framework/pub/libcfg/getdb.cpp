#include "framework.h"

char s[]="L4C_CFG=";
int main(int argc, char** argv)
{
	string tns;
	string user;
	string passwd;
	string bak;
	string type;
	putenv(s);
	if(argc<2) return -1;
	try{
		GetDBCfg(argv[1],  tns,   user,  passwd,  bak,  type);
	}catch(...){
		printf("error\n");
		return -2;
	}
	printf("%s %s %s %s %s %s\n", argv[1],  tns.c_str(),   user.c_str(),  passwd.c_str(),  bak.c_str(),  type.c_str());
	return 0;
}


