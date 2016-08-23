/*
Defines: int2str(), itoa(), ltoa()

int2str(dst, radix, val)
converts the (long) integer "val" to character form and moves it to
the destination string "dst" followed by a terminating NUL.  The
result is normally a pointer to this NUL character, but if the radix
is dud the result will be NULL and nothing will be changed.

If radix is -2..-36, val is taken to be SIGNED.
If radix is  2.. 36, val is taken to be UNSIGNED.
That is, val is signed if and only if radix is.  You will normally
use radix -10 only through itoa and ltoa, for radix 2, 8, or 16
unsigned is what you generally want.

_dig_vec is public just in case someone has a use for it.
The definitions of itoa and ltoa are actually macros in m_string.h,
but this is where the code is.

Note: The standard itoa() returns a pointer to the argument, when int2str
returns the pointer to the end-null.
itoa assumes that 10 -base numbers are allways signed and other arn't.
*/

#include "libdbug.h"

namespace NSPrime
{
	/*全局变量*/
	const char CLNumber::_dig_vec[DIG_VEC_LENGTH+1] =  "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	char *CLNumber::int2str(register long int val, register char *dst, register int radix)
	{
		char buffer[65];
		register char *p;
		long int new_val;

		if (radix < 0) {
			if (radix < -36 || radix > -2) return NULL;
			if (val < 0) {
				*dst++ = '-';
				val = -val;
			}
			radix = -radix;
		} else {
			if (radix > 36 || radix < 2) return NULL;
		}
		/*  The slightly contorted code which follows is due to the
		fact that few machines directly support unsigned long / and %.
		Certainly the VAX C compiler generates a subroutine call.  In
		the interests of efficiency (hollow laugh) I let this happen
		for the first digit only; after that "val" will be in range so
		that signed integer division will do.  Sorry 'bout that.
		CHECK THE CODE PRODUCED BY YOUR C COMPILER.  The first % and /
		should be unsigned, the second % and / signed, but C compilers
		tend to be extraordinarily sensitive to minor details of style.
		This works on a VAX, that's all I claim for it.
		*/
		p = &buffer[sizeof(buffer)-1];
		*p = '\0';
		new_val=(long)((ub8) val / (ub8) radix);
		*--p = _dig_vec[(ub1) ((ub8) val- (ub8) new_val*(ub8) radix)];
		val = new_val;
		while (val != 0)
		{
			new_val=val/radix;
			*--p = _dig_vec[(ub1) (val-new_val*radix)];
			val= new_val;
		}
		while ((*dst++ = *p++) != 0) ;
		return dst-1;
	}


	/*
	This is a faster version of the above optimized for the normal case of
	radix 10 / -10
	*/

	char *CLNumber::int10_to_str(sb8 val,char *dst,int radix)
	{
		char buffer[65];
		register char *p;
		sb8 new_val;

		if (radix < 0)				/* -10 */
		{
			if (val < 0)
			{
				*dst++ = '-';
				val = -val;
			}
		}

		p = &buffer[sizeof(buffer)-1];
		*p = '\0';
		new_val= (sb8) ((ub8) val / 10);
		*--p = '0'+ (char) ((ub8) val - (ub8) new_val * 10);
		val = new_val;

		while (val != 0)
		{
			new_val=val/10;
			*--p = '0' + (char) (val-new_val*10);
			val= new_val;
		}
		while ((*dst++ = *p++) != 0) ;
		return dst-1;
	}

	char *CLNumber::Int64ToStr(sb8 val,char *dst,int radix)
	{
		char buffer[65];
		register char *p;
		sb4 long_val;

		if (radix < 0)
		{
			if (radix < -36 || radix > -2) return (char*) 0;
			if (val < 0) {
				*dst++ = '-';
				val = -val;
			}
			radix = -radix;
		}
		else
		{
			if (radix > 36 || radix < 2) return (char*) 0;
		}
		if (val == 0)
		{
			*dst++='0';
			*dst='\0';
			return dst;
		}
		p = &buffer[sizeof(buffer)-1];
		*p = '\0';

		while ((ub8) val > (ub8) LONG_MAX)
		{
			ub8 quo=(ub8) val/(ub4) radix;
			ub4 rem= (ub4) (val- quo* (ub4) radix);
			*--p = _dig_vec[rem];
			val= quo;
		}
		long_val= (sb4) val;
		while (long_val != 0)
		{
			long quo= long_val/radix;
			*--p = _dig_vec[(ub1) (long_val - quo*radix)];
			long_val= quo;
		}
		while ((*dst++ = *p++) != 0) ;
		return dst-1;
	}

	char *CLNumber::Int64ToStr_10(sb8 val,char *dst,int radix)
	{
		char buffer[65];
		register char *p;
		ub4 long_val;

		if (radix < 0)
		{
			if (val < 0)
			{
				*dst++ = '-';
				val = -val;
			}
		}

		if (val == 0)
		{
			*dst++='0';
			*dst='\0';
			return dst;
		}
		p = &buffer[sizeof(buffer)-1];
		*p = '\0';

		while ((ub8) val > (ub8) LONG_MAX)
		{
			ub8 quo=(ub8) val/(ub4) 10;
			ub4 rem= (ub4) (val- quo* (ub4) 10);
			*--p = _dig_vec[rem];
			val= quo;
		}
		long_val= (sb4) val;
		while (long_val != 0)
		{
			long quo= long_val/10;
			*--p = _dig_vec[(ub1) (long_val - quo*10)];
			long_val= quo;
		}
		while ((*dst++ = *p++) != 0) ;
		return dst-1;
	}

#define INIT_CNT  9
#define LFACTOR   (sb8)(1000000000)
#define LFACTOR1  (sb8)(10000000000LL)
#define LFACTOR2  (sb8)(100000000000LL)
static unsigned long lfactor[9]=
{
  1L, 10L, 100L, 1000L, 10000L, 100000L, 1000000L, 10000000L, 100000000L
};

	/*
	  Convert a string to an to unsigned long long integer value
	  
	  SYNOPSYS
		StrToSB8_10()
		  nptr     in       pointer to the string to be converted
		  endptr   in/out   pointer to the end of the string/
							pointer to the stop character
		  error    out      returned error code
	 
	  DESCRIPTION
		This function takes the decimal representation of integer number
		from string nptr and converts it to an signed or unsigned
		long long integer value.
		Space characters and tab are ignored.
		A sign character might precede the the digit characters. The number
		may have any number of pre-zero digits.

		The function stops reading the string nptr at the first character
		that is not a decimal digit. If endptr is not NULL then the function
		will not read characters after *endptr.
	 
	  RETURN VALUES
		Value of string as a signed/unsigned longlong integer

		if no error and endptr != NULL, it will be set to point at the character
		after the number

		The error parameter contains information how things went:
		-1		Number was an ok negative number
		0	 	ok
		ERANGE	If the the value of the converted number exceeded the
				maximum negative/unsigned long long integer.
			In this case the return value is ~0 if value was
			positive and LONGLONG_MIN if value was negative.
		EDOM	If the string didn't contain any digits. In this case
    			the return value is 0.

		If endptr is not NULL the function will store the end pointer to
		the stop character here.
	*/
	sb8 CLNumber::StrToSB8_10(const char *nptr, char **endptr, int *error)
	{
		const char *s, *end, *start, *n_end, *true_end;
		char *dummy;
		unsigned char c;
		unsigned long i, j, k;
		ub8 li;
		int negative;
		ub4 cutoff, cutoff2, cutoff3;

		s= nptr;
		/* If fixed length string */
		if (endptr)
		{
			end= *endptr;
			while (s != end && (*s == ' ' || *s == '\t'))
				s++;
			if (s == end)
				goto no_conv;
		}
		else
		{
			endptr= &dummy;				/* Easier end test */
			while (*s == ' ' || *s == '\t')
				s++;
			if (!*s)
				goto no_conv;
			/* This number must be big to guard against a lot of pre-zeros */
			end= s+65535;				/* Can't be longer than this */
		}

		/* Check for a sign.	*/
		negative= 0;
		if (*s == '-')
		{
			*error= -1;					/* Mark as negative number */
			negative= 1;
			if (++s == end)
				goto no_conv;
			cutoff= (ub4)(SB8_MIN / (sb8)(100000000000LL));
			cutoff2= (SB8_MIN % (sb8)(100000000000LL)) / 100;
			cutoff3=  SB8_MIN % 100;
		}
		else
		{
			*error= 0;
			if (*s == '+')
			{
				if (++s == end)
					goto no_conv;
			}
			cutoff=  UB8_MAX / (sb8)(100000000000LL);
			cutoff2= UB8_MAX % (sb8)(100000000000LL) / 100;
			cutoff3=  UB8_MAX % 100;
		}

		/* Handle case where we have a lot of pre-zero */
		if (*s == '0')
		{
			i= 0;
			do
			{
				if (++s == end)
					goto end_i;				/* Return 0 */
			}
			while (*s == '0');
			n_end= s+ INIT_CNT;
		}
		else
		{
			/* Read first digit to check that it's a valid number */
			if ((c= (*s-'0')) > 9)
				goto no_conv;
			i= c;
			n_end= ++s+ INIT_CNT-1;
		}

		/* Handle first 9 digits and store them in i */
		if (n_end > end)
			n_end= end;
		for (; s != n_end ; s++)
		{
			if ((c= (*s-'0')) > 9)
				goto end_i;
			i= i*10+c;
		}
		if (s == end)
			goto end_i;

		/* Handle next 9 digits and store them in j */
		j= 0;
		start= s;				/* Used to know how much to shift i */
		n_end= true_end= s + INIT_CNT;
		if (n_end > end)
			n_end= end;
		do
		{
			if ((c= (*s-'0')) > 9)
				goto end_i_and_j;
			j= j*10+c;
		} while (++s != n_end);
		if (s == end)
		{
			if (s != true_end)
				goto end_i_and_j;
			goto end3;
		}
		if ((c= (*s-'0')) > 9)
			goto end3;

		/* Handle the next 1 or 2 digits and store them in k */
		k=c;
		if (++s == end || (c= (*s-'0')) > 9)
			goto end4;
		k= k*10+c;
		*endptr= (char*) ++s;

		/* number string should have ended here */
		if (s != end && (c= (*s-'0')) <= 9)
			goto overflow;

		/* Check that we didn't get an overflow with the last digit */
		if (i > cutoff || i == cutoff && (j > cutoff2 || j == cutoff2 &&
			k > cutoff3))
			goto overflow;
		li=i*LFACTOR2+ (ulonglong) j*100 + k;
		return (longlong) li;

overflow:					/* *endptr is set here */
		*error= MY_ERRNO_ERANGE;
		return negative ? SB8_MIN : UB8_MAX;

end_i:
		*endptr= (char*) s;
		return (negative ? ((longlong) -(long) i) : (longlong) i);

end_i_and_j:
		li= (ulonglong) i * lfactor[(uint) (s-start)] + j;
		*endptr= (char*) s;
		return (negative ? -((longlong) li) : (longlong) li);

end3:
		li=(ulonglong) i*LFACTOR+ (ulonglong) j;
		*endptr= (char*) s;
		return (negative ? -((longlong) li) : (longlong) li);

end4:
		li=(ulonglong) i*LFACTOR1+ (ulonglong) j * 10 + k;
		*endptr= (char*) s;
		if (negative)
		{
			if (li > SB8_MIN)
				goto overflow;
			return -((longlong) li);
		}
		return (longlong) li;

no_conv:
		/* There was no number to convert.  */
		*error= MY_ERRNO_EDOM;
		*endptr= (char *) nptr;
		return 0;
	}

	/*
	Defines: llstr();

	llstr(value, buff);

	This function saves a longlong value in a buffer and returns the pointer to
	the buffer.  This is useful when trying to portable print longlong
	variables with printf() as there is no usable printf() standard one can use.
	*/
	char *CLNumber::llstr(longlong value,char *buff)
	{
		Int64ToStr(value,buff,-10);
		return buff;
	}
}
