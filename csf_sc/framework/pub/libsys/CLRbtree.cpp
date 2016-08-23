#include "libsys.h"

namespace NSPrime
{
	/**
	 *     ��ʼ��һ�ú������
	 * @param tree ָ��������
	 * @param defaultAllocSize ��ʹ���ڴ��ʱĬ�ϳ�ʼ������ڵ�Ĵ�С�������ֵ
	 *        С��DEFAULT_ALLOC_SIZE����ȡDEFAULT_ALLOC_SIZEֵ����withDelete��ֵ
	 *        Ϊ��ʱ�˲���û�����塣
	 * @param memoryLimit ��Ԫ������ʹ���ڴ�Ĵ�С���ƣ�Ϊ���ʾû�����ơ����
	 *        �����ڴ����ƣ����������м���Ԫ��ʱ�����Ѿ�������ڴ�������Ƶ��ڴ�
	 *        ʱ����������е�����Ԫ�أ�Ȼ����뵱ǰ��Ԫ�أ�
	 * @param iKeySize  ���Ҫ�����б������ֵ�������ֵԪ�صĴ�С��������Ϊ0��
	 * @param compare ����Ԫ��ֵ�ıȽϺ�����
	 * @param withDelete ��������ֵΪ�٣��������㣩���͵���InitAllocRoot������
	 *        ʼ���ڴ�أ��Ժ����е�Ԫ�ؾ�ʹ���ڴ���е��ڴ棻�����Ժ�Ԫ�ؾ͵���
	 *        ֱ�ӷ����ڴ�������ڴ�ء�ע����������ڴ�صĻ����Ͳ���һ��һ����
	 *        ɾ�����е�Ԫ�أ�ֻ��ɾ����������
	 * @param freeElement �����ֵΪ�����Ժ��ͷ�Ԫ�ص��ڴ�ʱ�ᴥ��OnTreeElementFree
	 *        �¼��������û�����ʹ�ô��¼��ͷ��û�������ڴ棬��Ԫ�����ݺ�key��
	 *        �ڴ档
	 * @param customArg �˲���Ϊ��������OnTreeElementFree�¼�ʱ������OnTreeElementFree
	 *        �¼��Ĳ�����
	 */
	void CLRbTree::InitTree(TRbTree *tree, ub4 defaultAllocSize, ub8 memoryLimit,
				ub4 iKeySize, QsortCmp2 compare, bool withDelete,
			TOnTreeElementFree freeElement, void *customArg)
	{
		DBUG_ENTER("InitTree");
		DBUG_PRINT("enter",("tree: %lx  iKeySize: %d",tree,iKeySize));

		/**
		 *     ʹ������ֽ�����DEFAULT_ALIGN_SIZE���롣
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
	 *     ���withDelete��ֵΪ������Ĳ���freeFlagsΪMY_MARK_BLOCKS_FREE��ɾ
	 * ����������Ԫ�ص��ڴ档
	 *     ������е�withDelete��־Ϊ�棨�������㣩���͵���DeleteTreeElement
	 * ɾ���ڴ��ڴ档�����ִ������Ĳ��裺
	 *     ��1��������е�OnTreeElementFree����ָ�벻Ϊ�գ�����������е�memoryLimit
	 * ��Ϊ�վ͵��ô�FREE_INIT������OnTreeElementFree����ָ�뺯����
	 *     ��2�����ŵ���DeleteTreeElement�������ִ�д�FREE_FREE������
	 * OnTreeElementFree����ָ�뺯����
	 *     ��3��Ȼ����ô�FREE_END������OnTreeElementFree����ָ�뺯����
	 *     ��4��������NSPrime::CLMalloc::FreeRoot�ͷ��ڴ���е��ڴ档
	 *     ����ʼ�����е�Ԫ�ظ������Ѿ�������ڴ��ֽ�����
	 * @param freeFlags �����ڴ�ص��ͷ�ѡ���ֵ����Ϊ
	 *        NSPrime::CLMalloc::MY_MARK_BLOCKS_FREE��Ϊ�㣬�ɲο�FreeRoot������
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
	 *     �˺������Ƕ�FreeFree�����ķ�װ�������ڵ���FreeTree�ĺ����У�freeFlags
	 * ������ֵΪ�㣬���Բ���ʹ�õ����ڴ�أ�������ͨ��Malloc�����������ͷ�����
	 * �������ڴ档
	 */
	void CLRbTree::DeleteTree(TRbTree* tree)
	{
		FreeTree(tree, (myf)(0)); /* SafeFree() memRoot if applicable */
	}

	/**
	 *     �˺������Ƕ�FreeFree�����ķ�װ�������ڵ���FreeTree�ĺ����У�freeFlags
	 * ������ֵΪNSPrime::CLMalloc::MY_MARK_BLOCKS_FREE������������õ����ڴ�ػ�
	 * ����MarkBlocksFree��������ڴ���е����п�Ϊ��ʹ��״̬��
	 */
	void CLRbTree::ResetTree(TRbTree* tree)
	{
		FreeTree(tree, (myf)(NSPrime::CLMalloc::MY_MARK_BLOCKS_FREE));
		/* do not SafeFree() memRoot if applicable, just mark blocks as free */
	}


	/**
	 *     ͨ��SafeFree�����ݹ�ɾ��ָ����Ԫ���е���Ԫ�ؼ�ָ��Ԫ�ء�
	 * �����ĵݹ���ֹ����Ϊ��Ҷ�ڵ㣨null_element����
	 *     ������е�OnTreeElementFree����ָ�벻Ϊ�վ͵��ô˺���ָ�롣
	 *     ������е�withDelete��־Ϊ�棨�������㣩���͵���SafeFree
	 * �����ͷŴ�Ԫ�ص��ڴ棬����Ͳ�ɾ��Ԫ�ؽ���ڴ档
	 *     ʹ���ڴ�ص�������ʹ�ô˺�����ע��ʹ�ô˺���ɾ�����еĽڵ�󣬴�����
	 * �����Ǻ������
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
	 *     �����в���һ��Ԫ�أ�����ɹ���������Ԫ��Ԫ�ص�ָ�룬���򷵻��㡣��ע
	 * �⣬������е�Ԫ���ѷ���ռ�Ĵ�С���������Ƶ��ڴ�ʱ���������Ȼ����
	 * ResetTree������������Ѿ����ڵĽڵ㣬Ȼ���ٵ���TreeInsert���������ش˺���
	 * ��ֵ��
	 *     ����������룬���ز���Ľڵ㣬���򷵻ؿգ����ؿ������µļ������֮һ
	 * ���£�
	 *     ��1���ڴ治�㣺��Ϊ�ڳ�����ָ����MY_WME����������û�ָ����
	 *          NSPrime::CGlobalErrors::ErrorHandlerHook�����ľ��ϵͳ���Զ���
	 *          ���û�����ĺ�����
	 *     ��2�������Ѿ�����ָ���ļ�Key��������TRbTree->flag& TREE_NO_DUPSΪ�棬
	 *          �����ĳ�ʼ������InitTree��ָ����ֵΪ�٣��㣩��
	 *@param retStatus ֵΪ���£�
	 *                 ��1��������Ԫ�ر����ʱֵΪ 1
	 *                 ��2�����ڴ治��ʱֵΪ 2��
	 *                 ��3���������ظ���¼������TRbTree->flag& TREE_NO_DUPSΪ��
	 *                      ʱֵΪ4��
	 *                 ��4����������ʱ��ֵ���䣬Ϊ���������ֵ��
	 */
	CLRbTree::TRbTreeElement *CLRbTree::TreeInsert(TRbTree *tree, void *key, 
		void* customArg, int *retStatus)
	{
		int cmp;
		TRbTreeElement *element,***parent;

		/**
		 *     ����Ҫ�����λ��
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
				 *     �Ѵ����ֵ����TRbTreeElementԪ�غ��档
				 */
				memcpy((char*)(element+1),key,(size_t) tree->iKeySize);
			}
			else
			{
				/**
				 *     �Ѵ���keyָ��ĵ�ַ����TRbTreeElementԪ�صĺ��档
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
	 *     ɾ�����е�һ��Ԫ�أ�ע�����е�����withDeleteֵΪ��ʱ������ʹ���ڴ��
	 * ʱ�����ſ��Ե��ô˺���������������1��
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
	 *     �����в���ָ����KEY������ҵ���������ָ���KEY�ĵ�ַ�����򷵻�NULL��
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
	 *     ����ָ����Ԫ�أ�ͬʱ���ɱ߽�Ԫ�ص����ڵ�ĸ��ڵ��б�parents���Լ���
	 * ǰԪ�ص�λ��last_pos�����ǵĶ�����ʹ�����ṩ��
	 * @return �ҵ�����Ԫ�ؼ�key��ָ�룬���򷵻ؿա�
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
	 *     ���ұ߽�Ԫ�أ����������еĵ�һ��������ߣ������һ��Ԫ�أ����ұߣ���
	 * ͬʱ���ɱ߽�Ԫ�ص����ڵ�ĸ��ڵ��б�parents���˱����Ķ�����ʹ�����ṩ��
	 * һ�㶨��Ϊ��NSPrime::CLRbTree::TRbTreeElement *parents[MAX_TREE_HEIGHT+1]����child_offs��ֵ��
	 * ��OffsetOf��õ���Ա�ڽṹ���ƫ�������磺
	 *        ��1��OffsetOf(TRbTreeElement, left)�õ����ӽڵ��ƫ������
	 *        ��2��OffsetOf(TRbTreeElement, right)�õ����ӽڵ��ƫ������
	 * @return �ҵ����ر߽�ڵ�Ԫ�ؼ�key��ָ�룬���򷵻ؿա�
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
	 *     �ҵ���ǰ��ֵ��**last_pos������һ����ֵ��������ͼ�С�8������һ����ֵ
	 * �ǡ�7��������5������һ����ֵΪ��4����
	 *
	 *          last_pos-->   8    
	 *              4                       12
	 *         2        6             10           14
	 *      1    3    5    7       9    11     13     15
	 * @param last_pos ��ʼ���ҵĽڵ��ַ���˱���ָ��һ��������б��˸����б�
	 *                 ������TreeSearchEdge��TreeSearchKey��TreeSearchNext����
	 *                 ���ɵġ�
	 * @param l_offs   ��������ƫ����
	 * @param r_offs   ��������ƫ����
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
	 *     �ٶ���Ϊһ����ȫ��ƽ��Ķ��������Ӹ������е�ÿһ��Ҷ������ͬ�ĳ��ȣ���
	 * ����ָ����ֵ�����е�λ�ã����ռ��Ĵ�С˳��������򣬻�����1��ʼ��
	 *     �ɹ�����λ�ã����ɹ������㡣
	 */
	ub8 CLRbTree::TreeRecordPos(TRbTree *tree, const void *key, void *customArg)
	{
		int cmp;
		TRbTreeElement *element= tree->root;
		ub8 pos = tree->elementsInTree / 2 + 1;
		ub8 addValue = pos >> 1;//��ǰ�����ӻ���ٵ�����

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
	 *    ���κ����������visitָ�����εķ���
	 *        ��1����visit==LEFT_ROOT_RIGHT ��left --> root --> right�ķ�����������
	 *        ��2����visit==RIGHT_ROOT_LEFT ��right --> root --> left�ķ�����������
	 *    ��ȷ�����㣬���򷵻ش�����롣
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
	 *    ��left --> root --> right�ķ�������������ȷ�����㣬���򷵻ش�����롣
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
	 *    ��right --> root --> left�ķ�������������ȷ�����㣬���򷵻ش�����롣
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
