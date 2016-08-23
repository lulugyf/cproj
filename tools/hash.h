/*����hash��*/
void * hash_create(int size, int item_size);

/*ѹ������*/
int hash_put(void *hash, char *key, void *value);

/*ȡ����*/
void *hash_get(void *hash, char *key);


/*ɾ��һ���ڵ�*/
int hash_remove(void *hash, char *key);

/*�������hash��*/
void hash_clear(void *hash);


/*����hash������нڵ�*/
typedef void (*travel_func)(char *key, void *item, void *parm);
void hash_travel(void *hash, travel_func func, void *parm);
