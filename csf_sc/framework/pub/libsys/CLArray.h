#pragma once

#define dynamic_element(varray,array_index,type) ((type)((varray)->buffer) +(array_index))
#define push_dynamic(A,B) insert_dynamic(A,B)
#define reset_dynamic(varray) ((varray)->elements= 0)
#define dynamic_array_ptr(varray,array_index) ((varray)->buffer+(array_index)*(varray)->size_of_element)

namespace NSPrime
{
	typedef struct st_dynamic_array
	{
		char *buffer;
		unsigned long elements,max_element;
		unsigned long alloc_increment;
		unsigned long size_of_element;
	} DYNAMIC_ARRAY;
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
		unsigned long alloc_increment);

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

	bool insert_dynamic(DYNAMIC_ARRAY *array, gptr element);

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

	ub1 *alloc_dynamic(DYNAMIC_ARRAY *array);

	/*
	Pop last element from array.

	SYNOPSIS
	pop_dynamic()
	array

	RETURN VALUE    
	pointer	Ok
	0		Array is empty
	*/

	ub1 *pop_dynamic(DYNAMIC_ARRAY *array);

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

	bool set_dynamic(DYNAMIC_ARRAY *array, gptr element, ub4 idx);

	/*
	Get an element from array by given index

	SYNOPSIS
	get_dynamic()
	array	
	gptr	Element to be returned. If idx > elements contain zeroes.
	idx	Index of element wanted. 
	*/

	void get_dynamic(DYNAMIC_ARRAY *array, gptr element, unsigned long idx);

	/*
	Empty array by freeing all memory

	SYNOPSIS
	delete_dynamic()
	array	Array to be deleted
	*/

	void delete_dynamic(DYNAMIC_ARRAY *array);

	/*
	Delete element by given index

	SYNOPSIS
	delete_dynamic_element()
	array
	idx	Index of element to be deleted
	*/

	void delete_dynamic_element(DYNAMIC_ARRAY *array, ub4 idx);


	/*
	Free unused memory

	SYNOPSIS
	freeze_size()
	array	Array to be freed

	*/

	void freeze_size(DYNAMIC_ARRAY *array);
}
