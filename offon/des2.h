/* DES.H

   Data Encrypt Stand (DES����)

*/

#if !defined (__DES_H)
#define    __DES_H

#ifndef   ENCRYPT     /* DES ���� */
#define   ENCRYPT  1
#define   DECRYPT  0
#endif

#ifndef   MAC        /* MAC ��׼ */
#define   MAC_ST            0
#define   MAC_STAND         1
#define   MAC_BPI           2
#endif

/* DES�㷨
   ����:
      op       -- 0,����; ����, ����
      key      -- ��Կ
      inblock  -- Դ��
      outblock -- Ŀ�Ĵ�
      len      -- ��/���ܵĴ�����
   ����: ʵ�ʼ�/���ܵĳ���
   ע��:
       len���Ϊ8��������, outblock���ȱ�����ڵ���len
*/
int DES(int op, char *key, char *inblock, char *outblock, int len);


/* MAC�㷨:
   ST�㷨:
       ��"00000000"�����ݽ���8�ֽ����, �����ݳ��Ȳ�Ϊ8��������, ����
       ���ַ�0x00, �����Ľ���뵱ǰ��Կ����DES��������.
   Stand:
       ��"\0\0\0\0\0\0\0\0"�����ݽ���8�ֽ����, ���Ľ������DES������Ϊ
       �´����ĳ�ֵ, �����ݳ��Ȳ�Ϊ8��������, ������ַ�0x00.
   BPI:
       ��"\0\0\0\0\0\0\0\0"�����ݽ���8�ֽ����, �����ݳ��Ȳ�Ϊ8��������,
       ������ַ�0x00, �����Ľ���뵱ǰ��Կ����DES��������.
*/
/*����MACУ��*/
char *GenerateMAC(int method, char *databuf, int datalen, char *key, char *MAC);

/*
 * BCD��ת��ΪASCII��, ��0
 * ����: dest   -- Ŀ�Ļ�����
 *       src    -- Դ������
 *       length -- ����
 * ������: 0    -- �ɹ�
 */
int BcdToAsc_(unsigned char *dest, unsigned char *src, int length);


/*
 * ASCII��ת��ΪBCD��, ��0
 * ����: dest   -- Ŀ�Ļ�����
 *       src    -- Դ������
 *       length -- ����
 * ������: 0    -- �ɹ�
 *        -1    -- Դ�����޷�ת��ΪBCD��
 */
int AscToBcd_(unsigned char *dest, unsigned char *src, int length);

void  Do_XOR(char *dest, char *source, int size);

/*
 * ����һ��8�ֽڵ�����ַ���
 */
void GenNewKey(char *key);

/*
 * ��ȡϵͳ����
 */
char *GetSysDate();

/*
 * ��ȡϵͳʱ��
 */
char *GetSysTime();

/*
 * ɾ���ַ�����ǰ��ո�
 */
char *alltrim(char *str);

#endif
