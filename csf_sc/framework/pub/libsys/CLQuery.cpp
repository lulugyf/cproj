#include "libsys.h"

namespace NSPrime
{

	/*
	Init queue

	SYNOPSIS
	init_queue()
	queue		Queue to initialise
	iMaxElementCount	Max elements that will be put in queue
	iOffsetToKey	Offset to key in element stored in queue
	Used when sending pointers to compare function
	iMaxAtTop		Set to 1 if you want biggest element on top.
	compare		Compare function for elements, takes 3 arguments.
	pFirstCmpArg	First argument to compare function

	NOTES
	Will allocate max_element pointers for queue array

	RETURN
	ture	ok
	false	Could not allocate memory
	*/

	bool CLQuery::init_queue(ub4 iMaxElementCount, ub4 iOffsetToKey,
		ub4 iMaxAtTop, TQueueCompare compare,
		void *pFirstCmpArg)
	{
		DBUG_ENTER("init_queue");
		if ((m_pRoot= (ub1 **) SafeMalloc((iMaxElementCount+1)*sizeof(void*),(myf)(MY_WME))) == 0)
		{
			DBUG_RETURN(false);
		}
		m_iElementCount=0;
		m_tQueryCompare=compare;
		m_pFirstCmpArg=pFirstCmpArg;
		m_iMaxElementCount=iMaxElementCount;
		m_iOffsetToKey=iOffsetToKey;
		m_iMaxAtTop= iMaxAtTop ? (-1 ^ 1) : 0;
		DBUG_RETURN(true);
	}


	/*
	Reinitialize queue for other usage

	SYNOPSIS
	reinit_queue()
	queue		Queue to initialise
	iMaxElementCount	Max elements that will be put in queue
	iOffsetToKey	Offset to key in element stored in queue
	Used when sending pointers to compare function
	iMaxAtTop		Set to 1 if you want biggest element on top.
	compare		Compare function for elements, takes 3 arguments.
	pFirstCmpArg	First argument to compare function

	NOTES
	This will delete all elements from the queue.  If you don't want this,
	use resize_queue() instead.

	RETURN
	true			ok
	EE_OUTOFMEMORY	Wrong iMaxElementCount
	*/

	bool CLQuery::reinit_queue(ub4 iMaxElementCount, ub4 iOffsetToKey,
		ub4 iMaxAtTop, TQueueCompare compare,
		void *pFirstCmpArg)
	{
		DBUG_ENTER("reinit_queue");
		m_iElementCount=0;
		m_tQueryCompare=compare;
		m_pFirstCmpArg=pFirstCmpArg;
		m_iOffsetToKey=iOffsetToKey;
		m_iMaxAtTop= iMaxAtTop ? (-1 ^ 1) : 0;
		resize_queue(iMaxElementCount);
		DBUG_RETURN(true);
	}


	/*
	Resize queue

	SYNOPSIS
	resize_queue()
	queue			Queue
	iMaxElementCount		New max size for queue

	NOTES
	If you resize queue to be less than the elements you have in it,
	the extra elements will be deleted

	RETURN
	true	ok
	false	Error.  In this case the queue is unchanged
	*/

	bool CLQuery::resize_queue(ub4 iMaxElementCount)
	{
		ub1 **new_root;
		DBUG_ENTER("resize_queue");
		if (m_iMaxElementCount == iMaxElementCount)
			DBUG_RETURN(0);
		if ((new_root= (ub1 **) NSPrime::CLMalloc::Realloc((void *)m_pRoot,
			(iMaxElementCount+1)*sizeof(ub1*))) == 0)
		{
			DBUG_RETURN(false);
		}

		SetMinValue(m_iElementCount, iMaxElementCount);
		m_iMaxElementCount= iMaxElementCount;
		m_pRoot= new_root;
		DBUG_RETURN(true);
	}


	/*
	Delete queue

	SYNOPSIS
	delete_queue()
	queue		Queue to delete

	IMPLEMENTATION
	Just free allocated memory.

	NOTES
	Can be called safely multiple times
	*/

	void CLQuery::delete_queue()
	{
		DBUG_ENTER("delete_queue");
		if (m_pRoot)
		{
			SafeFree(m_pRoot, 0);
			m_pRoot = NULL;
		}
		DBUG_VOID_RETURN;
	}


	/* Code for insert, search and delete of elements */

	void CLQuery::queue_insert(ub1 *element)
	{
		reg2 ub4 idx,next;
		int cmp;

#ifndef DBUG_OFF
		if (m_iElementCount < m_iMaxElementCount)
#endif
		{
			m_pRoot[0]=element;
			idx= ++m_iElementCount;

			/* iMaxAtTop swaps the comparison if we want to order by desc */
			while ((cmp=m_tQueryCompare(m_pFirstCmpArg,
				element+m_iOffsetToKey,
				m_pRoot[(next=idx >> 1)] +
				m_iOffsetToKey)) &&
				(cmp ^ m_iMaxAtTop) < 0)
			{
				m_pRoot[idx]=m_pRoot[next];
				idx=next;
			}
			m_pRoot[idx]=element;
		}
	}

	/* Remove item from queue */
	/* Returns pointer to removed element */
	ub1 *CLQuery::queue_remove(ub4 idx)
	{
#ifndef DBUG_OFF
		if (idx >= m_iMaxElementCount)
			return 0;
#endif
		{
			ub1 *element=m_pRoot[++idx];	/* Intern index starts from 1 */
			m_pRoot[idx]=m_pRoot[m_iElementCount--];
			_downheap(idx);
			return element;
		}
	}


	/* Fix heap when index have changed */
	void CLQuery::_downheap(ub4 idx)
	{
		ub1 *element;
		ub4 elements,half_queue,next_index,iOffsetToKey;
		int cmp;

		iOffsetToKey=m_iOffsetToKey;
		element=m_pRoot[idx];
		half_queue=(elements=m_iElementCount) >> 1;

		while (idx <= half_queue)
		{
			next_index=idx+idx;
			if (next_index < elements &&
				(m_tQueryCompare(m_pFirstCmpArg,
				m_pRoot[next_index]+iOffsetToKey,
				m_pRoot[next_index+1]+iOffsetToKey) ^
				m_iMaxAtTop) > 0)
				next_index++;
			if ((cmp=m_tQueryCompare(m_pFirstCmpArg,
				m_pRoot[next_index]+iOffsetToKey,
				element+iOffsetToKey)) == 0 ||
				(cmp ^ m_iMaxAtTop) > 0)
				break;
			m_pRoot[idx]=m_pRoot[next_index];
			idx=next_index;
		}
		m_pRoot[idx]=element;
	}


	int queue_fix_cmp(CLQuery *pQuery, void **a, void **b)
	{
		return pQuery->m_tQueryCompare(pQuery->m_pFirstCmpArg,
			(ub1*) (*a)+pQuery->m_iOffsetToKey,
			(ub1*) (*b)+pQuery->m_iOffsetToKey);
	}

	/*
	Fix heap when every element was changed,
	actually, it can be done better, in linear time, not in n*log(n)
	*/

	void CLQuery::queue_fix()
	{
		qsort2(m_pRoot+1,m_iElementCount, sizeof(void *),
			(QsortCmp2)queue_fix_cmp, this);
	}
}
