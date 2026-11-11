#include <stdio.h>
#include "propulsion.h"

/* Programa de prueba del modulo de propulsion.
   Verifica los calculos con los valores de la consigna.
*/
int main(void)
{
    double desviacion;
    EstadoOrbita estado;

    printf("===== PRUEBA DEL MODULO DE PROPULSION =====\n\n");

    /* Caso de la consigna: a = 0.50 m/s^2 durante dt = 10 s */
    desviacion = calcular_desviacion_lateral(PULSO_ACELERACION, PULSO_DURACION);

    printf("Aceleracion del pulso: %.2f m/s^2\n", PULSO_ACELERACION);
    printf("Duracion del pulso:    %.2f s\n", PULSO_DURACION);
    printf("Desviacion lateral:    %.2f m\n", desviacion);
    printf("(Valor esperado por calculo manual: 25.00 m)\n\n");

    /* Evaluamos en que estado queda la mision */
    estado = evaluar_estado_mision(desviacion);

    printf("Estado de la mision: ");
    if (estado == ORBITA_ESTABLE) {
        printf("ORBITA ESTABLE\n");
    } else if (estado == ORBITA_DESVIADA) {
        printf("ORBITA DESVIADA\n");
    } else {
        printf("ORBITA CRITICA\n");
    }

    return 0;
}