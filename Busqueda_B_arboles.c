#include <stdio.h>
#include <stdlib.h>

#define T 2 // Grado mínimo del B-árbol (cada nodo puede tener T-1 Y 2*T-1 claves)

// Definición de un nodo B-Tree
typedef struct BArbolNodo {
    int *keys;                  // Arreglo de claves en el nodo
    struct BArbolNodo **hijos;  // Arreglo de punteros a hijos
    int n;                      // Número actual de claves
    int hoja;                   // 1 si es hoja, 0 si no
} BArbolNodo;

// Estructura para devolver el resultado de búsqueda
typedef struct {
    BArbolNodo *nodo; //Punteri al nodo que encontro la clave(NULL si no se encontro)
    int index;         // indice dentro del arreglo de claves donde esta la clave
} ResultadoBusqueda;

// Crea un nodo B-Tree vacío
BArbolNodo* crearNodo(int hoja) {
    //Reserva memoria para un nodo
    BArbolNodo* nodo = (BArbolNodo*)malloc(sizeof(BArbolNodo));
    // Se reserva espacio para el maximo numero de claves posibles
    nodo->keys = (int*)malloc(sizeof(int) * (2 * T - 1));
    //Se reserva espacio para lospunteros hijos
    nodo->hijos = (BArbolNodo**)malloc(sizeof(BArbolNodo*) * (2 * T));
    //Inicializamos el numero de claves actuales en 0
    nodo->n = 0;
    // Guardamos si el nodo es hoja (1) o no (0)
    nodo->hoja = hoja;
    //devolvemos el nodo recien creado
    return nodo;
}

// Implementación de la búsqueda en B-Tree
ResultadoBusqueda BArbolNodo_search(BArbolNodo *x, int k) {
    int i = 0;
    // Avanzamos mientras la clave buscada (k) sea mayor que la clave actual del nodo
    while (i < x->n && k > x->keys[i])
        i++;

    if (i < x->n && k == x->keys[i]) { //Encontramos la clave
        ResultadoBusqueda result = {x, i}; // guardamos nodo y posicion 
        return result;
    }

    if (x->hoja) { // Si llegamos a una hoja y no la encontramos, no existe en el arbol
        ResultadoBusqueda resultado = {NULL, -1};//Indocamos que no se encontro
        return resultado;
    }
    //Si no es hoja, continuamos buscando recursivamente 
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
    BArbolNodo* raiz = crearNodo(0); // nodo raíz (se marca como no hoja)
    int numRaiz, numHijo;

    printf("=== Construcción del B-árbol manual ===\n");
    //Pedimos cuantas claves tendra en nodo raiz
    printf("Número de claves en el nodo raíz (máx %d): ", 2 * T - 1);
    scanf("%d", &numRaiz);
    raiz->n = numRaiz;
    //Leemos las claves del nodo raiz
    for (int i = 0; i < raiz->n; i++) {
        printf("Clave %d de la raíz: ", i);
        scanf("%d", &raiz->keys[i]);
    }

    // Crear hijos
    for (int i = 0; i <= raiz->n; i++) {
        raiz->hijos[i] = crearNodo(1); // hijos hoja
        //Pedimos cuantas claves tendra
        printf("\nNúmero de claves en el hijo %d (máx %d): ", i, 2 * T - 1);
        scanf("%d", &numHijo);
        raiz->hijos[i]->n = numHijo;
        //Leemos las claves
        for (int j = 0; j < numHijo; j++) {
            printf("Clave %d del hijo %d: ", j, i);
            scanf("%d", &raiz->hijos[i]->keys[j]);
        }
    }
    //Mostramos la estructura del arbol completa
    printf("\n=== Estructura del B-árbol ===\n");
    printf("Nodo raíz: ");
    for (int j = 0; j < raiz->n; j++) printf("%d ", raiz->keys[j]);
    //Imprimimos las claves
    for (int i = 0; i <= raiz->n; i++) {
        printf("\nHijo %d: ", i);
        for (int j = 0; j < raiz->hijos[i]->n; j++) {
            printf("%d ", raiz->hijos[i]->keys[j]);
        }
    }
    printf("\n");
    //Busqueda del B-Tree
    int k;
    printf("\nIntroduce la clave a buscar: ");
    scanf("%d", &k);

    //Llamamos a la funcion de busqueda
    ResultadoBusqueda resultado = BArbolNodo_search(raiz, k);
    //Mostramos el resultado
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
