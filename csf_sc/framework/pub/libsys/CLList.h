#pragma once

//#include "global.h"

namespace NSPrime
{
	typedef struct tagDblList
	{
		struct tagDblList *prev,*next;
		void *data;
	} TDblList;

	class CMalloc;

	class CLDblList
	{
	public:
		/**
		 *     �����б�Ļص�����ָ�롣
		 */
		typedef int (*ListWalkAction)(void *,void *);

		/**
		 *     ����һ��Ԫ�ص�root��ǰ�棬���rootԪ�ؿ�����list���м�Ԫ�ء�����ֵΪ
		 * ���µ��б�ͷָ�뼴root��
		 *     �˺�����ִ�в���ʧ�ܣ�
		 */
		static TDblList *ListAdd(TDblList **root,TDblList *element);
		
		/**
		 *     ��˫������ɾ��ָ����Ԫ��element���˲���ֻ�ǰ�Ԫ��element��˫�������
		 * ���ж��ˣ�����û���ͷ�element��ռ�õ��ڴ棬��Ҫ�������ط������ͷţ�����
		 * ֵΪ�µ�����ͷ��
		 */
		static TDblList *ListDelete(TDblList **root,TDblList *element);

		/**
		 *      ��˫������ɾ��ָ����Ԫ��element��ͬʱ��ɾ��element�ڵ�ռ�õ��ڴ档
		 * @bFreeData ��ʾ�Ƿ��ͷŽڵ���������ռ�õ��ڴ档
		 */
		static TDblList *ListFreeItem(TDblList **root,TDblList *element, bool bFreeData);

		/**
		 *     �½�һ���ڵ㣬���Ѵ˽ڵ���뵽����ͷ�У�����list�е������¼��Ȼ��
		 * ��list������ListCons����Ϊdata�����ڴ棬ֻ������������һ��ָ��ָ��˱�����
		 * @return ����ִ�гɹ���������ͷ�����ʧ�ܣ�����Ϊ�գ���ʱ�����������list
		 *         �е�ֵ������Ϊ��һ�㶼����Ϊ�ڴ治�㡣
		 */
		static TDblList *ListCons(void *data,TDblList **root);

		/**
		 *     ��˫����ķ������෴����Ľ�����ԭ���ĺ�̽ڵ�������ڵ�ǰ���ڵ㣬
		 * ԭ����ǰ���ڵ�������ڵĺ�̽ڵ㡣
		 */
		static TDblList *ListReverse(TDblList *root);

		/**
		 *     ɾ�����ͷ�rootԪ�غ������к�����ص�ռ�õ��ڴ档ע��û���ͷŻ�ɾ��ǰ
		 * ���ڵ���ڴ棬Ҳ����˵��ֻɾ����˫��������root���������Ԫ�أ�������˫��
		 * �������rootָ��˫�����ͷ��ɾ��˫����boolΪ�������͵ı�����
		 * NSPrime::CMalloc::Free�Ƕ�free�����˷�װ�ĺ����������ͷ��ڴ档
		 */
		static void ListFree(TDblList **root,bool bFreeData);

		/**
		 *     �õ��˴�listԪ�ؿ�ʼ�ڵ������ĳ��ȡ�
		 */
		static ub4 ListLength(TDblList *list);

		/**
		 *     �������е�ÿһ���ڵ�ִ��ListWalkAction���͵ĺ���������action�Ĳ���
		 * �ֱ�Ϊ�����е�data���ݺʹ����gptr���͵�argument������
		 */
		static int ListWalk(TDblList *list,ListWalkAction action,gptr argument);

		/**
		 *     �õ���һ��Ԫ�ء�
		 */
		static inline TDblList* GetNext(TDblList *list) 
		{
			return list->next;
		}

		/**
		 *     ������ͷ����һ��Ԫ�أ�������ָ���Ԫ�ص�ָ�롣
		 */
		static inline TDblList* ListPush(void * data,TDblList **list)
		{
			return ListCons(data,list);
		}

		/**
		 *     ɾ�������ͷ�ڵ㣬ͬʱ�ͷ�ͷ�ڵ���ڴ档
		 */
		static void ListPop(TDblList **list);
	};
}
