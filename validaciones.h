#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/* Pide un entero en [min, max]. Repite hasta que sea valido. */
int leer_entero(const char *mensaje, int min, int max);

/* Pide un decimal en [min, max]. Repite hasta que sea valido. */
double leer_decimal(const char *mensaje, double min, double max);

/* Pide una opcion de menu entre min y max. */
int leer_opcion_menu(int min, int max);

/* Muestra un mensaje de advertencia uniforme. */
void mostrar_advertencia(const char *texto);

#endif
