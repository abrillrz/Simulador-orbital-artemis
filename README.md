# 🚀 Simulador de Misiones Artemis — Escenario 2: Órbita Terrestre Baja (LEO)

**Trabajo Final Integrador - Lenguaje C**
*Universidad Tecnológica Nacional - Facultad Regional Resistencia*
*Cátedra: Algoritmos y Estructuras de Datos | Ingeniería en Sistemas de Información*

---

## 👥 Integrantes y Comisión
*   **Comisión:** C
*   **Grupo:** "The Girls"
*   **Integrantes:**
    *   Abril Nahir LORINCZ
    *   Larisa Selene OCAMPO
    *   Brisa Alanis RODRIGUEZ
    *   Gisela Mabel SOLOAGA
    *   Pilar Agostina VARGAS

🔗 **Video de presentación:** [Enlace al video en YouTube/Drive/Loom - *Pendiente de subir*]

---

## 🌌 Descripción del Escenario Artemis y Reglas del Juego
Este proyecto simula la **Situación-Problema 2** de la misión Artemis: la inserción y estabilidad de la nave Orion en una Órbita Terrestre Baja (LEO). 

Tras apagar sus motores de ascenso, la nave es inyectada en una órbita a **192 km de altitud**, describiendo un Movimiento Circular Uniforme (MCU). El simulador permite calcular y responder a las preguntas de análisis del escenario:
*   **(a) Velocidad orbital (v):** Calculada igualando la fuerza gravitatoria con la centrípeta.
*   **(b) Período orbital (T):** Tiempo que tarda en dar una vuelta completa (en segundos y minutos).
*   **(c) Aceleración centrípeta (a):** Aceleración que experimentan los astronautas a esa altitud.
*   **(d) Pulso de propulsor lateral:** Simulación de un encendido auxiliar perpendicular a la órbita, calculando la desviación lateral y su efecto en la trayectoria.

**Reglas del Simulador:**
El usuario interactúa mediante un menú por consola. A medida que avanza la simulación (por turnos o eventos), se registran los cambios en la nave (ángulo, vueltas, tiempo). Al finalizar, el sistema genera un reporte detallado con el historial de eventos y el desempeño final de la misión.

---

## ⚙️ Detalle de Funcionamiento (Arquitectura del Software)
El código está diseñado bajo una estricta **modularización** (sin archivos monobloque), dividiendo las responsabilidades de la siguiente manera:

*   **`main.c`**: Contiene la función `main()`, el menú principal de navegación y la inicialización del flujo del programa.
*   **`simulador.h` / `simulador.c`**: Declaración y definición de la lógica de negocio y cálculos físicos. Incluye el diseño de los `structs` (Nave, Evento, Misión), el uso de arreglos para el historial, y funciones con punteros para actualizar el estado y generar el reporte final.
*   **`validaciones.h` / `validaciones.c`**: Funciones dedicadas al ingreso seguro de datos (enteros, flotantes) y manejo de errores, evitando que el programa se rompa ante entradas erróneas del usuario.

---

## 🛠️ Instrucciones de Compilación y Ejecución
Para compilar y ejecutar este proyecto, es necesario tener instalado el compilador **GCC** en un entorno Linux, Mac o Windows (usando MinGW o WSL).

1. Abrir una terminal en la carpeta raíz del repositorio.
2. Compilar todos los archivos `.c` juntos. *(Nota: se utiliza `-lm` para enlazar la librería matemática `<math.h>` utilizada en los cálculos orbitales).*
   ```bash
   gcc main.c simulador.c validaciones.c -o simulador_artemis -lm

3. Ejecutar el programa:

    En Linux / Mac:
    ```bash
   ./simulador_artemis
    ```
   En Windows:
   ```bash
   simulador_artemis.exe
   ```

   ## 🤖 Registro de Uso de Inteligencia Artificial
De acuerdo con lo solicitado por la cátedra, declaramos el uso de herramientas de IA generativa como apoyo al aprendizaje y al desarrollo del proyecto:

*   **Herramientas utilizadas:** ChatGPT (OpenAI) / Claude (Anthropic). *(Pongan la que hayan usado)*.
*   **Tareas específicas:** 
    *   Consultas sobre la sintaxis de punteros en C para actualizar los `structs`.
    *   Ayuda para estructurar la fórmula del Movimiento Circular Uniforme (MCU) en el código.
    *   Depuración de errores del compilador GCC.
*   **Prompts realizados:** *"¿Cómo crear un arreglo de structs para guardar un historial en C?"*, *"¿Cómo calcular el ángulo de una órbita usando la velocidad angular?"*.
*   **Validación y adaptación:** Todo el código sugerido por la IA fue revisado, comprendido y adaptado por las integrantes del grupo. Ajustamos las variables a nuestro propio diseño de `structs` y comprobamos que las fórmulas físicas coincidieran con los datos exactos dados en la consigna de la cátedra.
