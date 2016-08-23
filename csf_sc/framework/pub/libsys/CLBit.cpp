#include "libsys.h"

namespace NSPrime
{

	/* Some useful bit functions */

	/*
	Find smallest X in 2^X >= value
	This can be used to divide a number with value by doing a shift instead
	*/

	uint my_bit_log2(ulong value)
	{
		uint bit;
		for (bit=0 ; value > 1 ; value>>=1, bit++) ;
		return bit;
	}

	static char nbits[256] = {
		0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
		4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
	};

	uint my_count_bits(ub8 v)
	{
#if SIZEOF_LONG_LONG > 4
		/* The following code is a bit faster on 16 bit machines than if we would
		only shift v */
		ulong v2=(ulong) (v >> 32);
		return (uint) (ub1) (nbits[(ub1)  v] +
			nbits[(ub1) (v >> 8)] +
			nbits[(ub1) (v >> 16)] +
			nbits[(ub1) (v >> 24)] +
			nbits[(ub1) (v2)] +
			nbits[(ub1) (v2 >> 8)] +
			nbits[(ub1) (v2 >> 16)] +
			nbits[(ub1) (v2 >> 24)]);
#else
		return (uint) (ub1) (nbits[(ub1)  v] +
			nbits[(ub1) (v >> 8)] +
			nbits[(ub1) (v >> 16)] +
			nbits[(ub1) (v >> 24)]);
#endif
	}
}
