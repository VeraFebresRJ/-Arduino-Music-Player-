/*
3. Archivo: _C_tree.h
(Definiciones o declaraciones de Estructura)
Este es el «puente». Aquí usamos "extern". Esto le dice al archivo principal: «El arreglo existe, pero su contenido real está en otro archivo ".cpp"».
Por otro lado, evita que el programa principal intente definir el arreglo de nuevo.
*/

#ifndef TREE_H
#define TREE_H

// Lógica de compatibilidad para la memoria Flash.
#if defined(ARDUINO_ARCH_ESP32)

#include <pgmspace.h>  // Librería correcta para ESP32.
#else
  #include <avr/pgmspace.h> // Librería para Arduino Uno/Nano.
#endif

#define NUM_TUNES 8    // Filas (cantidad total de melodías).
#define N_MAX 500      // Máximo de notas por canción (ajustado) | Columnas (notas).

// DECLARACIÓN (sin valores, para que compile el .ino)
// Esto le dice al compilador: «Hay un arreglo llamado tunes en otro lado, no te preocupes».
extern const int tunes[NUM_TUNES][N_MAX] PROGMEM;

#endif