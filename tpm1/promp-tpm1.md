# Requisitos del Programa: Padrón Electoral San Luis

## 1. Enunciado Principal
[cite_start]Se debe implementar un sistema de registro para el padrón electoral de la provincia de San Luis[cite: 6]. 
* [cite_start]Se esperan **101 circuitos electorales**[cite: 50].
* [cite_start]Cada circuito tiene hasta **10 mesas**[cite: 21].
* [cite_start]Cada mesa soporta hasta **200 personas**[cite: 21].

## 2. Campos de Entrada (Datos de la Nupla)
[cite_start]El ingreso de datos **no debe ser sensible a mayúsculas y minúsculas** (ej. SOSA = SoSa = sosa)[cite: 65]. [cite_start]La relación está dada por: `Circuito (DNI, Nombre Apellido, Domicilio, Cód. Postal, Mesa)`[cite: 20].

* [cite_start]**Circuito:** Número de 4 dígitos[cite: 59].
* [cite_start]**D.N.I.:** Número entero[cite: 60].
* [cite_start]**Nombre y Apellido:** Secuencia de caracteres (hasta 50)[cite: 61].
* [cite_start]**Domicilio:** Secuencia de caracteres (hasta 50)[cite: 62].
* [cite_start]**Código Postal:** Número de 4 dígitos[cite: 63].
* [cite_start]**Mesa:** Número entero[cite: 64].

## 3. Estructuras a Desarrollar
[cite_start]Se deben cargar los mismos datos simultáneamente en 4 estructuras distintas[cite: 22]:
1. [cite_start]**LSOBB:** Lista Secuencial Ordenada con búsqueda binaria (Sin forzar dependencia funcional)[cite: 23].
2. [cite_start]**LSOBB_F:** Lista Secuencial Ordenada con búsqueda binaria (Forzando dependencia funcional)[cite: 24].
3. [cite_start]**ABB:** Árbol Binario de Búsqueda (Sin forzar dependencia funcional)[cite: 25].
4. [cite_start]**ABB_F:** Árbol Binario de Búsqueda (Forzando dependencia funcional)[cite: 26].

## 4. Gestión de Dependencia Funcional
* [cite_start]**Sin Forzar Dependencia:** Cada nodo/celda de la estructura principal contiene la nupla completa del elector[cite: 23, 25]. [cite_start]Para el ABB, los elementos menores o iguales se ubican por la rama derecha[cite: 57].
* **Forzando Dependencia:** La estructura principal almacena los "Circuitos". [cite_start]De cada circuito se desprende una lista vinculada (desordenada) que contiene a los electores correspondientes[cite: 24, 26, 58].

## 5. Interacción con el Archivo TXT de Entrada
* [cite_start]**Archivo:** `Operaciones_Padron.txt`[cite: 38].
* [cite_start]**Estado inicial:** Antes de procesar el archivo, las 4 estructuras deben estar completamente vacías[cite: 39].
* [cite_start]**Lectura:** El archivo contiene una primera línea con el **código de operación**[cite: 46]:
    * [cite_start]`1` = Alta [cite: 46]
    * [cite_start]`2` = Baja [cite: 46]
    * [cite_start]`3` = Evocación (Consulta) [cite: 46]
* [cite_start]Debajo de cada código, el archivo contiene los datos de la nupla en líneas individuales[cite: 46].
* [cite_start]Luego de procesar todas las operaciones del archivo, los datos deben persistir en las estructuras para ser mostrados[cite: 41].

## 6. Funciones del Menú y Salidas
[cite_start]El menú principal debe tener al menos estas dos opciones[cite: 27]:

### A. Mostrar Estructura
[cite_start]Debe mostrar por pantalla el contenido de la estructura elegida (con datos remanentes post-archivo)[cite: 28, 41].
* [cite_start]**Listas:** Mostrar cada circuito y sus electores asociados[cite: 29].
* [cite_start]**Árboles:** Realizar un **barrido preorden**[cite: 29]. [cite_start]Mostrar el circuito, los electores [cite: 29][cite_start], y por cada nodo indicar el campo Circuito de sus nodos hijos especificando si es hijo izquierdo o derecho[cite: 30].

### B. Comparación de Estructuras (y Costos)
[cite_start]Debe realizar ingresos, bajas y consultas sobre un circuito dado para comparar las 4 estructuras[cite: 31]. [cite_start]Al finalizar, mostrar por pantalla los costos para cada estructura[cite: 40].
* **Conclusión obligatoria:** Debe haber un análisis del peor escenario y el comportamiento esperado. [cite_start]Esta conclusión (incluyendo los resultados numéricos) debe ir **como comentario al principio del código fuente principal (en el main)**[cite: 32, 33, 34].

## 7. Reglas de Conteo de Costos
* **Listas Secuenciales (Altas y Bajas):** Costo = cantidad de corrimientos. (1 corrimiento = costo 1) [cite_start][cite: 35].
* **Árboles ABB (Altas y Bajas):** Costo = modificaciones de punteros. (1 modificación = costo 0.5) [cite_start][cite: 36]. [cite_start]Si se usa política de reemplazo en la baja, sumar un costo de 1 por la copia de datos[cite: 36].
* **Consultas / Evocación (Todas las estructuras):** Costo = total de celdas consultadas. (1 celda = costo 1) [cite_start][cite: 37].

## 8. Consideraciones Especiales del Contexto
* [cite_start]**Búsqueda Binaria (Listas):** Debe usar bisección, límite inferior inclusivo, límite superior inclusivo, testigo a la izquierda y el segmento más grande a la derecha[cite: 53].
* [cite_start]**Espacio en Listas:** Recirculan sobre su espacio[cite: 51]. [cite_start]No se permiten elementos ficticios para indicar inicio o fin[cite: 54].
* **Orden de Listas:** Ordenadas de menor a mayor por Circuito. [cite_start]No existe orden interno entre electores del mismo circuito[cite: 52].
* [cite_start]**Bajas / Eliminaciones:** La confirmación de la baja debe realizarse mediante código comparando **toda la nupla** en cualquiera de las estructuras[cite: 55].
* [cite_start]**Reemplazo en Árboles:** Para la baja en ABB de un nodo con dos hijos, usar la política del **menor de los mayores**, realizando el reemplazo con copia de datos[cite: 56].