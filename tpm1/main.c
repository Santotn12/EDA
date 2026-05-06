/*
============================================================================
                    PRÁCTICO DE MÁQUINA 1 - AÑO 2026
              Sistema de Registro del Padrón Electoral - San Luis

ANÁLISIS CRÍTICO PRELIMINAR:
============================

El siguiente programa implementa un sistema de registro electoral que almacena
electores en 4 estructuras de datos distintas para realizar un análisis 
comparativo de costos algorítmicos.

ESTRUCTURAS IMPLEMENTADAS:
------ LSOBB (Lista Secuencial Ordenada con Búsqueda Binaria):
         - Almacena nuplas completas en un arreglo ordenado por Circuito.
         - Búsqueda: O(log n) con bisección estricta (li inclusivo, ls inclusivo,
           testigo a izquierda, segmento más grande a derecha).
         - Altas/Bajas: O(n) por corrimientos en peor caso.
         - Ventaja: Búsqueda rápida.
         - Desventaja: Ineficiencia en inserciones/eliminaciones.

------ LSOBB_F (Lista con Dependencia Funcional Forzada):
         - Lista secuencial de Circuitos (ordenada).
         - Cada circuito apunta a una lista vinculada desordenada de electores.
         - Búsqueda Circuito: O(log m) siendo m cantidad de circuitos.
         - Búsqueda Elector: O(e) siendo e cantidad de electores del circuito.
         - Altas/Bajas en Circuitos: O(m) por corrimientos.
         - Altas/Bajas en Electores: O(1) al inicio de lista vinculada.
         - Ventaja: Menor espacio, altas/bajas rápidas en electores.
         - Desventaja: Búsqueda lineal dentro de circuito.

------ ABB (Árbol Binario de Búsqueda):
         - Almacena nuplas completas en nodos del árbol.
         - Menores o iguales van a la derecha (política especial).
         - Búsqueda: O(log n) promedio, O(n) peor caso.
         - Altas/Bajas: O(log n) promedio, conteo de modificaciones de punteros.
         - Política Baja: "Menor de los Mayores" con copia de datos.
         - Ventaja: Balance dinámico, inserción/eliminación relativamente eficiente.
         - Desventaja: Recorrido preorden completo para mostrar.

------ ABB_F (Árbol con Dependencia Funcional):
         - Árbol de Circuitos (nodos contienen nroCircuito).
         - Cada nodo apunta a lista vinculada desordenada de electores.
         - Búsqueda Circuito: O(log m) promedio.
         - Búsqueda Elector: O(e) lineal en la lista.
         - Altas/Bajas: Menores costos de punteros por estructura lineal de electores.
         - Ventaja: Combina eficiencia de árbol con eficiencia de listas.
         - Desventaja: Mayor complejidad de implementación.

HIPÓTESIS DE COMPORTAMIENTO ESPERADO:
------------------------------------
1. Búsquedas: ABB y LSOBB deberían ser similares en costo (O(log n) vs binaria).
   LSOBB_F y ABB_F incluyen búsqueda lineal, incrementando costo de consultas.

2. Altas/Bajas en Listas: LSOBB tendrá mayor costo por corrimientos.
   LSOBB_F tendrá corrimientos solo en circuitos (pocos), electores al inicio (O(1)).

3. Altas/Bajas en Árboles: ABB y ABB_F tendrán costos similares de punteros.
   ABB_F puede ahorrar si hay muchos electores por circuito.

4. Uso de Memoria: LSOBB usa más memoria (nupla completa en array).
   LSOBB_F y ABB_F usan menos por estructura lineal de electores.

CONCLUSIÓN ESPERADA:
En caso de muchas inserciones/eliminaciones: LSOBB_F es superior.
En caso de muchas búsquedas puntuales: LSOBB y ABB son superiores.
ABB_F es una alternativa balanceada.

Los resultados del archivo Operaciones_Padron.txt validarán estas hipótesis.

============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "lsobb.h"
#include "lsobb_f.h"
#include "abb.h"
#include "abb_f.h"
#include "utilidades.h"
#include "costos.h"

void mostrarMenu()
{
    printf("\n========== MENU PRINCIPAL ==========\n");
    printf("1. Mostrar Estructura (LSOBB)\n");
    printf("2. Mostrar Estructura (LSOBB_F)\n");
    printf("3. Mostrar Estructura (ABB)\n");
    printf("4. Mostrar Estructura (ABB_F)\n");
    printf("5. Comparar Costos de Estructuras\n");
    printf("6. Salir\n");
    printf("====================================\n");
    printf("Ingrese opción: ");
}

int main()
{
    // Inicializar estructuras
    LSOBB lsobb;
    LSOBB_F lsobb_f;
    ABB abb;
    ABB_F abb_f;
    SistemaCostos costos;

    inicializarLSOBB(&lsobb);
    inicializarLSOBB_F(&lsobb_f);
    inicializarABB(&abb);
    inicializarABB_F(&abb_f);
    inicializarCostos(&costos);

    // Procesar archivo de operaciones
    printf("Procesando archivo 'Operaciones_Padron.txt'...\n");
    if (!procesarArchivoOperaciones("Operaciones_Padron.txt", 
                                     &lsobb, &lsobb_f, &abb, &abb_f, &costos)) {
        printf("Advertencia: No se pudo procesar el archivo.\n");
    }

    // Menú interactivo
    int opcion;
    while (1) {
        mostrarMenu();
        scanf("%d", &opcion);
        getchar(); // Consumir el salto de línea

        switch (opcion) {
            case 1:
                mostrarLSOBB(lsobb);
                break;

            case 2:
                mostrarLSOBB_F(lsobb_f);
                break;

            case 3:
                mostrarABB(abb);
                break;

            case 4:
                mostrarABB_F(abb_f);
                break;

            case 5:
                mostrarTablaCostos(costos);
                break;

            case 6:
                printf("Finalizando programa...\n");
                // Liberar memoria dinámica
                liberarABB(abb.raiz);
                liberarABB_F(abb_f.raiz);
                // Las listas vinculadas en LSOBB_F se limpian aquí si es necesario
                return 0;

            default:
                printf("Opción inválida.\n");
        }
    }

    return 0;
}
