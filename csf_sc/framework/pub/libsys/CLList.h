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
		 *     漫游列表的回调函数指针。
		 */
		typedef int (*ListWalkAction)(void *,void *);

		/**
		 *     增加一个元素到root的前面，这个root元素可能是list的中间元素。返回值为
		 * 最新的列表头指针即root。
		 *     此函数的执行不会失败！
		 */
		static TDblList *ListAdd(TDblList **root,TDblList *element);
		
		/**
		 *     从双链表中删除指定的元素element。此操作只是把元素element与双链表的连
		 * 接切断了，但并没有释放element所占用的内存，需要此其它地方进行释放，返回
		 * 值为新的链表头。
		 */
		static TDblList *ListDelete(TDblList **root,TDblList *element);

		/**
		 *      从双链表中删除指定的元素element。同时会删除element节点占用的内存。
		 * @bFreeData 表示是否释放节点中数据所占用的内存。
		 */
		static TDblList *ListFreeItem(TDblList **root,TDblList *element, bool bFreeData);

		/**
		 *     新建一个节点，并把此节点插入到链表头中，更新list中的链表记录，然后返
		 * 回list。函数ListCons不会为data分配内存，只是在链表中有一个指针指向此变量。
		 * @return 函数执行成功返回链表头；如果失败，返回为空，此时不会更新链表list
		 *         中的值，返回为空一般都是因为内存不足。
		 */
		static TDblList *ListCons(void *data,TDblList **root);

		/**
		 *     把双链表的方向，做相反方向的接连。原来的后继节点成了现在的前趋节点，
		 * 原来的前趋节点成了现在的后继节点。
		 */
		static TDblList *ListReverse(TDblList *root);

		/**
		 *     删除并释放root元素和其所有后继无素的占用的内存。注意没有释放或删除前
		 * 趋节点的内存，也就是说，只删除了双向链表中root和其下面的元素，而不是双链
		 * 表本身。如果root指向双链表的头则将删除双链表。bool为布儿类型的变量。
		 * NSPrime::CMalloc::Free是对free进行了封装的函数，用于释放内存。
		 */
		static void ListFree(TDblList **root,bool bFreeData);

		/**
		 *     得到此从list元素开始节点的链表的长度。
		 */
		static ub4 ListLength(TDblList *list);

		/**
		 *     对链表中的每一个节点执行ListWalkAction类型的函数，函数action的参数
		 * 分别为链表中的data数据和传入的gptr类型的argument参数。
		 */
		static int ListWalk(TDblList *list,ListWalkAction action,gptr argument);

		/**
		 *     得到下一个元素。
		 */
		static inline TDblList* GetNext(TDblList *list) 
		{
			return list->next;
		}

		/**
		 *     向链表头插入一个元素，并返回指向此元素的指针。
		 */
		static inline TDblList* ListPush(void * data,TDblList **list)
		{
			return ListCons(data,list);
		}

		/**
		 *     删除链表的头节点，同时释放头节点的内存。
		 */
		static void ListPop(TDblList **list);
	};
}
