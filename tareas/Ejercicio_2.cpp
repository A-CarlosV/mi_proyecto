#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h> 

// Constante para el tamaño máximo de los conjuntos A y B.
#define MAX_ELEMENTOS 10

// -----------------------------------------------------------
// PROTOTIPOS DE FUNCIONES
// -----------------------------------------------------------
void capturarConjunto(int conjunto[], int *totalElementos, char nombreConjunto);
void imprimirConjunto(const int conjunto[], int totalElementos, const char *nombre);
bool existeElemento(const int conjunto[], int totalElementos, int elemento);
int eliminarDuplicados(int conjunto[], int *totalElementos);
void ordenarConjunto(int conjunto[], int totalElementos); 
void calcularInterseccion(const int conjuntoA[], const int conjuntoB[], int totalA, int totalB);

// -----------------------------------------------------------

void ordenarConjunto(int conjunto[], int totalElementos) {
    int i, j, temp; 
    // Compara pares adyacentes y los intercambia hasta que el arreglo esté ordenado.
    for (i = 0; i < totalElementos - 1; i++) for (j = 0; j < totalElementos - i - 1; j++) 
        if (conjunto[j] > conjunto[j + 1]) { // Si el elemento actual es mayor que el siguiente...
            temp = conjunto[j]; // Realiza el intercambio de valores
            conjunto[j] = conjunto[j + 1]; 
            conjunto[j + 1] = temp; 
        }
}


// Verifica si un elemento dado ya existe en un subconjunto (o arreglo).
bool existeElemento(const int conjunto[], int totalElementos, int elemento) {
    for (int i = 0; i < totalElementos; i++) if (conjunto[i] == elemento) return true;
    return false;
}


 // Elimina los elementos duplicados DENTRO del mismo conjunto.
 int eliminarDuplicados(int conjunto[], int *totalElementos) {
    int nuevoTotal = 0;
    int totalOriginal = *totalElementos;
    
    for (int i = 0; i < totalOriginal; i++) {
        bool esDuplicado = false;
        // Compara el elemento actual (conjunto[i]) con los elementos ya considerados únicos (hasta nuevoTotal-1).
        for (int j = 0; j < nuevoTotal; j++) if (conjunto[i] == conjunto[j]) { esDuplicado = true; break; }
        
        // Si no es duplicado, lo añade a la parte limpia del arreglo.
        if (!esDuplicado) conjunto[nuevoTotal++] = conjunto[i]; 
    }
    *totalElementos = nuevoTotal; 
    return nuevoTotal;
}

//Captura los elementos de un conjunto desde la entrada del usuario.
 
void capturarConjunto(int conjunto[], int *totalElementos, char nombreConjunto) {
    int i;
    printf("¿Cuántos elementos tendrá el conjunto %c (máximo %d)? ", nombreConjunto, MAX_ELEMENTOS);
    
    // Validar el número de elementos.
    if (scanf("%d", totalElementos) != 1 || *totalElementos < 0 || *totalElementos > MAX_ELEMENTOS) {
        printf("Error: Número de elementos inválido o fuera de rango. Saliendo.\n");
        while (getchar() != '\n'); exit(1); 
    }
    
    // Capturar cada elemento.
    for (i = 0; i < *totalElementos; i++) {
        printf("Ingrese el elemento %d del conjunto %c: ", i + 1, nombreConjunto);
        if (scanf("%d", &conjunto[i]) != 1) {
            printf("Error: Entrada no válida para el elemento. Saliendo.\n");
            while (getchar() != '\n'); exit(1);
        }
    }
    printf("Conjunto %c capturado: ", nombreConjunto); imprimirConjunto(conjunto, *totalElementos, "");
}

 //Imprime los elementos de un conjunto con formato matemático {a, b, c}.
void imprimirConjunto(const int conjunto[], int totalElementos, const char *nombre) {
    printf("%s{", nombre);
    for (int i = 0; i < totalElementos; i++) {
        printf("%d", conjunto[i]);
        // Imprime la coma, excepto después del último elemento.
        if (i < totalElementos - 1) printf(", ");
    }
    printf("}\n");
}


//Calcula la intersección (A n B) de dos conjuntos depurados y la imprime ordenada.
void calcularInterseccion(const int conjuntoA[], const int conjuntoB[], int totalA, int totalB) {
    // Arreglo para almacenar la intersección y contador para su tamaño.
    int interseccionAB[MAX_ELEMENTOS], totalInterseccion = 0; 
    
    // 1. Calcular la intersección sin duplicados.
    for (int i = 0; i < totalA; i++) {
        for (int j = 0; j < totalB; j++) {
            // Si hay coincidencia.
            if (conjuntoA[i] == conjuntoB[j]) {
                // Verificar que el elemento no se haya incluido ya en la intersección (robusto contra fallos de depuración).
                if (!existeElemento(interseccionAB, totalInterseccion, conjuntoA[i])) interseccionAB[totalInterseccion++] = conjuntoA[i];
                break; // El elemento conjuntoA[i] ya se encontró en B, pasar al siguiente elemento de A.
            }
        }
    }
    
    // 2. Ordenar e imprimir el resultado.
    ordenarConjunto(interseccionAB, totalInterseccion); 
    imprimirConjunto(interseccionAB, totalInterseccion, "A \u2229 B = ");
}

// -----------------------------------------------------------

//Función principal que coordina la captura, depuración, ordenación e intersección.
int main() {
    int conjuntoA[MAX_ELEMENTOS], conjuntoB[MAX_ELEMENTOS];
    int totalA = 0, totalB = 0;
    int totalAFinal, totalBFinal; // Variables para almacenar el tamaño final después de la depuración.

    // 1. Captura, depuración y ordenación del Conjunto A.
    printf("--- Captura del Conjunto A ---\n");
    capturarConjunto(conjuntoA, &totalA, 'A');
    totalAFinal = eliminarDuplicados(conjuntoA, &totalA); // Elimina duplicados y actualiza totalA.
    ordenarConjunto(conjuntoA, totalAFinal); // Ordena los elementos restantes.

    // 2. Captura, depuración y ordenación del Conjunto B.
    printf("\n--- Captura del Conjunto B ---\n");
    capturarConjunto(conjuntoB, &totalB, 'B');
    totalBFinal = eliminarDuplicados(conjuntoB, &totalB); // Elimina duplicados y actualiza totalB.
    ordenarConjunto(conjuntoB, totalBFinal); // Ordena los elementos restantes.

    // 3. Impresión de Resultados Finales Ordenados.
    printf("\n--- Resultados Finales ---\n");
    
    printf("Conjunto A (sin duplicados y ordenado):\n");
    imprimirConjunto(conjuntoA, totalAFinal, "A = ");
    
    printf("\nConjunto B (sin duplicados y ordenado):\n");
    imprimirConjunto(conjuntoB, totalBFinal, "B = ");

    printf("\nIntersección (ordenada):\n");
    // Llama a la función de intersección con los conjuntos ordenados.
    calcularInterseccion(conjuntoA, conjuntoB, totalAFinal, totalBFinal);

    return 0;
}
