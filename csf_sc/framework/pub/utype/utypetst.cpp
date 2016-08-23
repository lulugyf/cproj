#include <utype.h>
#include <stdlib.h>
#include <stdio.h>
extern "C" char* Trim(char *S);

static PrintTree(int* ay, int iLevel)
{
	for(int i=0;i<iLevel;++i){
		if(ay[i]) printf("    ");
		else  printf("��  ");
	}
	if(ay[iLevel]) printf("����");
	else printf("����");
}

static int validint(const char* s)
{
	int i;
	for(i=0;s[i]!=0;++i)
		if(s[i]<'0'||s[i]>'9') return 0;
	
	if(i>=10) return 0;
	return 1;
}

static int validlong(const char* s)
{
	int i;
	for(i=0;s[i]!=0;++i)
		if(s[i]<'0'||s[i]>'9') return 0;
	
	return 1;
}


static void PrintUtypeCurrent(const utype *pu, int iLevel, int* ay, int flag)
{
	int i;

	u_errno=0;
	for(i=0;i<pu->cnt;i++)
	{
		if(i==pu->cnt-1) ay[iLevel]=1;
		else ay[iLevel]=0;
		switch(pu->ppe[i]->type)
		{
			case U_EMPTY:
			{
				PrintTree(ay, iLevel);
				printf("%d.%s(empty)\n",i,utGetName(pu,i));
				break;
			}
			case U_CHAR:
			{
				PrintTree(ay, iLevel);
				printf("%d.%s(char):%c\n",i,utGetName(pu,i), pu->ppe[i]->value.v_char);
				break;
			}
			case U_INT:
			{
				PrintTree(ay, iLevel);
				printf("%d.%s(int):%d\n",i,utGetName(pu,i), pu->ppe[i]->value.v_int);
				break;
			}
			case U_LONG:
			{
				PrintTree(ay, iLevel);
				printf("%d.%s(long):%ld\n",i,utGetName(pu,i), pu->ppe[i]->value.v_long);
				break;
			}
			case U_DOUBLE:
			{
				PrintTree(ay, iLevel);
				printf("%d.%s(double):%lf\n",i,utGetName(pu,i), pu->ppe[i]->value.v_double);
				break;
			}
			case U_STRING:
			{
				PrintTree(ay, iLevel);
				printf("%d.%s(string):%s\n",i,utGetName(pu,i), pu->ppe[i]->value.p_char);
				break;
			}
			case U_ARRAY:
			case U_STRUCT:
			{
				PrintTree(ay, iLevel);
				printf("%d.%s(utype)\n",i,utGetName(pu,i));
				if(flag)
					PrintUtypeCurrent(pu->ppe[i]->value.p_utype,iLevel+1,ay,flag);
				break;
			}
			default:
			{
				break;
			}
		}
	}
}




void dive(const char* s, char* s1, char* s2)
{
	const char* sbeg, *send;

	int i=0;
	
	for(i=0;(*s)==' '||(*s)=='\t';++s);
	for(i=0;!(s[i]==0||((s[i]==' '||s[i]=='\t')&&s[0]!='\"')||(s[0]=='\"'&&s[i]=='\"'));++i);
	memcpy(s1, s, i);

	s1[i]=0;
	strcpy(s2, s+i);
	Trim(s2);	
}


typedef struct uStack{
	utype* ut;
	int pos;
} t_uStack;



void Add(const char* c, const char* target, t_uStack* st, int cur)
{

	char cmd[1024];
	char para[4096];
	dive(target, cmd, para);
	if(cmd[0]==0){
		fprintf(stderr,"ȱ�ٽڵ���\n");
		return;
	}
	switch(c[1]){
		case 'i':if(strcmp(c, "ai")!=0) break; try{utAddInt(st[cur].ut, cmd, atoi(para));}catch(uException& err){fprintf(stderr,"����%s\n",err.errMsg);}return;
		case 'l':if(strcmp(c, "al")!=0) break; try{utAddLong(st[cur].ut, cmd, atol(para));}catch(uException& err){fprintf(stderr,"����%s\n",err.errMsg);}return;
		case 's':if(strcmp(c, "as")!=0) break; try{utAddStr(st[cur].ut, cmd, para);}catch(uException& err){fprintf(stderr,"����%s\n",err.errMsg);}return;
		case 'd':if(strcmp(c, "ad")!=0) break; try{utAddDouble(st[cur].ut, cmd, atof(para));}catch(uException& err){fprintf(stderr,"����%s\n",err.errMsg);}return;		
		case 'u':if(strcmp(c, "au")!=0) break; try{utAddStruct(st[cur].ut, cmd, uInit(0));}catch(uException& err){fprintf(stderr,"����%s\n",err.errMsg);}return;
		default:		
	}
	fprintf(stderr,"δ֪������[%s]\n", c);
}


void Set(const char* c, const char* target, t_uStack* st, int cur)
{

	char cmd[1024];
	char para[4096];
	int pos;
	dive(target, cmd, para);
	if(cmd[0]==0){
		fprintf(stderr,"ȱ��λ��\n");
		return;
	}
	if(!validint(cmd)){
		fprintf(stderr,"λ��[%s]����Ч����\n", cmd);
		return;
	}
	pos=atoi(cmd);
	switch(c[1]){
		case 'i':if(strcmp(c, "si")!=0) break; try{utSetInt(st[cur].ut,"", pos, atoi(para));}catch(uException& err){fprintf(stderr,"����%s\n",err.errMsg);}return;
		case 'l':if(strcmp(c, "sl")!=0) break; try{utSetLong(st[cur].ut,"", pos, atol(para));}catch(uException& err){fprintf(stderr,"����%s\n",err.errMsg);}return;
		case 's':if(strcmp(c, "ss")!=0) break; try{utSetStr(st[cur].ut,"", pos, para);}catch(uException& err){fprintf(stderr,"����%s\n",err.errMsg);}return;
		case 'd':if(strcmp(c, "sd")!=0) break; try{utSetDouble(st[cur].ut,"", pos, atof(para));}catch(uException& err){fprintf(stderr,"����%s\n",err.errMsg);}return;		
		case 'u':if(strcmp(c, "su")!=0) break; try{utSetStruct(st[cur].ut, "",pos, uInit(0));}catch(uException& err){fprintf(stderr,"����%s\n",err.errMsg);}return;
		case 'e':if(strcmp(c, "se")!=0) break; try{utSetEmpty(st[cur].ut, "",pos);}catch(uException& err){fprintf(stderr,"����%s\n",err.errMsg);}return;
		default:		
	}
	fprintf(stderr,"δ֪������[%s]\n", c);
}


void Ls(const char* c, const char* target, t_uStack* st, int cur)
{
	int ay[100];
	if(strcmp(c, "ls")!=0){
		fprintf(stderr,"δ֪������[%s]\n", c);
		return;
	}
	if(target[0]!=0){
		if(strcmp(target, "a")!=0){
			fprintf(stderr,"δ֪��������[%s]\n", target);
			return;
		}
		PrintUtypeCurrent(st[cur].ut, 0,ay,1);
	}else
		PrintUtypeCurrent(st[cur].ut, 0,ay,0 );
}
void Cd(const char* c, const char* target, t_uStack* st, int& cur)
{
	if(strcmp(c, "cd")!=0){
		fprintf(stderr,"δ֪������[%s]\n", c);
		return;
	}
	if(strcmp(target, "..")==0){
		if(cur>0)
			--cur;
		else
			fprintf(stderr,"�Ѵﵽ���ڵ�\n");
	}else if(strcmp(target, "/")==0){
		cur=0;
	}else{
		char name[255];
		char num[100];
		int n=0;
		 
		dive(target, name, num);
		if(!validint(num)){
			fprintf(stderr,"λ��[%s]����Ч����\n", num);
			return;
		}
		if(num[0]!=0) n=atoi(num);

		try{
			int i=0;
			UPOS pos;
			for(pos=utFind(st[cur].ut, name); pos!=UPOS_END&&i<n; pos=utNext(st[cur].ut, pos), ++i);
			
			if(pos==UPOS_END){
				if(i==0)
					fprintf(stderr,"��Ϊ[%s]�Ľڵ㲻����\n", name);
				else
					fprintf(stderr,"���[%d]Խ��\n", n);
				return;
			}
			st[cur+1].pos=pos;
			st[cur+1].ut=(utype*)utGetStruct(st[cur].ut, pos);
			++cur;
		}catch(uException& err){fprintf(stderr,"����%s\n",err.errMsg);}
	}
}
void ToXML(const char* c, const char* target, t_uStack* st, int cur)
{
	if(strcmp(c, "tx")!=0){
		fprintf(stderr,"δ֪������[%s]\n", c);
		return;
	}
	
	char* s=uUType2Xml(st[cur].ut, "root");
	if(target[0]==0)
		printf("xml:  %s\n", s);
	else{
		FILE* fp=fopen(target, "w");
		if(fp==NULL) fprintf(stderr,"�ļ�[%s]��ʧ��\n", target);
		fprintf(fp, "%s\n", s);
		fclose(fp);	
	}
	free(s);
}

void Pwd(const char* c, const char* target, t_uStack* st, int cur)
{
	if(strcmp(c, "pwd")!=0){
		fprintf(stderr,"δ֪������[%s]\n", c);
		return;
	}
	printf("Path:  ��");
	for(int i=1;i<=cur;++i){
		printf(".%d", st[i].pos);
	}
	printf("\n");
}



int main(int argc, char** argv)
{
	char s[4096];
	char cmd[1024];
	char target[4096];
	t_uStack st[100];
	int cur=0;
	st[0].pos=-1;
	if(argc==1){
		st[0].ut=uInit(1);
	}else{
		char sLine[4096];
		char* sXmlFile;
		const char* sXML;
	
		if(argc!=3||argv[1][0]!='-'||(argv[1][1]!='s'&&argv[1][1]!='f')){
			fprintf(stderr, "USEAGE: ֱ��ִ�� um  �� um -s xmlstring ��um -f xmlfile\n");
			fprintf(stderr, "-------------------------------------------------------\n");
			fprintf(stderr, "ai <�ڵ���> [ֵ]           ����һ��int���͵��ӽڵ�\n");
			fprintf(stderr, "al <�ڵ���> [ֵ]           ����һ��long���͵��ӽڵ�\n");
			fprintf(stderr, "as <�ڵ���> [ֵ]           ����һ��string���͵��ӽڵ�\n");
			fprintf(stderr, "ad <�ڵ���> [ֵ]           ����һ��double���͵��ӽڵ�\n");
			fprintf(stderr, "au <�ڵ���> [ֵ]           ����һ��utype���ӽڵ�\n");
			fprintf(stderr, "si <λ��> [ֵ]             ��������int�����ӽڵ��ֵ\n");
			fprintf(stderr, "sl <λ��> [ֵ]             ��������long�����ӽڵ��ֵ\n");
			fprintf(stderr, "ss <λ��> [ֵ]             ��������string�����ӽڵ��ֵ\n");
			fprintf(stderr, "sd <λ��> [ֵ]             ��������double�����ӽڵ��ֵ\n");
			fprintf(stderr, "su <λ��> [ֵ]             ��utype�ӽڵ��ÿ�\n");
			fprintf(stderr, "se <λ��>                  ɾ��ĳ���ӽڵ�\n");
			fprintf(stderr, "ls [a]                     ��ʾ��ǰ�ڵ���ӽڵ㣬����a��ʾͬʱ�ݹ���ʾ�ӽڵ�\n");
			fprintf(stderr, "cd <�ڵ���> [ͬ���±�]     ����ĳ���ӽڵ㣬�����±����������ͬ���ڵ�\n");
			fprintf(stderr, "tx [�ļ���]                ����ǰ�ڵ�����еݹ��ӽڵ�תΪxml�������ļ�����������д���ļ�\n");
			fprintf(stderr, "pwd                        ��ӡ��ǰ�ڵ��λ��·��\n");
			exit(1);
		}
		if(argv[1][1]=='f'){
			FILE* fp;
			sXmlFile=(char*) malloc(1024*1024);
			if(sXmlFile==NULL) {
				fprintf(stderr, "�ڴ����ʧ��\n");
				fflush(stderr);
				exit(1);
			}
			if((fp=fopen(argv[2],"r"))==NULL){
				fprintf(stderr, "���ļ�[%s]ʧ��\n",argv[2]);
				fflush(stderr);
				exit(1);
			}
			while(fgets(sLine,sizeof(sLine),fp)!=NULL){
				strcat(sXmlFile,sLine);
			}
			Trim(sXmlFile);
			fclose(fp);
			if(sXmlFile[0]==0){
				fprintf(stderr, "�ļ�[%s]����Ϊ��\n",argv[2]);
				fflush(stderr);
				exit(1);
			}
			sXML=sXmlFile;		
		}else{
			sXML=argv[2];
		}
		if(sXML[0]==0){
				fprintf(stderr, "XML��Ϊ�մ�\n");
				fflush(stderr);
				exit(1);
		}
		try{st[0].ut=uXml2Utype(sXML);}catch(uException& err){fprintf(stderr,"����%s\nxml: %s",err.errMsg, sXML);fflush(stderr);exit(1);}
	}
	
	while(1){
		printf("��");
		for(int i=1;i<=cur;++i){
			printf(".%s", utGetName(st[i-1].ut, st[i].pos));
		}
		
		
		printf("> ");
		gets(s);
		dive(s, cmd, target);
		switch(cmd[0]){
			case 'e':if(strcmp(cmd, "exit")==0) {
				printf("�Ƿ񱣴�����utype�ṹ���ļ�(y/n/FileName)��");
				gets(s);
				if(s[0]=='y'&&s[1]==0) ToXML("tx", "save.xml", st, 0);
				else if(s[0]=='n'&&s[1]==0) ;
				else ToXML("tx", s, st, 0);
				exit(0);
			}
			case 'a':Add(cmd, target, st, cur);break;
			case 's':Set(cmd, target, st, cur);break;
			case 'l':Ls(cmd, target, st, cur);break;
			case 'c':Cd(cmd, target, st, cur);break;
			case 't':ToXML(cmd, target, st, cur);break;
			case 'p':Pwd(cmd, target, st, cur);break;
			default: printf("δ֪������[%s]\n", cmd);
		}
	}
}

