#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include <curl/curl.h>

int cal_tm(struct timeval *t1, struct timeval *t2){
        return (int)((t2->tv_sec - t1->tv_sec) * 1000 + (t2->tv_usec-t1->tv_usec) / 1000);
}

typedef struct __out_data{
  int  len;
  char *ptr;
} DT;

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  DT *p = (DT *)stream;
  size_t n = size * nmemb;
  if(p->ptr == NULL){
        p->ptr = malloc(n+1);
        p->len = 0;
  }else{
        p->ptr = realloc(p->ptr, p->len + n + 1);
  }
  /*printf("cur_len=%d newbytes=%ld\n", p->len, n); */
  memcpy(p->ptr + p->len, ptr, n);
  p->len += n;
  p->ptr[p->len] = 0;

  return n;
}

int onece(const char *url, const char *indata, char **outdata)
{
	CURL *curl_handle;
	DT data; //for output
	struct curl_slist *headers=NULL;
	int retcode;
	
	size_t inlen = strlen(indata);
	
	*outdata = NULL;

	data.ptr = NULL;
	data.len = 0;
	curl_global_init(CURL_GLOBAL_ALL);

	curl_handle = curl_easy_init();

	curl_easy_setopt(curl_handle, CURLOPT_URL, url);

	headers = curl_slist_append(headers, "Content-Type: application/json");
	curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, indata);
	curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDSIZE, inlen);
	curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, headers); 

	curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

	/* we want the headers be written to this file handle 
	curl_easy_setopt(curl_handle,   CURLOPT_WRITEHEADER, headerfile);*/

	curl_easy_setopt(curl_handle,   CURLOPT_WRITEDATA, &data);
	retcode = curl_easy_perform(curl_handle);
	if(retcode != 0){
		/*failed*/
		printf("perform failed, return %d\n", retcode);
	}else{
		*outdata = data.ptr;
	}

	/* cleanup curl stuff */
	curl_easy_cleanup(curl_handle);
	/*printf("INPUT[%s]\n", indata);
	printf("OUTPUT[%s]\n", (char *)data.ptr); 
	free(data.ptr);*/

	return retcode;
}

int main(int argc, char *argv[])
{
	char *outdata;
	int ret, i, count;
	const int verbose = 0;
	struct timeval t1, t2;
	const char *url = "http://172.21.1.30:51900/esbWS/rest/sCustInfoValid";
	const char *indata = "{ \"ROOT\": { \"HEADER\": { \"ROUTING\": { \"ROUTE_KEY\": \"10\", \"ROUTE_VALUE\": \"15799881753\" }, \"POOL_ID\": \"10\", \"CHANNEL_ID\": \"02\" }, \"BODY\": { \"PHONE_NO\": \"15799881753\", \"TEST\": \"ÖÐÎÄ²âÊÔ\" } } }";
  
	if(argc > 2){
		url = argv[1];
		indata = argv[2];
	}
	count = 1;
	if(argc > 3)
		count = atoi(argv[3]);
	if(argc > 4)
		if(argv[4][0] == 'v' || argv[4][0] == 'V')
			verbose = 1;
	
	if(verbose)
		printf("INPUT[%s]\n", indata);
	
	for(i=0; i<count; i++){
		gettimeofday(&t1, NULL);
		ret = onece(url, indata, &outdata);
		gettimeofday(&t2, NULL);
		if(ret != 0){
			printf("FAIL, ret=%d, TM=%d(ms)\n", ret, cal_tm(&t1, &t2));
		}else{
			printf("SUCC, tm=%d(ms)\n", cal_tm(&t1, &t2));
			if(verbose)
				printf("OUTPUT[%s]\n", outdata);
			free(outdata);
		}
	}

	return 0;
}