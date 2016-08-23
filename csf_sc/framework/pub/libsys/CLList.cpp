#include "libsys.h"

namespace NSPrime
{
	/**
	 *     ����һ��Ԫ�ص�root��ǰ�棬���rootԪ�ؿ�����list���м�Ԫ�ء�����ֵΪ
	 * ���µ��б�ͷָ�뼴root��
	 *     �˺�����ִ�в���ʧ�ܣ�
	 */
	NSPrime::TDblList *CLDblList::ListAdd(NSPrime::TDblList **root, NSPrime::TDblList *element)
	{
		DBUG_ENTER("ListAdd");
		DBUG_PRINT("enter",("*root: %lx  element: %lx", *root, element));
		if (*root)
		{
			if ((*root)->prev)			/* If add in mid of list */
				(*root)->prev->next= element;
			element->prev=(*root)->prev;
			(*root)->prev=element;
		}
		else
			element->prev=NULL;
		element->next=(*root);
		*root = element;
		DBUG_RETURN(*root);			/* New root */
	}
	
	
	/**
	 *     ��˫������ɾ��ָ����Ԫ��element���˲���ֻ�ǰ�Ԫ��element��˫�������
	 * ���ж��ˣ�����û���ͷ�element��ռ�õ��ڴ棬��Ҫ�������ط������ͷţ�����
	 * ֵΪ�µ�����ͷ��
	 */
	NSPrime::TDblList *CLDblList::ListDelete(NSPrime::TDblList **root, NSPrime::TDblList *element)
	{
		if (element->prev)
			element->prev->next=element->next;
		else
			*root=element->next;
		if (element->next)
			element->next->prev=element->prev;
		return *root;
	}

	/**
	 *     �ڲ�����ListDelete(TDblList **root,TDblList *element)������
	 * ͬʱ��ɾ��element�ڵ�ռ�õ��ڴ档
	 * @bFreeData ��ʾ�Ƿ��ͷŽڵ���������ռ�õ��ڴ档
	 */
	NSPrime::TDblList *CLDblList::ListFreeItem(TDblList **root,TDblList *element, bool bFreeData)
	{
		CLDblList::ListDelete(root, element);

		if (bFreeData)
		{
			SafeFree((gptr)element->data, 0);
		}
		SafeFree((gptr) element, 0);
		return *root;
	}
	
	
	/**
	 *     ɾ�����ͷ�rootԪ�غ������к�����ص�ռ�õ��ڴ档ע��û���ͷŻ�ɾ��ǰ
	 * ���ڵ���ڴ棬Ҳ����˵��ֻɾ����˫��������root���������Ԫ�أ�������˫��
	 * �������rootָ��˫�����ͷ��ɾ��˫����boolΪ�������͵ı�����
	 * SafeFree�Ƕ�free�����˷�װ�ĺ����������ͷ��ڴ档
	 */
	void CLDblList::ListFree(NSPrime::TDblList **root, bool bFreeData)
	{
		NSPrime::TDblList *next;

		if ((*root))
		{
			if ((*root)->prev)
			{
				//���root�ڵ�ǰ�滹�нڵ㣬��Ҫ��root��ǰ��Ľڵ����жϴ���
				(*root)->prev->next = NULL;
			}
		}
		while (*root)
		{
			next=(*root)->next;
			if (bFreeData)
			{
				SafeFree((gptr)(*root)->data, 0);
			}
			SafeFree((gptr) (*root), 0);
			*root=next;
		}
	}
	
	/**
	 *     �½�һ���ڵ㣬���Ѵ˽ڵ���뵽����ͷ�У�����list�е������¼��Ȼ��
	 * ��list������ListCons����Ϊdata�����ڴ棬ֻ������������һ��ָ��ָ��˱�����
	 * @return ����ִ�гɹ���������ͷ�����ʧ�ܣ�����Ϊ�գ���ʱ�����������list
	 *         �е�ֵ������Ϊ��һ�㶼����Ϊ�ڴ治�㡣
	 */
	NSPrime::TDblList *CLDblList::ListCons(void *data, NSPrime::TDblList **list)
	{
		NSPrime::TDblList *newEl=(NSPrime::TDblList*) SafeMalloc(sizeof(NSPrime::TDblList),(myf)(MY_FAE));
		if (!newEl)
		{
			return NULL;
		}
		newEl->data=data;
		return ListAdd(list,newEl);
	}
	
	/**
	 *     ��˫����ķ������෴����Ľ�����ԭ���ĺ�̽ڵ�������ڵ�ǰ���ڵ㣬
	 * ԭ����ǰ���ڵ�������ڵĺ�̽ڵ㡣
	 */
	NSPrime::TDblList *CLDblList::ListReverse(NSPrime::TDblList *root)
	{
		NSPrime::TDblList *last;
	
		last=root;
		while (root)
		{
			last=root;
			root=root->next;
			last->next=last->prev;
			last->prev=root;
		}
		return last;
	}
	
	/**
	 *     �õ��˴�listԪ�ؿ�ʼ�ڵ������ĳ��ȡ�
	 */
	ub4 CLDblList::ListLength(NSPrime::TDblList *list)
	{
		ub4 count;
		for (count=0 ; list ; list=list->next, count++) ;
		return count;
	}
	
	/**
	 *     �������е�ÿһ���ڵ�ִ��ListWalkAction���͵ĺ���������action�Ĳ���
	 * �ֱ�Ϊ�����е�data���ݺʹ����gptr���͵�argument������
	 */
	int CLDblList::ListWalk(NSPrime::TDblList *list, ListWalkAction action, gptr argument)
	{
		int error=0;
		while (list)
		{
			if ((error = (*action)(list->data,argument)))
				return error;
			list=GetNext(list);
		}
		return 0;
	}

	void CLDblList::ListPop(NSPrime::TDblList **list)
	{
		NSPrime::TDblList *old=*list;
		ListDelete(list,old) ;
		SafeFree((gptr) old, 0);
	}
}
