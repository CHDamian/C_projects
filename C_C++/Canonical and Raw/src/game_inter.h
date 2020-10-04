/** @file
 * Obsługa trybu interaktywnego.
 *
 * @author Damian Chańko <dc394127@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 15.05.2020
 */

#ifndef GAME_INTER_H
#define GAME_INTER_H

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include "game_status.h"

#define WHITE_COLOR 0
#define BLUE_COLOR 1
#define RED_COLOR 2
#define GREEN_COLOR 3
#define YELLOW_COLOR 4
#define DARK_BLUE_COLOR 5

struct termios original; /**< Stan orginalny konsoli */


/** @brief Zwraca długość liczby.
 * Zwraca liczbę cyfr podanej wartości.
 * @param[in] x       – liczba do sprawdzenia.
 * @return Liczba cyfr @x.
 */
uint32_t numLen(uint32_t x);

/** @brief Zmienia kolor napisów.
 * Zmienia kolor wypisywanego tekstu.
 * @param[in] x       – kod koloru.
 */
void switchColor(int x);


/** @brief Wypisuje plansze.
 * Wypisuje plansze w trybie interaktywnym zaznaczając kursor gracza,
 * oraz podając jego aktualne dane.
 */
void interBoard();

/** @brief Wyszykuje następnego gracza.
 * Przekazuje ruch następnemu graczowi.
 */
void interFind();

/** @brief Zmienia miejsce kursoar.
 * Na sygnał wciśnięcia strzałki zmienia miejsce kursora pilnując,
 * by nie wyjść poza plansze.
 * @param[in] x     – zakodowana komenda.
 */
void interSwitch(int x);

/** @brief Wykonuje ruch.
 * Po naciśnięciu klawisza sprawdza, jaką komende chciał wywołać gracz,
 * a w przypadku poprawnego ruchu inicjuje go.
 */
void interMove();

/** @brief Dezaktywuje Raw Mode.
 * Wyłącza tryb niekanoniczny konsoli.
 */
void RawModeOFF();

/** @brief Aktywuje Raw Mode.
 * Włącza tryb niekanoniczny konsoli.
 */
void RawModeON();


#endif
