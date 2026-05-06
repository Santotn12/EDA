#ifndef LSOBB_H
#define LSOBB_H

#include "tipos.h"
#include "costos.h"

#define MAX_LSOBB (MAX_CIRCUITOS * MAX_MESAS * MAX_PERSONAS_MESA)

typedef struct {
    Elector datos[MAX_LSOBB];
    int li;           // Límite inferior (primera posición usada)
    int ls;           // Límite superior (última posición usada)
    int cantidad;     // Cantidad de elementos
    int iint;         // Puntero interno para Inicio/Hay_mas/Deme_otro
    int circuito_iint; // Circuito buscado para validar Hay_mas
} LSOBB;

void inicializarLSOBB(LSOBB* lista);
int buscarLSOBB(LSOBB* lista, int circuito, int dni, int* pos, CostoEstructura* costos);
int altaLSOBB(LSOBB* lista, Elector elector, CostoEstructura* costos);
int bajaLSOBB(LSOBB* lista, Elector elector, CostoEstructura* costos);
void mostrarLSOBB(LSOBB lista);

// Funciones para evocación de respuesta múltiple
void inicioLSOBB(LSOBB* lista, int circuito, CostoEstructura* costos);
int hay_masLSOBB(LSOBB* lista);
int deme_otroLSOBB(LSOBB* lista, Elector* elector);

#endif // LSOBB_H

