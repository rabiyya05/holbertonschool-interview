#include "lists.h"

/**
 * check_cycle - checks singly linked list type listint_t for cycles (links
 *         to any other node other than next in list)
 *
 * @head: node in a singly linked list to begin search for cycles
 * Return: 0 if all links move forward through list, 1 if backward link
 *         is found
 */
int check_cycle(listint_t *head)
{
	listint_t *slow, *fast;

	if (!head || !(head->next))
		return (0);

	slow = head;
	fast = head->next;
	while (slow && slow->next && fast && fast->next)
	{
		if (slow == fast)
			return (1);
		slow = slow->next;
		fast = fast->next->next;
	}

	return (0);
}
