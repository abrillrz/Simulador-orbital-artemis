#ifndef SIMULADOR_H
#define SIMULADOR_H

// Constantes físicas del Escenario 2 (Órbita LEO)
#define MASA_TIERRA 5.972e24
#define RADIO_TIERRA 6371000.0
#define G 6.674e-11
#define ALTITUD_LEO 192000.0
#define MAX_EVENTOS 50 // Tamaño máximo del historial

// 1. Struct de la Nave (Estado físico en órbita)
typedef struct {
    float velocidad_orbital;  // m/s
    float altitud;            // m
    float angulo_orbital;     // grados (0 a 360)
    int   vueltas_completas;  // Contador de órbitas
    float tiempo_transcurrido;// segundos
} Nave;

// 2. Struct del Evento para el historial
typedef struct {
    int   tiempo;                   // Segundo de la simulación
    char  descripcion[100];         // Ej: "Inicio de órbita LEO"
    float angulo_registrado;        // Dónde estaba en la órbita
    int   vueltas_registradas;      // Cuántas vueltas llevaba
} Evento;

// 3. Struct de la Misión (Contiene la nave y el historial)
typedef struct {
    char    nombre_mision[50];
    Nave    orion;
    Evento  historial[MAX_EVENTOS]; // Arreglo de eventos
    int     cantidad_eventos;       // Contador de eventos
} Mision;

// Prototipos de funciones (usando punteros para actualizar el estado)
void inicializar_mision(Mision *m);
void registrar_evento(Mision *m, int tiempo, const char *desc);
void actualizar_estado_orbital(Nave *n, float delta_tiempo, float velocidad);
void generar_reporte_final(Mision *m);

#endif
