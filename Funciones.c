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
};

//Inicializar Arbol

//Free

//Ingresar elemento en  ́arbol.


//Eliminar elemento en  ́arbol.
//Buscar elemento en  ́arbol.
//Obtener tama ̃no del  ́arbol.
//Obtener altura del  ́arbol.
//El nivel que tiene la m ́axima suma.
//Encontrar el LCA el m ́ınimo comun ancestro.  ́
