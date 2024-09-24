#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//TIPO DE NUPLA
typedef struct
{
    int dni;
    char nombre[80];
    char servicios[120];
    char domicilio[80];
    char email[50];
    char telefono[30];
} Prestador;
//ARBOL
typedef struct Nodo {
    Prestador x;
    struct Nodo *hijoIzq;
    struct Nodo *hijoDer;
}Nodo;

typedef struct Arbol
{
    Nodo *raiz;
    Nodo *pos;
    Nodo *padre;
}Arbol;

Arbol* inicializarArbol() {
    Arbol* arbol = (Arbol*) malloc(sizeof(Arbol));
    if (arbol != NULL) {
        arbol->raiz = NULL;
        arbol->pos = NULL;
        arbol->padre = NULL;
    }
    return arbol;
}
//FUNCION AUXILIAR PARA LA BAJA
int compararPrestador(Prestador p1, Prestador p2)
{
    int nombre = strcmp(p1.nombre, p2.nombre);
    int servicios = strcmp(p1.servicios, p2.servicios);
    int domicilio = strcmp(p1.domicilio, p2.domicilio);
    int email = strcmp(p1.email, p2.email);
    int telefono = strcmp(p1.telefono, p2.telefono);

    return (nombre && servicios && domicilio && email && telefono);
}
//PILA

typedef struct NodoPila {
    Nodo *nodo; // Puntero al nodo del arbol
    struct NodoPila *siguiente; // Puntero al siguiente nodo en la pila
} NodoPila;

typedef struct Pila {
    NodoPila *tope; // Puntero al nodo en la parte superior de la pila
} Pila;

// Funcion para crear la pila
Pila* initPila() {
    Pila *pila = (Pila *)malloc(sizeof(Pila));
    pila->tope = NULL;
    return pila;
}

// Función para verificar si la pila está vacía
int PilaVacia(Pila *pila) {
    return pila->tope == NULL;
}

// Función para push un nodo
void push(Pila *pila, Nodo *nodo) {
    NodoPila *nuevoNodo = (NodoPila *)malloc(sizeof(NodoPila));
    nuevoNodo->nodo = nodo;
    nuevoNodo->siguiente = pila->tope;
    pila->tope = nuevoNodo;
}

// Función para despush un nodo
Nodo* pop(Pila *pila) {
    if (PilaVacia(pila)) {
        return NULL; // O manejar el error de otra manera
    }
    NodoPila *temp = pila->tope;
    Nodo *nodo = temp->nodo;
    pila->tope = temp->siguiente;
    free(temp); // Liberamos el nodo de la pila
    return nodo;
}

// Función para liberar la memoria de la pila 
void liberarPila(Pila *pila) {
    while (!PilaVacia(pila)) {
        pop(pila);
    }
    free(pila);
}

typedef struct Costos{
    float costoABB[4];
    float maxABB[4];
    int cant_Altas[3],cant_Bajas[3],cant_EvocarE[3],cant_EvocarF[3];
    float costos_medioABB[4];
}costos;


int main(){
    Prestador aux;
    Arbol* arbol = inicializarArbol();
    if (arbol == NULL) {
        printf("No se pudo inicializar el árbol.\n");
        return 1;
    }
    int des=1;
    int exito=3;
    while (des != 0)
    {
        printf("\n\n------ Bienvenido al Sistema de Prestadores ---------\n");
        printf("\n1- Alta\n2- Baja\n3- Modificar\n4- Mostrar estructura\n5- Leer desde archivo\n6- Evocar un elemento\n0- Salir\n\n");
        printf("Opcion elegida: ");
        scanf("%d", &des);
        while (des < 0 || des > 6)
        {
            printf("Ingrese un numero valido:\n");
            scanf("%d", &des);
        }
        switch (des)
        {
            case 1:
                printf("Ingresa el DNI\n");
                scanf("%d",&aux.dni);
                printf("Ingresa el nombre\n");
                scanf("%s",&aux.nombre);
                printf("Ingresa el servicio\n");
                scanf("%s",&aux.servicios);
                printf("Ingresa el domicilio\n");
                scanf("%s",&aux.domicilio);
                printf("Ingresa el email\n");
                scanf("%s",&aux.email);
                printf("Ingresa el telefono\n");
                scanf("%s",&aux.telefono);
                exito = altaABB(arbol,aux,&exito);
                if (exito == 1){printf("Elemento cargado con exito");}
                break;
            case 2:
                printf("Ingresa el DNI\n");
                scanf("%d",&aux.dni);
                printf("Ingresa el nombre\n");
                scanf("%s",&aux.nombre);
                printf("Ingresa el servicio\n");
                scanf("%s",&aux.servicios);
                printf("Ingresa el domicilio\n");
                scanf("%s",&aux.domicilio);
                printf("Ingresa el email\n");
                scanf("%s",&aux.email);
                printf("Ingresa el telefono\n");
                scanf("%s",&aux.telefono);
                exito = bajaABB(arbol,aux,&exito);
                if (exito == 1){printf("Elemento eliminado con exito");}
                break;
            case 3:
                mostrarABB(arbol);
                break;
            case 4:
                cargarDesdeArchivo(arbol);
        }
}}

void localizarABB(Arbol *arbol, int dni, int *exito) {
    if (arbol->raiz == NULL) {
        *exito = 2; // estructura vacía
        return;
    }

    arbol->pos = arbol->raiz;
    arbol->padre = NULL;

    while (arbol->pos != NULL && arbol->pos->x.dni != dni) {
        *costo = *costo + 1;
        arbol->padre = arbol->pos;
        if (dni < arbol->pos->x.dni) {
            arbol->pos = arbol->pos->hijoIzq;
        } else {
            arbol->pos = arbol->pos->hijoDer;
        }
    }

    if (arbol->pos != NULL && arbol->pos->x.dni == dni) {
        *costo = *costo + 1;
        *exito = 1; // éxito
    } else {
        *exito = 0; // fracaso
    }
}


Nodo* crearNodo(Prestador pres){
    Nodo *nodo = (Nodo*)malloc(sizeof(Nodo));
    if (nodo == NULL) {
        return NULL;
    }
    nodo->x = pres;
    nodo->hijoIzq = NULL;
    nodo->hijoDer = NULL;
    return nodo;
}

int altaABB(Arbol *arbol, Prestador pres, int *exito) {
    localizarABB(arbol, pres.dni, exito);
    if (*exito == 1) {
        *exito = 0; // fracaso, ya está el elemento en la estructura
        return 0;
    } else {
        Nodo *aux = crearNodo(pres);
        if (aux == NULL) {
            printf("No hay espacio para crear otro nodo");
            return 0; // fracaso
        }
        if (arbol->raiz == NULL) {
            arbol->raiz = aux;
            *costo = *costo + 0.5;

        } else {
            if (pres.dni > arbol->padre->x.dni) {
                arbol->padre->hijoDer = aux;
                *costo = *costo + 0.5;
            } else {
                arbol->padre->hijoIzq = aux;
                *costo = *costo + 0.5;
            }
        }
        *exito = 1; // éxito
    }
    return 1; // prestador cargado
}

int evocarABB(Arbol *arbol, int dni, int *exito) {
    localizarABB(arbol, dni, exito);
    if (*exito == 0) {
        *exito = 0; // fracaso, ya está el elemento en la estructura
        Prestador aux;
        aux.dni = -1;
        return aux.dni;
    } else {
        Prestador aux = arbol->pos->x;
        return aux.dni;
    }
}

int bajaABB(Arbol *arbol, Prestador aux, int *exito) {
    if (arbol->raiz == NULL) {
        *exito = 0;
        return 0;
    } else {
        localizarABB(arbol, aux.dni, exito);  // Buscar el nodo a eliminar
        if (*exito == 0) {
            *exito = 0;
            return 0;  // No se encontró
        }
        struct Nodo *elem;
        
        // Caso 1: El nodo a eliminar es una hoja (sin hijos)
        if (arbol->pos->hijoDer == NULL && arbol->pos->hijoIzq == NULL) {
            if (arbol->pos == arbol->raiz) {
                arbol->raiz = NULL;
                *costo = *costo + 0.5;
                free(arbol->pos);
            } else {
                // Eliminar el nodo hoja y ajustar el padre
                if (arbol->padre->hijoDer == arbol->pos) {
                    free(arbol->pos);
                    arbol->padre->hijoDer = NULL;
                    *costo = *costo + 0.5;
                } else {
                    free(arbol->pos);
                    arbol->padre->hijoIzq = NULL;
                    *costo = *costo + 0.5;
                }
            }

        // Caso 2: El nodo tiene solo un hijo
        } else if (arbol->pos->hijoDer == NULL || arbol->pos->hijoIzq == NULL) {
            if (arbol->pos == arbol->raiz) {
                // Si es la raíz con un solo hijo
                if (arbol->pos->hijoIzq != NULL) {
                    arbol->raiz = arbol->raiz->hijoIzq;
                    *costo = *costo + 0.5;
                } else {
                    arbol->raiz = arbol->raiz->hijoDer;
                    *costo = *costo + 0.5;
                }
                free(arbol->pos);
                *costo = *costo + 0.5;
            } else {
                // Ajustar el padre para reconectar al único hijo
                if (arbol->pos->hijoDer != NULL) {
                    if (arbol->padre->x.dni < arbol->pos->x.dni) {
                        arbol->padre->hijoDer = arbol->pos->hijoDer;
                    } else {
                        arbol->padre->hijoIzq = arbol->pos->hijoDer;
                        *costo = *costo + 0.5;
                    }
                } else {
                    if (arbol->padre->x.dni < arbol->pos->x.dni) {
                        arbol->padre->hijoDer = arbol->pos->hijoIzq;
                        *costo = *costo + 0.5;
                    } else {
                        arbol->padre->hijoIzq = arbol->pos->hijoIzq;
                        *costo = *costo + 0.5;
                    }
                }
                free(arbol->pos);
            }

        // Caso 3: El nodo tiene dos hijos
        } else {
            // Ahora buscamos el mayor del subárbol izquierdo
            elem = arbol->pos->hijoIzq;
            arbol->padre = arbol->pos;
            
            // Desplazarse hacia la derecha dentro del subárbol izquierdo
            while (elem->hijoDer != NULL) {
                arbol->padre = elem;
                elem = elem->hijoDer;
            }
            
            // Reemplazar los datos del nodo a eliminar por los del nodo encontrado
            arbol->pos->x = elem->x;
            *costo = *costo + 1;

            
            // Ajustar conexiones para eliminar el nodo encontrado
            if (arbol->padre->hijoIzq == elem) {
                arbol->padre->hijoIzq = elem->hijoIzq;
            } else {
                arbol->padre->hijoDer = elem->hijoIzq;
            }
            *costo = *costo + 0.5;
            free(elem);
        }
        return 1;
    }
}

int mostrarABB(Arbol *arbol) {
    if (arbol->raiz == NULL) {
        printf("El árbol está vacío.\n");
        return 0;
    }

    Pila *pila = initPila();
    push(pila, arbol->raiz);

    while (!PilaVacia(pila)) {
        Nodo *nodoActual = pop(pila);

        // Mostrar el prestador
        printf("DNI: %d\n", nodoActual->x.dni);
        printf("Prestador: %s\n", nodoActual->x.nombre);
        printf("  Servicios: %s\n", nodoActual->x.servicios);
        printf("  Domicilio: %s\n", nodoActual->x.domicilio);
        printf("  Email: %s\n", nodoActual->x.email);
        printf("  Teléfono: %s\n", nodoActual->x.telefono);

        // Si tiene hijo derecho, lo apilamos
        if (nodoActual->hijoDer != NULL) {
            push(pila, nodoActual->hijoDer);
            // Mostrar el DNI del hijo derecho
            printf("  Hijo derecho DNI: %d\n", nodoActual->hijoDer->x.dni);
        }

        // Si tiene hijo izquierdo, lo apilamos
        if (nodoActual->hijoIzq != NULL) {
            push(pila, nodoActual->hijoIzq);
            // Mostrar el DNI del hijo izquierdo
            printf("  Hijo izquierdo DNI: %d\n", nodoActual->hijoIzq->x.dni);
        }
    }

    liberarPila(pila);
}

void cargarDesdeArchivo(Arbol *arbol){
    Prestador aux;
    int exito = 0;
    int operacion=0;
    FILE *archivo = fopen("prueba.txt", "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
    }else{
        while(!(feof(archivo))){
            fscanf(archivo," %d", &operacion);
            if(operacion==1 || operacion==2){
                fscanf(archivo," %d", &aux.dni);
                fscanf(archivo," %[^\n]s", &aux.nombre);
                fscanf(archivo," %[^\n]s", &aux.servicios);
                fscanf(archivo," %[^\n]s", &aux.domicilio);
                fscanf(archivo," %[^\n]s", &aux.email);
                fscanf(archivo," %[^\n]s", &aux.telefono);
            }else{
                fscanf(archivo," %d", &aux.dni);
            }
            switch(operacion){
                case 1: {

                    printf("\n---alta---\n");
                    exito = altaABB(arbol,aux,&exito);
                    if (exito == 1){printf("Elemento cargado con exito");}
                    break;

                }
                case 2: {
                    printf("\n---baja---\n");
                    exito = bajaABB(arbol,aux,&exito);
                    if (exito == 1){printf("Elemento eliminado con exito");}
                    break;
                }
        }
    }
    fclose(archivo);
   
}}
