#include "costos.h"
#include <stdio.h>

void inicializarCostos(SistemaCostos* costos)
{
    costos->lsobb.altas = 0.0;
    costos->lsobb.bajas = 0.0;
    costos->lsobb.consultas = 0.0;

    costos->lsobb_f.altas = 0.0;
    costos->lsobb_f.bajas = 0.0;
    costos->lsobb_f.consultas = 0.0;

    costos->abb.altas = 0.0;
    costos->abb.bajas = 0.0;
    costos->abb.consultas = 0.0;

    costos->abb_f.altas = 0.0;
    costos->abb_f.bajas = 0.0;
    costos->abb_f.consultas = 0.0;
}

void mostrarTablaCostos(SistemaCostos costos)
{
    printf("\n=== TABLA COMPARATIVA DE COSTOS ===\n");
    printf("%-15s | %10s | %10s | %10s | %10s\n", "Estructura", "Altas", "Bajas", "Consultas", "Total");
    printf("%s\n", "-------------------------------------------------------------------");

    float total_lsobb = costos.lsobb.altas + costos.lsobb.bajas + costos.lsobb.consultas;
    float total_lsobb_f = costos.lsobb_f.altas + costos.lsobb_f.bajas + costos.lsobb_f.consultas;
    float total_abb = costos.abb.altas + costos.abb.bajas + costos.abb.consultas;
    float total_abb_f = costos.abb_f.altas + costos.abb_f.bajas + costos.abb_f.consultas;

    printf("%-15s | %10.2f | %10.2f | %10.2f | %10.2f\n", "LSOBB", costos.lsobb.altas, costos.lsobb.bajas, costos.lsobb.consultas, total_lsobb);
    printf("%-15s | %10.2f | %10.2f | %10.2f | %10.2f\n", "LSOBB_F", costos.lsobb_f.altas, costos.lsobb_f.bajas, costos.lsobb_f.consultas, total_lsobb_f);
    printf("%-15s | %10.2f | %10.2f | %10.2f | %10.2f\n", "ABB", costos.abb.altas, costos.abb.bajas, costos.abb.consultas, total_abb);
    printf("%-15s | %10.2f | %10.2f | %10.2f | %10.2f\n", "ABB_F", costos.abb_f.altas, costos.abb_f.bajas, costos.abb_f.consultas, total_abb_f);
    printf("=== FIN TABLA ===\n\n");
}
