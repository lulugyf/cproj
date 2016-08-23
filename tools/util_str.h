#ifndef _UTIL_STR_H_
#define _UTIL_STR_H_

void rtrim(char *str, int n);
char *trim(char *ptr);
void sreplace(char *src, char *dest, const char *s1, const char *s2);
int substring(char *dst, char *src, char chip, int fld);
int split(char *string, char *fields[], int nfields, char *sep);
char *strcasestr(const char *str, const char *sub);

#endif /*_UTIL_STR_H_*/
