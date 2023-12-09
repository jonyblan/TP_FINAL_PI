/*
* bstADT.h
* Contenido:
*     Prototipos de funciones para el usuario de bstADT.
*     bstADT:
*         bstADT es una libreria para utilizar árboles
*         de búsqueda binaria, especialmente para
*         complementar el funcionamiento de stationsADT.
* Autor:
*     Buela Mateo
* Version:
*     1.1.0
* Fecha de creación:
*     22/11/2023
*/

#ifndef __BST_ADT_H__
#define __BST_ADT_H__

typedef struct bstCDT * bstADT;

// Crea un arbol binario de busqueda
bstADT newBstADT(void);

// Libera toda la memoria reservada por el TAD
void freeBstADT(bstADT bst);

// Retorna el puntero
void * belongsBstADT(const bstADT bst, unsigned id);

// Agrega un elemento respetando el orden
void insertBstADT(bstADT bst, unsigned id, void * p);

#endif
