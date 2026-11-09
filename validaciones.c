#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include "validaciones.h"

#define TAM_LINEA 128

void mostrar_error(const char *mensaje) {
    printf("  [ERROR] %s\n", mensaje);
}

/* Lee una línea completa. 1 = OK, 0 = EOF, -1 = línea demasiado larga */
static int leer_linea(char *buf, size_t n) {
    size_t len;
    if (fgets(buf, (int)n, stdin) == NULL) return 0;
    len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
        return 1;
    }
    {   /* no entró el '\n': descartar el resto de la línea */
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    return -1;
}

int leer_double_rango(const char *mensaje, double min, double max, double *valor) {
    char linea[TAM_LINEA];
    char *fin;
    char *p;
    double v;
    int estado;

    for (;;) {
        printf("%s", mensaje);
        estado = leer_linea(linea, sizeof linea);
        if (estado == 0) return 0;
        if (estado == -1) { mostrar_error("Entrada demasiado larga."); continue; }

        for (p = linea; *p; p++) if (*p == ',') *p = '.';   /* acepta 6,5 */

        errno = 0;
        v = strtod(linea, &fin);
        if (fin == linea) { mostrar_error("Ingresa un numero valido."); continue; }
        while (isspace((unsigned char)*fin)) fin++;
        if (*fin != '\0') { mostrar_error("Hay caracteres no numericos."); continue; }
        if (errno == ERANGE || !isfinite(v)) { mostrar_error("Numero fuera de rango."); continue; }
        if (v < min || v > max) {
            printf("  [ERROR] El valor debe estar entre %g y %g.\n", min, max);
            continue;
        }
        *valor = v;
        return 1;
    }
}

int leer_entero_rango(const char *mensaje, long min, long max, long *valor) {
    char linea[TAM_LINEA];
    char *fin;
    long v;
    int estado;

    for (;;) {
        printf("%s", mensaje);
        estado = leer_linea(linea, sizeof linea);
        if (estado == 0) return 0;
        if (estado == -1) { mostrar_error("Entrada demasiado larga."); continue; }

        errno = 0;
        v = strtol(linea, &fin, 10);
        if (fin == linea) { mostrar_error("Ingresa un numero entero."); continue; }
        while (isspace((unsigned char)*fin)) fin++;
        if (*fin != '\0') { mostrar_error("Hay caracteres no numericos."); continue; }
        if (errno == ERANGE) { mostrar_error("Numero fuera de rango."); continue; }
        if (v < min || v > max) {
            printf("  [ERROR] El valor debe estar entre %ld y %ld.\n", min, max);
            continue;
        }
        *valor = v;
        return 1;
    }
}

void pausar(void) {
    printf("\nPresiona ENTER para continuar...");
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
}
