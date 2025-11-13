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
BArbolNodo* crearNodo(int hoja) {
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
    while (i < x->n && k > x->keys[i])
        i++;

    if (i < x->n && k == x->keys[i]) {
        ResultadoBusqueda result = {x, i};
        return result;
    }

    if (x->hoja) {
        ResultadoBusqueda resultado = {NULL, -1};
        return resultado;
    }

    return BArbolNodo_search(x->hijos[i], k);
}

// Utilidad para imprimir el resultado
void imprimirResultado(ResultadoBusqueda res) {
    if (res.nodo != NULL)
        printf("✅ Clave encontrada en la posición %d del nodo.\n", res.index);
    else
        printf("❌ Clave no encontrada en el B-árbol.\n");
}

// --- CÓDIGO PRINCIPAL ---
int main() {
    BArbolNodo* raiz = crearNodo(0); // nodo raíz no hoja
    int numRaiz, numHijo;

    printf("=== Construcción del B-árbol manual ===\n");
    printf("Número de claves en el nodo raíz (máx %d): ", 2 * T - 1);
    scanf("%d", &numRaiz);
    raiz->n = numRaiz;

    for (int i = 0; i < raiz->n; i++) {
        printf("Clave %d de la raíz: ", i);
        scanf("%d", &raiz->keys[i]);
    }

    // Crear hijos
    for (int i = 0; i <= raiz->n; i++) {
        raiz->hijos[i] = crearNodo(1); // hijos hoja
        printf("\nNúmero de claves en el hijo %d (máx %d): ", i, 2 * T - 1);
        scanf("%d", &numHijo);
        raiz->hijos[i]->n = numHijo;

        for (int j = 0; j < numHijo; j++) {
            printf("Clave %d del hijo %d: ", j, i);
            scanf("%d", &raiz->hijos[i]->keys[j]);
        }
    }

    printf("\n=== Estructura del B-árbol ===\n");
    printf("Nodo raíz: ");
    for (int j = 0; j < raiz->n; j++) printf("%d ", raiz->keys[j]);
    for (int i = 0; i <= raiz->n; i++) {
        printf("\nHijo %d: ", i);
        for (int j = 0; j < raiz->hijos[i]->n; j++) {
            printf("%d ", raiz->hijos[i]->keys[j]);
        }
    }
    printf("\n");

    int k;
    printf("\nIntroduce la clave a buscar: ");
    scanf("%d", &k);

    ResultadoBusqueda resultado = BArbolNodo_search(raiz, k);
    imprimirResultado(resultado);

    // Liberar memoria
    for (int i = 0; i <= raiz->n; i++) {
        free(raiz->hijos[i]->keys);
        free(raiz->hijos[i]);
    }
    free(raiz->keys);
    free(raiz->hijos);
    free(raiz);

    return 0;
}
