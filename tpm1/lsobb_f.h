#ifndef LSOBB_F_H
#define LSOBB_F_H

#include "tipos.h"
#include "costos.h"

typedef struct {
    Circuito circuitos[MAX_CIRCUITOS];
    int cantidad;
} LSOBB_F;

void inicializarLSOBB_F(LSOBB_F* lista);
int buscarCircuitoLSOBB_F(LSOBB_F* lista, int nroCircuito, int* pos, CostoEstructura* costos);
int altaLSOBB_F(LSOBB_F* lista, Elector elector, CostoEstructura* costos);
int bajaLSOBB_F(LSOBB_F* lista, Elector elector, CostoEstructura* costos);
int buscarElectorLSOBB_F(LSOBB_F* lista, int circuito, int dni, CostoEstructura* costos);
void mostrarLSOBB_F(LSOBB_F lista);

#endif // LSOBB_F_H
