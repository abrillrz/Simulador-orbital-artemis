
#include <stdio.h>

int main(void) {
    int opcion;
    char linea[100];
    char extra;

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
        printf("\nSeleccione una opcion: ");

        // Lectura provisional hasta integrar validaciones.c
        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            break;
        }

        if (sscanf(linea, " %d %c", &opcion, &extra) != 1) {
            printf("\nError: ingrese una opcion valida.\n");
            opcion = -1;
            continue;
        }

        switch (opcion) {
            case 1:
                printf("\nIniciando nueva mision...\n");
                break;

            case 2:
                printf("\nCalculando velocidad orbital...\n");
                break;

            case 3:
                printf("\nCalculando periodo orbital...\n");
                break;

            case 4:
                printf("\nCalculando aceleracion centripeta...\n");
                break;

            case 5:
                printf("\nSimulando propulsor lateral...\n");
                break;

            case 6:
                printf("\nConsultando estado e historial...\n");
                break;

            case 7:
                printf("\nGenerando reporte final...\n");
                break;

            case 0:
                printf("\nFinalizando simulador Artemis...\n");
                break;

            default:
                printf("\nError: opcion fuera de rango.\n");
                break;
        }

    } while (opcion != 0);

    return 0;
}

