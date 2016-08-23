
#include <stdio.h>
#include <unistd.h>

#include <utype.h>
#include <sys/stat.h>

char *readFile(const char *fname)
{
    struct stat st;
    char *buf;
    if(stat(fname, &st) != 0)
        return NULL;
    buf = (char *)malloc(st.st_size+1);
    buf[st.st_size] = 0;
    FILE *fp = fopen(fname, "r");
    fread(buf, 1, st.st_size, fp);
    fclose(fp);
    return buf;
}

void test3()
{
	utype *p1 = uInit(1);
	utAddInt(p1, "int", 11);
	utAddChar(p1, "char", 'a');
	utAddStr(p1, "str", "I'm hurry!");
	utAddLong(p1, "long", 3333333333L);
	utAddDouble(p1, "double", 1209123.12);

	printf("int=%d\n", utGetInt(p1, "int"));
	printf("char=%c\n", utGetChar(p1, "char"));
	printf("str=%s\n", utGetStr(p1, "str"));
	printf("long=%ld\n", utGetLong(p1, "long"));
	printf("double=%.2f\n", utGetDouble(p1, "double"));

	utype *p2 = uInit(1);
	utAddInt(p2, "int1", 123);
	utAddStruct(p1, "sub", p2);
	printf("sub-int1=%d\n", utGetInt(utGetStruct(p1, "sub"), "int1"));
	char *xml = uUType2Xml(p1, "root");
	printf("%s\n", xml);
	free(xml);
	uFree(p1);
	return;
}


/*!
执行一次utype的分配和释放测试
one test
*/
/*! \brief Brief description.
 *         Brief description continued.
 *
 *  Detailed description starts here.
 */
void test1()
{
	utype *p1 = uInit(1);
	char cname[30];
	for(int j=0; j<100; j++){
		for(int i=0; i<50; i++)
		{
			utype *p2 = uInit(1);
			const utype *p3;
			sprintf(cname, "str%d", i);
			utAddStr(p2, cname, "kkkkkkkkkkkkkkkkkkkkkkkkkkkkk");
			utAddStruct(p1, cname, p2);
			p3 = utGetStruct(p1, cname);
			utGetStr(p3, cname);
			sprintf(cname, "int%d", i);
			utAddInt(p1, cname, 12313);
			utGetInt(p1, cname);
			sprintf(cname, "double%d", i);
			utAddDouble(p1, cname, 123.0);
			utGetDouble(p1, cname);
			fflush(stdout);
		}
		uFree(p1);
		printf("cycle %d\n", j);
		sleep(2);
	}
	return;
}


void test11()
{
    const char *uxml = "<ROOT>"
                                  "<DATA>"
                                        "<ID type=\"long\">1</ID>"
                                        "<NAME type=\"string\">test_csf_1</NAME>"
                                  "</DATA>"
                                  "<DATA>"
                                        "<ID type=\"long\">2</ID>"
                                        "<NAME type=\"string\">test_csf_2</NAME>"
                                  "</DATA>"
                          "</ROOT>";
    puts(uxml);
    uAutoPtr  inParam(uXml2Utype(uxml)); // uXml2Utype函数返回
    char inDataName[32];
    const utype* rp;


    sprintf(inDataName,"DATA");

    for(UPOS pos=utFind(inParam,inDataName) ; pos!=UPOS_END ; pos=utNext(inParam,pos))
    {
    	//如果调用了utGetStruct取得一个utype*，则一定不能用智能指针包装这个utype*
    	rp=utGetStruct(inParam,inDataName,pos);


    	if(utGetEmpty(rp,"ID"))
    		printf("utGetEmpty ID NULL!\n");
    	else
    		printf("ID=[%ld] ",utGetLong(rp,"ID"));

    	if(utGetEmpty(rp,"NAME"))
    		printf("utGetEmpty NAME NULL!\n");
    	else
    		printf("NAME=[%s]\n",utGetStr(rp,"NAME"));
    }

}
#include <utype.h>
#include <stdio.h>
void test2()
{
	utype *p1;
	for(int i=0; i<50; i++)
	{
		p1 = uInit(1);
		utAddStr(p1, "rierman", "0000000000000000000000000000");
		utAddStr(p1, "rierman1", "00000000ddddddddddd000000000000000000000");
		utAddInt(p1, "rint", 123);
		utype *p2 = uInit(1);
		utAddStruct(p1, "next", p2);
		utAddStr(p2, "asdf", "123999");
		/*utype *p3 = uInit(1);
		utAddValues(p3, utstring, "name1", "value1", -1);
		utAddValues(p1, 
			utstring, "col1", "value1",
			utint, "col2", 123,
			utlong, "col3", 67990L,
			utchar, "col4", 'c',
			utdouble, "col5", 1233.1,
			utstring, "col6", "1233",
			utstruct, "col7", p3,
			-1); */

	}
	printf("str1=[%s] int=[%d] long=[%ld]\n", 
		utGetStr(p1, "col1"), utGetInt(p1, "col2"), utGetLong(p1, "col3"));
}

char * utype2json(const utype *pu);
utype *json2utype(const char *str);
void test4()
{
	const char *str = "{\"phone_no\":\"12345678901\",\"login_no\":\"aagh55\",\"valid_time\":12,\"op_code\":\"1122\",\"desc\":\"haha\"}";
	utype *u = json2utype(str);
	if(u == NULL){
		printf("failed\n");
	}else{
		printf("succ\n");
		uFree(u);
	}
}

void test12()
{
    char *uxml = readFile("a.txt");
    if(uxml == NULL){
        printf("file not found\n");
        return;
    }
    uAutoPtr  inParam(uXml2Utype((const char *)uxml));
    free(uxml);
    char *json = utype2json(inParam);
    printf("[%s]\n", json);
    free(json);
}

#include <stdlib.h>
int main(int argc, char** argv)
{
	/*
	int i;
	i = 0;
	uSetAutoFree(true);
	while(1)
	{
	    test2();
		uFreeAll();
		printf("test %04d\n", i++);
	    sleep(1);
	}*/

	//test4();
    test12();
	return 0;
}

