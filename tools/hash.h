/*创建hash表*/
void * hash_create(int size, int item_size);

/*压入数据*/
int hash_put(void *hash, char *key, void *value);

/*取数据*/
void *hash_get(void *hash, char *key);


/*删除一个节点*/
int hash_remove(void *hash, char *key);

/*清除整个hash表*/
void hash_clear(void *hash);


/*遍历hash表的所有节点*/
typedef void (*travel_func)(char *key, void *item, void *parm);
void hash_travel(void *hash, travel_func func, void *parm);
