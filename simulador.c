#include <stdio.h>
#include <string.h>
#include <math.h>
#include "simulador.h"

// Inicializa la nave en la órbita LEO con valores por defecto.
void inicializar_mision(Mision *m) {
    strcpy(m->nombre_mision, "Artemis II - Orbita LEO");
    m->orion.altitud = ALTITUD_LEO;
    
    // Cálculo de la velocidad orbital: v = sqrt(G * M / r)
    float radio_orbital = RADIO_TIERRA + m->orion.altitud;
    m->orion.velocidad_orbital = sqrt((G * MASA_TIERRA) / radio_orbital);
    
    // Estado inicial
    m->orion.angulo_orbital = 0.0;
    m->orion.vueltas_completas = 0;
    m->orion.tiempo_transcurrido = 0.0;
    m->cantidad_eventos = 0;
}

// Agrega un evento al arreglo de historial usando el contador.
void registrar_evento(Mision *m, int tiempo, const char *desc) {
    if (m->cantidad_eventos < MAX_EVENTOS) {
        int idx = m->cantidad_eventos;
        m->historial[idx].tiempo = tiempo;
        strcpy(m->historial[idx].descripcion, desc);
        m->historial[idx].angulo_registrado = m->orion.angulo_orbital;
        m->historial[idx].vueltas_registradas = m->orion.vueltas_completas;
        m->cantidad_eventos++;
    } else {
        printf("Advertencia: Historial lleno.\n");
    }
}

// Actualiza el movimiento circular uniforme (ángulo y vueltas).
void actualizar_estado_orbital(Nave *n, float delta_tiempo, float velocidad) {
    // Velocidad angular w = v / r
    float radio_orbital = RADIO_TIERRA + n->altitud;
    float w = velocidad / radio_orbital; // radianes por segundo
    
    // Actualizamos el tiempo total
    n->tiempo_transcurrido += delta_tiempo;
    
    // Calculamos el desplazamiento angular (en radianes y pasamos a grados)
    float delta_angulo = (w * delta_tiempo) * (180.0 / M_PI);
    
    // Actualizamos el ángulo
    n->angulo_orbital += delta_angulo;
    
    // Si supera los 360 grados, sumamos una vuelta y ajustamos el ángulo
    if (n->angulo_orbital >= 360.0) {
        int vueltas_nuevas = (int)(n->angulo_orbital / 360.0);
        n->vueltas_completas += vueltas_nuevas;
        n->angulo_orbital = n->angulo_orbital - (vueltas_nuevas * 360.0);
    }
}

// Genera el reporte final de desempeño con formato de tabla.
void generar_reporte_final(Mision *m) {
    printf("\n==================================================\n");
    printf("       REPORTE DE DESEMPENO - %s\n", m->nombre_mision);
    printf("==================================================\n");
    printf("Estado Final de la Nave en Orbita:\n");
    printf(" - Velocidad Orbital: %.2f m/s (aprox %.2f km/s)\n", m->orion.velocidad_orbital, m->orion.velocidad_orbital / 1000.0);
    printf(" - Altitud:           %.2f km\n", m->orion.altitud / 1000.0);
    printf(" - Vueltas completas: %d\n", m->orion.vueltas_completas);
    printf(" - Angulo actual:     %.2f grados\n", m->orion.angulo_orbital);
    printf(" - Tiempo simulado:   %.2f segundos\n", m->orion.tiempo_transcurrido);
    
    printf("\nHistorial de Eventos Registrados (%d):\n", m->cantidad_eventos);
    printf("--------------------------------------------------------------------------------\n");
    printf("%-8s | %-30s | %-12s | %-10s\n", "Tiempo", "Evento", "Angulo", "Vueltas");
    printf("--------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < m->cantidad_eventos; i++) {
        printf("%-8d | %-30s | %-12.2f | %-10d\n", 
               m->historial[i].tiempo, 
               m->historial[i].descripcion,
               m->historial[i].angulo_registrado,
               m->historial[i].vueltas_registradas);
    }
    printf("================================================================================\n");
}
