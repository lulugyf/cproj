
struct hlrdul_item{
    char hlrcode[4];
    int  dpt;
    int  rpt;
    char status;
    char dip[16];
    int  rcv_q_len;
    int  wfile_idx; /*������м��ļ��ĵ�ǰ���*/
    int  rfile_idx; /*��ȡ�ļ����*/
    int  rfile_pos; /*��ȡλ��*/ 
    char reserv[44];
};

extern struct hlrdul_item *local_item;

