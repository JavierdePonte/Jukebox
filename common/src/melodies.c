/**
 * @file melodies.c
 * @brief Melodies source file.
 * @author Sistemas Digitales II
 * @date 2024-01-01
 */

/* Includes ------------------------------------------------------------------*/
#include "melodies.h"

/* Melodies ------------------------------------------------------------------*/
// Melody Happy Birthday
#define HAPPY_BIRTHDAY_LENGTH 25 /*!< Happy Birthday melody length */

/**
 * @brief Happy Birthday melody notes.
 *
 * This array contains the frequencies of the notes for the Happy Birthday song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double happy_birthday_notes[HAPPY_BIRTHDAY_LENGTH] = {
    DO4, DO4, RE4, DO4, FA4, MI4, DO4, DO4, RE4, DO4, SOL4, FA4, DO4, DO4, DO5, LA4, FA4, MI4, RE4, LAs4, LAs4, LA4, FA4, SOL4, FA4};

/**
 * @brief Happy Birthday melody durations in miliseconds.
 *
 * This array contains the duration of each note in the Happy Birthday song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t happy_birthday_durations[HAPPY_BIRTHDAY_LENGTH] = {
    300, 100, 400, 400, 400, 800, 300, 100, 400, 400, 400, 800, 300, 100, 400, 400, 400, 400, 400, 300, 100, 400, 400, 400, 800};

/**
 * @brief Happy Birthday melody struct.
 *
 * This struct contains the information of the Happy Birthday melody.
 * It is used to play the melody using the buzzer.
 */
const melody_t happy_birthday_melody = {.p_name = "happy_birthday",
                                        .p_notes = (double *)happy_birthday_notes,
                                        .p_durations = (uint16_t *)happy_birthday_durations,
                                        .melody_length = HAPPY_BIRTHDAY_LENGTH};

// Tetris melody
#define TETRIS_LENGTH 40 /*!< Tetris melody length */

/**
 * @brief Tetris melody notes.
 *
 * This array contains the frequencies of the notes for the Tetris song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double tetris_notes[TETRIS_LENGTH] = {
    MI5, SI4, DO5, RE5, DO5, SI4, LA4, LA4, DO5, MI5, RE5, DO5, SI4, DO5, RE5, MI5, DO5, LA4,
    LA4, LA4, SI4, DO5, RE5, FA4, LA5, SOL5, FA5, MI5, DO5, MI5, RE5, DO5, SI4, SI4, LA4, RE5,
    MI5, DO5, LA4, LA4};

/** 
 * @brief Tetris melody durations in miliseconds.
 *
 * This array contains the duration of each note in the Tetris song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t tetris_durations[TETRIS_LENGTH] = {
    400, 200, 200, 400, 200, 200, 400, 200, 200, 400, 200, 200, 600, 200, 400, 400, 400, 400, 200, 200, 200, 200,
    600, 200, 400, 200, 200, 600, 200, 400, 200, 200, 400, 200, 200, 400, 400, 400, 400, 400};

/**
 * @brief Tetris melody struct.
 * 
 * This struct contains the information of the Tetris melody.
 * It is used to play the melody using the buzzer.
 */
const melody_t tetris_melody = {.p_name = "tetris",
                                .p_notes = (double *)tetris_notes,
                                .p_durations = (uint16_t *)tetris_durations,
                                .melody_length = TETRIS_LENGTH};

// Scale Melody
#define SCALE_MELODY_LENGTH 8   /*!< Scale melody length */

/**
 * @brief Scale melody notes.
 *
 * This array contains the frequencies of the notes for the scale song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double scale_melody_notes[SCALE_MELODY_LENGTH] = {
    DO4, RE4, MI4, FA4, SOL4, LA4, SI4, DO5};

/**
 * @brief Scale melody durations in miliseconds.
 * 
 * This array contains the duration of each note in the scale song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t scale_melody_durations[SCALE_MELODY_LENGTH] = {
    250, 250, 250, 250, 250, 250, 250, 250};

/**
 * @brief Scale melody struct.
 * 
 * This struct contains the information of the scale melody.
 * It is used to play the melody using the buzzer.
 */
const melody_t scale_melody = {.p_name = "scale",
                               .p_notes = (double *)scale_melody_notes,
                               .p_durations = (uint16_t *)scale_melody_durations,
                               .melody_length = SCALE_MELODY_LENGTH};


// Spanish Anthem
#define SPANISH_ANTHEM_LENGTH 101  /*!< Scale melody length */
/**
 * @brief Spanish anthem notes.
 *
 * This array contains the frequencies of the notes for the Spanish anthem.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */


static const double spanish_anthem_notes[SPANISH_ANTHEM_LENGTH] = {
    MI6, SOL6, MI6, DO6, SOL6, FA6, MI6, RE6, DO6, DO6, SI6, LA6, SOL6,
    DO6, RE6, MI6, SOL6, FA6, MI6, RE6, DO6, RE6, SOL6, LA6, SI6, DO7,
    SOL6, MI6, DO6, SOL6, FA6, MI6, RE6, DO6, DO6, SI6, LA6, SOL6,
    DO6, RE6, MI6, SOL6, FA6, MI6, RE6, DO6, RE6, SOL6, LA6, SI6, DO7,
    SOL6, MI6, DO6, SOL6, FA6, MI6, RE6, DO6, DO6, SI6, LA6, SOL6,
    DO6, RE6, MI6, SOL6, FA6, MI6, RE6, DO6, RE6, SOL6, LA6, SI6, DO7,
    SOL6, MI6, DO6, SOL6, FA6, MI6, RE6, DO6, DO6, SI6, LA6, SOL6,
    DO6, RE6, MI6, SOL6, FA6, MI6, RE6, DO6, RE6, SOL6, LA6, SI6, DO7
};
/**
 * @brief Spanish anthem durations in miliseconds.
 * 
 * This array contains the duration of each note in the spanish anthem song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t spanish_anthem_durations[SPANISH_ANTHEM_LENGTH] = {
    500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
    500, 500, 500, 500, 500, 500, 500, 500, 500, 500
};

/**
 * @brief Spanish anthem struct.
 * 
 * This struct contains the information of the spanish anthem.
 * It is used to play the melody using the buzzer.
 */
const melody_t spanish_anthem = {.p_name = "Spanish anthem",
                               .p_notes = (double *)spanish_anthem_notes,
                               .p_durations = (uint16_t *)spanish_anthem_durations,
                               .melody_length = SPANISH_ANTHEM_LENGTH};

 // Feliz Navidad Melody
#define FELIZ_NAVIDAD_MELODY_LENGTH 20   /*!< Feliz Navidad melody length */

/**
 * @brief Feliz Navidad melody notes.
 *
 * This array contains the frequencies of the notes for the Feliz Navidad song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double feliz_navidad_melody_notes[FELIZ_NAVIDAD_MELODY_LENGTH] = {
    MI5, MI5, SOL5, DO6, SI5, LA5, SOL5, FA5, MI5, RE5, DO5, RE5, SOL4, SOL4, LA4, LA4, DO5, SOL4, MI5, MI5};

/**
 * @brief Feliz Navidad melody durations in milliseconds.
 * 
 * This array contains the duration of each note in the Feliz Navidad song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t feliz_navidad_melody_durations[FELIZ_NAVIDAD_MELODY_LENGTH] = {
    250, 250, 500, 500, 500, 1000, 500, 500, 500, 1000, 500, 1000, 500, 500, 500, 1000, 500, 500, 500, 1000};

/**
 * @brief Feliz Navidad melody struct.
 * 
 * This struct contains the information of the Feliz Navidad melody.
 * It is used to play the melody using the buzzer.
 */
const melody_t feliz_navidad_melody = {.p_name = "Feliz Navidad",
                               .p_notes = (double *)feliz_navidad_melody_notes,
                               .p_durations = (uint16_t *)feliz_navidad_melody_durations,
                               .melody_length = FELIZ_NAVIDAD_MELODY_LENGTH};


// scale_reverse Melody
#define SCALE_REVERSE_MELODY_LENGTH 8   /*!< scale_reverse melody length */

/**
 * @brief scale_reverse melody notes.
 *
 * This array contains the frequencies of the notes for the scale_reverse song.
 * The notes are defined as frequency values in Hertz, and they are arranged in the order they are played in the song.
 */
static const double scale_reverse_melody_notes[SCALE_REVERSE_MELODY_LENGTH] = {
    DO5, SI4, LA4, SOL4, FA4, MI4, RE4, DO4};

/**
 * @brief scale_reverse melody durations in miliseconds.
 * 
 * This array contains the duration of each note in the scale_reverse song.
 * The durations are defined in milliseconds, and they are arranged in the order they are played in the song.
 */
static const uint16_t scale_reverse_melody_durations[SCALE_REVERSE_MELODY_LENGTH] = {
    250, 250, 250, 250, 250, 250, 250, 250};

/**
 * @brief scale_reverse melody struct.
 * 
 * This struct contains the information of the scale_reverse melody.
 * It is used to play the melody using the buzzer.
 */
const melody_t scale_reverse_melody = {.p_name = "scale_reverse",
                               .p_notes = (double *)scale_reverse_melody_notes,
                               .p_durations = (uint16_t *)scale_reverse_melody_durations,
                               .melody_length = SCALE_REVERSE_MELODY_LENGTH}; 
