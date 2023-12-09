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


/*
* genera un adt para realizar un arbol binario de busqueda 
* @returns puntero a arbol binario de busqueda
*/

bstADT newBstADT(void);

/*libera los recursos utilizados por el arbol
* @param bstADT puntero a arbol binario de busqueda
*/

void freeBstADT(bstADT bst);

/*
*  devuelve puntero a estructura vinculado a una clave
*  @returns bstADT el puntero a estructura, retorna NULL si no encuentra
*  @param puntero a arbol binario de busqueda
*  @param unsigned clave a verificar si esta
*/
void * belongsBstADT(const bstADT bst, unsigned id);

/* agrega un elemento vinculado a una clave al arbol de forma ordenada
*  @param bstADT arbol binario a agregar elemento
*  @param unsigned clave que da orden al arbol
*  @param void* estructura vinculada a id
*/
void insertBstADT(bstADT bst, unsigned id, void * p);

#endif
