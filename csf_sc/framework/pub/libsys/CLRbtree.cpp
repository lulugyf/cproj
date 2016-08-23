#include "libsys.h"

namespace NSPrime
{
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
	void CLRbTree::InitTree(TRbTree *tree, ub4 defaultAllocSize, ub8 memoryLimit,
				ub4 iKeySize, QsortCmp2 compare, bool withDelete,
			TOnTreeElementFree freeElement, void *customArg)
	{
		DBUG_ENTER("InitTree");
		DBUG_PRINT("enter",("tree: %lx  iKeySize: %d",tree,iKeySize));

		/**
		 *     使分配的字节数按DEFAULT_ALIGN_SIZE对齐。
		 */
		if (defaultAllocSize < DEFAULT_ALLOC_SIZE)
			defaultAllocSize= DEFAULT_ALLOC_SIZE;
		defaultAllocSize= MY_ALIGN(defaultAllocSize, DEFAULT_ALIGN_SIZE);

		memset((gptr) &tree->null_element,0,sizeof(tree->null_element));
		tree->root= &tree->null_element;
		tree->compare=compare;
		tree->memoryLimit=memoryLimit;
		tree->OnTreeElementFree=freeElement;
		tree->allocated=0;
		tree->elementsInTree=0;
		tree->customArg = customArg;
		tree->null_element.colour=BLACK;
		tree->null_element.left=tree->null_element.right=0;
		tree->flag= 0;
		if (iKeySize == 0)
		{
			tree->iKeySize = sizeof(gptr);
			tree->isSaveKey = false;
		}
		else
		{
			tree->iKeySize = iKeySize;
			tree->isSaveKey = true;
		}
		if (!(tree->withDelete=withDelete))
		{
			NSPrime::CLMalloc::InitAllocRoot(&tree->memRoot, defaultAllocSize);
			tree->memRoot.minMalloc=(sizeof(TRbTreeElement)+sizeof(gptr));
		}
		DBUG_VOID_RETURN;
	}

	/**
	 *     如果withDelete的值为真或函数的参数freeFlags为MY_MARK_BLOCKS_FREE就删
	 * 除树中所有元素的内存。
	 *     如果树中的withDelete标志为真（不等于零），就调用DeleteTreeElement
	 * 删除内存内存。否则就执行下面的步骤：
	 *     （1）如果树中的OnTreeElementFree函数指针不为空，并且如果树中的memoryLimit
	 * 不为空就调用带FREE_INIT参数的OnTreeElementFree函数指针函数。
	 *     （2）接着调用DeleteTreeElement函数归递执行带FREE_FREE参数的
	 * OnTreeElementFree函数指针函数。
	 *     （3）然后调用带FREE_END参数的OnTreeElementFree函数指针函数。
	 *     （4）最后调用NSPrime::CLMalloc::FreeRoot释放内存池中的内存。
	 *     最后初始化树中的元素个数和已经分配的内存字节数。
	 * @param freeFlags 用于内存池的释放选项，此值可能为
	 *        NSPrime::CLMalloc::MY_MARK_BLOCKS_FREE或为零，可参考FreeRoot函数。
	 */
	void CLRbTree::FreeTree(TRbTree *tree, myf freeFlags)
	{
		DBUG_ENTER("FreeTree");
		DBUG_PRINT("enter",("tree: %lx",tree));

		if (tree->root)				/* If initialized */
		{
			if (tree->withDelete)
			{
				DeleteTreeElement(tree,tree->root);
			}
			else
			{
				if (tree->OnTreeElementFree)
				{
					if (tree->memoryLimit)
					{
						(*tree->OnTreeElementFree)(NULL, FREE_INIT, tree->customArg);
					}
					DeleteTreeElement(tree,tree->root);
					if (tree->memoryLimit)
					{
						(*tree->OnTreeElementFree)(NULL, FREE_END, tree->customArg);
					}
				}
				NSPrime::CLMalloc::FreeRoot(&tree->memRoot, freeFlags);
			}
		}
		tree->root= &tree->null_element;
		tree->elementsInTree=0;
		tree->allocated=0;

		DBUG_VOID_RETURN;
	}

	/**
	 *     此函数中是对FreeFree函数的封装，由于在调用FreeTree的函数中，freeFlags
	 * 参数的值为零，所以不管使用的是内存池，还是普通的Malloc函数，都会释放树中
	 * 的所有内存。
	 */
	void CLRbTree::DeleteTree(TRbTree* tree)
	{
		FreeTree(tree, (myf)(0)); /* SafeFree() memRoot if applicable */
	}

	/**
	 *     此函数中是对FreeFree函数的封装，由于在调用FreeTree的函数中，freeFlags
	 * 参数的值为NSPrime::CLMalloc::MY_MARK_BLOCKS_FREE，所以如果树用的是内存池会
	 * 调用MarkBlocksFree函数标记内存池中的所有块为可使用状态。
	 */
	void CLRbTree::ResetTree(TRbTree* tree)
	{
		FreeTree(tree, (myf)(NSPrime::CLMalloc::MY_MARK_BLOCKS_FREE));
		/* do not SafeFree() memRoot if applicable, just mark blocks as free */
	}


	/**
	 *     通过SafeFree函数递归删除指定树元素中的子元素及指定元素。
	 * 函数的递归终止条件为到叶节点（null_element）。
	 *     如果树中的OnTreeElementFree函数指针不为空就调用此函数指针。
	 *     如果树中的withDelete标志为真（不等于零），就调用SafeFree
	 * 函数释放此元素的内存，否则就不删除元素结点内存。
	 *     使用内存池的树不能使用此函数，注意使用此函数删除树中的节点后，此树将
	 * 不再是红黑树。
	 */
	void CLRbTree::DeleteTreeElement(TRbTree *tree, TRbTreeElement *element)
	{
		if (element != &tree->null_element)
		{
			DeleteTreeElement(tree,element->left);
			if (tree->OnTreeElementFree)
				(*tree->OnTreeElementFree)(ELEMENT_KEY(tree,element), FREE_FREE, tree->customArg);
			DeleteTreeElement(tree,element->right);
			if (tree->withDelete)
				SafeFree((gptr) element, 0);
		}
	}

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
	CLRbTree::TRbTreeElement *CLRbTree::TreeInsert(TRbTree *tree, void *key, 
		void* customArg, int *retStatus)
	{
		int cmp;
		TRbTreeElement *element,***parent;

		/**
		 *     查找要插入的位置
		 */
		parent= tree->parents;
		*parent = &tree->root; element= tree->root;
		for (;;)
		{
			if (element == &tree->null_element ||
				(cmp = (*tree->compare)(customArg, ELEMENT_KEY(tree,element),key)) == 0)
			{
				break;
			}
			if (cmp < 0)
			{
				*++parent= &element->right; element= element->right;
			}
			else
			{
				*++parent = &element->left; element= element->left;
			}
		}
		
		if (element == &tree->null_element)
		{
			ub4 alloc_size=sizeof(TRbTreeElement)+tree->iKeySize;

			tree->allocated+=alloc_size;

			if (tree->memoryLimit && tree->elementsInTree	&& tree->allocated > tree->memoryLimit)
			{
				ResetTree(tree);
				*retStatus = 1;
				return TreeInsert(tree, key, customArg, retStatus);
			}

			if (tree->withDelete)
			{
				element=(TRbTreeElement *) SafeMalloc(alloc_size, (myf)(MY_WME));
			}
			else
			{
				element=(TRbTreeElement *)NSPrime::CLMalloc::AllocRoot(&tree->memRoot,alloc_size);
			}
			
			if (element == NULL)
			{
				*retStatus = 2;
				return(NULL);
			}
			
			**parent=element;
			element->left=element->right= &tree->null_element;

			if (tree->isSaveKey)
			{
				/**
				 *     把传入的值放在TRbTreeElement元素后面。
				 */
				memcpy((char*)(element+1),key,(size_t) tree->iKeySize);
			}
			else
			{
				/**
				 *     把传入key指针的地址存在TRbTreeElement元素的后面。
				 */
				*((void**) (element+1))=key;
			}
			
			element->count=1;				/* May give warning in purify */
			tree->elementsInTree++;
			rb_insert(tree,parent,element);		/* rebalance tree */
		}
		else
		{
			if (tree->flag & TREE_NO_DUPS)
			{
				*retStatus = 4;
				return(NULL);
			}
			element->count++;
		}
		DBUG_EXECUTE("check_tree", test_rb_tree(tree->root););
		return element;
	}

	/**
	 *     删除树中的一个元素，注意中有当树的withDelete值为正时（即不使用内存池
	 * 时），才可以调用此函数，否则函数返回1。
	 */
	int CLRbTree::TreeDelete(TRbTree *tree, void *key, void *customArg)
	{
		int cmp,remove_colour;
		TRbTreeElement *element,***parent, ***org_parent, *nod;
		if (!tree->withDelete)
			return 1;					/* not allowed */

		parent= tree->parents;
		*parent= &tree->root; element= tree->root;
		for (;;)
		{
			if (element == &tree->null_element)
				return 1;				/* Was not in tree */
			if ((cmp = (*tree->compare)(customArg, ELEMENT_KEY(tree,element),
				key)) == 0)
				break;
			if (cmp < 0)
			{
				*++parent= &element->right; element= element->right;
			}
			else
			{
				*++parent = &element->left; element= element->left;
			}
		}
		if (element->left == &tree->null_element)
		{
			(**parent)=element->right;
			remove_colour= element->colour;
		}
		else if (element->right == &tree->null_element)
		{
			(**parent)=element->left;
			remove_colour= element->colour;
		}
		else
		{
			org_parent= parent;
			*++parent= &element->right; nod= element->right;
			while (nod->left != &tree->null_element)
			{
				*++parent= &nod->left; nod= nod->left;
			}
			(**parent)=nod->right;		/* unlink nod from tree */
			remove_colour= nod->colour;
			org_parent[0][0]=nod;		/* put y in place of element */
			org_parent[1]= &nod->right;
			nod->left=element->left;
			nod->right=element->right;
			nod->colour=element->colour;
		}
		if (remove_colour == BLACK)
			rb_delete_fixup(tree,parent);
		if (tree->OnTreeElementFree)
			(*tree->OnTreeElementFree)(ELEMENT_KEY(tree,element), FREE_FREE, tree->customArg);
		SafeFree((gptr) element, 0);
		tree->elementsInTree--;
		return 0;
	}

	/**
	 *     在树中查找指定的KEY，如果找到返回树中指向的KEY的地址，否则返回NULL。
	 */
	void *CLRbTree::TreeSearch(TRbTree *tree, void *key, void *customArg)
	{
		int cmp;
		TRbTreeElement *element=tree->root;

		for (;;)
		{
			if (element == &tree->null_element)
			{
				return (void*) 0;
			}
			if ((cmp = (*tree->compare)(customArg, ELEMENT_KEY(tree,element),key)) == 0)
			{
				return ELEMENT_KEY(tree,element);
			}
			if (cmp < 0)
			{
				element=element->right;
			}
			else
			{
				element=element->left;
			}
		}
	}

	/**
	 *     查找指定的元素，同时生成边界元素到根节点的父节点列表parents，以及当
	 * 前元素的位置last_pos，他们的定义由使用者提供。
	 * @return 找到返回元素键key的指针，否则返回空。
	 */
	void *CLRbTree::TreeSearchKey(TRbTree *tree, const void *key, 
		TRbTreeElement **parents, TRbTreeElement ***last_pos,void *customArg)
	{
		int cmp;
		TRbTreeElement *element= tree->root;
		TRbTreeElement **last_left_step_parent= NULL, **last_right_step_parent= NULL;
		TRbTreeElement **last_equal_element= NULL;

		*parents = &tree->null_element;
		while (element != &tree->null_element)
		{
			*++parents= element;
			if ((cmp= (*tree->compare)(customArg, ELEMENT_KEY(tree, element), key)) == 0)
			{
				last_equal_element= parents;
			}
			if (cmp < 0)
			{
				last_right_step_parent= parents;
				element= element->right;
			}
			else
			{
				last_left_step_parent= parents;
				element= element->left;
			}
		}
		*last_pos= parents;
		return *last_pos ? ELEMENT_KEY(tree, **last_pos) : NULL;
	}

	/**
	 *     查找边界元素：查找在树中的第一个（最左边）或最后一个元素（最右边），
	 * 同时生成边界元素到根节点的父节点列表parents，此变量的定义由使用者提供，
	 * 一般定义为“NSPrime::CLRbTree::TRbTreeElement *parents[MAX_TREE_HEIGHT+1]”，child_offs的值可
	 * 用OffsetOf宏得到成员在结构体的偏移量，如：
	 *        （1）OffsetOf(TRbTreeElement, left)得到左子节点的偏移量，
	 *        （2）OffsetOf(TRbTreeElement, right)得到右子节点的偏移量。
	 * @return 找到返回边界节点元素键key的指针，否则返回空。
	 */
	gptr CLRbTree::TreeSearchEdge(TRbTree *tree, TRbTreeElement **parents, 
		TRbTreeElement ***last_pos, int child_offs)
	{
		TRbTreeElement *element= tree->root;

		*parents= &tree->null_element;
		while (element != &tree->null_element)
		{
			*++parents= element;
			element= ELEMENT_CHILD(element, child_offs);
		}
		*last_pos= parents;
		return **last_pos != &tree->null_element ? ELEMENT_KEY(tree, **last_pos) : (gptr)NULL;
	}

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
	void *CLRbTree::TreeSearchNext(TRbTree *tree, TRbTreeElement ***last_pos, int l_offs, int r_offs)
	{
		TRbTreeElement *x= **last_pos;

		if (ELEMENT_CHILD(x, r_offs) != &tree->null_element)
		{
			x= ELEMENT_CHILD(x, r_offs);
			*++*last_pos= x;
			while (ELEMENT_CHILD(x, l_offs) != &tree->null_element)
			{
				x= ELEMENT_CHILD(x, l_offs);
				*++*last_pos= x;
			}
			return ELEMENT_KEY(tree, x);
		}
		else
		{
			TRbTreeElement *y= *--*last_pos;
			while (y != &tree->null_element && x == ELEMENT_CHILD(y, r_offs))
			{
				x= y;
				y= *--*last_pos;
			}
			return y == &tree->null_element ? NULL : ELEMENT_KEY(tree, y);
		}
	}

	/**
	 *     假定树为一棵完全的平衡的二叉树（从根到树中的每一个叶都有相同的长度）。
	 * 返回指定键值在树中的位置，按照键的大小顺序进行排序，基数从1开始。
	 *     成功返回位置，不成功返回零。
	 */
	ub8 CLRbTree::TreeRecordPos(TRbTree *tree, const void *key, void *customArg)
	{
		int cmp;
		TRbTreeElement *element= tree->root;
		ub8 pos = tree->elementsInTree / 2 + 1;
		ub8 addValue = pos >> 1;//当前层增加或减少的数。

		while (element != &tree->null_element)
		{
			if ((cmp= (*tree->compare)(customArg, ELEMENT_KEY(tree, element), key)) == 0)
			{
				return pos;
			}
			
			if (cmp < 0)
			{
				pos += addValue;
				element= element->right;
			}
			else
			{
				pos -= addValue;
				element= element->left;
			}
			addValue = addValue >> 1;
		}
		return 0;
	}

	/**
	 *    漫游红黑树，参数visit指出漫游的方向：
	 *        （1）当visit==LEFT_ROOT_RIGHT 按left --> root --> right的方向漫游树。
	 *        （2）当visit==RIGHT_ROOT_LEFT 按right --> root --> left的方向漫游树。
	 *    正确返回零，否则返回错误代码。
	 */
	int CLRbTree::TreeWalk(TRbTree *tree, TreeWalkAction action, void *argument, TREE_WALK visit)
	{
		switch (visit)
		{
		case LEFT_ROOT_RIGHT:
			return tree_walk_left_root_right(tree,tree->root,action,argument);
		case RIGHT_ROOT_LEFT:
			return tree_walk_right_root_left(tree,tree->root,action,argument);
		}
		return 0;			/* Keep gcc happy */
	}

	/**
	 *    按left --> root --> right的方向漫游树，正确返回零，否则返回错误代码。
	 */
	int CLRbTree::tree_walk_left_root_right(TRbTree *tree, TRbTreeElement *element, TreeWalkAction action, void *argument)
	{
		int error;
		if (element->left)				/* Not null_element */
		{
			if ((error=tree_walk_left_root_right(tree,element->left,action,argument)) == 0 &&
				(error=(*action)(ELEMENT_KEY(tree,element),(element_count) element->count,argument)) == 0)
			{
				error=tree_walk_left_root_right(tree,element->right,action,argument);
			}
			return error;
		}
		return 0;
	}

	/**
	 *    按right --> root --> left的方向漫游树，正确返回零，否则返回错误代码。
	 */
	int CLRbTree::tree_walk_right_root_left(TRbTree *tree, TRbTreeElement *element, TreeWalkAction action, void *argument)
	{
		int error;
		if (element->right)				/* Not null_element */
		{
			if ((error=tree_walk_right_root_left(tree,element->right,action,argument)) == 0 &&
				(error=(*action)(ELEMENT_KEY(tree,element),(element_count) element->count,argument)) == 0)
			{
				error=tree_walk_right_root_left(tree,element->left,action,argument);
			}
			return error;
		}
		return 0;
	}


	/**
	 *     Functions to fix up the tree after insert and delete
	 */
	void CLRbTree::left_rotate(TRbTreeElement **parent, TRbTreeElement *leaf)
	{
		TRbTreeElement *y;

		y=leaf->right;
		leaf->right=y->left;
		parent[0]=y;
		y->left=leaf;
	}

	/**
	 *     Functions to fix up the tree after insert and delete
	 */
	void CLRbTree::right_rotate(TRbTreeElement **parent, TRbTreeElement *leaf)
	{
		TRbTreeElement *x;

		x=leaf->left;
		leaf->left=x->right;
		parent[0]=x;
		x->right=leaf;
	}

	void CLRbTree::rb_insert(TRbTree *tree, TRbTreeElement ***parent, TRbTreeElement *leaf)
	{
		TRbTreeElement *y,*par,*par2;

		leaf->colour=RED;
		while (leaf != tree->root && (par=parent[-1][0])->colour == RED)
		{
			if (par == (par2=parent[-2][0])->left)
			{
				y= par2->right;
				if (y->colour == RED)
				{
					par->colour=BLACK;
					y->colour=BLACK;
					leaf=par2;
					parent-=2;
					leaf->colour=RED;		/* And the loop continues */
				}
				else
				{
					if (leaf == par->right)
					{
						left_rotate(parent[-1],par);
						par=leaf;			/* leaf is now parent to old leaf */
					}
					par->colour=BLACK;
					par2->colour=RED;
					right_rotate(parent[-2],par2);
					break;
				}
			}
			else
			{
				y= par2->left;
				if (y->colour == RED)
				{
					par->colour=BLACK;
					y->colour=BLACK;
					leaf=par2;
					parent-=2;
					leaf->colour=RED;		/* And the loop continues */
				}
				else
				{
					if (leaf == par->left)
					{
						right_rotate(parent[-1],par);
						par=leaf;
					}
					par->colour=BLACK;
					par2->colour=RED;
					left_rotate(parent[-2],par2);
					break;
				}
			}
		}
		tree->root->colour=BLACK;
	}

	void CLRbTree::rb_delete_fixup(TRbTree *tree, TRbTreeElement ***parent)
	{
		TRbTreeElement *x,*w,*par;

		x= **parent;
		while (x != tree->root && x->colour == BLACK)
		{
			if (x == (par=parent[-1][0])->left)
			{
				w=par->right;
				if (w->colour == RED)
				{
					w->colour=BLACK;
					par->colour=RED;
					left_rotate(parent[-1],par);
					parent[0]= &w->left;
					*++parent= &par->left;
					w=par->right;
				}
				if (w->left->colour == BLACK && w->right->colour == BLACK)
				{
					w->colour=RED;
					x=par;
					parent--;
				}
				else
				{
					if (w->right->colour == BLACK)
					{
						w->left->colour=BLACK;
						w->colour=RED;
						right_rotate(&par->right,w);
						w=par->right;
					}
					w->colour=par->colour;
					par->colour=BLACK;
					w->right->colour=BLACK;
					left_rotate(parent[-1],par);
					x=tree->root;
					break;
				}
			}
			else
			{
				w=par->left;
				if (w->colour == RED)
				{
					w->colour=BLACK;
					par->colour=RED;
					right_rotate(parent[-1],par);
					parent[0]= &w->right;
					*++parent= &par->right;
					w=par->left;
				}
				if (w->right->colour == BLACK && w->left->colour == BLACK)
				{
					w->colour=RED;
					x=par;
					parent--;
				}
				else
				{
					if (w->left->colour == BLACK)
					{
						w->right->colour=BLACK;
						w->colour=RED;
						left_rotate(&par->left,w);
						w=par->left;
					}
					w->colour=par->colour;
					par->colour=BLACK;
					w->left->colour=BLACK;
					right_rotate(parent[-1],par);
					x=tree->root;
					break;
				}
			}
		}
		x->colour=BLACK;
	}

#ifndef DBUG_OFF

	/* Test that the proporties for a red-black tree holds */

	int CLRbTree::test_rb_tree(TRbTreeElement *element)
	{
		int count_l,count_r;

		if (!element->left)
			return 0;				/* Found end of tree */
		if (element->colour == RED &&
			(element->left->colour == RED || element->right->colour == RED))
		{
			printf("Wrong tree: Found two red in a row\n");
			return -1;
		}
		count_l=test_rb_tree(element->left);
		count_r=test_rb_tree(element->right);
		if (count_l >= 0 && count_r >= 0)
		{
			if (count_l == count_r)
				return count_l+(element->colour == BLACK);
			printf("Wrong tree: Incorrect black-count: %d - %d\n",count_l,count_r);
		}
		return -1;
	}
#endif
}
