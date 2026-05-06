#ifndef TIPOS_H
#define TIPOS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STR 51
#define MAX_CIRCUITOS 101
#define MAX_MESAS 10
#define MAX_PERSONAS_MESA 200
#define MAX_LSOBB (MAX_CIRCUITOS * MAX_MESAS * MAX_PERSONAS_MESA)

typedef struct {
    int dni;
    char nombreApellido[MAX_STR];
    char domicilio[MAX_STR];
    int codigoPostal;
    int mesa;
    int circuito;
} Elector;

// Nodo para listas vinculadas desordenadas (usadas en LSOBB_F y ABB_F)
typedef struct NodoElector {
    Elector dato;
    struct NodoElector* sig;
} NodoElector;

typedef struct {
    int nroCircuito;
    NodoElector* listaElectores;
} Circuito;

#endif // TIPOS_H
