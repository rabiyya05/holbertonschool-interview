#ifndef PALINDROME_H
#define PALINDROME_H

int is_palindrome(unsigned long exp);
int palindromeRecursion(unsigned long n, unsigned int upper_p10,
			unsigned int left_p10, unsigned int right_p10);
unsigned long pow10Recursion(unsigned int p);
unsigned long _pow10(unsigned int exp);
unsigned long pow10Lookup(unsigned int exp);

#endif /* PALINDROME_H */
