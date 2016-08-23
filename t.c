#include <stdio.h>
#include <limits.h>
#include <sys/time.h>

#include "offon.h"
#include "linkhash.h"

struct cmdtoorder
{
    char				hlrcode[4];			/* 交换机代码 */
    int					cmdcode;			/* 业务命令代码 */
    int					priority;			/* 命令优先级 */
    int					ordercode;			/* 交换机指令代码 */
    char				type;				/* 指令类型 */
    int					serial;				/* 交换机指令序号 */
    struct cmdtoorder	*next;
};


int splitc(char *string, char *fields[], int  nfields, char sep )
{
    char *p, *p1;
    int i;

    p = string;
    fields[0] = p;
    i = 1;
    while( (p1=strchr(p,sep))!= NULL && i<nfields){
        p1[0] = 0; p1++;
        fields[i] = p1;
        p = p1; i++;
    }
    return i;
}

typedef int (*fields_func) (char *flds[], int n, void *data);

int openfile(const char *fname, fields_func callback, char sep, const int max_flds_per_line, void *data) {
    FILE *fp;
    char line[1024];
    char *fs[max_flds_per_line], *p;
    int fc, find_flag, i;

    fp = fopen(fname, "r");
    while( fgets(line, sizeof(line)-1, fp) != NULL){
        fc = splitc(line, fs, max_flds_per_line, sep);
        if(callback(fs, fc, data) != 0)
            break;
    }
    fclose(fp);
    return 0;
}

static int get_hlr_cfg(const char *hlrcode, const int hlrport, char *gsmip,
                int *gsmport,char *gsmuser, char *gsmpswd,
                char *order_fname, char *reply_fname, char *query_fname,
                char *mgr_servip, int *mgr_servport, char *mgr_flag, char *mgr_user,
                char *mgr_pswd, char *mgr_term)
{
    FILE *fp;
    char line[1024];
    char fname[128];
    char *fs[15], *p;
    int fc, find_flag, i;

    sprintf(fname, "%s/hlr.cfg", getenv("ETCDIR"));
    fp = fopen(fname, "r");
    find_flag = 0;
    while( fgets(line, sizeof(line)-1, fp) != NULL){
        fc = splitc(line, fs, 14, '|');
        if(fc != 14){
            printf("format err %d\n", fc);
            continue;
        }
        if(strcmp(fs[0], hlrcode) == 0 && atoi(fs[1])==hlrport){
            find_flag = 1;
            break;
        }
    }
    fclose(fp);
    if(find_flag == 0)
            return -1;

    if( (p = strchr(fs[13], '\n') ) != NULL)
        p[0] = 0;

        strcpy(mgr_servip, fs[2]);
    /*for(i=0; i<fc; i++)
        printf("%d=%s\n", i, fs[i]); */
    fflush(stdout);
        *mgr_servport = atoi(fs[3]);
        if(mgr_flag != NULL)
                *mgr_flag = 'N';
        strcpy(gsmip, fs[4]);
        *gsmport = atoi(fs[5]);
        strcpy(gsmuser, fs[6]);
        strcpy(gsmpswd, fs[7]);

        strcpy(order_fname, fs[8]);
        strcpy(reply_fname, fs[9]);
        strcpy(query_fname, fs[10]);

        strcpy(mgr_user, fs[11]);
        strcpy(mgr_pswd, fs[12]);
        strcpy(mgr_term, fs[13]);

        return 0;
}

int main_1(int argc, char *argv[])
{
    char hlrcode[4];
    int hlrport;
    char mgr_user[20], mgr_pswd[20], mgr_term[10];
    char order_fname[256],reply_fname[256],query_fname[256];
    char srvip[30];
    int commport;

    char                                gsmip[32];
    int                                 gsmport;
    char                                gsmuser[32];
    char                                gsmpswd[32];
    int i;


    strcpy(hlrcode, "hab");
    hlrport=5;
    i = get_hlr_cfg(hlrcode, hlrport, gsmip, &gsmport, gsmuser, gsmpswd,
            order_fname,reply_fname,query_fname, srvip, &commport, NULL,
            mgr_user, mgr_pswd, mgr_term);

    if(i == 0){
        printf("Hello, world  %s\n", mgr_user);
    }else{
        printf("failed, %d\n", i);
    }
    
    return 0;
}

FILE *logfp;

static unsigned long lh_int_hash(const void *k)
{
        int c = (int)k;
        return (unsigned long)((((ptrdiff_t)c * LH_PRIME) >> 4) & UINT_MAX);
}

static int lh_int_equal(const void *k1, const void *k2)
{
        return ((int)k1 == (int)k2);
}
static void _lh_entry_free_cmdtoorder(struct lh_entry *ent){
        struct cmdtoorder *ptr = (struct cmdtoorder *)(ent->v), *p1;
        while(ptr != NULL) {
            p1 = ptr->next;
            //printf("FREE cmdcode: %d ordercode: %d\n", ptr->cmdcode, ptr->ordercode);
            free(ptr);
            ptr = p1;
        }
}

static struct cmdtoorder ** insert_hash(struct cmdtoorder *ptr) {
    struct cmdtoorder **table;
    struct cmdtoorder *last, *p1;
    //table = lh_table_new(1024, NULL, _lh_entry_free_cmdtoorder, lh_int_hash, lh_int_equal);
    table = (struct cmdtoorder **)malloc(sizeof(struct cmdtoorder *) * 1000);
    memset(table, 0, sizeof(struct cmdtoorder *) * 1000);

    last = NULL;
    while(ptr) {
      if(last == NULL ) {
          p1 = ptr->next;
          last = ptr;
          last->next = NULL;
          ptr = p1;
          continue;
      }
      if(last->cmdcode != ptr->cmdcode) {
          //lh_table_insert(table, (void *)last->cmdcode, last);
          table[last->cmdcode] = last;

          p1 = ptr->next;

          ptr->next = NULL;
          last = ptr;

          ptr = p1;
      }else{
          p1 = ptr->next;
          ptr->next = last;
          last = ptr;

          ptr = p1;
      }
    }
    //lh_table_insert(table, (void *)last->cmdcode, last);
    table[last->cmdcode] = last;
    return table;
}

static struct cmdtoorder *get_ordernode_list(struct cmdtoorder *cmdhead, int code)
{
        struct cmdtoorder *cmdtail=cmdhead->next;
        while(cmdtail)
        {
                if(cmdtail->cmdcode==code)
                        return cmdtail;

                cmdtail=cmdtail->next;
        }
        return NULL;
}

static struct cmdtoorder *get_ordernode_hash(struct lh_table *t, int code) {
    struct cmdtoorder *p1 = lh_table_lookup(t, code);
    if(p1 == NULL) {
        return NULL;
    }else{
        return p1;
    }
}

// return time diff in ms
static int timediff(struct timeval *t1,struct timeval *t2){
        return (t2->tv_sec-t1->tv_sec)*1000 + (t2->tv_usec-t1->tv_usec) / 1000;
}

int main(int argc, char *argv[])
{
    char conf[128];
    struct cmdtoorder cmdhead, *ptr, *last, *p1;
    const char *hlrcode = "hbp";
    //struct lh_table *table;
    struct cmdtoorder **table;
    int err = 0, i;
    struct timeval t1, t2;
    int code = 51;

    if(argc > 1)
        code = atoi(argv[1]);
    logfp = stdout;

    sprintf(conf, "%s/gdblogin.cfg", getenv("ETCDIR"));
    if(logindb(conf) != 0){
        printf("login db failed\n");
        return 2;
    }

    if(get_cmdtoorder(hlrcode, &cmdhead) != 0) {
        printf("get_cmdtorder failed\n");
        err = 1;
    }
    db_logout();

    if(err) return 1;

    gettimeofday(&t1, NULL);
    for(i=0; i<100000; i++)
        p1 = get_ordernode_list(&cmdhead, code);
    gettimeofday(&t2, NULL);
    printf("list: %d ms\n", timediff(&t1, &t2));


    table = insert_hash(cmdhead.next);

    gettimeofday(&t1, NULL);
     for(i=0; i<100000; i++)
         p1 = table[code];
     gettimeofday(&t2, NULL);
     printf("hash: %d ms\n", timediff(&t1, &t2));

    //p1 = lh_table_lookup(table, code);
     p1 = table[code];
    if(p1 == NULL) {
        printf("not found\n");
    }else{
        while(p1 != NULL) {
            printf("cmd %d, order: %d, serial: %d\n", p1->cmdcode, p1->ordercode, p1->serial);
            p1 = p1->next;
        }
    }

    //lh_table_free(table);

    return 0;
}
