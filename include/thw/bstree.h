#ifndef BSTREE_H
#define BSTREE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Change this typedef to the datatype the tree will store
typedef int treeValue;

// Define the following 3 functions in your code

bool bst_less(treeValue a, treeValue b);

bool bst_equal(treeValue a, treeValue b);

// Should print the value without any '\n'
void bst_printValue(treeValue value);

// That's it! Don't chage the code below

typedef struct s_BSTree *BSTree;

/* Creates a new BSTree with a value (a tree can't be empty) */
BSTree newBSTree(treeValue initialValue);

/* Dealocates a BSTree and all it's subtrees */
void delBSTree(BSTree *tree);

/* Greatest height of a BSTree. A BSTree with 1 element has height 0, and a
 * BSTree with 0 elements has height -1 */
long bst_height(BSTree tree);

// Ainda não é AVL
bool bst_insert(BSTree *tree, treeValue value);

///// IO /////

/* Prints the BSTree. The root is printed, then the right and left subtrees are
 * printed respectively. */
void bst_printTree(BSTree tree);

#endif // BSTREE_H
