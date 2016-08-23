#include "libsys.h"

namespace NSPrime
{

	inline void bitmap_lock(MY_BITMAP *map)
	{
#ifdef THREAD
		if (map->mutex)
			map->mutex->Lock();
#endif
	}


	inline void bitmap_unlock(MY_BITMAP *map)
	{
#ifdef THREAD
		if (map->mutex)
			map->mutex->Unlock();
#endif
	}


	ub4 bitmap_init(MY_BITMAP *map, ub1 *buf, uint bitmap_size,
		ub4 thread_safe)
	{
		DBUG_ENTER("bitmap_init");

		DBUG_ASSERT((bitmap_size & 7) == 0);
		bitmap_size/=8;
		if (!(map->bitmap=buf) &&
			!(map->bitmap= (ub1*) SafeMalloc(bitmap_size +
			(thread_safe ?
			sizeof(CLCriticalSection) : 0),
			(myf)(MY_WME | MY_ZEROFILL))))
			return 1;
		map->bitmap_size=bitmap_size;
#ifdef THREAD
		if (thread_safe)
		{
			map->mutex=(CLCriticalSection *)(map->bitmap+bitmap_size);
			map->mutex->Init(0);
		}
		else
			map->mutex=0;
#endif
		DBUG_RETURN(0);
	}


	void bitmap_free(MY_BITMAP *map)
	{
		DBUG_ENTER("bitmap_free");
		if (map->bitmap)
		{
#ifdef THREAD
			if (map->mutex)
				map->mutex->Term();
#endif
			SafeFree((char*) map->bitmap, (myf)(0));
			map->bitmap=0;
		}
		DBUG_VOID_RETURN;
	}


	void bitmap_set_bit(MY_BITMAP *map, uint bitmap_bit)
	{
		DBUG_ASSERT(map->bitmap && bitmap_bit < map->bitmap_size*8);
		bitmap_lock(map);
		map->bitmap[bitmap_bit / 8] |= (1 << (bitmap_bit & 7));
		bitmap_unlock(map);
	}


	uint bitmap_set_next(MY_BITMAP *map)
	{
		ub1 *bitmap=map->bitmap;
		uint bit_found = MY_BIT_NONE;
		uint bitmap_size=map->bitmap_size*8;
		uint i;

		DBUG_ASSERT(map->bitmap);
		bitmap_lock(map);
		for (i=0; i < bitmap_size ; i++, bitmap++)
		{
			if (*bitmap != 0xff)
			{						/* Found slot with free bit */
				uint b;
				for (b=0; ; b++)
				{
					if (!(*bitmap & (1 << b)))
					{
						*bitmap |= 1<<b;
						bit_found = (i*8)+b;
						break;
					}
				}
				break;					/* Found bit */
			}
		}
		bitmap_unlock(map);
		return bit_found;
	}


	void bitmap_clear_bit(MY_BITMAP *map, uint bitmap_bit)
	{
		DBUG_ASSERT(map->bitmap && bitmap_bit < map->bitmap_size*8);
		bitmap_lock(map);
		map->bitmap[bitmap_bit / 8] &= ~ (1 << (bitmap_bit & 7));
		bitmap_unlock(map);
	}


	void bitmap_set_prefix(MY_BITMAP *map, uint prefix_size)
	{
		uint prefix_bytes, prefix_bits;

		DBUG_ASSERT(map->bitmap &&
			(prefix_size <= map->bitmap_size*8 || prefix_size == (uint) ~0));
		bitmap_lock(map);
		SetMinValue(prefix_size, map->bitmap_size*8);
		if ((prefix_bytes= prefix_size / 8))
			memset(map->bitmap, 0xff, prefix_bytes);
		if ((prefix_bits= prefix_size & 7))
			map->bitmap[prefix_bytes++]= (1 << prefix_bits)-1;
		if (prefix_bytes < map->bitmap_size)
			memset(map->bitmap+prefix_bytes, 0, map->bitmap_size-prefix_bytes);
		bitmap_unlock(map);
	}


	void bitmap_clear_all(MY_BITMAP *map)
	{
		bitmap_set_prefix(map, 0);
	}


	void bitmap_set_all(MY_BITMAP *map)
	{
		bitmap_set_prefix(map, ~0);
	}


	ub4 bitmap_is_prefix(const MY_BITMAP *map, uint prefix_size)
	{
		uint prefix_bits= prefix_size & 7, res= 0;
		ub1 *m= map->bitmap, *end_prefix= map->bitmap+prefix_size/8,
			*end= map->bitmap+map->bitmap_size;

		DBUG_ASSERT(map->bitmap && prefix_size <= map->bitmap_size*8);

		bitmap_lock((MY_BITMAP *)map);
		while (m < end_prefix)
			if (*m++ != 0xff)
				goto ret;

		if (prefix_bits && *m++ != (1 << prefix_bits)-1)
			goto ret;

		while (m < end)
			if (*m++ != 0)
				goto ret;

		res=1;
ret:
		bitmap_unlock((MY_BITMAP *)map);
		return res;
	}


	ub4 bitmap_is_clear_all(const MY_BITMAP *map)
	{
		return bitmap_is_prefix(map, 0);
	}

	ub4 bitmap_is_set_all(const MY_BITMAP *map)
	{
		return bitmap_is_prefix(map, map->bitmap_size*8);
	}


	ub4 bitmap_is_set(const MY_BITMAP *map, uint bitmap_bit)
	{
		DBUG_ASSERT(map->bitmap && bitmap_bit < map->bitmap_size*8);
		return map->bitmap[bitmap_bit / 8] & (1 << (bitmap_bit & 7));
	}


	ub4 bitmap_is_subset(const MY_BITMAP *map1, const MY_BITMAP *map2)
	{
		uint res=0;
		ub1 *m1=map1->bitmap, *m2=map2->bitmap, *end;

		DBUG_ASSERT(map1->bitmap && map2->bitmap &&
			map1->bitmap_size==map2->bitmap_size);
		bitmap_lock((MY_BITMAP *)map1);
		bitmap_lock((MY_BITMAP *)map2);

		end= m1+map1->bitmap_size;

		while (m1 < end)
		{
			if ((*m1++) & ~(*m2++))
				goto ret;
		}

		res=1;
ret:
		bitmap_unlock((MY_BITMAP *)map2);
		bitmap_unlock((MY_BITMAP *)map1);
		return res;
	}


	ub4 bitmap_cmp(const MY_BITMAP *map1, const MY_BITMAP *map2)
	{
		uint res;

		DBUG_ASSERT(map1->bitmap && map2->bitmap &&
			map1->bitmap_size==map2->bitmap_size);
		bitmap_lock((MY_BITMAP *)map1);
		bitmap_lock((MY_BITMAP *)map2);

		res= memcmp(map1->bitmap, map2->bitmap, map1->bitmap_size)==0;

		bitmap_unlock((MY_BITMAP *)map2);
		bitmap_unlock((MY_BITMAP *)map1);
		return res;
	}


	void bitmap_intersect(MY_BITMAP *map, const MY_BITMAP *map2)
	{
		ub1 *to=map->bitmap, *from=map2->bitmap, *end;
		uint len=map->bitmap_size, len2=map2->bitmap_size;

		DBUG_ASSERT(map->bitmap && map2->bitmap);
		bitmap_lock(map);
		bitmap_lock((MY_BITMAP *)map2);

		end= to+NSPrime::CLNumber::Min(len,len2);

		while (to < end)
			*to++ &= *from++;

		if (len2 < len)
		{
			end+=len-len2;
			while (to < end)
				*to++=0;
		}

		bitmap_unlock((MY_BITMAP *)map2);
		bitmap_unlock(map);
	}


	void bitmap_subtract(MY_BITMAP *map, const MY_BITMAP *map2)
	{
		ub1 *to=map->bitmap, *from=map2->bitmap, *end;

		DBUG_ASSERT(map->bitmap && map2->bitmap &&
			map->bitmap_size==map2->bitmap_size);
		bitmap_lock(map);
		bitmap_lock((MY_BITMAP *)map2);

		end= to+map->bitmap_size;

		while (to < end)
			*to++ &= ~(*from++);

		bitmap_unlock((MY_BITMAP *)map2);
		bitmap_unlock(map);
	}


	void bitmap_union(MY_BITMAP *map, const MY_BITMAP *map2)
	{
		ub1 *to=map->bitmap, *from=map2->bitmap, *end;

		DBUG_ASSERT(map->bitmap && map2->bitmap &&
			map->bitmap_size==map2->bitmap_size);
		bitmap_lock(map);
		bitmap_lock((MY_BITMAP *)map2);

		end= to+map->bitmap_size;

		while (to < end)
			*to++ |= *from++;

		bitmap_unlock((MY_BITMAP *)map2);
		bitmap_unlock(map);
	}

}
