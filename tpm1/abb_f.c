#include "abb_f.h"
#include <stdlib.h>
#include <string.h>

void inicializarABB_F(ABB_F* arbol)
{
    arbol->raiz = NULL;
}

// Rutina auxiliar: búsqueda de circuito en el árbol
static NodoABB_F* _buscarNodoCircuito(NodoABB_F* nodo, int nroCircuito, float* celdas)
{
    if (nodo == NULL) {
        return NULL;
    }

    (*celdas)++;

    if (nodo->nroCircuito == nroCircuito) {
        return nodo;
    } else if (nroCircuito < nodo->nroCircuito) {
        return _buscarNodoCircuito(nodo->der, nroCircuito, celdas);
    } else {
        return _buscarNodoCircuito(nodo->izq, nroCircuito, celdas);
    }
}

// Rutina auxiliar para inserción recursiva
static int _altaABB_F(NodoABB_F** nodo, Elector elector, CostoEstructura* costos)
{
    if (*nodo == NULL) {
        *nodo = (NodoABB_F*)malloc(sizeof(NodoABB_F));
        if (!*nodo) return 0;

        (*nodo)->nroCircuito = elector.circuito;
        (*nodo)->listaElectores = (NodoElector*)malloc(sizeof(NodoElector));
        if (!(*nodo)->listaElectores) return 0;

        (*nodo)->listaElectores->dato = elector;
        (*nodo)->listaElectores->sig = NULL;
        (*nodo)->izq = NULL;
        (*nodo)->der = NULL;

        if (costos) {
            costos->altas += 0.5; // Reasignación de puntero
        }
        return 1;
    }

    if (elector.circuito == (*nodo)->nroCircuito) {
        // Circuito existe, insertar al principio de la lista
        NodoElector* nuevoNodo = (NodoElector*)malloc(sizeof(NodoElector));
        if (!nuevoNodo) return 0;

        nuevoNodo->dato = elector;
        nuevoNodo->sig = (*nodo)->listaElectores;
        (*nodo)->listaElectores = nuevoNodo;

        return 1;
    } else if (elector.circuito < (*nodo)->nroCircuito) {
        // Menores o iguales van a la derecha
        if (costos) {
            costos->altas += 0.5; // Modificación de puntero
        }
        return _altaABB_F(&(*nodo)->der, elector, costos);
    } else {
        if (costos) {
            costos->altas += 0.5; // Modificación de puntero
        }
        return _altaABB_F(&(*nodo)->izq, elector, costos);
    }
}

int altaABB_F(ABB_F* arbol, Elector elector, CostoEstructura* costos)
{
    return _altaABB_F(&arbol->raiz, elector, costos);
}

// Rutina auxiliar: encontrar el menor del árbol
static NodoABB_F* menorDelArbol_ABB_F(NodoABB_F* nodo)
{
    while (nodo->der != NULL) {
        nodo = nodo->der;
    }
    return nodo;
}

// Rutina auxiliar para baja
static int _bajaABB_F(NodoABB_F** nodo, Elector elector, CostoEstructura* costos)
{
    if (*nodo == NULL) {
        return 0;
    }

    if ((*nodo)->nroCircuito == elector.circuito) {
        // Buscar elector en la lista vinculada
        NodoElector* actual = (*nodo)->listaElectores;
        NodoElector* anterior = NULL;

        while (actual) {
            if (actual->dato.dni == elector.dni && compararElectores(actual->dato, elector)) {
                if (anterior) {
                    anterior->sig = actual->sig;
                } else {
                    (*nodo)->listaElectores = actual->sig;
                }
                free(actual);

                // Si la lista quedó vacía, eliminar el nodo del árbol
                if ((*nodo)->listaElectores == NULL) {
                    if ((*nodo)->izq == NULL) {
                        NodoABB_F* temp = *nodo;
                        *nodo = (*nodo)->der;
                        free(temp);
                        if (costos) {
                            costos->bajas += 0.5;
                        }
                    } else if ((*nodo)->der == NULL) {
                        NodoABB_F* temp = *nodo;
                        *nodo = (*nodo)->izq;
                        free(temp);
                        if (costos) {
                            costos->bajas += 0.5;
                        }
                    } else {
                        // Dos hijos - Menor de los Mayores
                        NodoABB_F* sucesor = menorDelArbol_ABB_F((*nodo)->izq);
                        (*nodo)->nroCircuito = sucesor->nroCircuito;
                        NodoElector* temp_lista = (*nodo)->listaElectores;
                        (*nodo)->listaElectores = sucesor->listaElectores;
                        sucesor->listaElectores = temp_lista;

                        if (costos) {
                            costos->bajas += 1.0; // Copia de datos
                        }

                        Elector dummy;
                        dummy.circuito = sucesor->nroCircuito;
                        dummy.dni = 0; // Dummy
                        _bajaABB_F(&(*nodo)->izq, dummy, costos);
                    }
                }

                return 1;
            }

            anterior = actual;
            actual = actual->sig;
        }

        return 0; // Elector no encontrado
    } else if (elector.circuito < (*nodo)->nroCircuito) {
        if (costos) {
            costos->bajas += 0.5;
        }
        return _bajaABB_F(&(*nodo)->der, elector, costos);
    } else {
        if (costos) {
            costos->bajas += 0.5;
        }
        return _bajaABB_F(&(*nodo)->izq, elector, costos);
    }
}

int bajaABB_F(ABB_F* arbol, Elector elector, CostoEstructura* costos)
{
    return _bajaABB_F(&arbol->raiz, elector, costos);
}

// Búsqueda de elector (buscar circuito, luego lineal en lista)
int buscarABB_F(ABB_F arbol, int circuito, int dni, CostoEstructura* costos)
{
    float celdas = 0.0;
    NodoABB_F* nodoCircuito = _buscarNodoCircuito(arbol.raiz, circuito, &celdas);

    if (!nodoCircuito) {
        if (costos) {
            costos->consultas += celdas;
        }
        return 0;
    }

    // Búsqueda lineal en la lista de electores
    NodoElector* actual = nodoCircuito->listaElectores;
    while (actual) {
        celdas++;
        if (actual->dato.dni == dni) {
            if (costos) {
                costos->consultas += celdas;
            }
            return 1;
        }
        actual = actual->sig;
    }

    if (costos) {
        costos->consultas += celdas;
    }
    return 0;
}

// Barrido Preorden
static void _mostrarABB_F_preorden(NodoABB_F* nodo, int nivel)
{
    if (nodo == NULL) {
        return;
    }

    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }

    printf("[Circuito: %d]\n", nodo->nroCircuito);

    // Mostrar electores
    NodoElector* actual = nodo->listaElectores;
    while (actual) {
        for (int i = 0; i < nivel + 2; i++) {
            printf("  ");
        }
        Elector e = actual->dato;
        printf("DNI: %d | Nombre: %s | Dom: %s | CP: %d | Mesa: %d\n",
               e.dni, e.nombreApellido, e.domicilio, e.codigoPostal, e.mesa);
        actual = actual->sig;
    }

    if (nodo->der != NULL) {
        for (int i = 0; i < nivel; i++) printf("  ");
        printf("  Hijo Derecho (Circuito: %d)\n", nodo->der->nroCircuito);
        _mostrarABB_F_preorden(nodo->der, nivel + 2);
    }

    if (nodo->izq != NULL) {
        for (int i = 0; i < nivel; i++) printf("  ");
        printf("  Hijo Izquierdo (Circuito: %d)\n", nodo->izq->nroCircuito);
        _mostrarABB_F_preorden(nodo->izq, nivel + 2);
    }
}

void mostrarABB_F(ABB_F arbol)
{
    if (arbol.raiz == NULL) {
        printf("ABB_F: Estructura vacía\n");
        return;
    }

    printf("\n=== ABB_F (Árbol con Dependencia Funcional) - Preorden ===\n");
    _mostrarABB_F_preorden(arbol.raiz, 0);
    printf("=== FIN ABB_F ===\n");
}

// Liberación
static void _liberarABB_F(NodoABB_F* nodo)
{
    if (nodo == NULL) {
        return;
    }

    _liberarABB_F(nodo->der);
    _liberarABB_F(nodo->izq);

    NodoElector* actual = nodo->listaElectores;
    while (actual) {
        NodoElector* temp = actual;
        actual = actual->sig;
        free(temp);
    }

    free(nodo);
}

void liberarABB_F(NodoABB_F* nodo)
{
    _liberarABB_F(nodo);
}
