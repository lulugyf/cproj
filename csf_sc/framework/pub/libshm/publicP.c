#include "publicsrv.h"

extern int errno;

/* ��ӡ�������� */
/***************************************
name:     Pinitprint							    
writer:   zhaohao           					
modi:     zhaohao           					
date:     2001.11.2       						
function: ������ƴ�ӡ��ʽ						
****************************************************************************/
void Pinitprint()
{
	/* enter control_print mode */
	putchar(27);
	putchar('[');
	putchar('/');
	putchar('5');
	putchar('i');

	/* set word_distance to 1 */
	putchar(27);
	putchar('[');
	putchar('/');
	putchar('1');
	putchar('U');

	/* set row_distance to 10 */
	putchar(27);
	putchar('[');
	putchar('/');
	putchar('1');
	putchar('0');
	putchar('V');

	/* set enlarge to vertical and horizontal */
	putchar(27);
	putchar('[');
	putchar('/');
	putchar('3');
	putchar('T');

	/* set director to horizontal */
	putchar(27);
	putchar('[');
	putchar('/');
	putchar('6');
	putchar('T');

	/* set print_mode to normal */
	putchar(27);
	putchar('[');
	putchar('/');
	putchar('7');
	putchar('T');

	/* set printer_type to OKI */
	putchar(27);
	putchar('[');
	putchar('/');
	putchar('7');
	putchar('t');

	/* set array to 24*24 */
	/*
	putchar(27);
	putchar('[');
	putchar('/');
	putchar('2');
	putchar('3');
	putchar('h');
	*/
}

/***************************************
name:     Pendprint							    
writer:   zhaohao           					
modi:     zhaohao           					
date:     2001.11.2       						
function: �˳����ƴ�ӡ��ʽ						
****************************************************************************/
void Pendprint()
{
        putchar(27);
        putchar('[');
        putchar('/');
        putchar('4');
        putchar('i');
}

/******************************************
 name:     Pcancelprint							     
 writer:   zhaohao           						 
 modi:     zhaohao           						 
 date:     2001.11.2       						   
 function: ȡ�����ƴ�ӡ��ʽ						   
*****************************************************************************/
void Pcancelprint()
{
	putchar(12);
}

/****************************************
name:     Pinitprintbright						 
writer:   zhaohao           						
modi:     zhaohao           						
date:     2001.11.2       						 
function: ����͸����ӡ��ʽ						 
****************************************************************************/
void Pinitprintbright()
{
       putchar(27);
       putchar('[');
       putchar('5');
       putchar('i');
       putchar(27);
       putchar('@');
}

/*****************************************
 name:     Pendprintbright						  
 writer:   zhaohao           						
 modi:     zhaohao           						
 date:     2001.11.2       						  
 function: �˳�͸����ӡ��ʽ						  
*****************************************************************************/
void Pendprintbright()
{
        putchar(27);
        putchar('[');
        putchar('4');
        putchar('i');
}
