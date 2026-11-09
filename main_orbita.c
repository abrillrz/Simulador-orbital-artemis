/* Demo del módulo de órbita (Escenario 2, problemas A y B).
   En el proyecto final, el main.c del grupo llama a estas mismas funciones. */
#include <stdio.h>
#include "orbita.h"
#include "validaciones.h"

#define H_MIN_KM  160.0      /* por debajo la órbita no es estable (arrastre) */
#define H_MAX_KM  2000.0     /* límite superior de LEO */
#define M_MIN_KG  1.0
#define M_MAX_KG  1.0e6

static void simular_consigna(void) {
    DatosOrbita o;
    o.altitud = H_CONSIGNA;
    o.masa    = M_CONSIGNA;
    if (calcular_orbita(&o)) mostrar_resultados_orbita(&o);
}

static void simular_personalizado(void) {
    DatosOrbita o;
    double h_km;

    if (!leer_double_rango("Altitud h [km] (160 a 2000): ", H_MIN_KM, H_MAX_KM, &h_km)) return;
    if (!leer_double_rango("Masa de la nave [kg] (1 a 1e6): ", M_MIN_KG, M_MAX_KG, &o.masa)) return;
    o.altitud = h_km * 1000.0;

    if (calcular_orbita(&o)) mostrar_resultados_orbita(&o);
    else mostrar_error("Datos de entrada invalidos.");
}

int main(void) {
    long opcion;

    do {
        printf("\n===== SIMULADOR ARTEMIS - ORBITA LEO =====\n");
        printf(" 1) Usar valores de la consigna (192 km, 33000 kg)\n");
        printf(" 2) Ingresar altitud y masa\n");
        printf(" 0) Salir\n");
        if (!leer_entero_rango("Opcion: ", 0, 2, &opcion)) break;

        switch (opcion) {
            case 1: simular_consigna();      break;
            case 2: simular_personalizado(); break;
            default: break;
        }
    } while (opcion != 0);

    printf("Fin del programa.\n");
    return 0;
}
