#include "bstADT.h"
#include <stdlib.h>
#include <stdio.h>

struct node {
    unsigned id; // id de la estacion
    void * ptr; // puntero a nodo de la lista
    struct node * left;
    struct node * right;
};

typedef struct node * tTree;

struct bstCDT {
    tTree tree;
};

bstADT newBstADT(void) {
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

void freeBstADT(bstADT bst) {
    freeTreeRec(bst->tree);
    free(bst);
}

static void * belongsTreeRec(tTree t, unsigned id) {
    if (t == NULL) {
        return NULL;
    }
    int c;
    if ((c = t->id - id) > 0) {
        return belongsTreeRec(t->left, id);
    }
    if (c < 0) {
        return belongsTreeRec(t->right, id);
    }
    return t->ptr;
}

void * belongsBstADT(const bstADT bst, unsigned id) {
    return belongsTreeRec(bst->tree, id);
}

static tTree insertTreeRec(tTree t, unsigned id, void * p) {
    if (t == NULL) {
        tTree newNode = malloc(sizeof(*newNode));
        newNode->id = id;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->ptr = p;
        return newNode;
    }
    int c;
    if ((c = t->id - id) > 0) {
        t->left = insertTreeRec(t->left, id, p);
    } else if (c < 0) {
        t->right = insertTreeRec(t->right, id, p);
    }
    return t;
}

void insertBstADT(bstADT bst, unsigned id, void * p) {
    bst->tree = insertTreeRec(bst->tree, id, p);
}
