#include <stdio.h>
#include <string.h>

#include "util_str.h"

int isBlankChar(char c){
	switch(c){
		case ' ':
		case '\0':
		case -1:
		case '\t':
		case '\r':
		case '\n':
			return 1;
		default:
			return 0;
	}
}

void rtrim(char *str, int n)
{
	n = strlen(str);
    for( ;n>=0; n--){
        if(isBlankChar(str[n])){
        	str[n] = '\0';
        }else{
            break;
        }
    }
}

char *trim(char *ptr)
{
  int l, i;
  l = strlen(ptr);
  while(isBlankChar(ptr[l-1]) && l > 0) l--;
  ptr[l] = 0;
  i = 0;
  while(isBlankChar(ptr[i]) && i < l) i++;
  strcpy(ptr, ptr + i);
  return ptr;
}

void sreplace(char *src, char *dest, const char *s1, const char *s2){
        int l1, l2;
        char *tmp, *sptr;
        l1 = strlen(s1);
        l2 = strlen(s2);

        if(l1 == 0){
                strcpy(dest, src);
                return;
        }

        sptr = src;
        dest[0] = 0;
        while( (tmp = strstr(sptr, s1) ) > 0){
                strncat(dest, sptr, tmp-sptr);
                strcat(dest, s2);
                sptr = tmp + l1;
        }
        strcat(dest, sptr);
}

/*字符串分段提取 以 chip 作为分隔符， 将 src 中的第 fld 段放在 dst 中*/
int substring(char *dst, char *src, char chip, int fld){
        char *ptr, *ptr1;
        ptr1 = ptr = src;
        while(fld > 1 && (ptr1 = strchr(ptr, chip)) > 0){
                ptr = ptr1 + 1;
                fld --;
        }
        if(fld > 1)
                return 0;
        ptr1 = strchr(ptr, chip);
        if(ptr1 <= 0){
                strcpy(dst, ptr);
        }else{
                strncpy(dst, ptr, ptr1-ptr);
                dst[ptr1-ptr] = '\0';
        }
        return 1;
}

/*
 - split - divide a string into fields, like awk split()
 = int split(char *string, char *fields[], int nfields, char *sep);
 */
int split(char *string, char *fields[], int nfields, char *sep)
{
	char *p = string;
	char c;                        /* latest character */
	char sepc;
	char sepc2;
	int fn;
	char **fp;
	char *sepp;
	int trimtrail;
	
	sepc = sep[0];
	fp = fields;
        /* white space */
        if (sepc == '\0') {
                while ((c = *p++) == ' ' || c == '\t')
                        continue;
                p--;
                trimtrail = 1;
                sep = " \t";    /* note, code below knows this is 2 long */
                sepc = ' ';
        } else
                trimtrail = 0;
        sepc2 = sep[1];         /* now we can safely pick this up */

        /* catch empties */
        if (*p == '\0')
                return(0);

        /* single separator */
        if (sepc2 == '\0') {
                fn = nfields;
                for (;;) {
                        *fp++ = p;
                        fn--;
                        if (fn == 0)
                                break;
                        while ((c = *p++) != sepc)
                                if (c == '\0')
                                        return(nfields - fn);
                        *(p-1) = '\0';
                }
                /* we have overflowed the fields vector -- just count them */
                fn = nfields;
                for (;;) {
                        while ((c = *p++) != sepc)
                                if (c == '\0')
                                        return(fn);
                        fn++;
                }
                /* not reached */
        }

        /* two separators */
        if (sep[2] == '\0') {
                fn = nfields;
                for (;;) {
                        *fp++ = p;
                        fn--;
                        while ((c = *p++) != sepc && c != sepc2)
                                if (c == '\0') {
                                        if (trimtrail && **(fp-1) == '\0')
                                                fn++;
                                        return(nfields - fn);
                                }
                        if (fn == 0)
                                break;
                        *(p-1) = '\0';
                        while ((c = *p++) == sepc || c == sepc2)
                                continue;
                        p--;
                }
                /* we have overflowed the fields vector -- just count them */
                fn = nfields;
                while (c != '\0') {
                        while ((c = *p++) == sepc || c == sepc2)
                                continue;
                        p--;
                        fn++;
                        while ((c = *p++) != '\0' && c != sepc && c != sepc2)
                                continue;
                }
                /* might have to trim trailing white space */
                if (trimtrail) {
                        p--;
                        while ((c = *--p) == sepc || c == sepc2)
                                continue;
                        p++;
                        if (*p != '\0') {
                                if (fn == nfields+1)
                                        *p = '\0';
                                fn--;
                        }
                }
                return(fn);
        }

        /* n separators */
        fn = 0;
        for (;;) {
                if (fn < nfields)
                        *fp++ = p;
                fn++;
                for (;;) {
                        c = *p++;
                        if (c == '\0')
                                return(fn);
                        sepp = sep;
                        while ((sepc = *sepp++) != '\0' && sepc != c)
                                continue;
                        if (sepc != '\0')       /* it was a separator */
                                break;
                }
                if (fn < nfields)
                        *(p-1) = '\0';
                for (;;) {
                        c = *p++;
                        sepp = sep;
                        while ((sepc = *sepp++) != '\0' && sepc != c)
                                continue;
                        if (sepc == '\0')       /* it wasn't a separator */
                                break;
                }
                p--;
        }

        /* not reached */
}

/*case-insensitive version of strstr*/
char *strcasestr(const char *str, const char *sub)
{
	int l1, l2, i, j;
	
	l1 = strlen(str);
	l2 = strlen(sub);
	for(i=0, j=0; i<l1; i++){
		if(toupper(str[i]) == toupper(sub[j]))
			j++;
		else
			j = 0;
		if(j == l2)
			return (char *)(str + i - j + 1);
	}
	return (char *)NULL;
}
