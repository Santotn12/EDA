#include "lsobb_f.h"
#include <string.h>
#include <stdlib.h>

void inicializarLSOBB_F(LSOBB_F* lista)
{
    lista->cantidad = 0;
}

// =====================================================================
// FUNCIONES PARA EVOCACIÓN DE RESPUESTA MÚLTIPLE
// =====================================================================

/* 
 * Función: localizarLSOBB
 * Objetivo: Realizar la búsqueda binaria del circuito.
 * Retorna: 1 si encuentra el circuito (éxito), 0 si no.
 * Parámetros: Devuelve la posición exacta en el arreglo mediante el puntero 'pos'.
 */
int localizarLSOBB(LSOBB_F* lista, int nroCircuito, int* pos, CostoEstructura* costos)
{
    int li = 0, ls = lista->cantidad - 1;
    int celdas_consultadas = 0;
    int exito = 0;

    while (li <= ls) {
        int medio = (li + ls) / 2;
        celdas_consultadas++;

        if (lista->circuitos[medio].nroCircuito == nroCircuito) {
            if (pos) *pos = medio; // Guardamos la posición
            exito = 1;
            break;
        } else if (lista->circuitos[medio].nroCircuito < nroCircuito) {
            li = medio + 1;
        } else {
            ls = medio - 1;
        }
    }

    if (costos) {
        costos->consultas += celdas_consultadas;
    }

    return exito;
}

/* 
 * Función: inicioLSOBB
 * Objetivo: Inicializar el proceso de recuperación múltiple.
 * Mecanismo: Invoca a localizarLSOBB. Si tiene éxito, configura el iterador (iint)
 * apuntando al primer elector de ese circuito para que el main pueda recorrerlos.
 */
int inicioLSOBB(LSOBB_F* lista, int nroCircuito, NodoElector** iterador, CostoEstructura* costos)
{
    int pos;

    // 1. Invoca a Localizar para encontrar la clave x (el circuito)
    if (localizarLSOBB(lista, nroCircuito, &pos, costos)) {
        
        // 2. Configura la variable de estado interna (apunta al primer valor asociado y)
        *iterador = lista->circuitos[pos].listaElectores;
        return 1; // Éxito
        
    } else {
        // El circuito no existe, el iterador queda en NULL
        *iterador = NULL;
        return 0; // Fracaso
    }
}

// =====================================================================
// RESTO DEL CÓDIGO (Alta, Baja, Mostrar)
// =====================================================================

// Alta: Modificada internamente para usar el nuevo localizarLSOBB
int altaLSOBB_F(LSOBB_F* lista, Elector elector, CostoEstructura* costos)
{
    int pos;

    if (localizarLSOBB(lista, elector.circuito, &pos, NULL)) {
        // Circuito existe, insertar elector al principio
        NodoElector* nuevoNodo = (NodoElector*)malloc(sizeof(NodoElector));
        if (!nuevoNodo) return 0;

        nuevoNodo->dato = elector;
        nuevoNodo->sig = lista->circuitos[pos].listaElectores;
        lista->circuitos[pos].listaElectores = nuevoNodo;

        return 1;
    } else {
        // Circuito no existe, crear uno nuevo
        if (lista->cantidad >= MAX_CIRCUITOS) {
            return 0; // Lista de circuitos llena
        }

        // Encontrar posición ordenada para insertar circuito
        int nuevaPos = lista->cantidad;
        for (int i = 0; i < lista->cantidad; i++) {
            if (elector.circuito < lista->circuitos[i].nroCircuito) {
                nuevaPos = i;
                break;
            }
        }

        // Desplazar circuitos
        int corrimientos = lista->cantidad - nuevaPos;
        if (corrimientos > 0) {
            memmove(&lista->circuitos[nuevaPos + 1], &lista->circuitos[nuevaPos],
                    corrimientos * sizeof(Circuito));
            if (costos) {
                costos->altas += corrimientos;
            }
        }

        // Inicializar nuevo circuito
        lista->circuitos[nuevaPos].nroCircuito = elector.circuito;
        lista->circuitos[nuevaPos].listaElectores = (NodoElector*)malloc(sizeof(NodoElector));
        if (!lista->circuitos[nuevaPos].listaElectores) return 0;

        lista->circuitos[nuevaPos].listaElectores->dato = elector;
        lista->circuitos[nuevaPos].listaElectores->sig = NULL;

        lista->cantidad++;
        return 1;
    }
}

// Baja: Modificada internamente para usar el nuevo localizarLSOBB
int bajaLSOBB_F(LSOBB_F* lista, Elector elector, CostoEstructura* costos)
{
    int pos;

    if (!localizarLSOBB(lista, elector.circuito, &pos, NULL)) {
        return 0;
    }

    NodoElector* actual = lista->circuitos[pos].listaElectores;
    NodoElector* anterior = NULL;

    while (actual) {
        if (actual->dato.dni == elector.dni && compararElectores(actual->dato, elector)) {
            if (anterior) {
                anterior->sig = actual->sig;
            } else {
                lista->circuitos[pos].listaElectores = actual->sig;
            }
            free(actual);
            return 1;
        }

        anterior = actual;
        actual = actual->sig;
    }

    return 0; // Elector no encontrado o nupla no coincide
}

void mostrarLSOBB_F(LSOBB_F lista)
{
    if (lista.cantidad == 0) {
        printf("LSOBB_F: Estructura vacía\n");
        return;
    }

    printf("\n=== LSOBB_F (Lista con Dependencia Funcional) ===\n");

    for (int i = 0; i < lista.cantidad; i++) {
        printf("\nCircuito %d:\n", lista.circuitos[i].nroCircuito);

        NodoElector* actual = lista.circuitos[i].listaElectores;
        while (actual) {
            Elector e = actual->dato;
            printf("  DNI: %d | Nombre: %s | Dom: %s | CP: %d | Mesa: %d\n",
                   e.dni, e.nombreApellido, e.domicilio, e.codigoPostal, e.mesa);
            actual = actual->sig;
        }
    }

    printf("\n=== FIN LSOBB_F ===\n");
}