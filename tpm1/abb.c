#include "abb.h"
#include <stdlib.h>
#include <string.h>

void inicializarABB(ABB* arbol)
{
    arbol->raiz = NULL;
}

// Rutina auxiliar para inserción recursiva con conteo de costos
static int _altaABB(NodoABB** nodo, Elector elector, CostoEstructura* costos)
{
    if (*nodo == NULL) {
        *nodo = (NodoABB*)malloc(sizeof(NodoABB));
        if (!*nodo) return 0;

        (*nodo)->dato = elector;
        (*nodo)->izq = NULL;
        (*nodo)->der = NULL;

        if (costos) {
            costos->altas += 0.5; // Reasignación de puntero
        }
        return 1;
    }

    // Menores o iguales van por derecha
    if (elector.circuito < (*nodo)->dato.circuito ||
        (elector.circuito == (*nodo)->dato.circuito && elector.dni <= (*nodo)->dato.dni)) {
        if (costos) {
            costos->altas += 0.5; // Modificación de puntero
        }
        return _altaABB(&(*nodo)->der, elector, costos);
    } else {
        if (costos) {
            costos->altas += 0.5; // Modificación de puntero
        }
        return _altaABB(&(*nodo)->izq, elector, costos);
    }
}

int altaABB(ABB* arbol, Elector elector, CostoEstructura* costos)
{
    return _altaABB(&arbol->raiz, elector, costos);
}

// Rutina auxiliar: encontrar el menor de los mayores (sucesor inmediato)
static NodoABB* menorDelArbol(NodoABB* nodo)
{
    while (nodo->der != NULL) {
        nodo = nodo->der;
    }
    return nodo;
}

// Rutina auxiliar para baja con "Menor de los Mayores"
static int _bajaABB(NodoABB** nodo, Elector elector, CostoEstructura* costos)
{
    if (*nodo == NULL) {
        return 0; // No encontrado
    }

    int cmp_nodo = (*nodo)->dato.circuito;
    int cmp_elector = elector.circuito;

    if (cmp_nodo != cmp_elector) {
        cmp_nodo = (*nodo)->dato.dni;
        cmp_elector = elector.dni;
    }

    if ((*nodo)->dato.circuito == elector.circuito &&
        (*nodo)->dato.dni == elector.dni &&
        compararElectores((*nodo)->dato, elector)) {
        // Nodo encontrado

        // Caso 1: Sin hijos o solo hijo izquierdo
        if ((*nodo)->izq == NULL) {
            NodoABB* temp = *nodo;
            *nodo = (*nodo)->der;
            free(temp);
            if (costos) {
                costos->bajas += 0.5; // Modificación de puntero
            }
            return 1;
        }

        // Caso 2: Solo hijo derecho
        if ((*nodo)->der == NULL) {
            NodoABB* temp = *nodo;
            *nodo = (*nodo)->izq;
            free(temp);
            if (costos) {
                costos->bajas += 0.5; // Modificación de puntero
            }
            return 1;
        }

        // Caso 3: Dos hijos - Menor de los Mayores
        NodoABB* sucesor = menorDelArbol((*nodo)->izq);
        (*nodo)->dato = sucesor->dato; // Copia de datos

        if (costos) {
            costos->bajas += 1.0; // 1 punto extra por copia de datos
        }

        // Eliminar el nodo sucesor
        Elector temp = sucesor->dato;
        return _bajaABB(&(*nodo)->izq, temp, costos);

    } else if (elector.circuito < (*nodo)->dato.circuito ||
               (elector.circuito == (*nodo)->dato.circuito && elector.dni <= (*nodo)->dato.dni)) {
        // Buscar en derecha (menores van a la derecha)
        if (costos) {
            costos->bajas += 0.5; // Movimiento en árbol
        }
        return _bajaABB(&(*nodo)->der, elector, costos);
    } else {
        // Buscar en izquierda
        if (costos) {
            costos->bajas += 0.5; // Movimiento en árbol
        }
        return _bajaABB(&(*nodo)->izq, elector, costos);
    }
}

int bajaABB(ABB* arbol, Elector elector, CostoEstructura* costos)
{
    return _bajaABB(&arbol->raiz, elector, costos);
}

// Rutina auxiliar para búsqueda recursiva
static int _buscarABB(NodoABB* nodo, int circuito, int dni, float* celdas_consultadas)
{
    if (nodo == NULL) {
        return 0;
    }

    (*celdas_consultadas)++;

    if (nodo->dato.circuito == circuito && nodo->dato.dni == dni) {
        return 1;
    } else if (circuito < nodo->dato.circuito ||
               (circuito == nodo->dato.circuito && dni <= nodo->dato.dni)) {
        return _buscarABB(nodo->der, circuito, dni, celdas_consultadas);
    } else {
        return _buscarABB(nodo->izq, circuito, dni, celdas_consultadas);
    }
}

int buscarABB(ABB arbol, int circuito, int dni, CostoEstructura* costos)
{
    float celdas = 0.0;
    int resultado = _buscarABB(arbol.raiz, circuito, dni, &celdas);

    if (costos) {
        costos->consultas += celdas;
    }

    return resultado;
}

// Barrido Preorden mostrando estructura explícitamente
static void _mostrarABB_preorden(NodoABB* nodo, int nivel)
{
    if (nodo == NULL) {
        return;
    }

    // Indentar según nivel
    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }

    Elector e = nodo->dato;
    printf("[Circuito: %d] DNI: %d | Nombre: %s | Dom: %s | CP: %d | Mesa: %d\n",
           e.circuito, e.dni, e.nombreApellido, e.domicilio, e.codigoPostal, e.mesa);

    if (nodo->der != NULL) {
        for (int i = 0; i < nivel; i++) printf("  ");
        printf("  Hijo Derecho (Circuito: %d)\n", nodo->der->dato.circuito);
        _mostrarABB_preorden(nodo->der, nivel + 2);
    }

    if (nodo->izq != NULL) {
        for (int i = 0; i < nivel; i++) printf("  ");
        printf("  Hijo Izquierdo (Circuito: %d)\n", nodo->izq->dato.circuito);
        _mostrarABB_preorden(nodo->izq, nivel + 2);
    }
}

void mostrarABB(ABB arbol)
{
    if (arbol.raiz == NULL) {
        printf("ABB: Estructura vacía\n");
        return;
    }

    printf("\n=== ABB (Árbol Binario de Búsqueda) - Preorden ===\n");
    _mostrarABB_preorden(arbol.raiz, 0);
    printf("=== FIN ABB ===\n");
}

// Liberación de memoria
static void _liberarABB(NodoABB* nodo)
{
    if (nodo == NULL) {
        return;
    }

    _liberarABB(nodo->der);
    _liberarABB(nodo->izq);
    free(nodo);
}

void liberarABB(NodoABB* nodo)
{
    _liberarABB(nodo);
}
