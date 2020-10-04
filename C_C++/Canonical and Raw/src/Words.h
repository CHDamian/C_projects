/** @file
 * Mój string.
 *
 * @author Damian Chańko <dc394127@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.04.2020
 */

#ifndef WORDS_H
#define WORDS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

/**
 * Implementacja własnego stringa.
 */

struct Words
{
    unsigned mSize;  /**< maksymalny rozmiar przed reallociem */
    size_t Size;     /**< aktualny rozmiar */
    char* Tab;       /**< tablica */
};

typedef struct Words Words;


/** @brief Tworzy strukture Words.
 * Alokuje pamięć na nową strukturę Words.
 * String jest na początek pusty.
 * @return  Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *          zaalokować pamięci.
 */
Words* WordsInit();

/** @brief Usuwa strukturę Words.
 * Usuwa z pamięci strukturę wskazywaną przez @p w.
 * Nic nie robi, jeśli wskaźnik ten ma wartość NULL.
 * @param[in] w     – wskaźnik na usuwaną strukturę.
 */
void WordsDel(Words *w);

/** @brief Podwaja maksymalny rozmiar tablicy.
 * Reallocuje wewnętrzną tablice, zwiększając maksymalny rozmiar dwukrotnie.
 * W przypadku niepowodzenia struktura może być niezdatna do użytku.
 * @param[in] w     – wskaźnik na usuwaną strukturę.
 * @return  Wartość @p true, jeśli tablica została powiększona, a @p false,
 *          gdy parametr ma wartość NULL lub nie udało się zaalokować dodatkowej pamięci.
 */
bool WordsInc(Words *w);

/**
 * @brief Ustawia odpowiednią wartość w wybrane miejsce.
 * Ustawia wartość @p c w miejsce @p i.
 * @param[in] w     – wskaźnik na strukture Words.
 * @param[in] c     - wartość do wstawienia.
 * @param[in] i     - miejsce, gdzie wstawimy nową wartość.
 * @return  Wartość @p true, jeśli poprawnie wstawiono nową wartość, a @p false,
 *          jeśli jakiś parametr jest niepoprawny.
 */
bool WordsSet(Words *w, char c, unsigned i);

/**
 * @brief Zwraca odpowiednią wartość.
 * Zwraca wartość znajdującą się w miejscu @p i
 * @param[in] w     – wskaźnik na strukture Words.
 * @param[in] i     - miejsce poszukiwanej wartości.
 * @return  Wartość z wybranego miejsca, lub zero
 *          jeśli któryś z parametrów jest niepoprawny.
 */
char WordsGet(Words *w, unsigned i);

/**
 * @brief Wstawia element na koniec stringa.
 * Wstawia element na koniec tablicy, zwiększając aktualny rozmiar o jeden,
 * a jeżeli trzeba to allokuje dodatkową pamięć.
 * W przypadku niepowodzenia struktura może być niezdatna do użytku.
 * @param[in] w     – wskaźnik na strukture Words.
 * @param[in] c     - element do wstawienia.
 * @return  Wartość @p true, jeśli poprawnie wstawiono nową wartość, a @p false,
 *          jeśli jakiś parametr jest niepoprawny, lub nie udało się zaalokować pamięci.
 */
bool WordsPush(Words *w, char c);

/**
 * @brief Łączy dwa napisy w jeden.
 * Dodaje cały string ze struktury @p Old do @p W. Nie zmienia struktury @p Old.
 * W przypadku niepowodzenia struktura @p W może być niezdatna do użytku.
 * @param[in] W     - Docelowy string.
 * @param[in] Old   - Źródło, z którego otrzymamy elementy.
 * @return  Wartość @p true, jeśli poprawnie połączono stringi, a @p false,
 *          jeśli jakiś parametr jest niepoprawny, lub nie udało się zaalokować pamięci.
 */
bool WordsAppend(Words *W, Words *Old);

/**
 * @brief Czyści stringa.
 * Ustawia aktualny rozmiar stringa na zero, nie reallocując nic.
 * Mimo, że elementy w teori wciąż istnieją, są już niedostępne.
 * Nic nie robi, jeśli wskaźnik @p W ma wartość NULL.
 * @param[in] w     - wskaźnik na strukture Words.
 */
void WordsClear(Words *w);

/**
 * @brief Wczytuje linie z wejścia do stringa.
 * Wczytuje następną linię ze standardowego wejścia i zapisuje ją w tablicy.
 * Poprawnie wczytana linia kończy się znakiem nowej linii.
 * @param[in] w     - wskaźnik na strukture Words.
 * @return  Zero, jeżeli poprawnie wczytano linię.
 *          Minus jeden, jeżeli na końcu linii znalazł się EOF.
 *          Minus dwa, jeżeli nie udało się zaalokować pamięci (struktura
 *          może być niezdatna do użytku).
 *          Minus trzy, jeżeli @p w wskazuje na NULL.
 */
int WordsReadLine(Words *w);

/**
 * @brief Przepisuje dane do zwykłego stringa.
 * Alokuje w pamięci bufor, w którym umieszcza napis
 * pochodzący ze struktury Words.
 * Należy samodzielnie zwolnić ten buffor.
 * @param[in] w     - wskaźnik na strukture Words.
 * @return  Wskaźnik na zaalokowany bufor zawierający napis ze struktury
 *          lub NULL, jeśli nie udało się zaalokować pamięci,
 *          bądź @p w wskazuje na NULL.
 */
char* WordsToString(Words *w);

int endcounter;

List* WordsToList(Words *w); /// Split into single words.

#endif
