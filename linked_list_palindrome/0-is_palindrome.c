#include "lists.h"


/**
 * is_palindrome - checks if a singly linked list could be considered a
 * palindrome, given the values stored in each node. An empty list is
 * considered a palindrome.
 *
 * @head: first node in a SLL that contains one integer per node
 * Return: 0 if it is not a palindrome, 1 if it is a palindrome
 */
int is_palindrome(listint_t **head)
{
	listint_t *temp = *head;
	int plndrm;

	/* list of 0 or 1 members is palindrome */
	if (!temp || !(temp->next))
		return (1);

	plndrm = is_palindrome_recursion(head, temp);
	head = &temp;

	return (plndrm);
}


/**
 * is_palindrome_recursion - recursviely traverses a singly linked list to
 * see if its values are arranged as a palindrome. For each recursion frame,
 * the head of the sublist should be the same offset from the true list head
 * that the sublist tail is from the true list tail.
 *
 * @head: first node in a SLL sublist that contains one integer per node
 * @tail: last node in a SLL sublist that contains one integer per node
 * Return: 0 if it is not a palindrome, 1 if it is a palindrome
 */
int is_palindrome_recursion(listint_t **head, listint_t *tail)
{
	int sublist_symmetry, symmetry;

	/* actual list tail reached in the previous recursion frame */
	if (!tail)
		return (1);

	/* stop recursion if sub-list not palindrome */
	sublist_symmetry = is_palindrome_recursion(head, tail->next);
	if (sublist_symmetry == 0)
		return (sublist_symmetry);

	/* if current frame symmetrical? */
	symmetry = ((*head)->n == tail->n) ? 1 : 0;

	/* narrow comparison towards center of list */
	*head = (*head)->next;

	return (symmetry);
}
