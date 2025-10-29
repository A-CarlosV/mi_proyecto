#include <stdio.h>
#include <string.h>

#define MAX_LEN 100
// -----------------------------------------------------------
// PROTOTIPOS DE FUNCIONES
// -----------------------------------------------------------
void capturar_cadena(char str[], int max_len)
{
    printf("Ingrese una cadena de caracteres: \n");
    if (fgets(str, max_len, stdin) != NULL)
	{
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
		{
    	str[len - 1] = '\0';
	    }
    }
}

// ----------------------------------------------------
// Función para invertir una cadena de caracteres usando 'for'
// ----------------------------------------------------
void invertir_cadena(char str[]) {
    int len = strlen(str);
    char temp;

    for (int i = 0, j = len - 1; i < j; i++, j--) {
        // Intercambio de caracteres
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void imprimir_cadenas(const char original[], const char invertida[]) {
    printf("\n*** RESULTADOS ***\n");
    printf("Cadena Original:   %s\n", original);
    printf("Cadena Invertida:  %s\n", invertida);
    printf("******************\n");
}

int main() {
    char cadena_original[MAX_LEN];
    char cadena_invertida[MAX_LEN];

    capturar_cadena(cadena_original, MAX_LEN);

    // Copia para preservar la original
    strcpy(cadena_invertida, cadena_original);

    invertir_cadena(cadena_invertida);

    imprimir_cadenas(cadena_original, cadena_invertida);

    return 0;
}
