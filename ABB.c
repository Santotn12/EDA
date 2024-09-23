#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dni;
    char nombre[80];
    char servicios[120];
    char domicilio[80];
    char email[50];
    char telefono[30];
} Prestador;

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

int compararPrestador(Prestador p1, Prestador p2)
{
    int nombre = strcmp(p1.nombre, p2.nombre);
    int servicios = strcmp(p1.servicios, p2.servicios);
    int domicilio = strcmp(p1.domicilio, p2.domicilio);
    int email = strcmp(p1.email, p2.email);
    int telefono = strcmp(p1.telefono, p2.telefono);

    return (nombre && servicios && domicilio && email && telefono);
}

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
                exito= altaABB(arbol,aux,&exito);
                if (baja_ABB(arbol,aux,&exito) == 1){
                    printf("Hemos eliminado el nodo con exito");
                }else{
                printf("El valor de aux es: %d",evocarABB(arbol,aux.dni,&exito));
                }
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
        arbol->padre = arbol->pos;
        if (dni < arbol->pos->x.dni) {
            arbol->pos = arbol->pos->hijoIzq;
        } else {
            arbol->pos = arbol->pos->hijoDer;
        }
    }

    if (arbol->pos != NULL && arbol->pos->x.dni == dni) {
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
        } else {
            if (pres.dni > arbol->padre->x.dni) {
                arbol->padre->hijoDer = aux;
            } else {
                arbol->padre->hijoIzq = aux;
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

int baja_ABB(Arbol *arbol, Prestador aux, int *exito) {
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
        
        // Caso 1: El nodo a eliminar es una hoja 
        if (arbol->pos->hijoDer == NULL && arbol->pos->hijoIzq == NULL) {
            if (arbol->pos == arbol->raiz) {
                arbol->raiz = NULL;
                free(arbol->pos);
            } else {
                // Eliminar el nodo hoja y acomodar el puntero del padre
                if (arbol->padre->hijoDer == arbol->pos) {
                    free(arbol->pos);
                    arbol->padre->hijoDer = NULL;
                } else {
                    free(arbol->pos);
                    arbol->padre->hijoIzq = NULL;
                }
            }

        // Caso 2: El nodo tiene solo un hijo
        } else if (arbol->pos->hijoDer == NULL || arbol->pos->hijoIzq == NULL) {
            if (arbol->pos == arbol->raiz) {
                // raíz con un solo hijo
                if (arbol->pos->hijoIzq != NULL) {
                    arbol->raiz = arbol->raiz->hijoIzq;
                } else {
                    arbol->raiz = arbol->raiz->hijoDer;
                }
                free(arbol->pos);
            } else {
                // acomodar el padre para conectar al único hijo
                if (arbol->pos->hijoDer != NULL) {
                    if (arbol->padre->x.dni < arbol->pos->x.dni) {
                        arbol->padre->hijoDer = arbol->pos->hijoDer;
                    } else {
                        arbol->padre->hijoIzq = arbol->pos->hijoDer;
                    }
                } else {
                    if (arbol->padre->x.dni < arbol->pos->x.dni) {
                        arbol->padre->hijoDer = arbol->pos->hijoIzq;
                    } else {
                        arbol->padre->hijoIzq = arbol->pos->hijoIzq;
                    }
                }
                free(arbol->pos);
            }

        // Caso 3: El nodo tiene dos hijos
        } else {
            // buscar el remplazo
            elem = arbol->pos->hijoIzq;
            arbol->padre = arbol->pos;
            
            // Desplazarse hacia la derecha dentro del subárbol izquierdo
            while (elem->hijoDer != NULL) {
                arbol->padre = elem;
                elem = elem->hijoDer;
            }
            
            // Reemplazar los datos del nodo a eliminar por los del nodo encontrado
            arbol->pos->x = elem->x;
            
            // acomdar punteros para eliminar el nodo encontrado
            if (arbol->padre->hijoIzq == elem) {
                arbol->padre->hijoIzq = elem->hijoIzq;
            } else {
                arbol->padre->hijoDer = elem->hijoIzq;
            }
            free(elem);
        }
        return 1;
    }
}
