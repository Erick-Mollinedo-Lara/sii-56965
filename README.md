# 🏓 Prácticas de Sistemas: Juego de Tenis 2D (C++, OpenGL & IPC)

Repositorio correspondiente a las prácticas de la asignatura, donde se desarrolla un juego interactivo de tenis/pong bidimensional en C++ (OpenGL/FreeGLUT) y se amplía con una arquitectura de Comunicación Entre Procesos (IPC) mediante tuberías FIFO en Linux.

---

## 📋 Estructura de las Prácticas

---

## 🎮 PRÁCTICA 1: Dinámica, Física y Movimiento del Juego

### 🎯 Objetivo
Desarrollar la lógica fundamental del juego en C++ y OpenGL: renderizado gráfico, control por teclado de las raquetas, cinemática de la pelota, detección de colisiones y conteo de tantos.

### 🛠️ Tareas y Cambios Realizados

1. **Movimiento y control de las raquetas (`Raqueta.cpp` / `Raqueta.h`):**
   * Definición de las coordenadas de las paletas (`x1, y1` a `x2, y2`) para ambos jugadores.
   * Implementación y calibración del método `Mueve(float t)` para lograr un desplazamiento vertical suave, reactivo y proporcionado a la velocidad del juego.
   * Vinculación con los eventos de teclado para mover cada raqueta de manera independiente.

2. **Cinemática y velocidad de la pelota (`Esfera.cpp` / `Esfera.h`):**
   * Configuración en el constructor `Esfera::Esfera()` de sus propiedades físicas: radio (`radio = 0.6f`) y vector de velocidad inicial (`velocidad.x = 3`, `velocidad.y = 3`).
   * Actualización continua de su posición en `Mueve(float t)` en función del delta de tiempo (`t`).

3. **Colisiones, marcador y corrección del saque (`Mundo.cpp`):**
   * Detección de rebotes contra paredes superior/inferior y contra las raquetas.
   * Detección de punto cuando la bola supera los límites laterales.
   * **Corrección del reinicio (saque):** Se corrigió la desaceleración que sufría la pelota tras marcar un tanto, asegurando que la velocidad reasignada en el saque sea consistente con la velocidad rápida inicial.

---

## 📡 PRÁCTICA 2: Comunicación Entre Procesos (IPC) con FIFO

### 🎯 Objetivo
Desacoplar la interfaz visual del registro de eventos mediante técnicas de concurrencia y **Comunicación Entre Procesos (IPC)** usando una tubería con nombre (**FIFO / Named Pipe**) en Linux.

### 🛠️ Tareas y Cambios Realizados

1. **Creación del canal de comunicación (FIFO):**
   * Creación de un archivo especial de tubería con nombre en el sistema de archivos (`mkfifo`) para conectar dos procesos independientes sin compartir memoria directa.

2. **Adaptación del juego `tenis` como Productor (`Mundo.cpp`):**
   * Modificación del juego para que, al producirse un tanto, escriba el evento formateado en la tubería FIFO en lugar de bloquear el hilo de renderizado gráfico con salidas por pantalla.

3. **Desarrollo del proceso `logger` como Consumidor (`logger.cpp`):**
   * Creación de un programa en consola independiente que abre la FIFO en modo lectura.
   * Al iniciar, queda a la espera de datos:
     ```text
     logger iniciado. Esperando datos...
     ```
   * Cada vez que recibe un mensaje a través de la tubería, procesa e imprime el marcador actualizado en tiempo real:
     ```text
     Jugador 1 marca 1 punto, lleva un total de 1 puntos.
     Jugador 2 marca 1 punto, lleva un total de 1 puntos.
     ```

4. **Ventajas de la solución:**
   * **Desacoplamiento:** El juego gráfico no pierde rendimiento por operaciones de entrada/salida (I/O).
   * **Modularidad:** El logger puede ejecutarse, reiniciarse o redirigirse a un archivo de registro en disco sin alterar el código del juego.

---

## 🚀 Compilación y Ejecución

### 1. Compilación (CMake + Make)
Ambos programas se compilan desde la carpeta `build`:
```bash
cd ~/Escritorio/practicas/sii-56965/workspace/build
make
