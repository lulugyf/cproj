#pragma once

namespace NSPrime
{
/*
  Code for generell handling of priority Queues.
  Implemention of queues from "Algoritms in C" by Robert Sedgewick.
  Copyright Monty Program KB.
  By monty.
*/

typedef int (*TQueueCompare)(void *,ub1 *, ub1 *);

class CLQuery
{
public:
	CLQuery()
	{
		m_pRoot = NULL;
		m_pFirstCmpArg = NULL;
		m_iElementCount = 0;
		m_iMaxElementCount = 0;
		m_iOffsetToKey = 0;
		m_iMaxAtTop = 0;
		m_tQueryCompare = NULL;
	}
	ub1 **m_pRoot;
	ub4 m_iElementCount;
	ub4 m_iMaxElementCount;
	ub4 m_iMaxAtTop;			/* Set if queue_top gives max */
public:
	TQueueCompare m_tQueryCompare;
	ub4 m_iOffsetToKey;			/* compare is done on element+offset */
	void *m_pFirstCmpArg;

	inline ub1* queue_top() 
	{
		return m_pRoot[1];
	}

	inline ub1* queue_element(ub4 index)
	{
		return m_pRoot[index+1];
	}

	inline ub1* queue_end()
	{
		return m_pRoot[m_iElementCount];
	}

	/* Fix when element on top has been replaced */
	inline void queue_replaced()
	{
		return _downheap(1);
	}
public:
	bool init_queue(ub4 iMaxElementCount,ub4 iOffsetToKey,
	       ub4 iMaxAtTop, TQueueCompare compare,
	       void *pFirstCmpArg);
	bool reinit_queue(ub4 iMaxElementCount,ub4 iOffsetToKey,
					 ub4 iMaxAtTop, TQueueCompare compare,
					 void *pFirstCmpArg);
	bool resize_queue(ub4 iMaxElementCount);
	void delete_queue();
	void queue_insert(ub1 *element);
	ub1 *queue_remove(ub4 idx);
	void _downheap(ub4 idx);
	void queue_fix();
};

#define is_queue_inited(queue) ((queue)->m_pRoot != 0)

}
