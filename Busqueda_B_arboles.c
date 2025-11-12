/*Implementa aquí la operación de búsqueda. 
Pueden modificar la extensión del documento para que se ajuste al lenguaje de su elección y comentar estas instrucciones.*/
#include <stdio.h>
#include <stdlib.h>

#define T 2 // Grado mínimo del B-árbol

// Definición de un nodo B-Tree
typedef struct BArbolNodo {
    int *keys;                  // Arreglo de claves en el nodo
    struct BArbolNodo **hijos;  // Arreglo de punteros a hijos
    int n;                      // Número actual de claves
    int hoja;                   // 1 si es hoja, 0 si no
} BArbolNodo;

// Estructura para devolver el resultado de búsqueda
typedef struct {
    BArbolNodo *nodo;
    int index;
} ResultadoBusqueda;

// Crea un nodo B-Tree vacío
BArbolNodo* crearNodo(int hoja) {  // 🔹 corregido nombre (antes: createNodo)
    BArbolNodo* nodo = (BArbolNodo*)malloc(sizeof(BArbolNodo));
    nodo->keys = (int*)malloc(sizeof(int) * (2 * T - 1));
    nodo->hijos = (BArbolNodo**)malloc(sizeof(BArbolNodo*) * (2 * T));
    nodo->n = 0;
    nodo->hoja = hoja;
    return nodo;
}

// Implementación de la búsqueda en B-Tree
ResultadoBusqueda BArbolNodo_search(BArbolNodo *x, int k) {
    int i = 0;
    // Encuentra el primer índice mayor o igual a k
    while (i < x->n && k > x->keys[i])
        i++;
    // Si se encuentra la clave
    if (i < x->n && k == x->keys[i]) {
        ResultadoBusqueda result = {x, i};
        return result;
    }
    // Si es hoja, no se encontró
    if (x->hoja) {
        ResultadoBusqueda resultado = {NULL, -1};
        return resultado;
    }
    // Buscar recursivamente en el hijo
    return BArbolNodo_search(x->hijos[i], k);
}

// Utilidad para imprimir un nodo encontrado
void imprimirResultado(ResultadoBusqueda res) {
    if (res.nodo != NULL)
        printf("Clave encontrada en la posición %d del nodo.\n", res.index);
    else
        printf("Clave no encontrada.\n");
}

// --- CÓDIGO DE PRUEBA Y SETUP MANUAL ---
int main() {
    // Crear raíz y llenarla manualmente
    BArbolNodo* raiz = crearNodo(0);  // 🔹 corregido nombre de función
    raiz->keys[0] = 10;
    raiz->keys[1] = 20;
    raiz->n = 2;

    raiz->hijos[0] = crearNodo(1); // 🔹 corregido nombre
    raiz->hijos[1] = crearNodo(1);
    raiz->hijos[2] = crearNodo(1);

    raiz->hijos[0]->keys[0] = 5;
    raiz->hijos[0]->n = 1;

    raiz->hijos[1]->keys[0] = 15;
    raiz->hijos[1]->n = 1;

    raiz->hijos[2]->keys[0] = 25;
    raiz->hijos[2]->n = 1;

    int k;
    printf("Arreglo (B-Arbol manual):\n");
    printf("Nodo raíz: ");
    for (int j = 0; j < raiz->n; j++) printf("%d ", raiz->keys[j]);  // 🔹 corregido "root" → "raiz"
    printf("\nHijo 0: %d\n", raiz->hijos[0]->keys[0]);
    printf("Hijo 1: %d\n", raiz->hijos[1]->keys[0]);
    printf("Hijo 2: %d\n", raiz->hijos[2]->keys[0]);

    printf("\nIntroduce la clave a buscar: ");
    scanf("%d", &k);

    ResultadoBusqueda resultado = BArbolNodo_search(raiz, k);
    imprimirResultado(resultado);

    // Liberar memoria
    free(raiz->keys);
    for (int i = 0; i < 3; i++) {
        free(raiz->hijos[i]->keys);
        free(raiz->hijos[i]);
    }
    free(raiz->hijos);
    free(raiz);

    return 0;
}
