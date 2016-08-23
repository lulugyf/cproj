#include "libsys.h"

namespace NSPrime
{
	/*
	Initiate dynamic array

	SYNOPSIS
	init_dynamic_array()
	array		Pointer to an array
	element_size	Size of element
	init_alloc	Number of initial elements
	alloc_increment	Increment for adding new elements

	DESCRIPTION
	init_dynamic_array() initiates array and allocate space for 
	init_alloc eilements. 
	Array is usable even if space allocation failed.

	RETURN VALUE
	TRUE	my_malloc_ci() failed
	FALSE	Ok
	*/

	bool init_dynamic_array(DYNAMIC_ARRAY *array, unsigned long element_size,
		unsigned long init_alloc,
		unsigned long alloc_increment)
	{
		DBUG_ENTER("init_dynamic_array");
		if (!alloc_increment)
		{
			alloc_increment=NSPrime::CLNumber::Max((8192-NSPrime::CLMalloc::MALLOC_OVERHEAD)/element_size,(unsigned long)16);
			if (init_alloc > 8 && alloc_increment > init_alloc * 2)
				alloc_increment=init_alloc*2;
		}

		if (!init_alloc)
			init_alloc=alloc_increment;
		array->elements=0;
		array->max_element=init_alloc;
		array->alloc_increment=alloc_increment;
		array->size_of_element=element_size;
		if (!(array->buffer=(char*) SafeMalloc(element_size*init_alloc,(myf)(MY_WME))))
		{
			array->max_element=0;
			DBUG_RETURN(TRUE);
		}
		DBUG_RETURN(FALSE);
	} 

	/*
	Insert element at the end of array. Allocate memory if needed.

	SYNOPSIS
	insert_dynamic()
	array
	element

	RETURN VALUE
	TRUE	Insert failed
	FALSE	Ok
	*/

	bool insert_dynamic(DYNAMIC_ARRAY *array, gptr element)
	{
		gptr buffer;
		if (array->elements == array->max_element)
		{						/* Call only when nessesary */
			if (!(buffer=alloc_dynamic(array)))
				return TRUE;
		}
		else
		{
			buffer=array->buffer+(array->elements * array->size_of_element);
			array->elements++;
		}
		memcpy(buffer,element,(size_t) array->size_of_element);
		return FALSE;
	}


	/*
	Alloc space for next element(s) 

	SYNOPSIS
	alloc_dynamic()
	array

	DESCRIPTION
	alloc_dynamic() checks if there is empty space for at least
	one element if not tries to allocate space for alloc_increment
	elements at the end of array.

	RETURN VALUE
	pointer	Pointer to empty space for element
	0		Error
	*/

	ub1 *alloc_dynamic(DYNAMIC_ARRAY *array)
	{
		if (array->elements == array->max_element)
		{
			char *new_ptr;
			if (!(new_ptr=(char*) NSPrime::CLMalloc::Realloc(array->buffer,(size_t)((array->max_element+
				array->alloc_increment)*
				array->size_of_element))))
				return 0;
			array->buffer=new_ptr;
			array->max_element+=array->alloc_increment;
		}
		return (ub1*)array->buffer+(array->elements++ * array->size_of_element);
	}


	/*
	Pop last element from array.

	SYNOPSIS
	pop_dynamic()
	array

	RETURN VALUE    
	pointer	Ok
	0		Array is empty
	*/

	ub1 *pop_dynamic(DYNAMIC_ARRAY *array)
	{
		if (array->elements)
			return (ub1*)(array->buffer+(--array->elements * array->size_of_element));
		return 0;
	}

	/*
	Replace elemnent in array with given element and index

	SYNOPSIS
	set_dynamic()
	array
	element	Element to be inserted
	idx	Index where element is to be inserted

	DESCRIPTION
	set_dynamic() replaces element in array. 
	If idx > max_element insert new element. Allocate memory if needed. 

	RETURN VALUE
	TRUE	Idx was out of range and allocation of new memory failed
	FALSE	Ok
	*/

	bool set_dynamic(DYNAMIC_ARRAY *array, gptr element, ub4 idx)
	{
		if (idx >= array->elements)
		{
			if (idx >= array->max_element)
			{
				unsigned long size;
				char *new_ptr;
				size=(idx+array->alloc_increment)/array->alloc_increment;
				size*= array->alloc_increment;
				if (!(new_ptr=(char*) NSPrime::CLMalloc::Realloc(array->buffer,(size_t)(size*
					array->size_of_element))))
					return TRUE;
				array->buffer=new_ptr;
				array->max_element=size;
			}
			memset((gptr) (array->buffer+array->elements*array->size_of_element),0,
				(size_t)((idx - array->elements)*array->size_of_element));
			array->elements=idx+1;
		}
		memcpy(array->buffer+(idx * array->size_of_element),element,
			(size_t) array->size_of_element);
		return FALSE;
	}

	/*
	Get an element from array by given index

	SYNOPSIS
	get_dynamic()
	array	
	gptr	Element to be returned. If idx > elements contain zeroes.
	idx	Index of element wanted. 
	*/

	void get_dynamic(DYNAMIC_ARRAY *array, gptr element, unsigned long idx)
	{
		if (idx >= array->elements)
		{
			DBUG_PRINT("warning",("To big array idx: %d, array size is %d",
				idx,array->elements));
			memset(element,0,(size_t)(array->size_of_element));
			return;
		}
		memcpy(element,array->buffer+idx*array->size_of_element,
			(size_t) array->size_of_element);
	}


	/*
	Empty array by freeing all memory

	SYNOPSIS
	delete_dynamic()
	array	Array to be deleted
	*/

	void delete_dynamic(DYNAMIC_ARRAY *array)
	{
		if (array->buffer)
		{
			SafeFree(array->buffer, 0);
			array->buffer=0;
			array->elements=array->max_element=0;
		}
	}

	/*
	Delete element by given index

	SYNOPSIS
	delete_dynamic_element()
	array
	idx	Index of element to be deleted
	*/

	void delete_dynamic_element(DYNAMIC_ARRAY *array, ub4 idx)
	{
		char *ptr=array->buffer+array->size_of_element*idx;
		array->elements--;
		memmove(ptr,ptr+array->size_of_element,
			(size_t)((array->elements-idx)*array->size_of_element));
	}


	/*
	Free unused memory

	SYNOPSIS
	freeze_size()
	array	Array to be freed

	*/

	void freeze_size(DYNAMIC_ARRAY *array)
	{
		unsigned long elements=NSPrime::CLNumber::Max(array->elements,(unsigned long)1);

		if (array->buffer && array->max_element != elements)
		{
			array->buffer=(char*) NSPrime::CLMalloc::Realloc(array->buffer,
				(size_t)(elements*array->size_of_element));
			array->max_element=elements;
		}
	}
}

