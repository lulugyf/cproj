#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "hash.h"
#include "mempool.h"

#define HASH_SEED 23464


int timecheck(int beg, int tt)
{
    static int i = 0;
    static struct timeval tt1, tt2;
    static int t = 0;


    if(beg == 0){
        gettimeofday(&tt1, NULL);
    }else{
        i++;
        gettimeofday(&tt2, NULL);
        t += (tt2.tv_sec - tt1.tv_sec )*1000000 + (tt2.tv_usec- tt1.tv_usec);
        if(i % tt == 0){
            printf("average time: %d\n", t/i);
            i = 0;
            t = 0;
        }
    }    
}

struct hashstru
{
    char key[50];
    struct hashstru *next;
    void *data;
};

struct hashtable
{
    int size;
    int item_size;
    cp_mempool *pool;
    struct hashstru **ptr;
};



int hash_mkey(struct hashtable *h, char *key)
{
    unsigned int l, i, r;

    l = strlen(key);
    r = 0;
    for(i=0; i<l; i++){
        r += (unsigned char)key[i] + i*HASH_SEED;
    }
    return r % h->size;
}





/*创建hash表*/
void * hash_create(int size, int item_size)
{
    struct hashtable *h;
    char *ptr;
    int len;

    len = sizeof(struct hashtable) + sizeof(struct hashstru *)*size;
    printf("create len[%d]\n", len);
    ptr = (char *)malloc(len);
    memset(ptr, 0, len);

    h = (struct hashtable *)ptr;
    h->pool = cp_mempool_create_by_option(0, sizeof(struct hashstru)+item_size, size);
    h->item_size = item_size;

    h->size = size;
    h->ptr = (struct hashstru *)(ptr + sizeof(struct hashtable));

    return (void *)ptr;
}

/*压入数据*/
int hash_put(void *hash, char *key, void *value)
{
    struct hashtable *h;
    struct hashstru *p;
    int ikey;

    h = (struct hashtable *)hash;

    ikey = hash_mkey(h, key);
    //printf("ikey[%d]\n", ikey);

    p = h->ptr[ikey];

    if(p == NULL){ /*节点无数据, 直接新加*/
            p = (struct hashstru *)cp_mempool_alloc(h->pool);
            p->data = (void *)(((char *)p) + sizeof(struct hashstru));
        p->next = NULL;
        h->ptr[ikey] = p;
        strcpy(p->key, key);
        memcpy(p->data, value, h->item_size);
    }else{
        int flag;
        int k;

        flag = 0; /*是否找到相同 key 的节点*/
        /*k = 0;
        while(p != NULL){
            if(strcmp(key, p->key) == 0){ //有相同的key, 替换
                memcpy(p->data, value, h->item_size);
                flag = 1;
                break;
            }
            k ++;
            p = p->next;
        }
        //printf("list size:%d\n", k);
        */
        if(flag == 0){ /*没有相同的key, 新加*/
            p = (struct hashstru *)cp_mempool_alloc(h->pool);
            p->data = (void *)(((char *)p) + sizeof(struct hashstru));
            p->next = h->ptr[ikey];
            h->ptr[ikey] = p;
            strcpy(p->key, key);
            memcpy(p->data, value, h->item_size);
        }
    }

    return 0;
}

/*取数据*/
void *hash_get(void *hash, char *key)
{
    struct hashtable *h;
    struct hashstru *p;
    int ikey;

    h = (struct hashtable *)hash;
    ikey = hash_mkey(h, key);

    p = h->ptr[ikey];
    while(p != NULL){
        if(strcmp(p->key, key) == 0)
            return p->data;
        p = p->next;
    }

    return NULL;
}

/*删除一个节点*/
int hash_remove(void *hash, char *key){
    struct hashtable *h;
    struct hashstru *p, *p1;
    int ikey;

    h = (struct hashtable *)hash;
    ikey = hash_mkey(h, key);

    p = h->ptr[ikey];
    p1 = p;
    while(p != NULL){
        if(strcmp(p->key, key) == 0){
            if(p1 == p)
                h->ptr[ikey] = p->next;
            else
                p1->next = p->next;
            cp_mempool_free(h->pool, p);
            return 1;
        }
        p1 = p;
        p = p->next;
    }

    return 0;
}

void hash_clear(void *hash)
{
    struct hashtable *h;
    struct hashstru *p, *p1;
    int i;

    h = (struct hashtable *)hash;

    for(i=0; i<h->size; i++){
        p = h->ptr[i];
        while(p != NULL){
            p1 = p->next;
            cp_mempool_free(h->pool, p);
            p = p1;
        }
    }
    cp_mempool_destroy(h->pool);
    free(hash);
}


void hash_travel(void *hash, travel_func func, void *parm)
{
    struct hashtable *h;
    struct hashstru *p, *p1;
    int i;

    h = (struct hashtable *)hash;

    for(i=0; i<h->size; i++){
        p = h->ptr[i];
        while(p != NULL){
            p1 = p->next;
            func(p->key, p->data, parm);
            p = p1;
        }
    }
}

#ifdef __TEST__

void myprint(void *key, void *item, void *parm)
{
    FILE *fp;

    fp = (FILE *)parm;
    fprintf(fp, "%s:%s\n", (char *)key, (char *)item);
}

int main(int argc, char *argv[])
{
    char *hash;
    char *p, key[20], value[30];
    int i;
    struct timeval tt1, tt2;
    FILE *fp;

    hash = hash_create(1000000, 30);

    printf("create h[%x]\n", hash);

    gettimeofday(&tt1, NULL);
    srand(time(0));
    for(i=0; i<10000000; i++){
        sprintf(key, "mykey%d", i);
        sprintf(value, "myvalue%d", rand());
        //printf("key[%s] value[%s]\n", key, value);

        hash_put(hash, key, value);

        if(i % 10000 == 0)
            printf("iii[%d]\n", i);
    }
    gettimeofday(&tt2, NULL);

    printf("put time val[%d]\n",
        (tt2.tv_sec - tt1.tv_sec )*1000000 + (tt2.tv_usec- tt1.tv_usec));


    for(i=0; i<10001; i++){
        sprintf(key, "mykey%d", rand()%10000000);
        timecheck(0, 50);
        p = hash_get(hash, key);
        timecheck(1, 50);
    }

    fp = fopen("data.txt", "w");
    hash_travel(hash, myprint, fp);
    fclose(fp);

    hash_clear(hash);

    return 0;
}

#endif /*__TEST__*/

