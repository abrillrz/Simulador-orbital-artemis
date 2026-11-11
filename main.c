/* ============================================================
   Simulador de Misiones Artemis - Escenario 2 (Orbita LEO)
   main.c : menu principal y flujo general del programa.

   Conecta los modulos:
     - simulador.c : motor fisico (orbita, pulso, historial, reporte)
     - validaciones.c : ingreso seguro de datos del usuario
   ============================================================ */
#include <stdio.h>
#include "simulador.h"
#include "validaciones.h"

/* Rangos validos para el ingreso de datos (orbita LEO) */
#define H_MIN_KM   160.0     /* por debajo la orbita no es estable (arrastre) */
#define H_MAX_KM  2000.0     /* limite superior de LEO */
#define M_MIN_KG     1.0
#define M_MAX_KG     1.0e6

/* Rangos para el pulso del propulsor lateral */
#define A_MIN  0.0
#define A_MAX  100.0
#define T_MIN  0.0
#define T_MAX  600.0

/* Verifica que la mision este iniciada antes de operar sobre ella. */
static int exige_mision(const Mision *m) {
    if (m->orion.radio <= 0.0) {
        mostrar_advertencia("Primero debe iniciar una mision (opcion 1).");
        return 0;
    }
    return 1;
}

/* Opcion 1: iniciar una nueva mision. */
static void opcion_iniciar_mision(Mision *m) {
    int modo;
    double altitud, masa, h_km;

    printf("\n--- NUEVA MISION ---\n");
    printf(" 1) Usar valores de la consigna (192 km, 33000 kg)\n");
    printf(" 2) Ingresar altitud y masa\n");
    modo = leer_entero("Opcion: ", 1, 2);

    if (modo == 1) {
        altitud = ALTITUD_LEO;
        masa    = MASA_ORION;
    } else {
        h_km = leer_decimal("Altitud h [km] (160 a 2000): ", H_MIN_KM, H_MAX_KM);
        masa = leer_decimal("Masa de la nave [kg] (1 a 1000000): ", M_MIN_KG, M_MAX_KG);
        altitud = h_km * 1000.0;
    }

    if (inicializar_mision(m, altitud, masa)) {
        printf("\nMision iniciada correctamente.\n");
        printf(" Velocidad orbital: %.2f m/s\n", m->orion.velocidad_orbital);
    } else {
        mostrar_advertencia("No se pudo iniciar la mision (datos invalidos).");
    }
}

/* Opcion 2: velocidad orbital (Problema A). */
static void opcion_velocidad(const Mision *m) {
    if (!exige_mision(m)) return;
    printf("\n--- VELOCIDAD ORBITAL (Problema A) ---\n");
    printf(" Radio orbital r   : %.1f m\n", m->orion.radio);
    printf(" Velocidad orbital : %.2f m/s (%.2f km/s)\n",
           m->orion.velocidad_orbital, m->orion.velocidad_orbital / 1000.0);
    printf(" Fuerza gravitatoria: %.2f N\n", m->f_gravitatoria);
    printf(" Fuerza centripeta  : %.2f N\n", m->f_centripeta);
    printf(" (la gravedad actua como fuerza centripeta del sistema)\n");
}

/* Opcion 3: periodo orbital (Problema B). */
static void opcion_periodo(const Mision *m) {
    if (!exige_mision(m)) return;
    printf("\n--- PERIODO ORBITAL (Problema B) ---\n");
    printf(" Periodo T : %.2f s (%.2f min)\n", m->periodo, m->periodo / 60.0);
}

/* Opcion 4: aceleracion centripeta (Problema C). */
static void opcion_acel_centripeta(const Mision *m) {
    if (!exige_mision(m)) return;
    printf("\n--- ACELERACION CENTRIPETA (Problema C) ---\n");
    printf(" a = v^2 / r = %.4f m/s^2\n", m->ac_centripeta);
    printf(" (equivale a %.2f veces la gravedad en superficie)\n", m->ac_centripeta / 9.8);
}

/* Opcion 5: simular el propulsor lateral (Problema D). */
static void opcion_propulsor(Mision *m) {
    int modo;
    double acel, dt;

    if (!exige_mision(m)) return;

    printf("\n--- PROPULSOR LATERAL (Problema D) ---\n");
    printf(" 1) Usar valores de la consigna (0.50 m/s^2 durante 10 s)\n");
    printf(" 2) Ingresar aceleracion y duracion\n");
    modo = leer_entero("Opcion: ", 1, 2);

    if (modo == 1) {
        acel = 0.50;
        dt   = 10.0;
    } else {
        acel = leer_decimal("Aceleracion del pulso [m/s^2] (0 a 100): ", A_MIN, A_MAX);
        dt   = leer_decimal("Duracion del pulso [s] (0 a 600): ", T_MIN, T_MAX);
    }

    if (aplicar_pulso(m, acel, dt)) {
        printf("\n Pulso: %.2f m/s^2 durante %.2f s\n", acel, dt);
        printf(" Desviacion lateral: %.2f m\n", m->pulso.desviacion);
        printf(" Giro del vector velocidad: %.4f grados\n", m->pulso.angulo_desvio);
        printf(" La orbita pasa de circular a eliptica.\n");
    } else {
        mostrar_advertencia("No se pudo aplicar el pulso (datos invalidos o ya no es circular).");
    }
}

/* Opcion 6: consultar estado e historial. */
static void opcion_estado(const Mision *m) {
    if (!exige_mision(m)) return;
    printf("\n--- ESTADO ACTUAL ---\n");
    printf(" Mision   : %s\n", m->nombre_mision);
    printf(" Altitud  : %.1f km\n", m->orion.altitud / 1000.0);
    printf(" Rapidez  : %.2f m/s\n", m->orion.velocidad_orbital);
    printf(" Orbita   : %s\n", m->orion.orbita_circular ? "circular (MCU)" : "eliptica (tras pulso)");
    printf(" Eventos registrados: %d\n", m->cantidad_eventos);
}

int main(void) {
    Mision mision;
    int opcion;

    /* Marca de "mision no iniciada": radio en 0 hasta que se inicialice */
    mision.orion.radio = 0.0;
    mision.cantidad_eventos = 0;

    do {
        printf("\n========================================\n");
        printf("        CONTROL DE MISION ARTEMIS\n");
        printf("========================================\n");
        printf("\n1. Iniciar nueva mision\n");
        printf("\n--- CALCULOS ORBITALES ---\n");
        printf("2. Calcular velocidad orbital\n");
        printf("3. Calcular periodo orbital\n");
        printf("\n--- DINAMICA Y PROPULSION ---\n");
        printf("4. Calcular aceleracion centripeta\n");
        printf("5. Simular propulsor lateral\n");
        printf("\n--- CONTROL Y RESULTADOS ---\n");
        printf("6. Consultar estado e historial\n");
        printf("7. Generar reporte final\n");
        printf("\n0. Salir\n");

        opcion = leer_entero("\nSeleccione una opcion: ", 0, 7);

        switch (opcion) {
            case 1: opcion_iniciar_mision(&mision);   break;
            case 2: opcion_velocidad(&mision);        break;
            case 3: opcion_periodo(&mision);          break;
            case 4: opcion_acel_centripeta(&mision);  break;
            case 5: opcion_propulsor(&mision);        break;
            case 6: opcion_estado(&mision);           break;
            case 7:
                if (exige_mision(&mision)) generar_reporte_final(&mision);
                break;
            case 0:
                printf("\nFinalizando simulador Artemis...\n");
                break;
            default:
                mostrar_advertencia("Opcion fuera de rango.");
                break;
        }
    } while (opcion != 0);

    return 0;
}