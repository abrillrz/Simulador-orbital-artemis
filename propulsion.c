#include <math.h>        
#include "propulsion.h"  /* Nuestras constantes, el enum y los prototipos */

/* ===== Problema D: desviacion lateral =====
   Cuando el propulsor empuja de costado con una aceleracion constante
   durante un tiempo dt, la nave se corre lateralmente.
   Como parte del reposo lateral (v0 = 0) y acelera constante, es un MRUV:
       d = 0.5 * a * dt^2
*/
double calcular_desviacion_lateral(double aceleracion, double dt)
{
    double desviacion;
    desviacion = 0.5 * aceleracion * pow(dt, 2);
    return desviacion;
}

/* ===== Evaluacion del estado de la mision =====
   Clasifica la desviacion en tres niveles usando los umbrales del .h.
   Devuelve uno de los valores del enum EstadoOrbita.
*/
EstadoOrbita evaluar_estado_mision(double desviacion)
{
    if (desviacion <= UMBRAL_ESTABLE) {
        return ORBITA_ESTABLE;
    } else if (desviacion <= UMBRAL_CRITICO) {
        return ORBITA_DESVIADA;
    } else {
        return ORBITA_CRITICA;
    }
}