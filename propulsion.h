#ifndef PROPULSION_H
#define PROPULSION_H

/* #include "orbita.h"   // TODO: activar al integrar (lo usara la aceleracion centripeta) */

/* ===== Valores del evento de propulsor lateral (consigna, Problema D) ===== */
#define PULSO_ACELERACION   0.50   /* a lateral [m/s^2] */
#define PULSO_DURACION      10.0   /* delta t [s]       */

/* ===== Umbrales de estado de la mision (decision de diseno del grupo) ===== */
#define UMBRAL_ESTABLE      25.0   /* hasta aca: orbita estable [m]  */
#define UMBRAL_CRITICO     100.0   /* mas de aca: estado critico [m] */

/* Estado de la orbita tras el pulso del propulsor lateral */
typedef enum {
    ORBITA_ESTABLE,
    ORBITA_DESVIADA,
    ORBITA_CRITICA
} EstadoOrbita;

/* ===== Funciones del modulo de propulsion ===== */

/* Problema D: desviacion lateral d = 0.5 * a * (dt)^2 */
double calcular_desviacion_lateral(double aceleracion, double dt);

/* Clasifica el estado de la mision segun la desviacion lateral */
EstadoOrbita evaluar_estado_mision(double desviacion);

#endif