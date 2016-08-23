#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <time.h>

#include "des2.h"


void Do_XOR(char *dest, char *source, int size)
{
    int i;

    for (i = 0; i < size; i++)
        dest[i] ^= source[i];
}

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
char *GenerateMAC(int method, char *databuf, int datalen, char *key, char *MAC)
{
    int size = 0;

    if (method == MAC_ST)
        memcpy(MAC, "00000000", 8);
    else
        memset(MAC, '\0', 8);

    while (datalen > size)
    {
        if (datalen - size <= 8)
        {
            Do_XOR(MAC, &databuf[size], datalen - size);
            DES(ENCRYPT, key, MAC, MAC, 8);
            return MAC;
        }

        Do_XOR(MAC, &databuf[size], 8);

        if (method == MAC_STAND)
            DES(ENCRYPT, key, MAC, MAC, 8);

        size += 8;
    }

    return MAC;
}



/*
 * ASCII码转换为BCD码, 后补0
 * 参数: dest   -- 目的缓冲区
 *       src    -- 源缓冲区
 *       length -- 长度
 * 返回码: 0    -- 成功
 *        -1    -- 源数据无法转换为BCD码
 */
int AscToBcd_(unsigned char *dest, unsigned char *src, int length)
{
    int i;

    for (i = 0; i < length / 2; i++)
    {
        if (src[2 * i] >= '0' && src[2 * i] <= '9')
            dest[i] = (src[2 * i] - '0') << 4;
        else
        if (src[2 * i] >= 'A' && src[2 * i] <= 'F')
            dest[i] = (src[2 * i] - 'A' + 10) << 4;
        else
        if (src[2 * i] >= 'a' && src[2 * i] <= 'f')
            dest[i] = (src[2 * i] - 'a' + 10) << 4;
        else
            return -1;

        if (src[2 * i + 1] >= '0' && src[2 * i + 1] <= '9')
            dest[i] += src[2 * i + 1] - '0';
        else
        if (src[2 * i + 1] >= 'A' && src[2 * i+ 1] <= 'F')
            dest[i] += src[2 * i + 1] - 'A' + 10;
        else
        if (src[2 * i + 1] >= 'a' && src[2 * i+ 1] <= 'f')
            dest[i] += src[2 * i + 1] - 'a' + 10;
        else
            return -1;
    }

    if (length % 2 != 0)
    {
        if (src[length - 1] >= '0' && src[length - 1] <= '9')
            dest[(length + 1) / 2 - 1] = (src[length - 1] - '0') << 4;
        else
        if (src[length - 1] >= 'A' && src[length - 1] <= 'F')
            dest[(length + 1) / 2 - 1] = (src[length - 1] - 'A' + 10) << 4;
        else
        if (src[length - 1] >= 'a' && src[length - 1] <= 'f')
            dest[(length + 1) / 2 - 1] = (src[length - 1] - 'a' + 10) << 4;
        else
            return -1;
    }

    return 0;
}

/*
 * BCD码转换为ASCII码, 后补0
 * 参数: dest   -- 目的缓冲区
 *       src    -- 源缓冲区
 *       length -- 长度
 * 返回码: 0    -- 成功
 */
int BcdToAsc_(unsigned char *dest, unsigned char *src, int length)
{
    char ascii_table[16] =
    {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };
    int i;

    for (i = 0; i < length / 2; i++)
    {
        dest[2 * i] = ascii_table[src[i] >> 4];
        dest[2 * i + 1] = ascii_table[src[i] & 0x0F];
    }

    if (length % 2 != 0)
        dest[length - 1] = ascii_table[src[(length + 1) / 2 - 1] >> 4];

    return 0;
}

int bcd_encode(unsigned char *dest, unsigned char *src, int length){
        return BcdToAsc_(dest, src, length);
}

int bcd_decode(unsigned char *dest, unsigned char *src, int length){
        return AscToBcd_(dest, src, length);
}




/*
 * 产生一个随机数
 */
void GenNewKey(char *key)
{
    long randnum;
    time_t t;

    srand((unsigned)time(&t));
    randnum = rand() % 10000;
    randnum *= 10000;
    randnum += rand() % 10000;
    sprintf(key, "%08ld", randnum);
}

/*
 * 获取系统日期
 */
char *GetSysDate()
{
    time_t tm;
    static char date[9];
    
    tm = time(NULL);
    strftime(date, 9, "%Y%m%d", localtime(&tm));
    return date;
}

/*
 * 获取系统时间
 */
char *GetSysTime()
{
    time_t tm;
    static char systime[7];
    
    tm = time(NULL);
    strftime(systime, 7, "%H%M%S", localtime(&tm));
    return systime;
}

/*
 * 删除前后空格
 */
char *alltrim(char *str)
{
    static char buffer[81];
    int i, j, k;

    for (i = 0; str[i] == ' ' && str[i] != '\0'; i++);
    for (j = strlen(str) - 1; str[j] == ' ' && j >= 0 ; j--);

    for (k = 0; k <= j - i; k++)
        buffer[k] = str[k + i];
    buffer[k] = '\0';

    return buffer;
}

/*生成8位随机数, 然后以 BCD 编码, 返回 16 字节的串
flag: 1 return bcd码; 2 return char; 3 return digits
*/
char *get_randstr(char *buf, int len, int flag)
{
    static char *basechars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    static char *digits = "0123456789";
    static int init = 0;
    unsigned char x[50];
    int i;

    if(init == 0){
        srand(time(0));
        init = 1;
    }
    if(flag == 1){
        for(i=0; i<len; i++){
            x[i] = rand() % 256;
        }
        bcd_encode(buf, x, len*2);
        buf[len*2] = 0;
    }else if(flag == 2){
        for(i=0; i<len; i++){
            buf[i] = basechars[rand() % 62];
        }
        buf[len] = 0;
    }else if(flag == 2){
        for(i=0; i<len; i++){
            buf[i] = digits[rand() % 10];
        }
        buf[len] = 0;
    }

    return buf;
}
