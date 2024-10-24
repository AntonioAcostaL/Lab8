#include <stdlib.h>
#include <stdio.h>

typedef struct _NodoBinario
{
    void *dato;
    struct _NodoBinario *izq;
    struct _NodoBinario *der;
}NodoBinario;

typedef struct _ArbolBinario
{
    NodoBinario *raiz;
    int altura;
    int tam;
}ArbolBinario;

// Inicializar Árbol
void inicializarArbol(ArbolBinario *arbol) {
    arbol->raiz = NULL;
    arbol->altura = 0;
    arbol->tam = 0;
}

// Liberar nodos recursivamente
void liberarNodos(NodoBinario *nodo) {
    if (nodo == NULL) return;
    liberarNodos(nodo->izq);
    liberarNodos(nodo->der);
    free(nodo);
}

// Free (Liberar el árbol)
void liberarArbol(ArbolBinario *arbol) {
    liberarNodos(arbol->raiz);
    arbol->raiz = NULL;
    arbol->tam = 0;
    arbol->altura = 0;
}

// Crear un nuevo nodo
NodoBinario* crearNodo(void *dato) {
    NodoBinario *nuevo = (NodoBinario*)malloc(sizeof(NodoBinario));
    nuevo->dato = dato;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

// Insertar elemento en el abol binario (inserción recursiva)
NodoBinario* insertarRecursivo(NodoBinario *nodo, void *dato, int (*comparar)(void*, void*)) {
    if (nodo == NULL) {
        return crearNodo(dato);
    }
    
    if (comparar(dato, nodo->dato) < 0) {
        nodo->izq = insertarRecursivo(nodo->izq, dato, comparar);
    } else if (comparar(dato, nodo->dato) > 0) {
        nodo->der = insertarRecursivo(nodo->der, dato, comparar);
    }

    return nodo;
}

// Insertar elemento en el árbol
void insertarEnArbol(ArbolBinario *arbol, void *dato, int (*comparar)(void*, void*)) {
    arbol->raiz = insertarRecursivo(arbol->raiz, dato, comparar);
    arbol->tam++;
}

// Buscar elemento en el árbol binario (recursivo)
NodoBinario* buscarRecursivo(NodoBinario *nodo, void *dato, int (*comparar)(void*, void*)) {
    if (nodo == NULL || comparar(dato, nodo->dato) == 0) {
        return nodo;
    }

    if (comparar(dato, nodo->dato) < 0) {
        return buscarRecursivo(nodo->izq, dato, comparar);
    } else {
        return buscarRecursivo(nodo->der, dato, comparar);
    }
}

// Buscar elemento en el árbol
NodoBinario* buscarEnArbol(ArbolBinario *arbol, void *dato, int (*comparar)(void*, void*)) {
    return buscarRecursivo(arbol->raiz, dato, comparar);
}

// Obtener el tamaño del árbol
int obtenerTamano(ArbolBinario *arbol) {
    return arbol->tam;
}

// Obtener la altura de un nodo (recursivo)
int obtenerAlturaNodo(NodoBinario *nodo) {
    if (nodo == NULL) {
        return -1; // La altura de un árbol vacío es -1
    }
    int alturaIzq = obtenerAlturaNodo(nodo->izq);
    int alturaDer = obtenerAlturaNodo(nodo->der);
    return (alturaIzq > alturaDer ? alturaIzq : alturaDer) + 1;
}

// Obtener la altura del árbol
int obtenerAltura(ArbolBinario *arbol) {
    return obtenerAlturaNodo(arbol->raiz);
}

// Eliminar el elemento mínimo de un subárbol
NodoBinario* eliminarMinimo(NodoBinario *nodo) {
    if (nodo->izq == NULL) {
        return nodo->der;
    }
    nodo->izq = eliminarMinimo(nodo->izq);
    return nodo;
}

// Encontrar el nodo con el valor mínimo en un subárbol
NodoBinario* encontrarMinimo(NodoBinario *nodo) {
    if (nodo->izq == NULL) {
        return nodo;
    }
    return encontrarMinimo(nodo->izq);
}

// Eliminar elemento del árbol (recursivo)
NodoBinario* eliminarRecursivo(NodoBinario *nodo, void *dato, int (*comparar)(void*, void*)) {
    if (nodo == NULL) {
        return NULL;
    }

    if (comparar(dato, nodo->dato) < 0) {
        nodo->izq = eliminarRecursivo(nodo->izq, dato, comparar);
    } else if (comparar(dato, nodo->dato) > 0) {
        nodo->der = eliminarRecursivo(nodo->der, dato, comparar);
    } else {
        if (nodo->izq == NULL) {
            NodoBinario *temp = nodo->der;
            free(nodo);
            return temp;
        } else if (nodo->der == NULL) {
            NodoBinario *temp = nodo->izq;
            free(nodo);
            return temp;
        }

        NodoBinario *temp = encontrarMinimo(nodo->der);
        nodo->dato = temp->dato;
        nodo->der = eliminarRecursivo(nodo->der, temp->dato, comparar);
    }

    return nodo;
}

// Eliminar elemento en el árbol
void eliminarEnArbol(ArbolBinario *arbol, void *dato, int (*comparar)(void*, void*)) {
    arbol->raiz = eliminarRecursivo(arbol->raiz, dato, comparar);
    arbol->tam--;
}

#include <stdlib.h>
#include <stdio.h>

// Estructuras y funciones anteriores...

// Función auxiliar para encontrar la suma de cada nivel (BFS)
int max(int a, int b) {
    return (a > b) ? a : b;
}

typedef struct _NodoCola {
    NodoBinario *nodo;
    int nivel;
    struct _NodoCola *siguiente;
} NodoCola;

typedef struct _Cola {
    NodoCola *frente;
    NodoCola *final;
} Cola;

void inicializarCola(Cola *cola) {
    cola->frente = NULL;
    cola->final = NULL;
}

int estaVaciaCola(Cola *cola) {
    return cola->frente == NULL;
}

void encolar(Cola *cola, NodoBinario *nodo, int nivel) {
    NodoCola *nuevo = (NodoCola *)malloc(sizeof(NodoCola));
    nuevo->nodo = nodo;
    nuevo->nivel = nivel;
    nuevo->siguiente = NULL;
    if (estaVaciaCola(cola)) {
        cola->frente = nuevo;
    } else {
        cola->final->siguiente = nuevo;
    }
    cola->final = nuevo;
}

NodoCola *desencolar(Cola *cola) {
    if (estaVaciaCola(cola)) {
        return NULL;
    }
    NodoCola *nodo = cola->frente;
    cola->frente = cola->frente->siguiente;
    if (cola->frente == NULL) {
        cola->final = NULL;
    }
    return nodo;
}

// Obtener el nivel con la máxima suma
int nivelConMaximaSuma(ArbolBinario *arbol, int (*obtenerValor)(void*)) {
    if (arbol->raiz == NULL) return -1;

    Cola cola;
    inicializarCola(&cola);
    encolar(&cola, arbol->raiz, 0);

    int nivelActual = 0, maxSuma = 0, nivelMaxSuma = 0, sumaNivel = 0;
    while (!estaVaciaCola(&cola)) {
        NodoCola *nodoCola = desencolar(&cola);
        NodoBinario *nodo = nodoCola->nodo;
        int nivel = nodoCola->nivel;

        if (nivel > nivelActual) {
            if (sumaNivel > maxSuma) {
                maxSuma = sumaNivel;
                nivelMaxSuma = nivelActual;
            }
            nivelActual = nivel;
            sumaNivel = 0;
        }

        sumaNivel += obtenerValor(nodo->dato);

        if (nodo->izq != NULL) encolar(&cola, nodo->izq, nivel + 1);
        if (nodo->der != NULL) encolar(&cola, nodo->der, nivel + 1);

        free(nodoCola);
    }

    // Verificar la suma del último nivel
    if (sumaNivel > maxSuma) {
        nivelMaxSuma = nivelActual;
    }

    return nivelMaxSuma;
}

// Función recursiva para encontrar el LCA (Mínimo Ancestro Común)
NodoBinario* encontrarLCA(NodoBinario* nodo, void* dato1, void* dato2, int (*comparar)(void*, void*)) {
    if (nodo == NULL) {
        return NULL;
    }

    // Si uno de los datos es igual al nodo actual, entonces este es el LCA
    if (comparar(dato1, nodo->dato) == 0 || comparar(dato2, nodo->dato) == 0) {
        return nodo;
    }

    // Buscar en el subárbol izquierdo y derecho
    NodoBinario* izqLCA = encontrarLCA(nodo->izq, dato1, dato2, comparar);
    NodoBinario* derLCA = encontrarLCA(nodo->der, dato1, dato2, comparar);

    // Si ambos datos están presentes en los subárboles izquierdo y derecho, el nodo actual es el LCA
    if (izqLCA != NULL && derLCA != NULL) {
        return nodo;
    }

    // De lo contrario, devolver el lado no NULL
    return (izqLCA != NULL) ? izqLCA : derLCA;
}

// Función para encontrar el LCA en el árbol binario
NodoBinario* encontrarLCAEnArbol(ArbolBinario *arbol, void* dato1, void* dato2, int (*comparar)(void*, void*)) {
    return encontrarLCA(arbol->raiz, dato1, dato2, comparar);
}

// Función auxiliar para obtener el valor de un nodo (según el tipo de datos del árbol)
int obtenerValorInt(void* dato) {
    return *(int*)dato;
}

