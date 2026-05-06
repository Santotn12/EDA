#ifndef ABB_F_H
#define ABB_F_H

#include "tipos.h"
#include "costos.h"

typedef struct NodoABB_F {
    int nroCircuito;
    NodoElector* listaElectores;
    struct NodoABB_F* izq;
    struct NodoABB_F* der;
} NodoABB_F;

typedef struct {
    NodoABB_F* raiz;
} ABB_F;

void inicializarABB_F(ABB_F* arbol);
int altaABB_F(ABB_F* arbol, Elector elector, CostoEstructura* costos);
int bajaABB_F(ABB_F* arbol, Elector elector, CostoEstructura* costos);
int buscarABB_F(ABB_F arbol, int circuito, int dni, CostoEstructura* costos);
void mostrarABB_F(ABB_F arbol);
void liberarABB_F(NodoABB_F* nodo);

#endif // ABB_F_H
