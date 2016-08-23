#pragma once

//#include "global.h"
/**
 *     NSPrime ��������ռ�
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
		 *     ������ʱ����������
		 */
		typedef int (*TreeWalkAction)(void *,element_count,void *);

		/**
		 *     ���ͷ��ڴ�ʱʹ�õ������궨�壬��������ֻ�е�TRbTree::withDelete
		 * ��ֵΪ��ʱ�������壬��Ϊ�ڴ�ز���������Ԫ�ص�ɾ����
		 */
		typedef enum { FREE_INIT, FREE_FREE, FREE_END } TREE_FREE;
		/**
		 *     ����Ԫ���ڴ��ͷ�ʱ��ͬʱ���õĺ���ָ�롣
		 */
		typedef void (*TOnTreeElementFree)(void*, TREE_FREE, void *);

		typedef struct tagRbTreeElement
		{
			struct tagRbTreeElement *left,*right;
			ub4 count:31,
				colour:1;			/* black is marked as 1������BLACK�� */
		} TRbTreeElement;

		typedef struct tagRbTree
		{
			TRbTreeElement *root,null_element;

			/**
			 *     ����MAX_TREE_HEIGHT��ָ��ָ��ָ���ָ�룬��Ԫ�ص���ʱ�б�
			 * �������в���һ��Ԫ��ʱ�õ��˱������˱����𵽶�ջ�����á�
			 */
			TRbTreeElement **parents[MAX_TREE_HEIGHT];
			
			/**
			 *     ���Ϊ�潫����Key��ֵ�����У����򱣴�Key�ĵ�ַ�����С�
			 */
			bool	isSaveKey;
			ub4		iKeySize;//��ֵ�Ĵ�С�����isSaveKeyΪtrue��Ϊ����ֵ�Ĵ�С��
			                 //����Ϊgptr�Ĵ��¡�

			ub4 elementsInTree;//���е�Ԫ�������ظ���Ԫ�ذ�һ�����㡣
			
			/**
			 *     ����ʹ�õ�����ڴ��С�����Ϊ���ʾû�����ơ���������ڴ���
			 * �ƣ����������м���Ԫ��ʱ�����Ѿ�������ڴ�������Ƶ��ڴ�ʱ������
			 * �����е�����Ԫ�أ�Ȼ����뵱ǰ��Ԫ�أ�
			 */
			ub8 memoryLimit;
			
			ub4 allocated;//���Ѿ�ʹ�õ��ڴ�������
			QsortCmp2 compare;

			void *customArg;//�û�����Ĳ�������Ҫ������TOnTreeElementFree�¼��ĺ����á�

			/**
			 *     ֻ�е�withDelete��ֵΪ��ʱ����ʹ���ڴ�أ�����ʹ��Malloc����
			 * ��̬���䡣
			 */
			NSPrime::TMemRoot memRoot;
			
			//�����ֵΪ��͵���NSPrime::CMalloc::Malloc����������͵���NSPrime::CMalloc::AllocRoot������
			bool withDelete;
			
			//�����еĽڵ����ͷ�ʱ�������¼���
			TOnTreeElementFree OnTreeElementFree;

			/**
			 *     ���ı�־λ����ֵΪTREE_NO_DUPSʱ��ʾ���в������ظ��Ľڵ㣬��
			 * ���ظ��Ľڵ�ʱTreeInsert�����ķ���״̬retStatus��Ϊ�㣨Ϊ4����
			 */
			ub4 flag;
		} TRbTree;
		
		
		/**
		 *     �õ���ֵkey�ĵ�ַ��
		 */
		static inline gptr  ELEMENT_KEY(TRbTree *tree,TRbTreeElement *element)
		{
			return tree->isSaveKey ? (void*) (element+1): *((void**) (element+1));
		}

		/**
		 *     ����offs�õ��ӽڵ�ĵ�ַ��
		 */
		static inline TRbTreeElement* ELEMENT_CHILD(TRbTreeElement *element, ub8 offs)
		{
			return (*(TRbTreeElement**)((char*)element + offs));
		}

	private:
		static const int	BLACK				=	1;//��ɫ�ڵ㶨��
		static const int	RED					=	0;//��ɫ�ڵ㶨��

		//Ĭ�Ϸ�����ֽڴ�С��
		static const int	DEFAULT_ALLOC_SIZE	=	8192;

		//Ĭ�ϵĶ����ֽڴ�С��
		static const int	DEFAULT_ALIGN_SIZE	=	8192;

		static int tree_walk_left_root_right(TRbTree *,TRbTreeElement *,TreeWalkAction,void *);
		static int tree_walk_right_root_left(TRbTree *,TRbTreeElement *,TreeWalkAction,void *);
		static void left_rotate(TRbTreeElement **parent,TRbTreeElement *leaf);
		static void right_rotate(TRbTreeElement **parent, TRbTreeElement *leaf);
		static void rb_insert(TRbTree *tree,TRbTreeElement ***parent,TRbTreeElement *leaf);
		static void rb_delete_fixup(TRbTree *tree,TRbTreeElement ***parent);
		static void FreeTree(TRbTree *tree, myf freeFlags);

		/**
		 *     ͨ��NSPrime::CMalloc::Free�����ݹ�ɾ��ָ����Ԫ���е���Ԫ�ؼ�ָ��Ԫ�ء�
		 * �����ĵݹ���ֹ����Ϊ��Ҷ�ڵ㣨null_element����
		 *     ������е�OnTreeElementFree����ָ�벻Ϊ�վ͵��ô˺���ָ�롣
		 *     ������е�withDelete��־Ϊ�棨�������㣩���͵���NSPrime::CMalloc::Free
		 * �����ͷŴ�Ԫ�ص��ڴ棬����Ͳ�ɾ��Ԫ�ؽ���ڴ档
		 *     ʹ���ڴ�ص�������ʹ�ô˺�����ע��ʹ�ô˺���ɾ�����еĽڵ�󣬴�����
		 * �����Ǻ������
		 */
		static void DeleteTreeElement(TRbTree *,TRbTreeElement *);
#ifndef DBUG_OFF
		/* The actuall code for handling binary trees */
		static int test_rb_tree(TRbTreeElement *element);
#endif
	public:
		/**
		 *     ��������ⲿ�ӿڡ�
		 */

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
		static void InitTree(TRbTree *tree, ub4 defaultAllocSize, ub8 memoryLimit,
					ub4 iKeySize, QsortCmp2 compare, bool withDelete,
				TOnTreeElementFree freeElement, void *customArg);

		/**
		 *     �˺������Ƕ�FreeFree�����ķ�װ�������ڵ���FreeTree�ĺ����У�freeFlags
		 * ������ֵΪ�㣬���Բ���ʹ�õ����ڴ�أ�������ͨ��Malloc�����������ͷ�����
		 * �������ڴ档
		 */
		static void DeleteTree(TRbTree*);

		/**
		 *     �˺������Ƕ�FreeFree�����ķ�װ�������ڵ���FreeTree�ĺ����У�freeFlags
		 * ������ֵΪNSPrime::CMalloc::MY_MARK_BLOCKS_FREE������������õ����ڴ�ػ�
		 * ����MarkBlocksFree��������ڴ���е����п�Ϊ��ʹ��״̬��
		 */
		static void ResetTree(TRbTree*);
		

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
		static TRbTreeElement *TreeInsert(TRbTree *tree,void *key, void *customArg, int *retStatus);


		/**
		 *     �����в���ָ����KEY������ҵ���������ָ���KEY�ĵ�ַ�����򷵻�NULL��
		 */
		static void *TreeSearch(TRbTree *tree, void *key, void *customArg);

		/**
		 *    ���κ����������visitָ�����εķ���
		 *        ��1����visit==LEFT_ROOT_RIGHT ��left --> root --> right�ķ�����������
		 *        ��2����visit==RIGHT_ROOT_LEFT ��right --> root --> left�ķ�����������
		 *    ��ȷ�����㣬���򷵻ش�����롣
		 */
		static int TreeWalk(TRbTree *tree,TreeWalkAction action,void *argument, TREE_WALK visit);
		
		/**
		 *     ɾ�����е�һ��Ԫ�أ�ע�����е�����withDeleteֵΪ��ʱ������ʹ���ڴ��
		 * ʱ�����ſ��Ե��ô˺���������������1��
		 */
		static int TreeDelete(TRbTree *tree, void *key, void *customArg);

		/**
		 *     ����ָ����Ԫ�أ�ͬʱ���ɱ߽�Ԫ�ص����ڵ�ĸ��ڵ��б�parents���Լ���
		 * ǰԪ�ص�λ��last_pos�����ǵĶ�����ʹ�����ṩ��
		 * @return �ҵ�����Ԫ�ؼ�key��ָ�룬���򷵻ؿա�
		 */
		static void *TreeSearchKey(TRbTree *tree, const void *key, 
							TRbTreeElement **parents, TRbTreeElement ***last_pos,void *customArg);

		/**
		 *     ���ұ߽�Ԫ�أ����������еĵ�һ��������ߣ������һ��Ԫ�أ����ұߣ���
		 * ͬʱ���ɱ߽�Ԫ�ص����ڵ�ĸ��ڵ��б�parents���˱����Ķ�����ʹ�����ṩ��
		 * һ�㶨��Ϊ��NSPrime::CLRbTree::TRbTreeElement *parents[MAX_TREE_HEIGHT+1]����child_offs��ֵ��
		 * ��OffsetOf��õ���Ա�ڽṹ���ƫ�������磺
		 *        ��1��OffsetOf(TRbTreeElement, left)�õ����ӽڵ��ƫ������
		 *        ��2��OffsetOf(TRbTreeElement, right)�õ����ӽڵ��ƫ������
		 * @return �ҵ����ر߽�ڵ�Ԫ�ؼ�key��ָ�룬���򷵻ؿա�
		 */
		static gptr TreeSearchEdge(TRbTree *tree, TRbTreeElement **parents, 
			TRbTreeElement ***last_pos, int child_offs);
		
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
		static void *TreeSearchNext(TRbTree *tree, TRbTreeElement ***last_pos, int l_offs, int r_offs);

		/**
		 *     �ٶ���Ϊһ����ȫ��ƽ��Ķ��������Ӹ������е�ÿһ��Ҷ������ͬ�ĳ��ȣ���
		 * ����ָ����ֵ�����е�λ�ã����ռ��Ĵ�С˳��������򣬻�����1��ʼ��
		 *     �ɹ�����λ�ã����ɹ������㡣
		 */
		static ub8 TreeRecordPos(TRbTree *tree, const void *key, void *customArg);
	};
}
