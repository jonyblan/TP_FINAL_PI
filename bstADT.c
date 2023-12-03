#include "tp11_18.h"
#include <stdlib.h>
#include <stdio.h>

struct node {
    elemType head;
    struct node * left;
    struct node * right;
};

typedef struct node * tTree;

struct bstCDT {
    tTree tree;
};

bstADT newBst(void) {
    return calloc(1, sizeof(struct bstCDT));
}

static void freeTreeRec(tTree t) {
    if (t == NULL) {
        return;
    }
    freeTreeRec(t->left);
    freeTreeRec(t->right);
    free(t);
}

void freeBst(bstADT bst) {
    freeTreeRec(bst->tree);
    free(bst);
}

static int belongsTreeRec(tTree t, elemType elem) {
    if (t == NULL) {
        return 0;
    }
    int c;
    if ((c = compare(t->head, elem)) > 0) {
        return belongsTreeRec(t->left, elem);
    }
    if (c < 0) {
        return belongsTreeRec(t->right, elem);
    }
    return 1;
}

int belongs(const bstADT bst, elemType elem) {
    return belongsTreeRec(bst->tree, elem);
}

static tTree insertTreeRec(tTree t, elemType elem, int * added, int * height) {
    if (t == NULL) {
        tTree newNode = malloc(sizeof(*newNode));
        newNode->head = elem;
        newNode->left = NULL;
        newNode->right = NULL;
        *added = 1;
        return newNode;
    }
    int c;
    if ((c = compare(t->head, elem)) > 0) {
        (*height)++;
        t->left = insertTreeRec(t->left, elem, added, height);
    } else if (c < 0) {
        (*height)++;
        t->right = insertTreeRec(t->right, elem, added, height);
    }
    return t;
}

int insert(bstADT bst, elemType elem) {
    int added = 0, height = 0;
    bst->tree = insertTreeRec(bst->tree, elem, &added, &height);
    bst->size += added;
    bst->height = added ? height : bst->height;
    return added;
}

int main(void) {
    bstADT bst = newBst();
    printf("Size=0: %d\n", size(bst));
    printf("Height=0: %d\n", height(bst));
    printf("Belongs=0: %d\n", belongs(bst, 1));
    puts("");
    printf("Insert=1: %d\n", insert(bst, 1));
    printf("Size=1: %d\n", size(bst));
    printf("Height=0: %d\n", height(bst));
    printf("Belongs=1: %d\n", belongs(bst, 1));
    puts("");
    printf("Insert=0: %d\n", insert(bst, 1));
    printf("Insert=1: %d\n", insert(bst, 3));
    printf("Insert=1: %d\n", insert(bst, 6));
    printf("Insert=1: %d\n", insert(bst, 10));
    printf("Insert=1: %d\n", insert(bst, 11));
    puts("");
    printf("Size=5: %d\n", size(bst));
    printf("Height=4: %d\n", height(bst));
    printf("belongs=1: %d\n", belongs(bst, 1));
    printf("belongs=1: %d\n", belongs(bst, 3));
    printf("belongs=1: %d\n", belongs(bst, 6));
    printf("belongs=1: %d\n", belongs(bst, 10));
    printf("belongs=1: %d\n", belongs(bst, 11));
    puts("");
    int * arr = inorder(bst);
    for (int i = 0; i < size(bst); i++) {
        printf("[%d] ", arr[i]);
    }
    puts("");
    puts("");
    return 0;
}
