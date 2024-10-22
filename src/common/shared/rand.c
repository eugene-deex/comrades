/*
 * KISS PRNG (c) 2011 Shinobu
 *
 * This file was optained from zuttobenkyou.wordpress.com
 * and modified by the Yamagi Quake II developers.
 *
 * LICENSE: Public domain
 *
 * =======================================================================
 *
 * KISS PRNG, as devised by Dr. George Marsaglia
 *
 * =======================================================================
 */

#include <stdio.h>

#pragma warning(disable : 4244)	// MIPS
#pragma warning(disable : 4305)	// truncation from const double to float

#if defined(_WIN32)
	typedef unsigned _int64	uint64_t;
#else
	typedef unsigned long long uint64_t;
#endif

#define QSIZE 0x200000
#define CNG (cng = 6906969069UL * cng + 13579)
#define XS (xs ^= (xs << 13), xs ^= (xs >> 17), xs ^= (xs << 43))
#define KISS (B64MWC() + CNG + XS)




#if defined(_WIN32)

	static uint64_t QARY[QSIZE];
	static int j;
	static uint64_t carry;
	static uint64_t xs;
	static uint64_t cng;
	  
	uint64_t
	B64MWC(void)
	{
		uint64_t t, x;

		j = (j + 1) & (QSIZE - 1);
		x = QARY[j];
		t = (x << 28) + carry;
		carry = (x >> 36) - (t < x);
		return QARY[j] = t - x;
	} 

#else

	static unsigned long long QARY[QSIZE];
	static int j;
	static unsigned long long carry;
	static unsigned long long xs;
	static unsigned long long cng;
	  
	unsigned long long
	B64MWC(void)
	{
		unsigned long long t, x;

		j = (j + 1) & (QSIZE - 1);
		x = QARY[j];
		t = (x << 28) + carry;
		carry = (x >> 36) - (t < x);
		return QARY[j] = t - x;
	} 

#endif





/* 
 * Generate a pseudorandom 
 * integer >0. 
 */
int
randk(void)
{
	int r;

	r = (int)KISS;
	r = (r < 0) ? (r * -1) : r;

	return r;
}

/*
 * Generate a pseudorandom
 * signed float between 
 * 0 and 1.
 */
float
frandk(void)
{
	return (randk()&32767)* (1.0/32767);
}

/* Generate a pseudorandom
 * float between -1 and 1.
 */
float
crandk(void)
{
	return (randk()&32767)* (2.0/32767) - 1;
}

/*
 * Seeds the PRNG
 */
void
randk_seed(void)
{
	//uint64_t i;
#if defined(_WIN32)
	uint64_t i;
#else
	unsigned long long i;
#endif 

	/* Seed QARY[] with CNG+XS: */
	for (i = 0; i < QSIZE; i++)
	{
		QARY[i] = CNG + XS;
	}

	/* Run through several rounds 
	   to warm up the state */
	for (i = 0; i < 256; i++)
	{
		randk();
	}
}

