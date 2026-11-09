#include <stdio.h>
#include <math.h>
#include "orbita.h"

double calcular_radio_orbital(double altitud) {
    return R_TIERRA + altitud;
}

/* Problema A: F_g = F_c  =>  G M m / r² = m v² / r  =>  v = sqrt(G M / r) */
double calcular_velocidad_orbital(double radio) {
    return sqrt(G_CONST * M_TIERRA / radio);
}

/* Problema B: T = 2 π r / v */
double calcular_periodo(double radio, double velocidad) {
    if (velocidad <= 0.0) return 0.0;
    return 2.0 * PI * radio / velocidad;
}

double segundos_a_minutos(double segundos) {
    return segundos / 60.0;
}

double calcular_fuerza_gravitatoria(double radio, double masa) {
    return G_CONST * M_TIERRA * masa / (radio * radio);
}

double calcular_fuerza_centripeta(double masa, double velocidad, double radio) {
    return masa * velocidad * velocidad / radio;
}

double calcular_aceleracion_centripeta(double velocidad, double radio) {
    return velocidad * velocidad / radio;
}

/* Comparación con tolerancia relativa (nunca == con doubles) */
int verificar_fuerzas(double fg, double fc, double tolerancia) {
    if (fg == 0.0) return 0;
    return fabs(fg - fc) / fabs(fg) < tolerancia;
}

int calcular_orbita(DatosOrbita *o) {
    if (o == NULL || o->altitud <= 0.0 || o->masa <= 0.0) return 0;

    o->radio             = calcular_radio_orbital(o->altitud);
    o->velocidad         = calcular_velocidad_orbital(o->radio);
    o->periodo_s         = calcular_periodo(o->radio, o->velocidad);
    o->periodo_min       = segundos_a_minutos(o->periodo_s);
    o->fuerza_grav       = calcular_fuerza_gravitatoria(o->radio, o->masa);
    o->fuerza_centr      = calcular_fuerza_centripeta(o->masa, o->velocidad, o->radio);
    o->aceleracion_centr = calcular_aceleracion_centripeta(o->velocidad, o->radio);
    o->fuerzas_coinciden = verificar_fuerzas(o->fuerza_grav, o->fuerza_centr, 1e-9);
    return 1;
}

void mostrar_resultados_orbita(const DatosOrbita *o) {
    printf("\n=========== ORBITA TERRESTRE BAJA (MCU) ===========\n");
    printf(" Altitud h            : %.1f m (%.1f km)\n", o->altitud, o->altitud / 1000.0);
    printf(" Masa de la nave m    : %.1f kg\n", o->masa);
    printf(" Radio orbital r      : %.1f m\n", o->radio);
    printf("---------------------------------------------------\n");
    printf(" PROBLEMA A\n");
    printf("  Fuerza gravitatoria : %.2f N\n", o->fuerza_grav);
    printf("  Fuerza centripeta   : %.2f N\n", o->fuerza_centr);
    printf("  Fg = Fc ?           : %s\n",
           o->fuerzas_coinciden ? "SI (la gravedad actua como fuerza centripeta)" : "NO");
    printf("  Velocidad orbital v : %.2f m/s (%.2f km/s, %.1f km/h)\n",
           o->velocidad, o->velocidad / 1000.0, o->velocidad * 3.6);
    printf("---------------------------------------------------\n");
    printf(" PROBLEMA B\n");
    printf("  Periodo orbital T   : %.2f s (%.2f min)\n", o->periodo_s, o->periodo_min);
    printf("---------------------------------------------------\n");
    printf(" Aceleracion centripeta: %.4f m/s^2\n", o->aceleracion_centr);
    printf("===================================================\n");
}
