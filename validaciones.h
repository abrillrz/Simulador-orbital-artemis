#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/* Solicita un entero dentro del rango [min, max].
   Vuelve a preguntar hasta que el valor ingresado sea válido. */
int leer_entero(const char *mensaje, int min, int max);

/* Pide al usuario un real entre min y max (inclusive).
   Insiste mientras la entrada no sea correcta. */
double leer_decimal(const char *mensaje, double min, double max);

/* Pide una opcion de menu entre min y max. */
int leer_opcion_menu(int min, int max);

/* Muestra un mensaje de advertencia uniforme. */
void mostrar_advertencia(const char *texto);

#endif
