#pragma once

#define MY_BIT_NONE (~(uint) 0)

namespace NSPrime
{
#define MY_BIT_NONE (~(uint) 0)

	typedef struct st_bitmap
	{
		ub1 *bitmap;
		uint bitmap_size;
		/*
		mutex will be acquired for the duration of each bitmap operation if
		thread_safe flag in bitmap_init was set.  Otherwise, we optimize by not
		acquiring the mutex
		*/
#ifdef THREAD
		CLCriticalSection *mutex;
#endif
	} MY_BITMAP;

	extern ub4 bitmap_cmp(const MY_BITMAP *map1, const MY_BITMAP *map2);
	extern ub4 bitmap_init(MY_BITMAP *map, ub1 *buf, uint bitmap_size, ub4 thread_safe);
	extern ub4 bitmap_is_clear_all(const MY_BITMAP *map);
	extern ub4 bitmap_is_prefix(const MY_BITMAP *map, uint prefix_size);
	extern ub4 bitmap_is_set(const MY_BITMAP *map, uint bitmap_bit);
	extern ub4 bitmap_is_set_all(const MY_BITMAP *map);
	extern ub4 bitmap_is_subset(const MY_BITMAP *map1, const MY_BITMAP *map2);
	extern uint bitmap_set_next(MY_BITMAP *map);
	extern void bitmap_clear_all(MY_BITMAP *map);
	extern void bitmap_clear_bit(MY_BITMAP *map, uint bitmap_bit);
	extern void bitmap_free(MY_BITMAP *map);
	extern void bitmap_intersect(MY_BITMAP *map, const MY_BITMAP *map2);
	extern void bitmap_set_all(MY_BITMAP *map);
	extern void bitmap_set_bit(MY_BITMAP *map, uint bitmap_bit);
	extern void bitmap_set_prefix(MY_BITMAP *map, uint prefix_size);
	extern void bitmap_subtract(MY_BITMAP *map, const MY_BITMAP *map2);
	extern void bitmap_union(MY_BITMAP *map, const MY_BITMAP *map2);

}
