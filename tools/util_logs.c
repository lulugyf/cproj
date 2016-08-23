#include <stdarg.h>
#include <stdio.h>
#include <time.h>

#define __DEBUG

void file_log(char *log_file, char *fmt, ...)
{
	va_list args;
	FILE	*fp;
	char filename[128];
	char tmpstr[256];
	long t;
	struct tm *ttt;

	time(&t);
	ttt = localtime(&t);

	/* file name $WORKDIR/log/log_file.yymmdd */
	sprintf(filename, "%s/log/%s.%04d%02d%02d", 
		getenv("WORKDIR"),
		log_file,
		ttt->tm_year+1900, ttt->tm_mon+1, ttt->tm_mday);
	fp=fopen(filename,"a");
	if(fp == 0) return;

	/*content format:  hh:mm:ss, content*/
	fprintf(fp,"%02d:%02d:%02d, ",
		ttt->tm_hour,ttt->tm_min,ttt->tm_sec);

	/* write content */
	va_start(args, fmt);
	vfprintf(fp,fmt,args);
	va_end(args);
	fprintf(fp, "\n");

	fclose(fp);

	return;
}

char *get_cur_month(){
	time_t v_time;
	struct tm *v_tm;
	static char v_asctime[20];

	v_time = time(0);
	v_tm = localtime(&v_time);
	sprintf(v_asctime, "%04d%02d",
		v_tm->tm_year+1900,
		v_tm->tm_mon+1);
	return (char *)v_asctime;
}


char *logtime(){
	time_t v_time;
	struct tm *v_tm;
	static char v_asctime[50];

	v_time = time(0);
	v_tm = localtime(&v_time);
	sprintf(v_asctime, "%04d%02d%02d %02d:%02d:%02d",
		v_tm->tm_year+1900,
		v_tm->tm_mon+1,
		v_tm->tm_mday,
		v_tm->tm_hour,
		v_tm->tm_min,
		v_tm->tm_sec);
	return (char *)v_asctime;
}

void stdout_log(const char *fmt, ...){
#ifdef __DEBUG
	static char msg_buf[1024];
	va_list arglist;
	time_t tt;
	
	tt = time(0);
	va_start(arglist, fmt);
	vsprintf(msg_buf, fmt, arglist);
	va_end(arglist);
	
	fprintf(stdout, "%s,%s\n", logtime(), msg_buf);
#endif
}

