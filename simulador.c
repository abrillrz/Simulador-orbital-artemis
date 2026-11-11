#include <stdio.h>
#include <string.h>
#include <math.h>
#include "simulador.h"

/* Inicializa la mision en orbita LEO a partir de la altitud y la masa.
   Devuelve 1 si todo esta bien, 0 si los datos son invalidos. */
int inicializar_mision(Mision *m, double altitud, double masa)
{
    double r;
    if (altitud <= 0.0 || masa <= 0.0)
        return 0;

    strncpy(m->nombre_mision, "Artemis II - Orbita LEO", sizeof(m->nombre_mision) - 1);
    m->nombre_mision[sizeof(m->nombre_mision) - 1] = '\0';

    r = RADIO_TIERRA + altitud;

    m->orion.altitud           = altitud;
    m->orion.radio             = r;
    m->orion.masa              = masa;
    /* v = sqrt(G*M / r)  (la gravedad es la fuerza centripeta) */
    m->orion.velocidad_orbital = sqrt((G_UNIV * MASA_TIERRA) / r);

    m->periodo        = 2.0 * PI * r / m->orion.velocidad_orbital;
    m->ac_centripeta  = m->orion.velocidad_orbital * m->orion.velocidad_orbital / r;
    m->f_gravitatoria = G_UNIV * MASA_TIERRA * masa / (r * r);
    m->f_centripeta   = masa * m->ac_centripeta;

    m->orion.angulo_orbital      = 0.0;
    m->orion.vueltas_completas   = 0;
    m->orion.tiempo_transcurrido = 0.0;
    m->orion.orbita_circular     = 1;

    m->pulso.aplicado = 0;
    m->cantidad_eventos = 0;
    return 1;
}

/* Agrega un evento al historial con el estado ACTUAL de la nave.
   Devuelve 1 si pudo, 0 si el historial esta lleno. */
int registrar_evento(Mision *m, const char *desc)
{
    Evento *e;
    if (m->cantidad_eventos >= MAX_EVENTOS)
        return 0;

    e = &m->historial[m->cantidad_eventos];
    e->tiempo = m->orion.tiempo_transcurrido;
    strncpy(e->descripcion, desc, MAX_TEXTO - 1);
    e->descripcion[MAX_TEXTO - 1] = '\0';
    e->angulo_registrado  = m->orion.angulo_orbital;
    e->vueltas_registradas = m->orion.vueltas_completas;
    m->cantidad_eventos++;
    return 1;
}

/* Avanza delta_tiempo segundos en MCU (omega = v / r).
   Cierra cada vuelta en el instante exacto y la registra como evento. */
void actualizar_estado_orbital(Mision *m, double delta_tiempo)
{
    Nave *n = &m->orion;
    double w, faltante;
    char texto[MAX_TEXTO];

    if (!n->orbita_circular)
        return;                              /* tras el pulso ya no hay MCU */

    w = n->velocidad_orbital / n->radio;     /* rad/s */

    while (delta_tiempo > 0.0) {
        faltante = (2.0 * PI - n->angulo_orbital) / w;   /* s hasta cerrar la vuelta */

        if (delta_tiempo >= faltante) {
            n->tiempo_transcurrido += faltante;
            n->angulo_orbital = 0.0;
            n->vueltas_completas++;
            snprintf(texto, MAX_TEXTO, "Vuelta %d completada", n->vueltas_completas);
            registrar_evento(m, texto);
            delta_tiempo -= faltante;
        } else {
            n->tiempo_transcurrido += delta_tiempo;
            n->angulo_orbital += w * delta_tiempo;
            delta_tiempo = 0.0;
        }
    }
}

/* Pulso del propulsor lateral (perpendicular a v):
   delta_v = a*t ; desviacion = 1/2*a*t^2 ; |v'| = sqrt(v^2 + delta_v^2) */
int aplicar_pulso(Mision *m, double aceleracion, double duracion)
{
    Pulso *p = &m->pulso;
    Nave  *n = &m->orion;

    if (aceleracion <= 0.0 || duracion <= 0.0 || !n->orbita_circular)
        return 0;

    p->aplicado      = 1;
    p->aceleracion   = aceleracion;
    p->duracion      = duracion;
    p->delta_v       = aceleracion * duracion;
    p->desviacion    = 0.5 * aceleracion * duracion * duracion;
    p->rapidez_nueva = sqrt(n->velocidad_orbital * n->velocidad_orbital
                            + p->delta_v * p->delta_v);
    p->angulo_desvio = atan(p->delta_v / n->velocidad_orbital) * 180.0 / PI;

    n->tiempo_transcurrido += duracion;
    n->velocidad_orbital    = p->rapidez_nueva;
    n->orbita_circular      = 0;
    registrar_evento(m, "Pulso lateral: orbita deja de ser circular");
    return 1;
}

/* Reporte final de desempeno */
void generar_reporte_final(const Mision *m)
{
    int i;
    const Pulso *p = &m->pulso;

    printf("\n==================================================\n");
    printf("       REPORTE DE DESEMPENO - %s\n", m->nombre_mision);
    printf("==================================================\n");

    printf("Resultados analiticos (orbita circular):\n");
    printf(" - Altitud:             %.2f km\n", m->orion.altitud / 1000.0);
    printf(" - Radio orbital:       %.2f km\n", m->orion.radio / 1000.0);
    printf(" - Fuerza gravitatoria: %.2f N\n", m->f_gravitatoria);
    printf(" - Fuerza centripeta:   %.2f N\n", m->f_centripeta);
    printf(" - Aceleracion centripeta: %.3f m/s2\n", m->ac_centripeta);
    printf(" - Periodo:             %.2f s (%.2f min)\n", m->periodo, m->periodo / 60.0);

    printf("\nEstado final de la nave:\n");
    printf(" - Rapidez:             %.2f m/s (%.3f km/s)\n",
           m->orion.velocidad_orbital, m->orion.velocidad_orbital / 1000.0);
    printf(" - Vueltas completas:   %d\n", m->orion.vueltas_completas);
    printf(" - Angulo actual:       %.2f grados\n", m->orion.angulo_orbital * 180.0 / PI);
    printf(" - Tiempo simulado:     %.2f s\n", m->orion.tiempo_transcurrido);

    if (p->aplicado) {
        printf("\nPulso lateral (a=%.2f m/s2, t=%.1f s):\n", p->aceleracion, p->duracion);
        printf(" - Delta v perpendicular: %.2f m/s\n", p->delta_v);
        printf(" - Desviacion lateral:    %.2f m\n", p->desviacion);
        printf(" - Giro del vector v:     %.4f grados\n", p->angulo_desvio);
        printf(" - La orbita pasa de circular a eliptica.\n");
    }

    printf("\nHistorial de eventos registrados (%d):\n", m->cantidad_eventos);
    printf("--------------------------------------------------------------------------------\n");
    printf("%-10s | %-48s | %-8s | %-7s\n", "Tiempo[s]", "Evento", "Angulo", "Vueltas");
    printf("--------------------------------------------------------------------------------\n");
    for (i = 0; i < m->cantidad_eventos; i++) {
        printf("%-10.1f | %-48s | %-8.2f | %-7d\n",
               m->historial[i].tiempo,
               m->historial[i].descripcion,
               m->historial[i].angulo_registrado * 180.0 / PI,
               m->historial[i].vueltas_registradas);
    }
    if (m->cantidad_eventos >= MAX_EVENTOS)
        printf("(Aviso: el historial llego al maximo de %d eventos)\n", MAX_EVENTOS);
    printf("================================================================================\n");
}
