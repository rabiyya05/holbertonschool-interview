u#include <stdlib.h>
#include "binary_trees.h"

/**
 * binary_tree_node - Creates a binary tree node
 * @parent: Pointer to the parent node of the node to create
 * @value: The value to put in the new node
 *
 * Return: A pointer to the new node, or NULL on failure
 */
binary_tree_t *binary_tree_node(binary_tree_t *parent, int value)
{
    binary_tree_t *new_node;

    /* 1. Yeni qovşaq üçün yaddaş ayırırıq */
    new_node = malloc(sizeof(binary_tree_t));
    if (new_node == NULL)
    {
        return (NULL);
    }

    /* 2. Qovşağın daxili dəyişənlərini (məlumatlarını) doldururuq */
    new_node->n = value;
    new_node->parent = parent;
    
    /* Tapşırığa əsasən yeni yaranan qovşağın başlanğıcda heç bir övladı olmur */
    new_node->left = NULL;
    new_node->right = NULL;

    /* 3. Yaradılmış qovşağın ünvanını geri qaytarırıq */
    return (new_node);
}}
