
#include <limits.h>
#ifdef CHAR_BIT
# if CHAR_BIT!=8
#  error "Number of bits in a char is not 8."
# endif
#else
# error "Macro CHAR_BIT is not define."
#endif


#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define LOAD_PTR(a, n) ((n)==0?NULL:((a)[(n)-1]))
#define MAX_STACK_LEVEL 100
#define PUSH(a, s, len) \
	{int n=((a)->top)++;(a)->tagname[n]=s, (a)->taglen[n]=(len); \
	(a)->eh((a)->data, LOAD_PTR((a)->save, n), &((a)->save[n]), n, (a)->tagname[n], (a)->taglen[n]);}
#define POP(a) \
	{int n=--((a)->top);\
	(a)->lh((a)->data, LOAD_PTR((a)->save, n), &((a)->save[n]), n, (a)->tagname[n], (a)->taglen[n]); \
	(a)->tagname[n]=NULL, (a)->taglen[n]=0, (a)->save[n]=NULL;}

#define DICT_ITEM(a, b) {a, sizeof(a)-1, b}

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

typedef struct xml_parse{
	const char* tagname[MAX_STACK_LEVEL];
	void* save[MAX_STACK_LEVEL];
	size_t taglen[MAX_STACK_LEVEL];
	int top;
	void* data;
	value_hook_f vh;
	attrib_hook_f ah;
	attrib_hook_f mh;
	enter_hook_f eh;
	leave_hook_f lh;
} t_xml_parse;

typedef struct tcitem{
	const char* s;
	size_t len;
	char c;
} t_tcitem;


t_tcitem dict[]={DICT_ITEM("&lt;", '<'), DICT_ITEM("&gt;", '>'), DICT_ITEM("&amp;", '&'), DICT_ITEM("&apos;", '\''), DICT_ITEM("&quot;", '"')};

#define RTOK						0
#define ERR_BASE					-3000
#define ERR_OTHER_INTAGS			ERR_BASE-1  //有其他字符出现在标签间
#define ERR_UNEXPECT_END			ERR_BASE-2  //xml文件意外结束，或意外的出现了>
#define ERR_END_TAG_MISMATCH		ERR_BASE-3  //标签必须成对出现
#define ERR_EMPTY_TAG				ERR_BASE-4  //空标签
#define ERR_TAG_NAME				ERR_BASE-5  //标签名包含非法字符
#define ERR_QUOTES_OPEN				ERR_BASE-6  //引号未结束
#define ERR_ATTRIBUTE_FMT			ERR_BASE-7  //属性格式错误，未包含等号
#define ERR_ATTRIBUTE_HOOK			ERR_BASE-8  //属性回调函数调用失败
#define ERR_FIRST_CHAR				ERR_BASE-9	//第一个有效字符不是<
#define ERR_HEAD_END_FMT			ERR_BASE-10	//头部的格式不正确，缺少结束的问号
#define ERR_MEM_ALLOC				ERR_BASE-11	//内存分配失败
#define ERR_ATTRVALUE_NO_QUOTES		ERR_BASE-12
#define ERR_UNKNOW_TAG				ERR_BASE-13

//>0中间有其他字符
//=0无特殊字符
//<0找不到下一个tag
static int next_tag(const char* xmlstr, const char* maxend, const char** c)
{
	int i=0, hasother=0;

	for(i=0;xmlstr+i<maxend&&xmlstr[i]!=0;i++){
		if(xmlstr[i]=='>') return -2;
		else if(xmlstr[i]=='<'){
			*c=xmlstr+i;
			if(hasother) return 1;
			else return 0;
		}
		if(!hasother){
			if(xmlstr[i]!='<'&&xmlstr[i]!='\t'&&xmlstr[i]!=' '&&xmlstr[i]!='\r'&&xmlstr[i]!='\n'){
				hasother=1;
			}
		}
	}
	return -1;
}


static int next_word(const char* s1, size_t len, const char** begin, const char** end, int attr_flag)
{
	int qt=0, st=0, et=0;
	unsigned i=0;
	*begin=NULL;
	*end=NULL;
	if(attr_flag<=0) et=1;
	for(i=0;i<len;i++){
		if(s1[i]=='=') et=1;
		if(s1[i]=='"')
			qt=(qt+1)%2;
		else if(s1[i]=='\''&&qt==0)
			st=(st+1)%2;


		if(s1[i]=='\n'||s1[i]=='\r'||(s1[i]==' ')||s1[i]=='\t'||(s1[i]=='='&&attr_flag<0)){
			if(*begin&&qt==0&&st==0&&et==1&&attr_flag<=0){
				*end=s1+i;
				return 0;
			}
		}else{
			if(*begin==NULL){
				*begin=s1+i;
			}
			if(et&&attr_flag>0&&s1[i]!='=') attr_flag=0;
		}
	
	}
	if(*begin&&qt==0&&st==0){
		*end=s1+i;
		return 0;
	}
	if(qt||st) return -1;
	else return 1;
}


static int valid_name(const char* s1, size_t len)
{
	unsigned i=0;
	int is_start=0;
	for(i=0;i<len;i++){
		if(s1[i]==0) return 1;
		if((s1[i]<='Z'&&s1[i]>='A')||(s1[i]<='z'&&s1[i]>='a')||s1[i]=='_'){
			is_start=1;
			continue;
		}else if(s1[i]<='9'&&s1[i]>='0'){
			if(is_start==0) return 0;
			continue;
		}
		return 0;
	}
	return 1;
}

static int proc_attr(const char* s, const char* end, attrib_hook_f ah, void* data, void** save, const char* tagname, size_t len, int top)
{
	int rt;
	const char* cur;
	const char* bg;
	const char* name_begin;
	const char* name_end;
	const char* value_begin;
	const char* value_end;
	size_t ed;
	rt=next_word(s, end-s, &name_begin, &name_end, -1);
	if(rt){
		if(rt>0) return ERR_TAG_NAME;
		if(rt<0) return ERR_QUOTES_OPEN;
	}
	for(cur=name_begin;cur<end;++cur){
		if(*cur=='=') break;
	}
	if(cur==end) return ERR_ATTRIBUTE_FMT;
	rt=next_word(cur+1, end-(cur+1), &value_begin, &value_end, 0);
	if(rt){
		if(rt>0) return ERR_ATTRIBUTE_FMT;
		if(rt<0) return ERR_QUOTES_OPEN;
	}
	if(!valid_name(s, name_end-s)) return ERR_TAG_NAME;
	if(end-(value_begin)>=2&&((value_begin[0]=='"'&&end[-1]=='"')||(value_begin[0]=='\''&&end[-1]=='\''))){
		bg=value_begin+1;
		ed=(end-value_begin)-2;
	}else{
		return ERR_ATTRVALUE_NO_QUOTES;
		/*bg=value_begin;
		ed=end-value_begin;*/
	}
	if(top==-1){
		if(ah(data, NULL, NULL, -1, tagname, len, s, name_end-s, bg, ed))
			return ERR_ATTRIBUTE_HOOK;
	}
	else{
		if(ah(data, LOAD_PTR(save, top), &(save[top]), top, tagname, len, s, name_end-s, bg, ed))
			return ERR_ATTRIBUTE_HOOK;
	}
	return RTOK;
}


//处理开始标签
static int begin_tag(t_xml_parse* handle, const char* s, const char* end)
{
	const char* wbegin;
	const char* wend;
	int rt, af=0;

	int is_tagnm=0;
	if(end-s<1) return ERR_EMPTY_TAG;
	if(end[-1]=='/'){
		--end;
	}
	wend=s;
	while((rt=next_word(wend, end-wend, &wbegin, &wend, af))==0){
		if(is_tagnm==0){
			if(!valid_name(wbegin, wend-wbegin)) return ERR_TAG_NAME;
			is_tagnm=1;
			PUSH(handle, wbegin, (wend-wbegin));
			af=1;
			continue;
		}else{
			rt=proc_attr(wbegin, wend, handle->ah, 
				handle->data, handle->save, handle->tagname[handle->top-1], 
				handle->taglen[handle->top-1], handle->top-1);
			if(rt) return rt;
		}
	}
	if(is_tagnm==0) return ERR_EMPTY_TAG;
	if(rt<0) return ERR_QUOTES_OPEN;

	return RTOK;
}

//处理xml头
static int head_tag(t_xml_parse* handle, const char* s, const char* end)
{
	const char* wbegin;
	const char* wend;
	const char* tagname;
	const char* cur;
	const char* rig;
	size_t len;
	int rt, is_tagnm=0, hashead=0, attrflag=0;

	if(end-s<1) return ERR_EMPTY_TAG;

	for(cur=s; cur<end; cur++){
		if(((*cur)=='\n'||*cur=='\r'||*cur==' '||*cur=='\t')){
			continue;
		}
		if(*cur=='<'){
			if(end-cur>1)
				if(*(cur+1)=='?')
					++hashead;
			break;
		}else{
			return ERR_FIRST_CHAR;
		}
	}
	if(cur==end) return ERR_FIRST_CHAR;
	if(!hashead) return RTOK;
	rig=strchr(cur, '>');
	if(rig==NULL||rig>=end) return ERR_UNEXPECT_END;
	if(rig[-1]!='?') return ERR_HEAD_END_FMT;

	end=rig-1;
	wend=cur+2;

	while((rt=next_word(wend, end-wend, &wbegin, &wend, attrflag))==0){
		if(is_tagnm==0){
			if(!valid_name(wbegin, wend-wbegin)) return ERR_TAG_NAME;
			is_tagnm=1;
			tagname=wbegin;
			len=wend-wbegin;
			attrflag=1;
			continue;
		}else{
			rt=proc_attr(wbegin, wend, handle->mh, handle->data, NULL, tagname, len, -1);
			if(rt<0) return rt;
		}
	}
	if(is_tagnm==0) return ERR_EMPTY_TAG;
	if(rt<0) return ERR_QUOTES_OPEN;

	return (int)(rig-s+1);
}

static int tranc(const  char* s, size_t last)
{
	int i=0;
	for(;i<sizeof(dict)/sizeof(t_tcitem);++i){
		if(last<dict[i].len) continue;
		if(memcmp(s, dict[i].s, dict[i].len)==0) return i;
	}
	return -1;
}


const char* xs_strerr(int error)
{
#define EM_ITEM(rt, msg) case rt: return "[" #rt "]" msg


	switch(error){
		EM_ITEM(ERR_OTHER_INTAGS		,"有其他字符出现在标签间");
		EM_ITEM(ERR_UNEXPECT_END		,"xml文件意外结束，或意外的出现了“>”");
		EM_ITEM(ERR_END_TAG_MISMATCH	,"标签必须成对出现");
		EM_ITEM(ERR_EMPTY_TAG			,"空标签");
		EM_ITEM(ERR_TAG_NAME			,"标签名包含非法字符");
		EM_ITEM(ERR_QUOTES_OPEN			,"引号未结束");
		EM_ITEM(ERR_ATTRIBUTE_FMT		,"属性格式错误，未包含等号");
		EM_ITEM(ERR_ATTRIBUTE_HOOK		,"属性回调函数调用失败");
		EM_ITEM(ERR_FIRST_CHAR			,"第一个有效字符不是“<”");
		EM_ITEM(ERR_HEAD_END_FMT		,"头部的格式不正确，缺少结束的问号");
		EM_ITEM(ERR_MEM_ALLOC			,"内存分配失败");
		EM_ITEM(ERR_ATTRVALUE_NO_QUOTES	,"属性值必须有引号");
		EM_ITEM(ERR_UNKNOW_TAG			,"意义不明的标签");
		default: {
			return "未知";
		}
	}
}


int xs_engine(const char* s, size_t maxbuf, void* data, attrib_hook_f mh, enter_hook_f eh, leave_hook_f lh, attrib_hook_f ah, value_hook_f vh)
{
	const char* cur;
	const char* last_cur=NULL;
	int lasttype=0;
	int resl, rt=RTOK, isover=0, i;
	const char* tag_beg;
	const char* tag_end;
	
	t_xml_parse* handle=(t_xml_parse*)malloc(sizeof(t_xml_parse));
	if(handle==NULL) return ERR_MEM_ALLOC;
	memset(handle, 0, sizeof(t_xml_parse));
	handle->ah=ah;
	handle->vh=vh;
	handle->lh=lh;
	handle->eh=eh;
	handle->mh=mh;
	handle->data=data;
	rt=head_tag(handle, s, s+maxbuf);
	if(rt<0) goto end;
	tag_end=s-1+rt;
	
	do{
		int top=handle->top-1;
		cur=tag_end+1;
		resl=next_tag(cur, s+maxbuf, &tag_beg);
		if(resl<0){
			rt=ERR_UNEXPECT_END;
			goto end;
		}
		if(tag_beg[1]=='!'){
			int cmd_type=0;
			if(last_cur==NULL) last_cur=cur;
			if((s+maxbuf)-(tag_beg+2)>sizeof("[CDATA[")-1) 
				if(memcmp(tag_beg+2, "[CDATA[", sizeof("[CDATA[")-1)==0) cmd_type=1;
			if(((s+maxbuf)-(tag_beg+2)>sizeof("--")-1) )
				if(memcmp(tag_beg+2, "--", sizeof("--")-1)==0) cmd_type=2;
			if(cmd_type==0){
				rt=ERR_UNKNOW_TAG;
				goto end;
			}
			tag_end=tag_beg;
			while(tag_end=strchr(tag_end+1, '>')){
				if(cmd_type==1){
					if(memcmp(tag_end-2, "]]", 2)==0) break;
				}
				else if(memcmp(tag_end-2, "--", 2)==0) break;
			}
			if(tag_end==NULL){
				rt=ERR_END_TAG_MISMATCH;
				goto end;
			}
			continue;
		}
		//如果是end标签，弹栈，如果是开始标签，压栈
		if((tag_end=strchr(tag_beg+1, '>'))==NULL){
			rt=ERR_UNEXPECT_END;
			goto end;
		}

		if(tag_beg[1]=='/'){//这是end标签
			if(tag_end-tag_beg<=2){
				rt=ERR_END_TAG_MISMATCH;
				goto end;
			}
			if(strncmp(handle->tagname[top], tag_beg+2, tag_end-(tag_beg+2))){
				rt=ERR_END_TAG_MISMATCH;
				goto end;
			}
			
			if(lasttype){
				if(last_cur) cur=last_cur;
				rt=handle->vh(handle->data, LOAD_PTR(handle->save, top), &handle->save[top], top, handle->tagname[top], handle->taglen[top], cur, tag_beg-cur);
				last_cur=NULL;
				if(rt) goto end;
			}	
			POP(handle);
			lasttype=0;
			continue;
		}
		last_cur=NULL;
		if(resl>0){
			rt=ERR_OTHER_INTAGS;
			goto end;
		}
		if(tag_end-(tag_beg+1)>1){
			if(tag_end[-1]=='/'){
				--tag_end;
				isover=1;
			}
			else isover=0;
		}else isover=0;

		rt=begin_tag(handle, tag_beg+1, tag_end);
		if(rt) goto end;
		top=handle->top-1;
		if(isover){
			rt=handle->vh(handle->data, LOAD_PTR(handle->save, top), &handle->save[top], top, handle->tagname[top], handle->taglen[top], "", 0);
			if(rt) goto end;
			lasttype=0;
			POP(handle);
			++tag_end;
		}
		else
			lasttype=1;

	}while(handle->top);

end:
	for(i=handle->top-1;i>=0;--i){
		handle->lh(handle->data, LOAD_PTR(handle->save, i), &(handle->save[i]), i, handle->tagname[i], handle->taglen[i]);
	}

	free(handle);
	return rt;

}


int xs_speccpy(char* dst, size_t dst_len, const char* src, size_t src_len)
{
	size_t i=0, j=0;
	int cmd_type=0, pass_flag=0;;

	for(;i<src_len&&j<dst_len-1;++i){
		if(src[i]==0) break;
		if(src[i]=='&'&&cmd_type==0){
			int c=tranc(src+i, src_len-i);
			if(c>=0){
				dst[j]=dict[c].c;
				i+=dict[c].len-1;
				++j;
				continue;
			}
		}else if(src[i]=='<'&&src_len-i>1&&src[i+1]=='!'&&cmd_type==0){
			if(src_len-i>sizeof("<![CDATA[")-1) 
				if(memcmp(src+i, "<![CDATA[", sizeof("<![CDATA[")-1)==0){
					i+=sizeof("<![CDATA[")-2;
					cmd_type=1;
					continue;
				}
			if(src_len-i>sizeof("<!--")-1)
				if(memcmp(src+i, "<!--", sizeof("<!--")-1)==0){
					i+=sizeof("<!--")-2;
					pass_flag=1;
					cmd_type=2;
					continue;
				}
		}else if(cmd_type==2&&src_len-i>2&&src[i]=='-'&&src[i+1]=='-'&&src[i+2]=='>'){
			i+=sizeof("-->")-2;
			pass_flag=0;
			cmd_type=0;
			continue;
		}else if(cmd_type==1&&src_len-i>2&&src[i]==']'&&src[i+1]==']'&&src[i+2]=='>'){
			i+=sizeof("]]>")-2;
			cmd_type=0;
			continue;
		}
		if(pass_flag){
			continue;
		}
		dst[j]=src[i];
		++j;
	}
	dst[j]=0;
	return (int)j;
}

