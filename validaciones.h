#ifndef VALIDACIONES_H
#define VALIDACIONES_H

/* Todas devuelven 1 si se leyó un valor válido, 0 si se cerró la entrada (EOF).
   Repiten la consulta hasta que el dato sea válido (tipo y rango). */
int  leer_double_rango(const char *mensaje, double min, double max, double *valor);
int  leer_entero_rango(const char *mensaje, long min, long max, long *valor);
void mostrar_error(const char *mensaje);
void pausar(void);

#endif
