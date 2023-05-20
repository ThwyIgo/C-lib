#ifndef BSTREE_H
#define BSTREE_H

/* Binary search tree data structure.

   You probably need to define some functions and change some typedefs to make
   this code work (It tries to be agnostic about the values the tree will
   store).

   Functions that take a BSTree* may change the tree; functions that take a
   BSTree won't change the tree.
 */
//#define NO_AVL // Define to disable auto-balancing of the tree
#include <stdbool.h>

///// SETUP /////

// Change this typedef to the datatype the tree will store
typedef struct treePair *treeValue;
// What is the type of the key?
typedef int treeValueKey;

// Define the following 3 functions in your code

treeValueKey bst_getKeyByValue(treeValue value);

// Return 0 if a == b, -1 if a < b, 1 if a > b
int bst_compare(treeValueKey a, treeValueKey b);

// Should print the value without any '\n'
void bst_printValue(treeValue value);

///// That's it! Don't chage the code below

typedef struct s_BSTree *BSTree;

/* Creates a new BSTree with a value (a tree can't be empty) */
BSTree newBSTree(treeValue initialValue);

/* Dealocates a BSTree and all it's subtrees */
void delBSTree(BSTree *tree);

/* Greatest height of a BSTree. A BSTree with 1 element has height 0, and a
 * BSTree with 0 elements has height -1 */
long bst_height(BSTree tree);

bool bst_insert(BSTree *tree, treeValue value);

/* Set "retValue" to the treeValue which has key = "key".
   Returns true if a value was found, false otherwise.
 */
bool bst_find(BSTree tree, treeValueKey key, treeValue *retValue);

///// IO /////

/* Prints the BSTree. The root is printed, then the right and left subtrees are
 * printed respectively. */
void bst_printTree(BSTree tree);

#endif // BSTREE_H
