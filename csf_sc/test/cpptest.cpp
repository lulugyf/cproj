#include <string>
#include <iostream>

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>

using namespace std;

class ErrType{
public:
    int code;
    char msg[256];
    void ErrType(int c, const char *m){
        code = c;
        strncpy(msg, m, sizeof(msg)-1);
        msg[sizeof(msg)-1] = 0;
    }
}

class EntryRecord{
public:
    void EntryRecord(const char *func){
        strncpy(funcname, func, sizeof(funcname)-1);
        funcname[sizeof(funcname)-1] = 0;
        gettimeofday(&t1, NULL);
        code = 0;
    }
    void ~EntryRecord(){
        gettimeofday(&t2, NULL);
        printf("--func[%s]  time[%ld] code[%d]\n", funcname, (t2.tv_sec-t1.tv_sec)*1000 + (t2.tv_usec-t1.tv_usec)/1000, code);
    }
    void setCode(int c){code = c;}
private:
    char funcname[64];
    struct timeval t1;
    struct timeval t2;
    int code;
}

void func1(){
    EntryRecord __e(__FUNCTION__);
    usleep(10);
    throw ErrType(123, "hello exception");
}

void func2(){
    EntryRecord __e(__FUNCTION__);
    usleep(20);
    func1();
}

void func3(){
    EntryRecord __e(__FUNCTION__);
    usleep(25);
    func2();
}

// __LINE__, __FUNCTION__, __FILE__
int main(int argc, char *argv[])
{
    EntryRecord __e(__FUNCTION__);
    try{
        func3();
    }catch(ErrType &e){
        __e.setCode(e.code);
    }
    return 0;
}

