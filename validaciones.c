#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "validaciones.h"

#define TAM_BUFFER 64

/* Lee una linea. Devuelve 1 si ok, 0 si fin de entrada, -1 si fue demasiado larga. */
static int leer_linea(char *buf, size_t tam)
{
    if (fgets(buf, tam, stdin) == NULL) {
        return 0;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
        return 1;
    }
    /* No habia salto de linea: la linea no entro en el buffer. Limpiamos el resto. */
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    return -1;
}

void mostrar_advertencia(const char *texto)
{
    printf("  [!] %s\n", texto);
}

int leer_entero(const char *mensaje, int min, int max)
{
    char buf[TAM_BUFFER];
    char *fin;
    long valor;

    while (1) {
        printf("%s", mensaje);
        int estado = leer_linea(buf, sizeof(buf));

        if (estado == 0) {
            printf("\nEntrada finalizada. Cerrando el programa.\n");
            exit(EXIT_FAILURE);
        }
        if (estado == -1) {
            mostrar_advertencia("Entrada demasiado larga.");
            continue;
        }

        errno = 0;
        valor = strtol(buf, &fin, 10);

        if (fin == buf) {                       /* no leyo ningun digito */
            mostrar_advertencia("Debe ingresar un numero entero (no letras).");
        } else if (*fin != '\0') {              /* sobraron caracteres: "12abc" */
            mostrar_advertencia("Entrada invalida: hay caracteres que no son digitos.");
        } else if (errno == ERANGE || valor < min || valor > max) {
            printf("  [!] El valor debe estar entre %d y %d.\n", min, max);
        } else {
            return (int)valor;
        }
    }
}

double leer_decimal(const char *mensaje, double min, double max)
{
    char buf[TAM_BUFFER];
    char *fin;
    double valor;

    while (1) {
        printf("%s", mensaje);
        int estado = leer_linea(buf, sizeof(buf));

        if (estado == 0) {
            printf("\nEntrada finalizada. Cerrando el programa.\n");
            exit(EXIT_FAILURE);
        }
        if (estado == -1) {
            mostrar_advertencia("Entrada demasiado larga.");
            continue;
        }

        errno = 0;
        valor = strtod(buf, &fin);

        if (fin == buf) {
            mostrar_advertencia("Debe ingresar un numero (use punto decimal, ej: 192.5).");
        } else if (*fin != '\0') {
            mostrar_advertencia("Entrada invalida: hay caracteres que no son parte del numero.");
        } else if (errno == ERANGE || !isfinite(valor)) {
            mostrar_advertencia("Numero fuera de rango o no valido.");
        } else if (valor < min || valor > max) {
            printf("  [!] El valor debe estar entre %.2f y %.2f.\n", min, max);
        } else {
            return valor;
        }
    }
}

int leer_opcion_menu(int min, int max)
{
    return leer_entero("Ingrese una opcion: ", min, max);
}
