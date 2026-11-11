#include <stdio.h>
#include "simulador.h"
#include "validaciones.h"

int main(void)
{
    Mision mision_leo;
    int opcion;
    int meta;
    double altitud_km, masa, a, dt;

    /* Datos de la mision ingresados (y validados) por el usuario */
    printf("=== CONFIGURACION DE LA MISION ===\n");
    altitud_km = leer_decimal("Altitud orbital [km] (160 a 2000): ", 160.0, 2000.0);
    masa       = leer_decimal("Masa de la nave [kg] (1000 a 1000000): ", 1000.0, 1000000.0);

    if (!inicializar_mision(&mision_leo, altitud_km * 1000.0, masa)) {
        printf("Error: datos de mision invalidos.\n");
        return 1;
    }
    registrar_evento(&mision_leo, "Insercion exitosa en orbita LEO");

    do {
        printf("\n=========================================\n");
        printf("   SIMULADOR ARTEMIS II - ORBITA LEO\n");
        printf("=========================================\n");
        printf("1. Avanzar simulacion (1 vuelta completa)\n");
        printf("2. Encender propulsor lateral (Pulso)\n");
        printf("3. Ver estado actual de la nave\n");
        printf("4. Ver reporte final\n");
        printf("5. Salir\n");

        opcion = leer_opcion_menu(1, 5);

        switch (opcion) {
            case 1:
                if (!mision_leo.orion.orbita_circular) {
                    printf("\nTras el pulso la orbita ya no es circular: no se puede avanzar en MCU.\n");
                    break;
                }
                printf("\nSimulando paso del tiempo...\n");
                meta = mision_leo.orion.vueltas_completas + 1;
                while (mision_leo.orion.vueltas_completas < meta)
                    actualizar_estado_orbital(&mision_leo, 1.0);   /* registra la vuelta solo */
                printf("Se ha completado una vuelta orbital (T = %.2f s).\n", mision_leo.periodo);
                break;

            case 2:
                if (mision_leo.pulso.aplicado) {
                    printf("\nEl pulso ya fue aplicado en esta mision.\n");
                    break;
                }
                a  = leer_decimal("Aceleracion del propulsor [m/s2] (0.01 a 5): ", 0.01, 5.0);
                dt = leer_decimal("Duracion del pulso [s] (1 a 60): ", 1.0, 60.0);
                if (aplicar_pulso(&mision_leo, a, dt)) {
                    printf("\nPropulsor lateral encendido.\n");
                    printf("Delta v perpendicular: %.2f m/s\n", mision_leo.pulso.delta_v);
                    printf("Desviacion lateral:    %.2f m\n",   mision_leo.pulso.desviacion);
                    printf("Nueva rapidez:         %.4f m/s\n", mision_leo.pulso.rapidez_nueva);
                } else {
                    printf("\nNo se pudo aplicar el pulso.\n");
                }
                break;

            case 3:
                printf("\n--- Estado Actual ---\n");
                printf("Altitud:  %.1f km\n", mision_leo.orion.altitud / 1000.0);
                printf("Rapidez:  %.2f m/s\n", mision_leo.orion.velocidad_orbital);
                printf("Angulo:   %.2f grados\n", mision_leo.orion.angulo_orbital * 180.0 / PI);
                printf("Vueltas:  %d\n", mision_leo.orion.vueltas_completas);
                printf("Tiempo:   %.2f segundos\n", mision_leo.orion.tiempo_transcurrido);
                break;

            case 4:
                generar_reporte_final(&mision_leo);
                break;

            case 5:
                printf("Saliendo del simulador...\n");
                break;
        }
    } while (opcion != 5);

    return 0;
}
