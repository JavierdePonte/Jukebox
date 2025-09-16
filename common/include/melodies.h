/**
 * @file melodies.h
 * @brief Definition of notes and melodies arrays in file `melodies.c`.
 * @author Sistemas Digitales II
 * @date 2024-01-01
 */

#ifndef MELODIES_H_
#define MELODIES_H_
/* Includes ------------------------------------------------------------------*/
/* Standard C includes */
#include <stdint.h>

/* Defines and enums ----------------------------------------------------------*/
#define SILENCE 0 /*!< Silence note */

// 1st Octave (Primera Octava)
#define DO1 32.70  /*!< DO1 note frequency */
#define DOs1 34.65 /*!< DO#1 note frequency */
#define RE1  36.71 /*!< RE1 note frequency */
#define REs1 38.89 /*!< RE#1 note frequency */
#define MI1  41.20 /*!< MI1 note frequency */
#define FA1  43.65 /*!< FA1 note frequency */
#define FAs1 46.25 /*!< FA#1 note frequency */
#define SOL1 49.00 /*!< SOL1 note frequency */
#define SOLs1 51.91 /*!< SOL#1 note frequency */
#define LA1  55.00  /*!< LA1 note frequency */
#define LAs1 58.27  /*!< LA#1 note frequency */
#define SI1  61.74  /*!< SI1 note frequency */


// 2nd Octave (Segunda Octava)
#define DO2 65.41     /*!< DO2 note frequency */
#define DOs2 69.30   /*!< DO#2 note frequency */
#define RE2 73.42    /*!< RE2 note frequency */
#define REs2 77.78   /*!< RE#2 note frequency */
#define MI2 82.41    /*!< MI2 note frequency */
#define FA2 87.31    /*!< FA2 note frequency */
#define FAs2 92.50   /*!< FA#2 note frequency */
#define SOL2 98.00   /*!< SOL2 note frequency */
#define SOLs2 103.83  /*!< SOL#2 note frequency */
#define LA2  110.00   /*!< LA2 note frequency */
#define LAs2 116.54 /*!< LA#2 note frequency */
#define SI2  123.47  /*!< SI2 note frequency */

// 3rd Octave (Tercera Octava)
#define DO3 130.813   /*!< DO3 note frequency */
#define DOs3 138.591  /*!< DO#3 note frequency */
#define RE3 146.832   /*!< RE3 note frequency */
#define REs3 155.563  /*!< RE#3 note frequency */
#define MI3 164.814   /*!< MI3 note frequency */
#define FA3 174.614   /*!< FA3 note frequency */
#define FAs3 184.997  /*!< FA#3 note frequency */
#define SOL3 195.998  /*!< SOL3 note frequency */
#define SOLs3 207.652 /*!< SOL#3 note frequency */
#define LA3 220.000   /*!< LA3 note frequency */
#define LAs3 233.082  /*!< LA#3 note frequency */
#define SI3 246.942   /*!< SI3 note frequency */

// 4th Octave (Cuarta Octava)
#define DO4 261.626   /*!< DO4 note frequency */
#define DOs4 277.183  /*!< DO#4 note frequency */
#define RE4 293.665   /*!< RE4 note frequency */
#define REs4 311.127  /*!< RE#4 note frequency */
#define MI4 329.628   /*!< MI4 note frequency */
#define FA4 349.228   /*!< FA4 note frequency */
#define FAs4 369.994  /*!< FA#4 note frequency */
#define SOL4 391.995  /*!< SOL4 note frequency */
#define SOLs4 415.305 /*!< SOL#4 note frequency */
#define LA4 440.000   /*!< LA4 note frequency */
#define LAs4 466.164  /*!< LA#4 note frequency */
#define SI4 493.883   /*!< SI4 note frequency */

// 5th Octave (Quinta Octava)
#define DO5 523.251   /*!< DO5 note frequency */
#define DOs5 554.365  /*!< DO#5 note frequency */
#define RE5 587.330   /*!< RE5 note frequency */
#define REs5 622.254  /*!< RE#5 note frequency */
#define MI5 659.255   /*!< MI5 note frequency */
#define FA5 698.456   /*!< FA5 note frequency */
#define FAs5 739.989  /*!< FA#5 note frequency */
#define SOL5 783.991  /*!< SOL5 note frequency */
#define SOLs5 830.609 /*!< SOL#5 note frequency */
#define LA5 880.000   /*!< LA5 note frequency */
#define LAs5 932.328  /*!< LA#5 note frequency */
#define SI5 987.767   /*!< SI5 note frequency */

// 6th Octave (Sexta Octava)
#define DO6 1046.502   /*!< DO6 note frequency */
#define DOs6 1108.731  /*!< DO#6 note frequency */
#define RE6 1174.659   /*!< RE6 note frequency */
#define REs6 1244.508  /*!< RE#6 note frequency */
#define MI6 1318.510   /*!< MI6 note frequency */
#define FA6 1396.913   /*!< FA6 note frequency */
#define FAs6 1479.978  /*!< FA#6 note frequency */
#define SOL6 1567.982  /*!< SOL6 note frequency */
#define SOLs6 1661.219 /*!< SOL#6 note frequency */
#define LA6 1760.000   /*!< LA6 note frequency */
#define LAs6 1864.655  /*!< LA#6 note frequency */
#define SI6 1975.533   /*!< SI6 note frequency */

// 7th Octave (Séptima Octava)
#define DO7 2093.005   /*!< DO7 note frequency */
#define DOs7 2217.461  /*!< DO#7 note frequency */
#define RE7 2349.318   /*!< RE7 note frequency */
#define REs7 2489.016  /*!< RE#7 note frequency */
#define MI7 2637.020   /*!< MI7 note frequency */
#define FA7 2793.826   /*!< FA7 note frequency */
#define FAs7 2959.955  /*!< FA#7 note frequency */
#define SOL7 3135.964  /*!< SOL7 note frequency */
#define SOLs7 3322.438 /*!< SOL#7 note frequency */
#define LA7 3520.000   /*!< LA7 note frequency */
#define LAs7 3729.310  /*!< LA#7 note frequency */
#define SI7 3951.066   /*!< SI7 note frequency */

// 8th Octave (Octava Octava)
#define DO8 4186.009   /*!< DO8 note frequency */
#define DOs8 4434.922  /*!< DO#8 note frequency */
#define RE8 4698.636   /*!< RE8 note frequency */
#define REs8 4978.032  /*!< RE#8 note frequency */
#define MI8 5274.041   /*!< MI8 note frequency */
#define FA8 5587.652   /*!< FA8 note frequency */
#define FAs8 5919.910  /*!< FA#8 note frequency */
#define SOL8 6271.928  /*!< SOL8 note frequency */
#define SOLs8 6644.876 /*!< SOL#8 note frequency */
#define LA8 7040.000   /*!< LA8 note frequency */
#define LAs8 7458.620  /*!< LA#8 note frequency */
#define SI8 7902.133   /*!< SI8 note frequency */

/* Typedefs --------------------------------------------------------------------*/
/**
 * @brief Structure to define the Buzzer melody player FSM.
 */
typedef struct
{
    char *p_name;           /*!< Pointer to the name of the melody to play */
    double *p_notes;        /*!< Pointer to the notes of the melody */
    uint16_t *p_durations;  /*!< Pointer to the duration of each note of the melody in milliseconds */
    uint16_t melody_length; /*!< Length of the melody to play */
} melody_t;

// Melodies must be defined in melodies.c, and declared here as extern
// Scale melody
extern const melody_t scale_melody; 

// Melody Happy Birthday
extern const melody_t happy_birthday_melody;

// Tetris melody
extern const melody_t tetris_melody;

// Spansih anthem
extern const melody_t spanish_anthem;

// Feliz navidad
 extern const melody_t feliz_navidad_melody;

// Reversed scale
extern const melody_t scale_reverse_melody;

#endif /* MELODIES_H_ */