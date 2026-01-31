/*
2. Archivo: _B_music.cpp 
(Datos de las canciones).
Aquí es donde realmente reside la música. 
⚠️ Importante: Debe tener la extensión ".cpp" para que el IDE de Arduino lo maneje correctamente junto al archivo principal ".ino".
✅ Nota: Asegúrate de que este sea el único archivo ".cpp" en tu carpeta.
*/

#include "_A_notes.h"
#include "_C_tree.h"

// DEFINICIÓN REAL (aquí se asigna la memoria).
// Definimos el arreglo con «N» columnas (sujetas al tamaño de la variable del archivo C++ principal) para mantener la estructura fija en memoria Flash.
const int tunes[NUM_TUNES][N_MAX] PROGMEM = {

    // 0 - Jingle bells
    {
        NOTE_E5, 8, NOTE_E5, 8, NOTE_E5, 4,
        NOTE_E5, 8, NOTE_E5, 8, NOTE_E5, 4,
        NOTE_E5, 8, NOTE_G5, 8, NOTE_C5, 8, NOTE_D5, 8,
        NOTE_E5, 2,
        NOTE_F5, 8, NOTE_F5, 8, NOTE_F5, 8, NOTE_F5, 8,
        NOTE_F5, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_E5, 16, NOTE_E5, 16,
        NOTE_E5, 8, NOTE_D5, 8, NOTE_D5, 8, NOTE_E5, 8,
        NOTE_D5, 4, NOTE_G5, 4, NOTE_END
    },

    // 1 - Santa Claus coming to town
    {
        NOTE_G4, 8,
        NOTE_E4, 8, NOTE_F4, 8, NOTE_G4, 4, NOTE_G4, 4, NOTE_G4, 4,
        NOTE_A4, 8, NOTE_B4, 8, NOTE_C5, 4, NOTE_C5, 4, NOTE_C5, 4,
        NOTE_E4, 8, NOTE_F4, 8, NOTE_G4, 4, NOTE_G4, 4, NOTE_G4, 4,
        NOTE_A4, 8, NOTE_G4, 8, NOTE_F4, 4, NOTE_F4, 2,
        NOTE_E4, 4, NOTE_G4, 4, NOTE_C4, 4, NOTE_E4, 4,
        NOTE_D4, 4, NOTE_F4, 2, NOTE_B3, 4,
        NOTE_C4, 1, NOTE_END
    },

    // 2) Silent Night, Original Version 
    { 
       NOTE_G4, 1, NOTE_REST, 8, NOTE_A4, 4, NOTE_G4, 2, NOTE_E4, 1, NOTE_REST, 2, 
       NOTE_G4, 1, NOTE_REST, 8, NOTE_A4, 4, NOTE_G4, 2, NOTE_E4, 1, NOTE_REST, 2,
       
       NOTE_D5, 1, NOTE_D5, 2, NOTE_B4, 1, NOTE_REST, 2, NOTE_C5, 1, NOTE_C5, 2, NOTE_G4, 1, NOTE_REST, 2, 

       NOTE_A4, 1, NOTE_A4, 2, NOTE_C5, 4, NOTE_REST, 4, NOTE_B4, 2, NOTE_A4, 2, NOTE_G4, 2, NOTE_REST, 3, NOTE_A4, 4, NOTE_G4, 2, NOTE_E4, 1, NOTE_REST, 2, 
       NOTE_A4, 1, NOTE_A4, 2, NOTE_C5, 4, NOTE_REST, 4, NOTE_B4, 2, NOTE_A4, 2, NOTE_G4, 2, NOTE_REST, 3, NOTE_A4, 4, NOTE_G4, 2, NOTE_E4, 1, NOTE_REST, 2, 
       
       NOTE_D5, 1, NOTE_D5, 2, NOTE_F5, 2, NOTE_REST, 4, NOTE_D5, 3, NOTE_B4, 2, NOTE_C5, 1, NOTE_REST, 3, NOTE_E5, 1, 
       
       NOTE_C5, 2, NOTE_G4, 2, NOTE_E4, 2, NOTE_G4, 1, NOTE_REST, 4, NOTE_F4, 2, NOTE_D4, 2, NOTE_C4, 1, NOTE_C4, 2, NOTE_C4, 1, NOTE_END
    }, 

    // 3 - We wish you a merry Xmas • Tiene un problema con la finalización.
    {
        NOTE_C5,4, NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8, NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,  
        NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,4, NOTE_C5,4, NOTE_C5,4,  
        NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8,  
        NOTE_D5,4, NOTE_G5,4, NOTE_E5,4, NOTE_F5,2, NOTE_C5,4, NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, 
        NOTE_E5,8, NOTE_D5,4, NOTE_D5,4, NOTE_D5,4, NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8,  
        NOTE_E5,4, NOTE_C5,4, NOTE_C5,4, NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,4, 
        NOTE_D5,4, NOTE_C5,8, NOTE_C5,8, NOTE_D5,4, NOTE_G5,4, NOTE_E5,4, NOTE_F5,2, NOTE_C5,4, NOTE_F5,4, 
        NOTE_F5,4, NOTE_F5,4, NOTE_E5,2, NOTE_E5,4, NOTE_F5,4, NOTE_E5,4, NOTE_D5,4, NOTE_C5,2, NOTE_A5,4,  
        NOTE_AS5,4, NOTE_A5,4, NOTE_G5,4, NOTE_C6,4, NOTE_C5,4, NOTE_C5,8, NOTE_C5,8, NOTE_D5,4, NOTE_G5,4, 
        NOTE_E5,4, NOTE_F5,2, NOTE_C5,4, NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8, NOTE_D5,4, 
        NOTE_D5,4, NOTE_D5,4, NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,4, NOTE_C5,4, 
        NOTE_C5,4, NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, 
        NOTE_C5,8, NOTE_D5,4, NOTE_G5,4, NOTE_E5,4, NOTE_F5,2, NOTE_C5,4, NOTE_F5,4, NOTE_F5,4, NOTE_F5,4,  
        NOTE_E5,2, NOTE_E5,4, NOTE_F5,4, NOTE_E5,4, NOTE_D5,4, NOTE_C5,2, NOTE_A5,4, NOTE_AS5,4, NOTE_A5,4, 
        NOTE_G5,4, NOTE_C6,4, NOTE_C5,4, NOTE_C5,8, NOTE_C5,8, NOTE_D5,4, NOTE_G5,4, NOTE_E5,4, NOTE_F5,2, 
        NOTE_C5,4, NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8, NOTE_D5,4, NOTE_D5,4, NOTE_D5,4,  
        NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,4, NOTE_C5,4, NOTE_C5,4, NOTE_A5,4, 
        NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,4, NOTE_D5,4, NOTE_C5,8, NOTE_C5,8, NOTE_D5,4, 
        NOTE_G5,4, NOTE_E5,4, NOTE_F5,2, NOTE_C5,4, NOTE_F5,4, NOTE_F5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,8,  
        NOTE_D5,4, NOTE_D5,4, NOTE_D5,4, NOTE_G5,4, NOTE_G5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,8, NOTE_E5,4, 
        NOTE_C5,4, NOTE_C5,4, NOTE_A5,4, NOTE_A5,8, NOTE_AS5,8, NOTE_A5,8, NOTE_G5,8, NOTE_F5,4, NOTE_D5,4, 
        NOTE_C5,8, NOTE_C5,8, NOTE_D5,4, NOTE_G5,4, NOTE_E5,4, NOTE_F5,2, NOTE_REST,4, NOTE_END
    },

    // 4 - Cartoon ending
    {
        NOTE_C7, 5, NOTE_G6, 10, NOTE_G6, 10, NOTE_A6, 5, NOTE_G6, 5, NOTE_REST, 5,
        NOTE_B6, 5, NOTE_C7, 3, NOTE_END
    },

    // 5 - First Noel
    {
        NOTE_E4, 6, NOTE_D4, 6, NOTE_C4, 2, NOTE_D4, 6, NOTE_E4, 6, NOTE_F4, 6, NOTE_G4, 4, NOTE_A4, 6, NOTE_B4, 6, NOTE_C5, 3, NOTE_B4, 3, NOTE_A4, 3,
        NOTE_G4, 2, NOTE_A4, 6, NOTE_B4, 6, NOTE_C5, 3, NOTE_B4, 3, NOTE_A4, 3, NOTE_G4, 3, NOTE_A4, 3, NOTE_B4, 3, NOTE_C5, 3, NOTE_G4, 3, NOTE_F4, 1, NOTE_END
    },

    // 6 - We three kings (short version)
    {
        NOTE_B4, 2, NOTE_A4, 6, NOTE_G4, 2, NOTE_E4, 6, NOTE_FS4, 6, NOTE_G4, 6, NOTE_FS4, 6, NOTE_E4, 2,
        NOTE_B4, 2, NOTE_A4, 6, NOTE_G4, 2, NOTE_E4, 6, NOTE_FS4, 6, NOTE_G4, 6, NOTE_FS4, 6, NOTE_E4, 2, NOTE_END
    },

    // 7 - Good King Wenceslass
    {
        NOTE_G4, 4, NOTE_G4, 4, NOTE_G4, 4, NOTE_A4, 4, NOTE_G4, 4, NOTE_G4, 4, NOTE_D3, 2, NOTE_END
    } // Fin del arreglo
};