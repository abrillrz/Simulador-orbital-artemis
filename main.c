#include <stdio.h>
#include "simulador.h"

int main() {
    Mision mision_leo;
    int opcion;
    
    // 1. Inicializamos la nave en órbita
    inicializar_mision(&mision_leo);
    registrar_evento(&mision_leo, 0, "Insercion exitosa en LEO");
    
    // Aquí iría tu menú principal y las validaciones...
    
    // 2. Simulamos el paso del tiempo (Ejemplo: 1 vuelta completa ~ 90 min = 5400 seg)
    // Puedes hacer un bucle para simular el avance del tiempo
    for(int t = 1; t <= 5400; t++) {
        // Actualizamos el estado en cada segundo
        actualizar_estado_orbital(&mision_leo.orion, 1.0, mision_leo.orion.velocidad_orbital);
    }
    
    // 3. Registramos un evento importante (ej. el pulso del propulsor lateral)
    registrar_evento(&mision_leo, 2700, "Pulso de propulsor lateral (10s)");
    
    // 4. Simulamos otra vuelta más...
    for(int t = 5401; t <= 10800; t++) {
        actualizar_estado_orbital(&mision_leo.orion, 1.0, mision_leo.orion.velocidad_orbital);
    }
    registrar_evento(&mision_leo, 10800, "Fin de la simulacion orbital");
    
    // 5. Mostramos el reporte final de desempeño
    generar_reporte_final(&mision_leo);
    
    return 0;
}
