
#include "framework.h"

char s[]="L4C_CFG=";

string& stringlower(string& str)
{
	int i =0 ; 
	for(;i < str.length() ; ++i )
	{
		str[i]=tolower(str[i]);
	}
  return str;
}

int main(int argc,char * argv[])
{        
    FILE *fp;
    char user[50];
    char pwd[50];
    char tmp_line[10];
    char filename[200];
    int  i,k,pointer=0;
	char key[5];
    
    string tns;
    string user1;
    string passwd;
    string bak;
    string type;
    putenv(s);
    if(argc<2) return -1;
    try{
            GetDBCfg(argv[1],  tns,   user1,  passwd,  bak,  type);
    }catch(...){
            return -2;
    }
    
    // 统一转换成小写
    stringlower(tns);
    stringlower(user1);
    stringlower(passwd);
    
    sprintf(filename ,"login");  /*生成的文件命名为 login*/
    sprintf(key,"DFJLT");
    pointer=0;
        
    memset(user, 0, sizeof(user));
    memset(pwd, 0, sizeof(pwd));
    sprintf(user, "%s", user1.c_str());
    sprintf(pwd, "%s", passwd.c_str());
    
    i=strlen(user);
    user[i]='\n';
    for (k=0;k<i;k++)
    {
        user[k]=user[k]^key[pointer];
        pointer++;
        if (pointer==5)
            pointer=0;
    }
    
    pointer=0;
    i=strlen(pwd);
    pwd[i]='\n';
    for (k=0;k<i;k++)
    {
        pwd[k]=pwd[k]^key[pointer];
        pointer++;
        if (pointer==5)
            pointer=0;
    }
    
    if((fp=fopen(filename,"w"))==NULL) 
    {
        printf("open file fail!\n");
        exit(1);
    }
    fputs("user\n",fp);
    fputs(user,fp);
    fputs("pwd\n",fp);
    fputs(pwd,fp);
    fclose(fp);
    printf("%s\n",tns.c_str());
    return 0;
}


