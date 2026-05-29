#include "palindrome.h"


/**
 * pow10Lookup - finds powers of 10 up to 19 in lookup table for speed
 *
 * @exp: exponent
 * Return: 10^exp
 */
unsigned long pow10Lookup(unsigned int exp)
{
	static const unsigned long pow10_table[19] = {
		1u,
		10u,
		100u,
		1000u,
		10000u,
		100000u,
		1000000u,
		10000000u,
		100000000u,
		1000000000u,
		10000000000u,
		100000000000u,
		1000000000000u,
		10000000000000u,
		100000000000000u,
		1000000000000000u,
		10000000000000000u,
		100000000000000000u,
		1000000000000000000u
	};

	return (pow10_table[exp]);
}


/**
 * _pow10 - finds power of 10
 *
 * @exp: exponent
 * Return: 10^exp
 */
unsigned long _pow10(unsigned int exp)
{
	unsigned long pow_10 = 1;

	while (exp)
	{
		pow_10 *= 10;
		exp--;
	}

	return (pow_10);
}


/**
 * pow10Recursion - recursively finds power of 10
 *
 * @exp: exponent
 * Return: 10^exp
 */
unsigned long pow10Recursion(unsigned int exp)
{
	if (exp == 0)
		return (1);
	else
		return (10 * pow10Recursion(exp - 1));
}


/**
 * palindromeRecursion - helper to is_palindrome, recursively compares
 * digits in an unsigned int, from midpoint out to ends
 *
 * @n: number to check
 * @upper_p10: power of 10 at leftmost digit of n
 * @left_p10: power of 10 at first position to compare
 * @right_p10: power of 10 at second position to compare
 * Return: 1 if n is a palindrome, and 0 otherwise
 */
int palindromeRecursion(unsigned long n, unsigned int upper_p10,
			unsigned int left_p10, unsigned int right_p10)
{
	unsigned int left, right;

	left = (n / pow10Lookup(left_p10)) % 10;
	right = (n / pow10Lookup(right_p10)) % 10;

	if (left == right)
	{
		if (left_p10 == upper_p10)
			return (1);
		else
			return (palindromeRecursion(n, upper_p10, left_p10 + 1,
						    right_p10 - 1));
	}

	return (0);
}


/**
 * is_palindrome - checks whether or not a given unsigned integer is a
 * palindrome
 *
 * @n: number to check
 * Return: 1 if n is a palindrome, and 0 otherwise
 */
int is_palindrome(unsigned long n)
{
	unsigned int upper_p10 = 1, left_p10, right_p10;

	if (n < 10)
		return (1);

	/*
	 * In theory, power of 10 should stop at 10^19 for ULONG_MAX at
	 * 18446744073709551615. But atol() as used in main will not return
	 * values over LONG_MAX, 9223372036854775807, thus 10^18.
	*/
	while (upper_p10 < 18 && n / pow10Lookup(upper_p10) > 10)
		upper_p10++;

	if (upper_p10 % 2) /* odd number p_10, even number digits in n */
	{
		right_p10 = upper_p10 / 2;
		left_p10 = right_p10 + 1;
	}
	else /* even number p_10, odd number digits in n */
		left_p10 = right_p10 = upper_p10 / 2;

	return (palindromeRecursion(n, upper_p10, left_p10, right_p10));
}
