#include "thw/bstree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_BSTree
{
    treeValue value;
    struct s_BSTree *left, *right;
} * BSTree;

#define bst_max(a, b) (bst_compare(a, b) >= 0 ? a : b)

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

#ifndef NO_AVL
static short bst_balanceFactor(BSTree tree)
{
    if (tree == NULL)
        return 0;
    return bst_height(tree->right) - bst_height(tree->left);
}

static void bst_balance(BSTree *tree)
{
    short bf = bst_balanceFactor(*tree);
    // Checking if the tree is balanced
    if (bf <= -2) {
        if (bst_balanceFactor((*tree)->left) < 0)
            bst_LLrotation(tree);
        else
            bst_LRrotation(tree);
    }
    if (bf >= 2) {
        if (bst_balanceFactor((*tree)->right) > 0)
            bst_RRrotation(tree);
        else
            bst_RLrotation(tree);
    }
}
#endif // NO_AVL

bool bst_insert(BSTree *tree, treeValue value)
{
    if (*tree == NULL) {
        *tree = malloc(sizeof(struct s_BSTree));
        **tree =
          (struct s_BSTree){ .value = value, .left = NULL, .right = NULL };
        return true;
    }

    if (bst_compare(bst_getKeyByValue((*tree)->value),
                    bst_getKeyByValue(value)) == 0)
        return false;

    bool ret;
    if (bst_compare(bst_getKeyByValue(value),
                    bst_getKeyByValue((*tree)->value)) < 0)
        ret = bst_insert(&(*tree)->left, value);
    else
        ret = bst_insert(&(*tree)->right, value);
    if (ret == false)
        return false;

#ifndef NO_AVL
    bst_balance(tree);
#endif // NO_AVL

    return ret;
}

static BSTree *bst_findMaxValueSubtree(BSTree *tree)
{
    if ((*tree)->right == NULL)
        return tree;
    return bst_findMaxValueSubtree(&(*tree)->right);
}

bool bst_remove(BSTree *tree, treeValueKey key)
{
    if (*tree == NULL) // Value not found
        return false;

    bool ret;
    int cmp = bst_compare(key, bst_getKeyByValue((*tree)->value));
    if (cmp < 0)
        ret = bst_remove(&(*tree)->left, key);
    if (cmp > 0)
        ret = bst_remove(&(*tree)->right, key);
    if (cmp == 0) { // The value to be removed was found
        BSTree toBeRemoved = *tree;
        if (toBeRemoved->left == NULL) {
            if (toBeRemoved->right == NULL) {
                free(toBeRemoved);
                *tree = NULL;
            } else {
                *tree = toBeRemoved->right;
                free(toBeRemoved);
            }
        } else if (toBeRemoved->right == NULL) {
            *tree = toBeRemoved->left;
            free(toBeRemoved);
        } else {
            // Find biggest of the left or smaller of the right
            BSTree *save = bst_findMaxValueSubtree(&toBeRemoved->left);
            toBeRemoved->value = (*save)->value;
            bst_remove(save, bst_getKeyByValue((*save)->value));
        }
        ret = true;
    }

#ifndef NO_AVL
    if (ret)
        bst_balance(tree);
#endif // NO_AVL

    return ret;
}

bool bst_find(BSTree tree, treeValueKey key, treeValue *retValue)
{
    if (tree == NULL)
        return false;
    if (bst_compare(bst_getKeyByValue(tree->value), key) == 0) {
        *retValue = tree->value;
        return true;
    }

    if (bst_compare(key, bst_getKeyByValue(tree->value)) < 0)
        return bst_find(tree->left, key, retValue);
    else
        return bst_find(tree->right, key, retValue);
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
