#ifndef ABB_H
#define ABB_H

#include "tipos.h"
#include "costos.h"

typedef struct NodoABB {
    Elector dato;
    struct NodoABB* izq;
    struct NodoABB* der;
} NodoABB;

typedef struct {
    NodoABB* raiz;
} ABB;

void inicializarABB(ABB* arbol);
int altaABB(ABB* arbol, Elector elector, CostoEstructura* costos);
int bajaABB(ABB* arbol, Elector elector, CostoEstructura* costos);
int buscarABB(ABB arbol, int circuito, int dni, CostoEstructura* costos);
void mostrarABB(ABB arbol);
void liberarABB(NodoABB* nodo);

#endif // ABB_H
