#include <stdio.h>
#include <stdbool.h>

// Definición del tamaño máximo para los conjuntos
#define MAX_SIZE 100
// -----------------------------------------------------------
// PROTOTIPOS DE FUNCIONES
// -----------------------------------------------------------
//Funcion que verifica si un elemento ya existe en un conjunto (o subconjunto).
bool existe_elemento(int conjunto[], int total_elementos, int elemento) {
    for (int i = 0; i < total_elementos; i++) {
        if (conjunto[i] == elemento) {
            return true;
        }
    }
    return false;
}
// --------------------------------------------------
//Funcion que captura los elementos de un conjunto.
void capturar_conjunto(int conjunto[], int total_elementos) {
    printf("Ingrese %d elementos:\n", total_elementos);
    for (int i = 0; i < total_elementos; i++) {
        printf("Elemento %d: ", i + 1);
        if (scanf("%d", &conjunto[i]) != 1) {
            printf("Error en la entrada.\n");
            conjunto[i] = 0;
        }
    }
}
// --------------------------------------------------
//Funcion que elimina los elementos duplicados DENTRO del mismo conjunto.
int eliminar_duplicados(int conjunto[], int *total_elementos) {
    int nuevo_tamano = 0;
    
    // Se recorre el conjunto original (hasta *total_elementos antes de la limpieza)
    for (int i = 0; i < *total_elementos; i++) {
        bool duplicado = false;
        // Buscamos si el elemento ya fue añadido a la parte limpia (conjunto[0] a conjunto[nuevo_tamano-1])
        for (int j = 0; j < nuevo_tamano; j++) {
            if (conjunto[i] == conjunto[j]) {
                duplicado = true;
                break;
            }
        }
        // Si no es un duplicado, se añade a la parte limpia
        if (!duplicado) {
            conjunto[nuevo_tamano++] = conjunto[i];
        }
    }
    *total_elementos = nuevo_tamano;
    return nuevo_tamano;
}
// --------------------------------------------------
//Funcion que alcula la unión de dos conjuntos A y B, asegurando la no-repetición.
int union_conjuntos(int A[], int B[], int total_elementos_A, int total_elementos_B, int union_AB[]) {
    int total_union = 0;

    // 1. Recorrer el Conjunto A
    for (int i = 0; i < total_elementos_A; i++) {
        // En este paso, el elemento A[i] ya es único porque A fue "limpiado" en main().
        union_AB[total_union++] = A[i];
    }

    // 2. Recorrer el Conjunto B y añadir solo si no existe en la UNIÓN (AUB) hasta el momento.
    for (int i = 0; i < total_elementos_B; i++) {
        // La clave de la corrección: verificar contra la parte de la unión que ya se llenó.
        if (!existe_elemento(union_AB, total_union, B[i])) { 
            union_AB[total_union++] = B[i];
        }
    }

    return total_union;
}
// --------------------------------------------------
//Funcion que imprime los elementos de un conjunto.
void imprimir_conjunto(int conjunto[], int total_elementos, const char *nombre) {
    printf("%s={", nombre);
    for (int i = 0; i < total_elementos; i++) {
        printf("%d", conjunto[i]);
        if (i < total_elementos - 1) {
            printf(",");
        }
    }
    printf("}\n");
}
// --------------------------------------------------
//FUNCIÓN PRINCIPAL DEL PROGRAMA
int main() {
    int A[MAX_SIZE];
    int B[MAX_SIZE];
    int union_AB[2 * MAX_SIZE]; 

    // Variables para el tamaño INICIAL ingresado por el usuario
    int total_elementos_A_ingresados; // Antes: total_elementos_A_raw
    int total_elementos_B_ingresados; // Antes: total_elementos_B_raw
    
    // Variables auxiliares que se pasan por referencia a eliminar_duplicados para actualizar su valor
    int total_elementos_A_para_limpiar; 
    int total_elementos_B_para_limpiar;
    
    // Variables para el tamaño FINAL después de la limpieza
    int total_elementos_A_final;
    int total_elementos_B_final;

    printf("--- Calculadora de la Unión de DOS CONJUNTOS (A U B) ---\n\n");

    // Paso 1: Capturar y limpiar el conjunto A
    printf("=> Captura del Conjunto A\n");
    printf("Ingrese el número total de elementos a capturar para A (máx %d elementos): ", MAX_SIZE);
    
    // Lectura del tamaño inicial
    if (scanf("%d", &total_elementos_A_ingresados) != 1 || total_elementos_A_ingresados <= 0 || total_elementos_A_ingresados > MAX_SIZE) {
        printf("Entrada inválida o fuera de rango. Saliendo.\n");
        return 1;
    }
    
    capturar_conjunto(A, total_elementos_A_ingresados);
    
    // Configuramos la variable que se pasará por referencia (total_elementos_A_para_limpiar) 
    // con el tamaño inicial ingresado.
    total_elementos_A_para_limpiar = total_elementos_A_ingresados;
    
    // Limpiar los duplicados del conjunto A. 
    total_elementos_A_final = eliminar_duplicados(A, &total_elementos_A_para_limpiar);
    printf("-> El conjunto 'A' tiene %d elementos.\n", total_elementos_A_final);

    printf("\n");

    // Paso 2: Capturar y limpiar el conjunto B
    printf("=> Captura del Conjunto B\n");
    printf("Ingrese el número total de elementos a capturar para B (máx %d elementos): ", MAX_SIZE);
    
    // Lectura del tamaño inicial
    if (scanf("%d", &total_elementos_B_ingresados) != 1 || total_elementos_B_ingresados <= 0 || total_elementos_B_ingresados > MAX_SIZE) {
        printf("Entrada inválida o fuera de rango. Saliendo.\n");
        return 1;
    }
    
    capturar_conjunto(B, total_elementos_B_ingresados);
    
    // Configuramos la variable que se pasará por referencia
    total_elementos_B_para_limpiar = total_elementos_B_ingresados;
    
    // Limpiar los duplicados del conjunto B
    total_elementos_B_final = eliminar_duplicados(B, &total_elementos_B_para_limpiar);
    printf("-> El conjunto 'B' tiene %d elementos.\n", total_elementos_B_final);

    printf("\n");

    // Paso 3: Calcular la Unión
    int total_union = union_conjuntos(A, B, total_elementos_A_final, total_elementos_B_final, union_AB);

    // Paso 4: Imprimir los resultados
    printf("--- Resultados Finales ---\n");
    imprimir_conjunto(A, total_elementos_A_final, "A");
    imprimir_conjunto(B, total_elementos_B_final, "B");
    printf("\nEl Conjunto Unión es:\n");
    imprimir_conjunto(union_AB, total_union, "AUB");

    return 0;
}
