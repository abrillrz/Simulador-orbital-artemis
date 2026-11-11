#ifndef SIMULADOR_H
#define SIMULADOR_H

/* Constantes fisicas del Escenario 2 (Orbita LEO) */
#define G_UNIV        6.674e-11      /* N*m^2/kg^2 (antes "G": nombre peligroso) */
#define MASA_TIERRA   5.972e24       /* kg */
#define RADIO_TIERRA  6371000.0      /* m  */
#define PI            3.14159265358979323846

/* Valores por defecto (reemplazar por datos validados del usuario) */
#define ALTITUD_LEO   192000.0       /* m  */
#define MASA_ORION    33000.0        /* kg */

#define MAX_EVENTOS   50             /* tamano maximo del historial */
#define MAX_TEXTO     100

/* 1. Struct de la Nave (estado fisico en orbita) */
typedef struct {
    double velocidad_orbital;   /* m/s                                   */
    double altitud;             /* m                                     */
    double radio;               /* m (RADIO_TIERRA + altitud)            */
    double masa;                /* kg                                    */
    double angulo_orbital;      /* radianes, 0 a 2*PI (vuelta actual)    */
    int    vueltas_completas;   /* contador de orbitas                   */
    double tiempo_transcurrido; /* s                                     */
    int    orbita_circular;     /* 1 = MCU vigente, 0 = tras el pulso    */
} Nave;

/* 2. Struct del Evento para el historial */
typedef struct {
    double tiempo;                  /* s de la simulacion                */
    char   descripcion[MAX_TEXTO];  /* ej: "Insercion exitosa en LEO"    */
    double angulo_registrado;       /* radianes                          */
    int    vueltas_registradas;
} Evento;

/* Resultado del pulso del propulsor lateral */
typedef struct {
    int    aplicado;
    double aceleracion;    /* m/s^2 */
    double duracion;       /* s     */
    double delta_v;        /* m/s   */
    double desviacion;     /* m     */
    double rapidez_nueva;  /* m/s   */
    double angulo_desvio;  /* grados */
} Pulso;

/* 3. Struct de la Mision (nave + resultados + historial) */
typedef struct {
    char    nombre_mision[50];
    Nave    orion;
    Pulso   pulso;
    double  periodo;          /* s            */
    double  ac_centripeta;    /* m/s^2        */
    double  f_gravitatoria;   /* N            */
    double  f_centripeta;     /* N            */
    Evento  historial[MAX_EVENTOS];
    int     cantidad_eventos;
} Mision;

/* Prototipos (punteros para actualizar el estado) */
int    inicializar_mision(Mision *m, double altitud, double masa);
int    registrar_evento(Mision *m, const char *desc);
void   actualizar_estado_orbital(Mision *m, double delta_tiempo);
int    aplicar_pulso(Mision *m, double aceleracion, double duracion);
void   generar_reporte_final(const Mision *m);

#endif
