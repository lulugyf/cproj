#pragma once

namespace NSPrime
{
typedef int	(*QsortCmp)(const void *,const void *);
typedef int	(*QsortCmp2)(void*, const void *,const void *);

	/* The following node is used to store ranges to avoid recursive calls */

	typedef struct st_stack
	{
		char *low,*high;
	} stack_node;

	/****************************************************************************
	** 'standard' quicksort with the following extensions:
	**
	** Can be compiled with the QsortCmp2 compare function
	** Store ranges on stack to avoid recursion
	** Use insert sort on small ranges
	** Optimize for sorting of pointers (used often by MySQL)
	** Use median comparison to find partition element
	*****************************************************************************/

	void qsort2(void *base_ptr, size_t count, size_t size, QsortCmp2 cmp,
		void *cmp_argument);
}
