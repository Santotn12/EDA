#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "tipos.h"
#include "lsobb.h"
#include "lsobb_f.h"
#include "abb.h"
#include "abb_f.h"
#include "costos.h"

// Normalizaci贸n de texto (insensibilidad a may煤sculas/min煤sculas)
void str_normalize(char* str);
void str_normalize_copy(const char* src, char* dst);

// Lectura de archivo de operaciones
int procesarArchivoOperaciones(const char* nombreArchivo,
                               LSOBB* lsobb, LSOBB_F* lsobb_f,
                               ABB* abb, ABB_F* abb_f,
                               SistemaCostos* costos);

// Comparaci贸n de electores (para bajas)
int compararElectores(Elector e1, Elector e2);

#endif // UTILIDADES_H
