#include "thw/bstree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_BSTree
{
    treeValue value;
    struct s_BSTree *left, *right;
} * BSTree;

// Tentar não usar esta função
bool bst_greater(treeValue a, treeValue b)
{
    return !bst_equal(a, b) && !bst_less(a, b);
}

#define bst_max(a, b) (bst_less(a, b) ? b : a)

BSTree newBSTree(treeValue initialValue)
{
    BSTree ret = malloc(sizeof(struct s_BSTree));
    *ret =
      (struct s_BSTree){ .value = initialValue, .left = NULL, .right = NULL };
    return ret;
}

void delBSTree(BSTree *tree)
{
    if (*tree == NULL)
        return;

    delBSTree(&(*tree)->left);
    delBSTree(&(*tree)->right);
    free(*tree);
}

static long h_bst_height(BSTree tree, long height)
{
    if (tree == NULL)
        return height - 1;
    return bst_max(h_bst_height(tree->left, height + 1),
                   h_bst_height(tree->right, height + 1));
}

long bst_height(BSTree tree)
{
    return h_bst_height(tree, 0);
}

///// Rotations /////

// Rotation to use when the tree is LL unbalanced.
static void bst_LLrotation(BSTree *tree)
{
    BSTree A = *tree;
    BSTree B = A->left;

    A->left = B->right;
    B->right = A;

    *tree = B;
}

// Rotation to use when the tree is RR unbalanced.
static void bst_RRrotation(BSTree *tree)
{
    BSTree A = *tree;
    BSTree B = A->right;

    A->right = B->left;
    B->left = A;

    *tree = B;
}

// Rotation to use when the tree is LR unbalanced.
static void bst_LRrotation(BSTree *tree)
{
    BSTree A = *tree;
    BSTree B = A->left;
    BSTree C = B->right;
    B->right = C->left;
    C->left = B;
    A->left = C->right;
    C->right = A;

    *tree = C;
}

// Rotation to use when the tree is RL unbalanced.
static void bst_RLrotation(BSTree *tree)
{
    BSTree A = *tree;
    BSTree B = A->right;
    BSTree C = B->left;
    B->left = C->right;
    C->right = B;
    A->right = C->left;
    C->left = A;

    *tree = C;
}

//////////

// Ainda não é AVL
bool bst_insert(BSTree *tree, treeValue value)
{
    if (*tree == NULL) {
        *tree = malloc(sizeof(struct s_BSTree));
        **tree =
          (struct s_BSTree){ .value = value, .left = NULL, .right = NULL };
        return true;
    }

    if (bst_equal((*tree)->value, value))
        return false;

    if (bst_less(value, (*tree)->value))
        return bst_insert(&(*tree)->left, value);

    return bst_insert(&(*tree)->right, value);
}

///// IO /////

static void h_bst_printTree(BSTree tree, int tabs)
{
    // Tabs are actually 4 spaces here
    for (int i = 0; i < tabs - 1; ++i)
        printf("|    ");
    if (tabs > 0)
        printf("|----");

    if (tree == NULL) {
        puts("Empty");
        return;
    }

    bst_printValue(tree->value);
    putchar('\n');
    h_bst_printTree(tree->right, tabs + 1);
    h_bst_printTree(tree->left, tabs + 1);
}

void bst_printTree(BSTree tree)
{
    h_bst_printTree(tree, 0);
}

#undef bst_max
