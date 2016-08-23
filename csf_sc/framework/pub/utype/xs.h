

#include <stdlib.h>

typedef int (*attrib_hook_f)(void* data, void* load, void** save, int level,
							const char* tagname, size_t len,
							const char* attname, size_t len2,
							const char* attvalue, size_t len3);
typedef int (*value_hook_f)(void* data, void* load, void** save, int level,
							const char* tagname, size_t len,
							const char* value, size_t len2);
typedef int (*enter_hook_f)(void* data, void* load, void** save, int level,
							const char* tagname, size_t len);
typedef int (*leave_hook_f)(void* data, void* load, void** save, int level,
							const char* tagname, size_t len);
const char* xs_strerr(int error);
int xs_engine(const char* s, size_t maxbuf, void* data, attrib_hook_f mh, enter_hook_f eh, leave_hook_f lh, attrib_hook_f ah, value_hook_f vh);
int xs_speccpy(char* dst, size_t dst_len, const char* src, size_t src_len);



