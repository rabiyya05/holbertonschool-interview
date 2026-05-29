#include "slide_line.h"

/* fprintf */
#include <stdio.h>
/* true false */
#include <stdbool.h>


/**
 * slide_line_left - helper to slide_line, reproduces a version of the "2048"
 * game mechanics, on a single horizontal line, sliding left
 *
 * @line: array of integers
 * @size: amount of members in `line`
 * Return: 1 upon success, or 0 upon failure
 */
static void slide_line_left(int *line, size_t size)
{
	int i, j, last_j = 0;

	i = 0;
	while (i < (int)size)
	{
		/* find next unslid value */
		for (j = last_j > i ? last_j : i + 1;
		     j < (int)size && line[j] == 0; j++)
		{}
		/* no more unslid found */
		if (j == (int)size)
			break;
		last_j = j;

		/* slide unslid value to left if space open */
		if (line[i] == 0)
		{
			line[i] = line[j];
			line[j] = 0;

		}
		/* value already in that position: combine? */
		else
		{
			/* next non-0 value matches current */
			if (line[j] == line[i])
			{
				line[i] *= 2;
				line[j] = 0;
			}
			/* advance to next whether combined or incompatible */
			i++;
		}
	}
}


/**
 * slide_line_right - helper to slide_line, reproduces a version of the "2048"
 * game mechanics, on a single horizontal line, sliding right
 *
 * @line: array of integers
 * @size: amount of members in `line`
 * Return: 1 upon success, or 0 upon failure
 */
static void slide_line_right(int *line, size_t size)
{
	int i, j, last_j = (int)size - 1;

	i = (int)size - 1;
	while (i >= 0)
	{
		/* find next unslid value */
		for (j = last_j < i ? last_j : i - 1;
		     j >= 0 && line[j] == 0; j--)
		{}
		/* no more unslid found */
		if (j == -1)
			break;
		last_j = j;

		/* slide unslid value to right if space open */
		if (line[i] == 0)
		{
			line[i] = line[j];
			line[j] = 0;

		}
		/* value already in that position: combine? */
		else
		{
			/* next non-0 value matches current */
			if (line[j] == line[i])
			{
				line[i] *= 2;
				line[j] = 0;
			}
			/* advance to next whether combined or incompatible */
			i--;
		}
	}
}


/**
 * slide_line - reproduces a version of the "2048" game mechanics, on a single
 * horizontal line
 *
 * @line: array of integers
 * @size: amount of members in `line`
 * @direction: integer indicating left or right movement, expect macros
 * SLIDE_LEFT and SLIDE_RIGHT
 * Return: 1 upon success, or 0 upon failure
 */
int slide_line(int *line, size_t size, int direction)
{
	int i;

	/* screen invalid args */
	if (line == NULL || size == 0 ||
	    (direction != SLIDE_LEFT && direction != SLIDE_RIGHT))
		return (0);

	/* reject arrays with any odd numbers */
	for (i = 0; i < (int)size; i++)
		if (line[i] % 2)
			return (0);

	/* array of 1 is already solved */
	if ((int)size == 1)
		return (1);

	if (direction == SLIDE_LEFT)
		slide_line_left(line, size);

	if (direction == SLIDE_RIGHT)
		slide_line_right(line, size);

	return (1);
}
