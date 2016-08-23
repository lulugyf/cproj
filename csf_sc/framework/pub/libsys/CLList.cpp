#include "libsys.h"

namespace NSPrime
{
	/**
	 *     增加一个元素到root的前面，这个root元素可能是list的中间元素。返回值为
	 * 最新的列表头指针即root。
	 *     此函数的执行不会失败！
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
	 *     从双链表中删除指定的元素element。此操作只是把元素element与双链表的连
	 * 接切断了，但并没有释放element所占用的内存，需要此其它地方进行释放，返回
	 * 值为新的链表头。
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
	 *     内部调用ListDelete(TDblList **root,TDblList *element)函数，
	 * 同时会删除element节点占用的内存。
	 * @bFreeData 表示是否释放节点中数据所占用的内存。
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
	 *     删除并释放root元素和其所有后继无素的占用的内存。注意没有释放或删除前
	 * 趋节点的内存，也就是说，只删除了双向链表中root和其下面的元素，而不是双链
	 * 表本身。如果root指向双链表的头则将删除双链表。bool为布儿类型的变量。
	 * SafeFree是对free进行了封装的函数，用于释放内存。
	 */
	void CLDblList::ListFree(NSPrime::TDblList **root, bool bFreeData)
	{
		NSPrime::TDblList *next;

		if ((*root))
		{
			if ((*root)->prev)
			{
				//如果root节点前面还有节点，需要把root和前面的节点做切断处理。
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
	 *     新建一个节点，并把此节点插入到链表头中，更新list中的链表记录，然后返
	 * 回list。函数ListCons不会为data分配内存，只是在链表中有一个指针指向此变量。
	 * @return 函数执行成功返回链表头；如果失败，返回为空，此时不会更新链表list
	 *         中的值，返回为空一般都是因为内存不足。
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
	 *     把双链表的方向，做相反方向的接连。原来的后继节点成了现在的前趋节点，
	 * 原来的前趋节点成了现在的后继节点。
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
	 *     得到此从list元素开始节点的链表的长度。
	 */
	ub4 CLDblList::ListLength(NSPrime::TDblList *list)
	{
		ub4 count;
		for (count=0 ; list ; list=list->next, count++) ;
		return count;
	}
	
	/**
	 *     对链表中的每一个节点执行ListWalkAction类型的函数，函数action的参数
	 * 分别为链表中的data数据和传入的gptr类型的argument参数。
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
