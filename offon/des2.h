/* DES.H

   Data Encrypt Stand (DES加密)

*/

#if !defined (__DES_H)
#define    __DES_H

#ifndef   ENCRYPT     /* DES 方向 */
#define   ENCRYPT  1
#define   DECRYPT  0
#endif

#ifndef   MAC        /* MAC 标准 */
#define   MAC_ST            0
#define   MAC_STAND         1
#define   MAC_BPI           2
#endif

/* DES算法
   参数:
      op       -- 0,加密; 非零, 解密
      key      -- 密钥
      inblock  -- 源串
      outblock -- 目的串
      len      -- 加/解密的串长度
   返回: 实际加/解密的长度
   注意:
       len最好为8的整数倍, outblock长度必须大于等于len
*/
int DES(int op, char *key, char *inblock, char *outblock, int len);


/* MAC算法:
   ST算法:
       串"00000000"与数据进行8字节异或, 若数据长度不为8的整数倍, 则添
       空字符0x00, 将异或的结果与当前密钥进行DES运算生成.
   Stand:
       串"\0\0\0\0\0\0\0\0"与数据进行8字节异或, 异或的结果进行DES运算作为
       下次异或的初值, 若数据长度不为8的整数倍, 则添空字符0x00.
   BPI:
       串"\0\0\0\0\0\0\0\0"与数据进行8字节异或, 若数据长度不为8的整数倍,
       则添空字符0x00, 将异或的结果与当前密钥进行DES运算生成.
*/
/*生成MAC校验*/
char *GenerateMAC(int method, char *databuf, int datalen, char *key, char *MAC);

/*
 * BCD码转换为ASCII码, 后补0
 * 参数: dest   -- 目的缓冲区
 *       src    -- 源缓冲区
 *       length -- 长度
 * 返回码: 0    -- 成功
 */
int BcdToAsc_(unsigned char *dest, unsigned char *src, int length);


/*
 * ASCII码转换为BCD码, 后补0
 * 参数: dest   -- 目的缓冲区
 *       src    -- 源缓冲区
 *       length -- 长度
 * 返回码: 0    -- 成功
 *        -1    -- 源数据无法转换为BCD码
 */
int AscToBcd_(unsigned char *dest, unsigned char *src, int length);

void  Do_XOR(char *dest, char *source, int size);

/*
 * 产生一个8字节的随机字符串
 */
void GenNewKey(char *key);

/*
 * 获取系统日期
 */
char *GetSysDate();

/*
 * 获取系统时间
 */
char *GetSysTime();

/*
 * 删除字符串的前后空格
 */
char *alltrim(char *str);

#endif
