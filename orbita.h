#ifndef ORBITA_H
#define ORBITA_H

/* ===== Constantes físicas de la consigna (SI) ===== */
#define G_CONST    6.674e-11     /* N·m²/kg²  */
#define M_TIERRA   5.972e24      /* kg        */
#define R_TIERRA   6371000.0     /* m         */
#define PI         3.14159265358979323846

/* Valores por defecto de la consigna (Escenario 2) */
#define H_CONSIGNA 192000.0      /* m  (192 km) */
#define M_CONSIGNA 33000.0       /* kg (Orion)  */

/* Estado de una órbita circular (MCU) alrededor de la Tierra */
typedef struct {
    double altitud;            /* h  [m]    (entrada) */
    double masa;               /* m  [kg]   (entrada) */
    double radio;              /* r = R_T + h [m]     */
    double velocidad;          /* v  [m/s]            */
    double periodo_s;          /* T  [s]              */
    double periodo_min;        /* T  [min]            */
    double fuerza_grav;        /* F_g [N]             */
    double fuerza_centr;       /* F_c = m v² / r [N]  */
    double aceleracion_centr;  /* a_c = v² / r [m/s²] */
    int    fuerzas_coinciden;  /* 1 si F_g == F_c (con tolerancia) */
} DatosOrbita;

/* --- Cálculos individuales (funciones puras) --- */
double calcular_radio_orbital(double altitud);
double calcular_velocidad_orbital(double radio);            /* Problema A */
double calcular_periodo(double radio, double velocidad);    /* Problema B */
double segundos_a_minutos(double segundos);
double calcular_fuerza_gravitatoria(double radio, double masa);
double calcular_fuerza_centripeta(double masa, double velocidad, double radio);
double calcular_aceleracion_centripeta(double velocidad, double radio);
int    verificar_fuerzas(double fg, double fc, double tolerancia);

/* --- Cálculo completo: usa o->altitud y o->masa, completa el resto ---
   Devuelve 1 si OK, 0 si los datos de entrada no son válidos. */
int  calcular_orbita(DatosOrbita *o);
void mostrar_resultados_orbita(const DatosOrbita *o);

#endif
