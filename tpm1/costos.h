#ifndef COSTOS_H
#define COSTOS_H

typedef struct {
    float altas;
    float bajas;
    float consultas;
} CostoEstructura;

typedef struct {
    CostoEstructura lsobb;
    CostoEstructura lsobb_f;
    CostoEstructura abb;
    CostoEstructura abb_f;
} SistemaCostos;

void inicializarCostos(SistemaCostos* costos);
void mostrarTablaCostos(SistemaCostos costos);

#endif // COSTOS_H
