//
// Created by antonio on 24. 01. 2022..
//


#include <stddef.h>
#include <malloc.h>

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef TreeNode *Tree;

Tree newTreeNode() {
    Tree node = malloc(sizeof(TreeNode));
    node->left = NULL;
    node->right = NULL;
    return node;
}

Tree *newTree() {
    Tree *newTree = malloc(sizeof(Tree *));
    (*newTree) = NULL;
    return newTree;
}

void insertTreeNode(Tree *tree, int value) {
    if ((*tree) == NULL) {
        Tree new = newTreeNode();
        new->value = value;
        (*tree) = new;
        return;
    }
    if ((*tree)->value == value)
        return;
    if ((*tree)->value < value) {
        Tree new = newTreeNode();
        new->left = (*tree);
        *tree = new;
        return;
    }
    if ((*tree)->left != NULL && (*tree)->left->value > value)
        insertTreeNode(&(*tree)->left, value);
    else if ((*tree)->right != NULL && (*tree)->right->value > value)
        insertTreeNode(&(*tree)->right, value);
    else if ((*tree)->left == NULL) {
        Tree new = newTreeNode();
        new->value = value;
        (*tree)->left = new;
        return;
    } else if ((*tree)->right == NULL && (*tree)->left != NULL) {
        Tree new = newTreeNode();
        new->value = value;
        (*tree)->right = new;
        return;
    } else {
        Tree new = newTreeNode();
        new->left = (*tree)->left;
        new->right = (*tree)->right;
        new->value = value;
        (*tree)->left = new;
        return;
    }
}

void printTree(Tree *tree) {
    if ((*tree) != NULL)
        printf("%d \n", (*tree)->value);
    if ((*tree)->left != NULL)
        printTree(&(*tree)->left);
    if ((*tree)->right != NULL)
        printTree(&(*tree)->right);
}

int mainvv() {
    Tree *tree = newTree();
    insertTreeNode(tree, 15);
    insertTreeNode(tree, 10);
    insertTreeNode(tree, 9);
    insertTreeNode(tree, 12);
    printTree(tree);
    return 0;
}

