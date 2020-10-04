/** @file
 * Obsługa trybu wsadowego.
 *
 * @author Damian Chańko <dc394127@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 15.05.2020
 */

#ifndef GAME_IO_H
#define GAME_IO_H

#include "Words.h"
#include "game_status.h"

#define EOF_FOUND -1
#define MODE_NOT_FOUND 0
#define B_MODE 1
#define I_MODE 2
#define ERROR_FOUND 3


Words *inputer; /**< Struktura trzymająca input */
uint32_t line; /**< Aktualna linia */
int enl; /**< Stan trybu wsadowego */
uint32_t params[4]; /**< Przetworzone parametry ostatniego wejscia */



/** @brief Chroni przed wyjsciem liczby za zakres.
 * Sprawdza czy tworzona z wejscia liczba wyjdzie za zakres,
 * gdy dodamy kolejną cyfre.
 * @param[in] akt   – aktualny stan liczby.
 * @param[in] last  – cyfra do dodania.
 * @return  Wartość @p true, jeśli wartość nie wyjdzie za zakres, a @p false,
 *          w przeciwnym wypadku.
 */
bool maxLimit(uint32_t act, uint32_t last);

/** @brief Zamienia string na liczbę.
 * Tworzy liczbę naturalną 32 bitową ze stringa.
 * @param[in] c     – string do zamiany.
 * @return  Zamieniona liczba lub 0, jeżeli wystąpił błąd przy konwersji.
 * Inne funkcje zostają powiadomione wewnątz o niepowodzeniu.
 */
uint32_t stToInt32(char* c);

/** @brief Zamienia stringi z wejścia na liczby.
 * Zamienia stringi z cyframi na liczby naturalne 32 bitowe,
 * umieszczając wyniki w tablicy na parametry.
 * @param[in] E     – Wnętrze listy ze stringami, zaczynając się od stringa z kodem funkcji.
 * @param[in] numbs – liczba cyfr do konwersji.
 * @param[in] ifSt  – informacja, czy zamiana jest tworzona dla sprawdzenia trybu gry.
 * @return  Wartość @p true, jeśli poprawnie zamieniono wejście, a @p false,
 *          w przeciwnym wypadku.
 */
bool funParams(elemL *E, uint32_t numbs,  bool ifSt);

/** @brief Sprawdza jaki tryb gry wybrano.
 * Przetwarza pierwsze liniki wejścia sprawdzając,
 * jaki tryb gry wybrał użytkownik.
 * @return  Zero, jeżeli linia jest do zignorowania.
 *          Jeden, jeżeli wybrano tryb wsadowy.
 *          Dwa, jeżeli wybrano tryb interaktywny.
 *          Trzy, jeżeli niepoprawnie wpisano dane.
 */
int modeFinder();

/** @brief Wybiera funkcje od odpalenia o trzech parametrach.
 * Przetwarza wejście w poszukiwaniu funkcji z trzema parametrami
 * (plus grą) i inicjuje ją.
 * @param[in] L     – wskaźnik na listę z wejściem.
 * @return  Wartość @p true, jeśli odpalono funkcje, a @p false,
 *          w przeciwnym wypadku.
 */
bool tripleData(List *L);

/** @brief Wybiera funkcje od odpalenia z jednym parametrem.
 * Przetwarza wejście w poszukiwaniu funkcji z jednym parametrem
 * (plus grą) i inicjuje ją.
 * @param[in] L     – wskaźnik na listę z wejściem.
 * @return  Wartość @p true, jeśli odpalono funkcje, a @p false,
 *          w przeciwnym wypadku.
 */
bool singleData(List *L);

/** @brief Przetwarza linię wejścia w trybie wsadowym.
 * Wczytuje linie wejścia i wstępnie ją przetwarza.
 * Może ona wypisać stan planszy, jeżeli wpisano odpowiednie parametry.
 * @return  Wartość @p true, jeśli wpisano poprawną linię, a @p false,
 *          w przeciwnym wypadku.
 */
bool batchHandler();

#endif
