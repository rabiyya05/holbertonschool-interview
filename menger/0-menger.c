#include "menger.h"
/* pow */
#include <math.h>
/* puts putchar fprintf */
#include <stdio.h>
/* malloc free */
#include <stdlib.h>
/* true false */
#include <stdbool.h>


/**
 * isCellAtCoords - tests whether a given coordinate pair in a 2D Menger Sponge
 * is a cell (void)
 *
 * @x: column of printed 2D sponge
 * @y: row of printed 2D sponge
 * @level: level of 2D Menger Sponge, determines size and degree of recursion
 * @coords: `level` number of int arrays, each containing the potential
 * coordinates of cells of a given size (powers of 3) - if both x and y are in
 * one of these sets, then position is in a cell
 * Return: true if x/y is in a cell, false if not or if bad arguments
 */
static bool isCellAtCoords(int x, int y, int level, int **coords)
{
	bool cell;
	int i, j, k, arr_sz;

	if (x < 1 || y < 1 || level < 1 || coords == NULL)
		return (false);

	arr_sz = (int)pow(3, level - 1);

	cell = false;
	for (i = 0; i < level && !cell; i++)
	{
		for (j = 0; j < arr_sz && !cell; j++)
		{
			if (y == coords[i][j])
			{
				for (k = 0; k < arr_sz && !cell; k++)
				{
					if (x == coords[i][k])
						cell = true;
				}
			}
		}
	}

	return (cell);
}


/**
 * print2DMengerSponge - prints a 2D representation of a Menger Sponge
 *
 * @level: level of 2D Menger Sponge, determines size and degree of recursion
 * @coords: `level` number of int arrays, each containing the potential
 * coordinates of cells of a given size (powers of 3) - if both x and y are in
 * one of these sets, then position is in a cell
 */
static void print2DMengerSponge(int level, int **coords)
{
	int x, y, sponge_sz;

	if (level < 1 || coords == NULL)
		return;

	sponge_sz = (int)pow(3, level);

	for (y = 1; y <= sponge_sz; y++)
	{
		for (x = 1; x <= sponge_sz; x++)
		{
			if (isCellAtCoords(x, y, level, coords))
				putchar(' ');
			else
				putchar('#');
		}
		putchar('\n');
	}
}


/**
 * freeCellCoords - frees array of int arrays containing sponge cell coords
 *
 * @coords: `level` number of int arrays, each containing the potential
 * coordinates of cells of a given size (powers of 3) - if both x and y are in
 * one of these sets, then position is in a cell
 * @stop_i: last array that needs freeing, varies in case of previously failed
 * allocation
 */
static void freeCellCoords(int **coords, int stop_i)
{
	int i;

	for (i = 0; i < stop_i; i++)
		free(coords[i]);
	free(coords);
}


/**
 * MengerSpongeCellCoords - calculates the potential coordinates of a given
 * layer of cells (voids) in a 2D Menger Sponge
 *
 * @level: level of 2D Menger Sponge, determines size and degree of recursion
 * @layer: corresponds to cell(void) size, in powers of 3
 * Return: array of cell coordinates for a given level and layer, or NULL
 * on failure
 */
static int *MengerSpongeCellCoords(int level, int layer)
{
	int *arr = NULL;
	int arr_sz, i, j, k, j_lim, k_lim;

	if (level < 1 || layer < 0 ||
	    layer >= level)
		return (NULL);

	arr_sz = (int)pow(3, level - 1);

	arr = malloc(sizeof(int) * arr_sz);
	if (!arr)
	{
		fprintf(stderr, "MengerSpongeCellCoords: malloc failure\n");
		return (NULL);
	}

	j_lim = (int)pow(3, level - (level - layer));
	k_lim = (int)pow(3, level - (layer + 1));

	for (i = 0; i < arr_sz; )
	{
		for (j = 0; j < j_lim; j++)
		{
			for (k = 1; k <= k_lim; k++)
			{
				arr[i] = (int)pow(3, level - (layer + 1)) +
					((int)pow(3, level - layer) * j) + k;
				i++;
			}
		}
	}

	return (arr);
}


/**
 * menger - draws a 2 dimensional version of a Menger Sponge, in '#' and ' '
 *
 * @level: level of 2D Menger Sponge, determines size and degree of recursion
 * (0 = 1x1, 1 = 3x3, 2 = 9x9, etc.)
 */
void menger(int level)
{
	int **cell_coords = NULL;
	int i;

	if (level < 0)
		return;

	if (level == 0)
	{
		puts("#");
		return;
	}

	cell_coords = malloc(sizeof(int *) * level);
	if (!cell_coords)
	{
		fprintf(stderr, "menger: malloc failure\n");
		return;
	}

	for (i = 0; i < level; i++)
	{
		cell_coords[i] = MengerSpongeCellCoords(level, i);
		if (!cell_coords[i])
		{
			freeCellCoords(cell_coords, i);
			return;
		}
	}

	print2DMengerSponge(level, cell_coords);

	freeCellCoords(cell_coords, level);
}
