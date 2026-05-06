#include "lsobb.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void inicializarLSOBB(LSOBB* lista)
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
int localizarLSOBB(LSOBB* lista, int nroCircuito, int* pos, CostoEstructura* costos) {
    int li = 0, ls = lista->cantidad - 1;
    int celdas_consultadas = 0;
    int exito = 0;
    int medio;

    if (lista->cantidad == 0) {
        *pos = 0; 
        //por lista vacia retornamos -1 
        return -1; 
    }

    while (li <= ls) {
        medio = (li + ls) / 2;
        celdas_consultadas++;
        
        if (lista->circuitos[medio].nroCircuito < nroCircuito) {
            li = medio + 1;
        } else {
            ls = medio - 1;
        }
    }    
    
    *pos = li;

    if (li < lista->cantidad && lista->circuitos[li].nroCircuito == nroCircuito) {
        celdas_consultadas++;
        exito = 1;
    }

    costos->consultas += celdas_consultadas;

    return exito;
}

int inicioLSOBB(LSOBB* lista, int nroCircuito, int* iterador, CostoEstructura* costos)
{
    int pos;
    // 1. Invoca a Localizar para encontrar la clave x (el circuito)
    if (localizarLSOBB(lista, nroCircuito, &pos, costos)) {
        *iterador = lista->circuitos[pos].listaElectores;
        return 1; // exito
    } else {
        return 0; // Fracaso
    }
}

bool hay_masLSOBB(LSOBB* lista, int iterador, int nroCircuitoBuscado,CostoEstructura costos) {
    // 1. Verificacion de limite
    if (iterador >= 0 && iterador < lista->cantidad) {
        costos->consultas += celdas_consultadas;
        if (lista->circuitos[iterador].nroCircuito == nroCircuitoBuscado) {
            return true;
        }
    }
    return false; 
}

void deme_otroLSOBB(LSOBB* lista, int* iterador, Elector* asociado) {
    
    *asociado = lista->circuitos[*iterador];

    (*iterador)++;
}

bool sonElectoresIguales(Elector a, Elector b) {
    if (a.circuito != b.circuito) return false;
    if (a.dni != b.dni)           return false;
    if (a.codigoPostal != b.codigoPostal) return false;
    if (a.mesa != b.mesa)         return false;

    if (strcasecmp(a.nombreApellido, b.nombreApellido) != 0) return false;
    if (strcasecmp(a.domicilio, b.domicilio) != 0) return false;

    return true;
}

int localizarLSOBB_por_y(LSOBB* lista, Elector elector, int* pos, CostoEstructura* costos){
    int iterador = *pos;
    Elector electorActual;
    while (hay_masLSOBB(lista, iterador, elector.circuito,costos)) {
            // 3. sacar y avanzar
            deme_otroLSOBB(lista, &iterador, &electorActual);
            
            if (sonElectoresIguales(elector,electorActual)){
                // nupla repetida por lo que no damos de alta
                return 0;
            }
        }
    // no encontramos la nupla, damos de alta
    return 1;

}

bool altaLSOBB(LSOBB* lista, Elector nuevo_elector, CostoEstructura* costos) {
    int pos,exito;
    // 1. Verificar Saturación
    if (lista->cantidad >= MAX_LSOBB) {
        return false; // Fracaso: La estructura este llena
    }

    exito = localizarLSOBB(lista, nuevo_elector.nroCircuito, &pos, costos);
    if (exito == -1){
        lista->datos[pos] = nuevo_elector;
        lista->cantidad = 1;
        // no hay corrimientos en lista vacia 
        return true;
    }   
    else if (exito == 1){
        //encontre el elemento
        exito = localizarLSOBB_por_y(lista,nuevo_elector,&pos,costos);
        if (exito == 0){
            //la nupla ya esta, xq lo no doy de alta
            return false;
        }else{

        }
    }
    // 3. Decidir Dirección: Distancia en el arreglo circular
    // Calculamos cuántos elementos hay a la izquierda (antes) y a la derecha (después) de 'pos'
    int elementos_antes = (pos - lista->li + MAX_LSOBB) % MAX_LSOBB;
    int elementos_despues = lista->cantidad - elementos_antes;
    
    int pos_insercion = pos;

    // 4. Desplazar (Aritmética Modular)
    if (elementos_antes < elementos_despues) {
        // CAMINO MÁS CORTO: Mover los elementos previos hacia la izquierda (antihorario)
        costos->corrimientos += elementos_antes; // Sumamos el costo
        
        // Calculamos el índice actual (nuevo inicio) y el siguiente (el que vamos a copiar)
        int act = (lista->li - 1 + MAX_LSOBB) % MAX_LSOBB;
        int sig = lista->li;
        
        for (int i = 0; i < elementos_antes; i++) {
            lista->datos[act] = lista->datos[sig];
            act = sig;
            sig = (sig + 1) % MAX_LSOBB;
        }
        
        // Actualizamos el Límite Inferior (li)
        lista->li = (lista->li - 1 + MAX_LSOBB) % MAX_LSOBB;
        
        // Como corrimos la parte izquierda hacia atrás, el "hueco" se desplazó uno a la izquierda
        pos_insercion = (pos - 1 + MAX_LSOBB) % MAX_LSOBB;
        
    } else {
        // CAMINO MÁS CORTO: Mover los elementos posteriores hacia la derecha (horario)
        costos->corrimientos += elementos_despues; // Sumamos el costo
        
        // Calculamos el índice actual (nuevo final) y el anterior (el que vamos a copiar)
        int act = (lista->ls + 1) % MAX_LSOBB;
        int ant = lista->ls;
        
        for (int i = 0; i < elementos_despues; i++) {
            lista->datos[act] = lista->datos[ant];
            act = ant;
            ant = (ant - 1 + MAX_LSOBB) % MAX_LSOBB;
        }
        
        // Actualizamos el Límite Superior (ls)
        lista->ls = (lista->ls + 1) % MAX_LSOBB;
        
        // El "hueco" queda exactamente en la posición que indicó la búsqueda
        // pos_insercion = pos; 
    }

    // 5. Insertar
    lista->datos[pos_insercion] = nuevo_elector;
    lista->cantidad++;

    return true; // Alta exitosa
}

// Baja: Modificada internamente para usar el nuevo localizarLSOBB
int bajaLSOBB(LSOBB* lista, Elector elector, CostoEstructura* costos)
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

void mostrarLSOBB(LSOBB lista)
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