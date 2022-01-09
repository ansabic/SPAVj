#include <stdio.h>
#include <malloc.h>
#include "bstree.h"

BSTree NewBSTree() {
    // Novo prazno stablo
    BSTree tree = malloc(sizeof(BSTree));
    tree->right = NULL;
    tree->left = NULL;
    tree->word = NULL;
    return tree;
}

int AddNode(BSTree *bst, char *word) {
    // Rekurzivno se tra?i mjesto za novi ?vor u stablu. Ako rije? postoji u stablu, ne dodaje se.
    // bst parametar je dvostruki pokaziva?.
    if (bst == NULL)
        return 0;
    if ((*bst)->word == NULL) {
        (*bst)->word = word;
        return 1;
    }
    int diff = strcmp(word, (*bst)->word);
    if (diff == 0)
        return 0;
    else if (diff < 0) {
        if ((*bst)->left == NULL) {
            BSTree newNode = NewBSTree();
            newNode->word = word;
            (*bst)->left = newNode;
            return 1;
        } else
            return AddNode(&((*bst)->left), word);
    } else if (diff > 0) {
        if ((*bst)->right == NULL) {
            BSTree newNode = NewBSTree();
            newNode->word = word;
            (*bst)->right = newNode;
            return 1;
        } else
            return AddNode(&((*bst)->right), word);
    }
    return 0;
}

int BSTHeight(BSTree bst) {
    if (bst == NULL)
        return 0;
    int left = BSTHeight(bst->left);
    int right = BSTHeight(bst->right);
    if (left > right)
        return left + 1;
    else
        return right + 1;
}

void PrintBSTree(BSTree bst) {
    // Ispisuje rije?i u stablu na ekran po abecednom redu.
    // In-order ?etnja po stablu (lijevo dijete, ?vor, desno dijete)
    if (bst != NULL) {
        PrintBSTree(bst->left);
        printf("%s ", bst->word);
        PrintBSTree(bst->right);
    }
}

void SaveBSTree(BSTree bst, FILE *fd) {
    // Snima rije? po rije? iz stabla u tekstualnu datoteku. Rije?i su odvojene razmakom.
    // Pre-order ?etnja po stablu (ttenutni ?vor pa djeca)
    if (bst != NULL) {
        char *space = " ";
        fwrite(bst->word, sizeof(char), strlen(bst->word), fd);
        fwrite(space, sizeof(char), 1, fd);
        SaveBSTree(bst->left, fd);
        SaveBSTree(bst->right, fd);
    }

}

void DeleteBSTree(BSTree bst) {
    //PostOrder
    if (bst != NULL) {
        DeleteBSTree(bst->left);
        DeleteBSTree(bst->right);
        free(bst);
        bst = NULL;
    }

}

BSTree LoadBSTree(FILE *fd) {
    // U?itava rije? po rije? iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
    // Rije? duplicirati sa strdup().
    char buffer[1024];
    if (fd == NULL)
        return NULL;
    BSTree bst = NewBSTree();
    while (readWord(fd, buffer)) {
        char *word = strdup(buffer);
        AddNode(&bst, word);
    }
    return bst;
}


