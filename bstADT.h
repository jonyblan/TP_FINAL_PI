#ifndef __BST_ADT_H__
#define __BST_ADT_H__

typedef struct bstCDT * bstADT;

// Crea un arbol binario de busqueda
bstADT newBst(void);

// Libera toda la memoria reservada por el TAD
void freeBst(bstADT bst);

// Retorna 1 si el elemento estaก en el arbol, cero si no esta
int belongs(const bstADT bst, elemType elem);

// Agrega un elemento respetando el orden
// Retorna 1 si lo pudo agregar (no estaba), cero si no (ya estaba)
int insert(bstADT bst, elemType elem, void * p);

#endif
