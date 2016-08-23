#pragma once

namespace NSPrime
{
	class CLNumber
	{
	private:
		static const int DIG_VEC_LENGTH = 36;
	public:
		/*全局变量*/
		static const char _dig_vec[DIG_VEC_LENGTH+1];

		static char *int2str(register long int val, register char *dst, register int radix);

		/*
		This is a faster version of the above optimized for the normal case of
		radix 10 / -10
		*/
		static char *int10_to_str(sb8 val,char *dst,int radix);

		static char *Int64ToStr(sb8 val,char *dst,int radix);

		static char *Int64ToStr_10(sb8 val,char *dst,int radix);

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
		static sb8 StrToSB8_10(const char *nptr, char **endptr, int *error);
		
		template <class Type>
		static inline Type Max(Type a, Type b)
		{
			return 	a > b ? a : b;
		}

		template <class Type>
		static inline Type Min(Type a, Type b)
		{
			return 	a < b ? a : b;
		}

		/*
		Defines: llstr();

		llstr(value, buff);

		This function saves a longlong value in a buffer and returns the pointer to
		the buffer.  This is useful when trying to portable print longlong
		variables with printf() as there is no usable printf() standard one can use.
		*/
		static char *llstr(longlong value,char *buff);
	};
}
