#include <framework.h>

utype* __CALLBP(TUtypeFuncPtr bpfunc, const char *bpname, const utype *uInParam, TCtrlInfo *ctrlInfo);
#define CALLBP(bpname, uInParam, ctrlInfo) __CALLBP(bpname, #bpname, uInParam, ctrlInfo)

/*
crm.cfg 中增加如下的内容
[CALL_LOG]
uni_accept_path=COMMON_INFO.TRACE_ID
log_path=udp://172.21.3.187:7788
svc_sQDual=1
svc_sQDual2=1
 */
struct TCtrlInfoEx2: TCtrlInfoEx
{
	char __flag1[4];
    void *reserve1;
    void *reserve2;
    void *reserve3;
    void *reserve4;

    TCtrlInfoEx2();
    ~TCtrlInfoEx2();
    void init1(const char *servicename, const char *bpname, const utype *uin);
    const char *getServiceName();
    const char *getBPName();
	bool checkStruct();
};


class EntryRecord{
public:
    EntryRecord(const char *func, TCtrlInfo *tinfo);
    ~EntryRecord();
    void setCode(long c);
    void setMsg(const char *m);
    void setIn(const char *pin);
    void setIn(const utype *pin);
    void setOut(const utype *pout);
    void setOut(const char *pout);
private:
    void *cii;
    const char *funcname;
    struct timeval t1;
    struct timeval t2;
    long code;
    const char *errmsg;
    const char *callid_p;
    char callid[64];
    const utype *pin;
    const utype *pout;
    const char *s_pin, *s_pout;
};

