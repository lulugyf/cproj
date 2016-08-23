#pragma once

//#include "global.h"
/**
 *     NSPrime 库的命名空间
 */

namespace NSPrime
{
	class CLRbTree
	{
	public:
		static const int MAX_TREE_HEIGHT		=	40;	// = max 1048576 leafs in tree
		static const int TREE_NO_DUPS			=	1;

		typedef enum { LEFT_ROOT_RIGHT, RIGHT_ROOT_LEFT } TREE_WALK;
		typedef ub4 element_count;

		/**
		 *     漫游树时触发动作。
		 */
		typedef int (*TreeWalkAction)(void *,element_count,void *);

		/**
		 *     当释放内存时使用的三个宏定义，这三个宏只有当TRbTree::withDelete
		 * 的值为真时才有意义，因为内存池不会做单个元素的删除。
		 */
		typedef enum { FREE_INIT, FREE_FREE, FREE_END } TREE_FREE;
		/**
		 *     当树元素内存释放时，同时调用的函数指针。
		 */
		typedef void (*TOnTreeElementFree)(void*, TREE_FREE, void *);

		typedef struct tagRbTreeElement
		{
			struct tagRbTreeElement *left,*right;
			ub4 count:31,
				colour:1;			/* black is marked as 1（即：BLACK） */
		} TRbTreeElement;

		typedef struct tagRbTree
		{
			TRbTreeElement *root,null_element;

			/**
			 *     定义MAX_TREE_HEIGHT个指向指向指针的指针，父元素的临时列表，
			 * 在向树中插入一个元素时用到此变量，此变量起到堆栈的作用。
			 */
			TRbTreeElement **parents[MAX_TREE_HEIGHT];
			
			/**
			 *     如果为真将保存Key的值到树中，否则保存Key的地址到树中。
			 */
			bool	isSaveKey;
			ub4		iKeySize;//键值的大小。如果isSaveKey为true，为传入值的大小，
			                 //否则为gptr的大下。

			ub4 elementsInTree;//树中的元素数，重复的元素按一个计算。
			
			/**
			 *     树可使用的最大内存大小，如果为零表示没有限制。如果存在内存限
			 * 制，则在向树中加入元素时，当已经分配的内存大于限制的内存时，会清
			 * 空树中的所有元素，然后插入当前的元素！
			 */
			ub8 memoryLimit;
			
			ub4 allocated;//树已经使用的内存数量。
			QsortCmp2 compare;

			void *customArg;//用户定义的参数，主要给触发TOnTreeElementFree事件的函数用。

			/**
			 *     只有当withDelete的值为假时，才使用内存池，否则使用Malloc函数
			 * 动态分配。
			 */
			NSPrime::TMemRoot memRoot;
			
			//如果此值为真就调用NSPrime::CMalloc::Malloc函数，否则就调用NSPrime::CMalloc::AllocRoot函数。
			bool withDelete;
			
			//当树中的节点树释放时触发的事件。
			TOnTreeElementFree OnTreeElementFree;

			/**
			 *     树的标志位，当值为TREE_NO_DUPS时表示树中不能有重复的节点，当
			 * 有重复的节点时TreeInsert函数的返回状态retStatus不为零（为4）。
			 */
			ub4 flag;
		} TRbTree;
		
		
		/**
		 *     得到键值key的地址。
		 */
		static inline gptr  ELEMENT_KEY(TRbTree *tree,TRbTreeElement *element)
		{
			return tree->isSaveKey ? (void*) (element+1): *((void**) (element+1));
		}

		/**
		 *     根据offs得到子节点的地址。
		 */
		static inline TRbTreeElement* ELEMENT_CHILD(TRbTreeElement *element, ub8 offs)
		{
			return (*(TRbTreeElement**)((char*)element + offs));
		}

	private:
		static const int	BLACK				=	1;//黑色节点定义
		static const int	RED					=	0;//红色节点定义

		//默认分配的字节大小。
		static const int	DEFAULT_ALLOC_SIZE	=	8192;

		//默认的对齐字节大小。
		static const int	DEFAULT_ALIGN_SIZE	=	8192;

		static int tree_walk_left_root_right(TRbTree *,TRbTreeElement *,TreeWalkAction,void *);
		static int tree_walk_right_root_left(TRbTree *,TRbTreeElement *,TreeWalkAction,void *);
		static void left_rotate(TRbTreeElement **parent,TRbTreeElement *leaf);
		static void right_rotate(TRbTreeElement **parent, TRbTreeElement *leaf);
		static void rb_insert(TRbTree *tree,TRbTreeElement ***parent,TRbTreeElement *leaf);
		static void rb_delete_fixup(TRbTree *tree,TRbTreeElement ***parent);
		static void FreeTree(TRbTree *tree, myf freeFlags);

		/**
		 *     通过NSPrime::CMalloc::Free函数递归删除指定树元素中的子元素及指定元素。
		 * 函数的递归终止条件为到叶节点（null_element）。
		 *     如果树中的OnTreeElementFree函数指针不为空就调用此函数指针。
		 *     如果树中的withDelete标志为真（不等于零），就调用NSPrime::CMalloc::Free
		 * 函数释放此元素的内存，否则就不删除元素结点内存。
		 *     使用内存池的树不能使用此函数，注意使用此函数删除树中的节点后，此树将
		 * 不再是红黑树。
		 */
		static void DeleteTreeElement(TRbTree *,TRbTreeElement *);
#ifndef DBUG_OFF
		/* The actuall code for handling binary trees */
		static int test_rb_tree(TRbTreeElement *element);
#endif
	public:
		/**
		 *     红黑树的外部接口。
		 */

		/**
		 *     初始化一棵红黑树。
		 * @param tree 指向树根。
		 * @param defaultAllocSize 当使用内存池时默认初始分配给节点的大小，如果此值
		 *        小于DEFAULT_ALLOC_SIZE，则取DEFAULT_ALLOC_SIZE值，当withDelete的值
		 *        为真时此参数没有意义。
		 * @param memoryLimit 树元素最大可使用内存的大小限制，为零表示没有限制。如果
		 *        存在内存限制，则在向树中加入元素时，当已经分配的内存大于限制的内存
		 *        时，会清空树中的所有元素，然后插入当前的元素！
		 * @param iKeySize  如果要在树中保存键的值，传入键值元素的大小，否则置为0。
		 * @param compare 树中元素值的比较函数。
		 * @param withDelete 如果传入的值为假（即等于零），就调用InitAllocRoot函数初
		 *        始化内存池，以后树中的元素就使用内存池中的内存；否则以后元素就调用
		 *        直接分配内存而不用内存池。注意如果是用内存池的话，就不能一个一个的
		 *        删除树中的元素，只能删除整个树。
		 * @param freeElement 如果此值为真则以后释放元素的内存时会触发OnTreeElementFree
		 *        事件，而且用户可能使用此事件释放用户定义的内存，如元素数据和key的
		 *        内存。
		 * @param customArg 此参数为：当触发OnTreeElementFree事件时，传给OnTreeElementFree
		 *        事件的参数。
		 */
		static void InitTree(TRbTree *tree, ub4 defaultAllocSize, ub8 memoryLimit,
					ub4 iKeySize, QsortCmp2 compare, bool withDelete,
				TOnTreeElementFree freeElement, void *customArg);

		/**
		 *     此函数中是对FreeFree函数的封装，由于在调用FreeTree的函数中，freeFlags
		 * 参数的值为零，所以不管使用的是内存池，还是普通的Malloc函数，都会释放树中
		 * 的所有内存。
		 */
		static void DeleteTree(TRbTree*);

		/**
		 *     此函数中是对FreeFree函数的封装，由于在调用FreeTree的函数中，freeFlags
		 * 参数的值为NSPrime::CMalloc::MY_MARK_BLOCKS_FREE，所以如果树用的是内存池会
		 * 调用MarkBlocksFree函数标记内存池中的所有块为可使用状态。
		 */
		static void ResetTree(TRbTree*);
		

		/**
		 *     向树中插入一个元素，如果成功返回新增元素元素的指针，否则返回零。请注
		 * 意，如果树中的元素已分配空间的大小大于树限制的内存时，程序首先会调用
		 * ResetTree函数清空树中已经存在的节点，然后再调用TreeInsert函数，返回此函数
		 * 的值。
		 *     如果正常插入，返回插入的节点，否则返回空，返回空由以下的几种情况之一
		 * 导致：
		 *     （1）内存不足：因为在程序中指定了MY_WME参数，如果用户指定了
		 *          NSPrime::CGlobalErrors::ErrorHandlerHook函数的句柄系统会自动调
		 *          用用户定义的函数。
		 *     （2）树中已经存在指定的键Key，并且树TRbTree->flag& TREE_NO_DUPS为真，
		 *          在树的初始化函数InitTree中指定此值为假（零）。
		 *@param retStatus 值为如下：
		 *                 （1）当树中元素被清空时值为 1
		 *                 （2）当内存不足时值为 2。
		 *                 （3）当存在重复记录，并且TRbTree->flag& TREE_NO_DUPS为真
		 *                      时值为4。
		 *                 （4）正常返回时，值不变，为函数传入的值。
		 */
		static TRbTreeElement *TreeInsert(TRbTree *tree,void *key, void *customArg, int *retStatus);


		/**
		 *     在树中查找指定的KEY，如果找到返回树中指向的KEY的地址，否则返回NULL。
		 */
		static void *TreeSearch(TRbTree *tree, void *key, void *customArg);

		/**
		 *    漫游红黑树，参数visit指出漫游的方向：
		 *        （1）当visit==LEFT_ROOT_RIGHT 按left --> root --> right的方向漫游树。
		 *        （2）当visit==RIGHT_ROOT_LEFT 按right --> root --> left的方向漫游树。
		 *    正确返回零，否则返回错误代码。
		 */
		static int TreeWalk(TRbTree *tree,TreeWalkAction action,void *argument, TREE_WALK visit);
		
		/**
		 *     删除树中的一个元素，注意中有当树的withDelete值为正时（即不使用内存池
		 * 时），才可以调用此函数，否则函数返回1。
		 */
		static int TreeDelete(TRbTree *tree, void *key, void *customArg);

		/**
		 *     查找指定的元素，同时生成边界元素到根节点的父节点列表parents，以及当
		 * 前元素的位置last_pos，他们的定义由使用者提供。
		 * @return 找到返回元素键key的指针，否则返回空。
		 */
		static void *TreeSearchKey(TRbTree *tree, const void *key, 
							TRbTreeElement **parents, TRbTreeElement ***last_pos,void *customArg);

		/**
		 *     查找边界元素：查找在树中的第一个（最左边）或最后一个元素（最右边），
		 * 同时生成边界元素到根节点的父节点列表parents，此变量的定义由使用者提供，
		 * 一般定义为“NSPrime::CLRbTree::TRbTreeElement *parents[MAX_TREE_HEIGHT+1]”，child_offs的值可
		 * 用OffsetOf宏得到成员在结构体的偏移量，如：
		 *        （1）OffsetOf(TRbTreeElement, left)得到左子节点的偏移量，
		 *        （2）OffsetOf(TRbTreeElement, right)得到右子节点的偏移量。
		 * @return 找到返回边界节点元素键key的指针，否则返回空。
		 */
		static gptr TreeSearchEdge(TRbTree *tree, TRbTreeElement **parents, 
			TRbTreeElement ***last_pos, int child_offs);
		
		/**
		 *                 
		 *     找到当前键值（**last_pos）的下一个键值，例如下图中“8”的下一个键值
		 * 是“7”，而“5”的下一个键值为“4”：
		 *
		 *          last_pos-->   8    
		 *              4                       12
		 *         2        6             10           14
		 *      1    3    5    7       9    11     13     15
		 * @param last_pos 开始查找的节点地址，此变量指向一个父点点列表，此父点列表
		 *                 可能是TreeSearchEdge、TreeSearchKey或TreeSearchNext函数
		 *                 生成的。
		 * @param l_offs   左子树的偏移量
		 * @param r_offs   右子树的偏移量
		 */
		static void *TreeSearchNext(TRbTree *tree, TRbTreeElement ***last_pos, int l_offs, int r_offs);

		/**
		 *     假定树为一棵完全的平衡的二叉树（从根到树中的每一个叶都有相同的长度）。
		 * 返回指定键值在树中的位置，按照键的大小顺序进行排序，基数从1开始。
		 *     成功返回位置，不成功返回零。
		 */
		static ub8 TreeRecordPos(TRbTree *tree, const void *key, void *customArg);
	};
}
