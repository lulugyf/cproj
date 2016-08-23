#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <limits.h>

#include "linkhash.h"

typedef struct _cmdtoorder
{
    char				hlrcode[4];			/* 交换机代码 */
    int					cmdcode;			/* 业务命令代码 */
    int					priority;			/* 命令优先级 */
    int					ordercode;			/* 交换机指令代码 */
    char				type;				/* 指令类型 */
    int					serial;				/* 交换机指令序号 */
    struct _cmdtoorder	*next;
} cmdtoorder;


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
    int fc, i = 0;

    fp = fopen(fname, "r");
    if(fp == NULL)
        return -1;
    while( fgets(line, sizeof(line)-1, fp) != NULL){
        fc = splitc(line, fs, max_flds_per_line, sep);
        if(callback(fs, fc, data) != 0)
            break;
        i++;
    }
    fclose(fp);
    return i;
}

static int line_deal(char *flds[], int n, void *data) {
    cmdtoorder *head = (cmdtoorder *)data, *ptr;
    if(n < 4)
        return 0;

    ptr=(cmdtoorder *)malloc(sizeof(cmdtoorder));
    memset(ptr,0x0,sizeof(cmdtoorder));

    // 008 0081 2 2
    ptr->cmdcode=atoi(flds[0]);
    ptr->priority=0;
    ptr->ordercode=atoi(flds[1]);
    ptr->serial=atoi(flds[3]);
    ptr->type=flds[2][0];
    ptr->next=head->next;
    head->next=ptr;

    return 0;
}




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
        cmdtoorder *ptr = (cmdtoorder *)(ent->v), *p1;
        while(ptr != NULL) {
            p1 = ptr->next;
            //printf("FREE cmdcode: %d ordercode: %d\n", ptr->cmdcode, ptr->ordercode);
            free(ptr);
            ptr = p1;
        }
}

static cmdtoorder ** insert_array(cmdtoorder *ptr) {
    cmdtoorder **table;
    cmdtoorder *last, *p1;
    //table = lh_table_new(1024, NULL, _lh_entry_free_cmdtoorder, lh_int_hash, lh_int_equal);
    table = (cmdtoorder **)malloc(sizeof(cmdtoorder *) * 1000);
    memset(table, 0, sizeof(cmdtoorder *) * 1000);

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

static struct lh_table* insert_linkhash(cmdtoorder *ptr) {
    struct lh_table *table;
    cmdtoorder *last, *p1;
    table = lh_table_new(1024, _lh_entry_free_cmdtoorder, lh_int_hash, lh_int_equal);

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
          lh_table_insert(table, (void *)last->cmdcode, last);
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
    lh_table_insert(table, (void *)last->cmdcode, last);
    return table;
}

static cmdtoorder *get_ordernode_list(cmdtoorder *cmdhead, int code)
{
        cmdtoorder *cmdtail=cmdhead->next;
        while(cmdtail)
        {
                if(cmdtail->cmdcode==code)
                        return cmdtail;

                cmdtail=cmdtail->next;
        }
        return NULL;
}

static cmdtoorder *get_ordernode_hash(struct lh_table *t, int code) {
    cmdtoorder *p1 = lh_table_lookup(t, code);
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
    cmdtoorder cmdhead, *ptr, *last, *p1;
    const char *hlrcode = "hbp";
    //struct lh_table *table;
    struct lh_table *ltable;
    cmdtoorder **table;
    int err = 0, i;
    struct timeval t1, t2;
    int code = 51;

    if(argc > 1)
        code = atoi(argv[1]);

    /*
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
    */

    const char *fname = "ccmdtoorder.txt";
    cmdhead.next = NULL;
    i = openfile(fname, line_deal, ' ', 4, &cmdhead);
    printf("openfile return %d\n", i);


    gettimeofday(&t1, NULL);
    for(i=0; i<100000; i++)
        p1 = get_ordernode_list(&cmdhead, code);
    gettimeofday(&t2, NULL);
    printf("list: %d ms\n", timediff(&t1, &t2));


    /*
    table = insert_array(cmdhead.next);

    gettimeofday(&t1, NULL);
     for(i=0; i<100000; i++)
         p1 = table[code];
     gettimeofday(&t2, NULL);
     printf("hash: %d ms\n", timediff(&t1, &t2));
     */


    ltable = insert_linkhash(cmdhead.next);

    if(lh_table_lookup_ex(ltable, code, &p1) == NULL) {
        printf("not found\n");
    }else{
        while(p1 != NULL) {
            printf("cmd %d, order: %d, serial: %d\n", p1->cmdcode, p1->ordercode, p1->serial);
            p1 = p1->next;
        }
    }

    gettimeofday(&t1, NULL);
     for(i=0; i<100000; i++)
         lh_table_lookup_ex(ltable, code, &p1);
     gettimeofday(&t2, NULL);
     printf("hash: %d ms\n", timediff(&t1, &t2));

    //lh_table_free(table);

    return 0;
}
