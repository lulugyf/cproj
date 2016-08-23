#include <string.h>
#include <stdio.h>

#include <map>
#include <iostream>

using namespace std;

#define MAX_CFG_BUF 4096

static int is_blank(char c)
{
    return (c== ' ' || c == 0 || c == -1 || c == '\t'
			|| c == '\r' || c == '\n');
}

static char *Trim(char *ptr)
{
  int l, i;
  l = strlen(ptr);
  while(is_blank(ptr[l-1]) && l > 0) l--;
  ptr[l] = 0;
  i = 0;
  while(is_blank(ptr[i]) && i < l) i++;
  strcpy(ptr, ptr + i);
  return ptr;
}

/*
   Split key=val pair:
   xxx    =   yyyyyyyy
   |      |   |
   k1     k2  i
   return:
     1 --- ok
     0 --- blank line
    -1 --- no key, "= val"
    -2 --- only key, no '='

   M.L.Y  2000.8, 2000.11
*/
int  split_key_val(char *buf, char **key, char **val)
{
  int  i, k1, k2, n;

  if((n = strlen((char *)buf)) < 1) return 0;
  for(i = 0; i < n; i++)
    if(buf[i] != ' ' && buf[i] != '\t') break;
  if(i >= n) return 0;
  if(buf[i] == '=') return -1;
  k1 = i;
  for(i++; i < n; i++)
    if(buf[i] == '=') break;
  if(i >= n) return -2;
  k2 = i;
  for(i++; i < n; i++)
    if(buf[i] != ' ' && buf[i] != '\t') break;
  buf[k2] = '\0';
  *key = buf + k1;
  *val = buf + i;
  return 1;
}



int cfg_get_keys(const char *CFG_file, const char *section, map<string, string> *amap)
{
	FILE *fp;
	char buf1[MAX_CFG_BUF + 1];
	char *key_ptr, *val_ptr;
	int  n, rc;

	if((fp = fopen(CFG_file, "r")) == NULL)
		return -10;

	while(1)                                       /* seek section */
	{
		rc = -12;
		if(fgets(buf1, MAX_CFG_BUF, fp) == NULL)
			break;
		rc = -1;
		n = strlen(Trim(buf1));
		if(n == 0 || buf1[0] == ';')
			continue;       /* blank/remarks line */
		rc = -14;
		if(n > 2 && ((buf1[0] == '[' && buf1[n-1] != ']') ||
                 (buf1[0] == '{' && buf1[n-1] != '}')))
			break;
		if(buf1[0] == '[' || buf1[0] == '{')
		{
			buf1[n-1] = 0x00;
			if(strcmp(buf1+1, section) == 0){
				rc = 0;
				break; /* section found */
			}
		}
	}
	if(rc != 0){
		fclose(fp);
		return 0;
	}
	while(1)
	{
		rc = -12;
		if(fgets(buf1, MAX_CFG_BUF, fp) == NULL)
			break;
		n = strlen(Trim(buf1));
		if(n == 0 || buf1[0] == ';')
			continue;       /* blank/remarks line */
		rc = -2;
		if(buf1[0] == '[' || buf1[0] == '{')
			break;                                     /* another section */

		rc = -14;
		if(split_key_val(buf1, &key_ptr, &val_ptr) != 1)
			continue;
		Trim(key_ptr);
		Trim(val_ptr);
		amap->insert(std::pair<string, string>(key_ptr, val_ptr));
	}
	if(fp != NULL)
		fclose(fp);
	return 0;
}

