# 🚀 Simulador de Misiones Artemis — Escenario 2: Órbita Terrestre Baja (LEO)

**Trabajo Final Integrador — Lenguaje C**
Universidad Tecnológica Nacional — Facultad Regional Resistencia
Cátedra: Algoritmos y Estructuras de Datos | Ingeniería en Sistemas de Información

---

## 👥 Integrantes y Comisión

**Comisión:** C
**Grupo:** "The Girls"

**Integrantes:**
- Abril Nahir LORINCZ
- Larisa Selene OCAMPO
- Brisa Alanis RODRIGUEZ
- Gisela Mabel SOLOAGA
- Pilar Agostina VARGAS

> ⚠️ 🔗 **Video de presentación:** [PENDIENTE: pegar acá el enlace al video]

---

## 🌌 Descripción del Escenario y Reglas del Juego

El proyecto simula la **Situación-Problema 2** de la misión Artemis: la nave **Orion** queda en una **Órbita Terrestre Baja (LEO)** describiendo un **Movimiento Circular Uniforme (MCU)**. La altitud y la masa de la nave las ingresa el usuario (referencia de la consigna: 192 km).

El simulador resuelve las preguntas de análisis del escenario:

| Punto | Magnitud | Fórmula utilizada |
|-------|----------|-------------------|
| (a) | Velocidad orbital | La gravedad actúa como fuerza centrípeta: G·M·m/r² = m·v²/r → v = √(G·M/r) |
| (b) | Período orbital | T = 2π·r / v |
| (c) | Aceleración centrípeta | a_c = v² / r |
| (d) | Pulso de propulsor lateral | Aceleración a perpendicular a v durante Δt: Δv = a·Δt, desviación = ½·a·Δt², rapidez final = √(v² + Δv²) |

donde r = R_Tierra + altitud, G = 6,674·10⁻¹¹ N·m²/kg², M_Tierra = 5,972·10²⁴ kg y R_Tierra = 6 371 000 m. El programa además muestra que la fuerza gravitatoria y la centrípeta son iguales.

### Ejemplo de resultados (altitud 192 km)
- Velocidad orbital: **7792,95 m/s** (≈ 7,79 km/s)
- Período: **5291,52 s** (≈ 88,19 min)
- Aceleración centrípeta: **9,253 m/s²**
- Pulso de 0,50 m/s² durante 10 s: Δv = 5 m/s, **desviación lateral = 25 m**, giro del vector velocidad ≈ 0,037°.

### Reglas del simulador
- Al iniciar, el usuario ingresa la altitud (160 a 2000 km) y la masa de la nave (1000 a 1 000 000 kg).
- Un menú por consola permite:
  - Avanzar la simulación una vuelta completa. Cada vuelta queda registrada sola en el historial.
  - Encender el propulsor lateral. Se ingresan aceleración (0,01 a 5 m/s²) y duración (1 a 60 s). Solo puede aplicarse una vez por misión.
  - Ver el estado actual de la nave (altitud, rapidez, ángulo, vueltas, tiempo).
  - Ver el reporte final con resultados analíticos e historial de eventos.
  - Salir.
- Tras aplicar el pulso, la órbita deja de ser circular (pasa a ser elíptica), por lo que el modelo de MCU ya no vale y no se puede seguir avanzando.
- El historial guarda hasta 50 eventos.
- Todas las entradas se validan: letras en lugar de números, valores fuera de rango o líneas demasiado largas no rompen el programa; se informa el error y se vuelve a pedir el dato.

---

## ⚙️ Detalle de Funcionamiento (Arquitectura del Software)

El código está modularizado en varios archivos (sin código monobloque).

### Archivos del programa final
Estos son los archivos que se compilan y forman el simulador ejecutable:

| Archivo | Responsabilidad |
|---------|-----------------|
| `main.c` | `main()`, menú principal, flujo del programa y pedido de datos al usuario |
| `simulador.h` / `simulador.c` | Constantes físicas, structs (`Nave`, `Evento`, `Pulso`, `Mision`), arreglo de historial, cálculos físicos y reporte final |
| `validaciones.h` / `validaciones.c` | Ingreso seguro de enteros y decimales, opción de menú y mensajes de advertencia |
| `Makefile` | Compilación automatizada |

### Archivos de evidencia de desarrollo
Durante el trabajo, cada módulo se desarrolló y probó por separado antes de integrarse. Estos archivos se dejan en el repositorio como **evidencia del proceso** de cada integrante. **No forman parte de la compilación del programa final** (el Makefile solo usa `main.c`, `simulador.c` y `validaciones.c`):

| Archivo | Evidencia de |
|---------|--------------|
| `orbita.h` / `orbita.c` | Módulo de cálculos orbitales (velocidad y período) desarrollado por separado; su lógica se integró luego en `simulador.c` |
| `main_orbita.c` / `test_orbita.c` | Menú de prueba y casos de prueba del módulo de órbita |
| `propulsion.h` / `propulsion.c` | Módulo de propulsión (aceleración y propulsor lateral) desarrollado por separado; su lógica se integró luego en `simulador.c` (función `aplicar_pulso`) |
| `test_propulsion.c` | Caso de prueba del módulo de propulsión: verifica que un pulso de 0,50 m/s² durante 10 s da una desviación lateral de 25 m |

### Estructuras principales
- **Nave:** estado físico (rapidez, altitud, radio, masa, ángulo en radianes, vueltas, tiempo, bandera `orbita_circular`).
- **Evento:** registro del historial (tiempo, descripción, ángulo y vueltas en ese instante).
- **Pulso:** resultados de la maniobra lateral (Δv, desviación, rapidez nueva, giro del vector velocidad).
- **Mision:** agrupa la nave, el pulso, los resultados analíticos (período, a_c, Fg, Fc) y el arreglo `historial[MAX_EVENTOS]` con su contador.

### Funciones con punteros (simulador.c)
- `inicializar_mision(Mision *m, altitud, masa)`: calcula v, T, a_c y las fuerzas. Devuelve 0 si los datos son inválidos.
- `registrar_evento(Mision *m, descripcion)`: agrega un evento al arreglo con el estado actual. Devuelve 0 si el historial está lleno.
- `actualizar_estado_orbital(Mision *m, delta_tiempo)`: avanza en MCU (ω = v/r) y cierra cada vuelta en el instante exacto.
- `aplicar_pulso(Mision *m, aceleracion, duracion)`: calcula Δv, desviación y nueva rapidez.
- `generar_reporte_final(const Mision *m)`: imprime resultados e historial en formato de tabla.

---

## 🛠️ Instrucciones de Compilación y Ejecución

**Requisito:** compilador GCC (Linux, macOS, o Windows con MinGW/WSL) y `make`.

### Con Makefile (recomendado)
```
make          # compila
make run      # compila y ejecuta
make clean    # borra los archivos generados
```

### Sin Makefile
```
gcc -Wall -Wextra -pedantic -std=c99 main.c simulador.c validaciones.c -o simulador_artemis -lm
```
`-lm` enlaza la librería matemática (`<math.h>`), necesaria para `sqrt` y `atan`.

### Ejecución
**Linux / macOS**
```
./simulador_artemis
```
**Windows**
```
simulador_artemis.exe
```

---

## 🤖 Registro de Uso de Inteligencia Artificial

De acuerdo con lo solicitado por la cátedra, declaramos el uso de IA generativa como apoyo al aprendizaje y al desarrollo.

> ⚠️ **Completar antes de entregar:** esta sección debe reflejar lo que el grupo realmente usó. Agreguen otras herramientas si las hubo y confirmen que cada integrante revisó y comprendió el código.

**Herramientas utilizadas:** Claude (Anthropic), DeepSeek y Qwen. 

**Tareas específicas:**
- Explicación de los conceptos físicos del escenario (velocidad orbital, aceleración centrípeta, desviación lateral) antes de llevarlos a código.
- Revisión del diseño de structs y del uso de punteros para actualizar el estado.
- Corrección de errores y mejoras: uso de `double` en lugar de `float`, cierre exacto de cada vuelta, cálculo del pulso lateral, control de desborde del historial y de cadenas.
- Guía en el uso de Git y GitHub: creación de ramas, commits, Pull Requests y resolución de conflictos.
- Integración de `main.c` (menú) con el módulo del simulador y con `validaciones.c`.
- Redacción del Makefile y de este README.

**Prompts realizados (resumen):**
- "Explicame la física de mi parte (aceleración centrípeta y pulso del propulsor) como si no supiera nada del tema."
- "Completa el Estado, reportes e historial de simulación (struct, arreglos, punteros, reporte final) siguiendo el escenario 2."
- "¿Cómo puedo calcular el ángulo de una órbita usando la velocidad angular en C?"
- "Me da error el compilador con la librería math.h, ¿qué significa el flag -lm?"
- "Analiza este código de main.c y decime si hay algún bucle infinito con las validaciones."
- "Ayudame a crear una rama en Git y resolver un conflicto al integrar los módulos."
- "Actualiza el README y arma un Makefile."

**Validación y adaptación:**
- Se compiló con `-Wall -Wextra -pedantic -std=c99` sin advertencias.
- Se contrastaron los resultados del programa (v, T, a_c, Fg = Fc, Δv y desviación) con el cálculo analítico.
- Se probó el programa con entradas erróneas (letras, negativos, fuera de rango) para verificar las validaciones.
- Todas las integrantes revisaron el código y pueden explicar cada función.
