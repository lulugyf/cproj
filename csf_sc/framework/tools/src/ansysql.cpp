
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define DELETE		"DELETE"
#define DELETE_FROM	"DELETE FROM"
#define UPDATE		"UPDATE"
#define INSERT_INTO	"INSERT INTO"
#define FROM		"FROM"

#define GROUPBY		"GROUP BY"
#define WHERE		"WHERE"
#define ORDERBY		"ORDER BY"
#define ON			"ON"
#define JOIN		"JOIN"

#define SELECT		"SELECT"
#define MAX_LINE_CHAR 100
#ifndef min
#define min(a, b)            (((a) < (b)) ? (a) : (b))
#endif
#ifndef max
#define max(a, b)            (((a) > (b)) ? (a) : (b))
#endif

typedef enum optype{
	OT_NULL=0,
	OT_INERT,
	OT_SELECT,
	OT_UPDATE,
	OT_DELETE
} e_optype;

typedef struct table{
	char tbname[32];
	e_optype op;
} t_table;


const char* ch="(),.[]<";
t_table ta[100];
int sufx;


//剔除多余的空格，并将所有字符转为大写
int inner_trim(char* s)
{
	int i=0, j=0, sq=0, dq=0;

	for(;s[i]!=0;++i, ++j){
		if(s[i]=='\'') sq=(sq+1)%2;
		if((s[i]=='\t'||s[i]=='\r'||s[i]=='\n')&&sq==0&&dq==0)
			s[i]=' ';
		if(j>0&&sq==0&&dq==0){
			if(s[j-1]==' '&&s[i]==' ') --j;
			else if(s[j-1]==' '&&strchr(ch, s[i])) --j;
			else if(s[i]==' '&&strchr(ch, s[j-1])){
				--j;
				continue;
			}
		}
		//if(i==j) continue;

		s[j]=toupper(s[i]);
	}
	s[j]=0;
	if(s[j-1]==' ') s[--j]=0;
	return j;
}


int getname(char* s, e_optype ot)
{
	int i=0;
	char name[32];
	for(i=0;i<31&&s[i]!=0;i++){
		if(isalnum(s[i])||s[i]=='_'||s[i]=='.'){
			name[i]=s[i];
		}else break;
	}
	if(i==0) return 0;
	name[i]=0;
	strcpy(ta[sufx].tbname, name);
	ta[sufx++].op=ot;
	return i;
}


//寻找匹配括号
int findpp(char* s)
{
	int i=0, level=0;

	for(i=0;s[i]!=0;i++){
		if(s[i]=='(') ++level;
		if(s[i]==')') --level;
		if(level==0) return i;
	}
	return -1;
}
//标示符匹配
int idencmp(const char* s, const char* s1, int n)
{
	int i=0;
	for(;i<n&&(s[i]!=0||s1[i]!=0);i++){
		if(s[i]!=s1[i]) return s[i]-s1[i];
	}
	if(s[i]==0&&s1[i]==0) return 0;

	if(isalnum(s[i])||s[i]=='_'||s[i]=='.') return 1;
	if(isalnum(s1[i])||s1[i]=='_'||s1[i]=='.') return -1;
	return 0;
}


void ansy_sql(char* s, size_t len);
//分析from子句
int ansy_from(char* s)
{
	int i=1;
	if(idencmp(s+i, SELECT, sizeof(SELECT)-1)!=0){
		i+=getname(s+i, OT_SELECT);
	}else{
		i=0;
	}
	for(;s[i]!=0;++i){
		switch(s[i]){
			case ')': return i;
			case '(':{
					int pos=findpp(s+i);
					if(pos<0) return -1;
					if(idencmp(s+i+1, SELECT, sizeof(SELECT)-1)==0){//如果括号后第一个单词是select，则认为这是一个完整的select子句，否则只是from子句
						ansy_sql(s+i, pos);
					}else{
						ansy_from(s+i);
					}
					i+=pos;
				}
				break;
			case 'G':
				if(idencmp(s+i, GROUPBY, sizeof(GROUPBY)-1)==0){
					return i+sizeof(GROUPBY)-1;;
				}
				break;
			case 'W':
				if(idencmp(s+i, WHERE, sizeof(WHERE)-1)==0){
					return i+sizeof(WHERE)-1;
				}
				break;

			case 'O':
				if(idencmp(s+i, ORDERBY, sizeof(ORDERBY)-1)==0){
					return i+sizeof(ORDERBY)-1;
				}
				else if(idencmp(s+i, ON, sizeof(ON)-1)==0){
					return i+sizeof(ON)-1;
				}
				break;
			case 'J':
				if(idencmp(s+i, JOIN, sizeof(JOIN)-1)==0){
					i+=sizeof(JOIN)-2;
					if(s[i+1]=='(') continue;
					else{
						i+=2;
						i+=getname(s+i, OT_SELECT)-1;
					}
				}
				break;
			case ',':
				++i;
				i+=getname(s+i, OT_SELECT)-1;
				break;
			default:;
		}
	}
	return i;
}

void ansy_sql(char* s, size_t len)
{
	int i=0, last_c=1;

	for(i=0;i<len&&s[i]!=0;i++){
		if(!isalnum(s[i])&&s[i]!='_'&&s[i]!='.'){
			last_c=1;
			continue;
		}
		if(last_c==0) continue;
		switch(s[i]){
			case 'F':
				if(idencmp(s+i, FROM, sizeof(FROM)-1)==0){
					i+=sizeof(FROM)-1;
					i+=ansy_from(s+i);
				}
				break;
			case 'I':
				if(idencmp(s+i, INSERT_INTO, sizeof(INSERT_INTO)-1)==0){
					i+=sizeof(INSERT_INTO);
					i+=getname(s+i, OT_INERT)-1;
				}
				break;
			case 'D':
				if(idencmp(s+i, DELETE_FROM, sizeof(DELETE_FROM)-1)==0){
					i+=sizeof(DELETE_FROM);
					i+=getname(s+i, OT_DELETE)-1;
				}else if(idencmp(s+i, DELETE, sizeof(DELETE)-1)==0){
					i+=sizeof(DELETE);
					i+=getname(s+i, OT_DELETE)-1;
				}
				break;
			case 'U':
				if(idencmp(s+i, UPDATE, sizeof(UPDATE)-1)==0){
					i+=sizeof(UPDATE);
					i+=getname(s+i, OT_UPDATE)-1;
				}
				break;
			default:;

		}
		last_c=0;
	}
}

const char* keystr=",()= *\t";
int sqlcat(char* s, char* s1, size_t s1len, int lastLine)
{
	int i=0;
	char* last_c=s1;
	for(i=max(MAX_LINE_CHAR-lastLine, 0); s1[i]!=0&&i<s1len;i++){
		if(strchr(keystr, s1[i])!=NULL){
			char c=s1[i];
			if(c==' '){
				int num=0, k;
				for(k=i;k>=0;--k){
					if(s1[k]=='\'') ++num;
				}
				for(k=0;s[k]!=0;++k){
					if(s[k]=='\'') ++num;
				}
				if(num%2!=0) continue;
			}
			s1[i]=0;
			strcat(s, last_c);
			strcat(s, "\\\n\t\t");
			s1[i]=c;
			last_c=s1+i;
			i+=MAX_LINE_CHAR-1;

		}
	}
	strcat(s, last_c);
	if(last_c==s1)
		return lastLine+(s1+s1len-last_c);
	else
		return s1+s1len-last_c;
}

