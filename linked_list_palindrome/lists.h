#ifndef LISTS_H
#define LISTS_H

/* NULL size_t */
#include <stddef.h>

/**
 * struct listint_s - singly linked list
 * @n: integer
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct listint_s
{
	int n;
	struct listint_s *next;
} listint_t;

/* linked_lists.c */
size_t print_listint(const listint_t *h);
listint_t *add_nodeint_end(listint_t **head, const int n);
void free_listint(listint_t *head);

/* 0-is_palindrome.c */
int is_palindrome(listint_t **head);
int is_palindrome_recursion(listint_t **head, listint_t *tail);


#endif /* LISTS_H */
