/** @file
 * Macierz będąca też polem do gry.
 *
 * @author Damian Chańko <dc394127@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.04.2020
 */


#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Struktura przechowując macierz x na y.
 */

struct matrix
{
    uint32_t **arr;     /**< tablica */
    uint32_t x;         /**< wiersze */
    uint32_t y;         /**< kolumny */
};

typedef struct matrix matrix;

/**
 * @brief Tworzy macierz.
 * Alokuje pamięć na nową macierz @p x na @p y .
 * Macierz jest wypełniona na początek zerami.
 * @param[in] x     - liczba wirszy.
 * @param[in] y     - liczba kolumn.
 * @return  Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *          zaalokować pamięci lub któryś z parametrów jest niepoprawny.
 */
matrix* matInit(uint32_t x, uint32_t y);

/**
 * @brief Usuwa macierz.
 * Usuwa z pamięci strukturę wskazywaną przez @p m.
 * Nic nie robi, jeśli wskaźnik ten ma wartość NULL.
 * @param[in] m     – wskaźnik na usuwaną strukturę.
 */
void matDel(matrix *m);

/**
 * @brief Czyści macierz.
 * Ustawia macierz na macierz zerową.
 * @param[in] m     - macierz do wyzerowania.
 */
void matClear(matrix *m);

/**
 * @brief Sprawdza czy pole jest wewnątrz.
 * Sprawdza, czy pole ( @p x , @p y ) należy do macierzy.
 * @param[in] m     - macierz.
 * @param[in] x     - kolumna.
 * @param[in] y     - wiersz.
 * @return  Wartość @p true, jeśli pole jest wewnątrz macierzy, a @p false,
 *          jeśli nie należy lub któryś z parametrów jest niepoprawny.
 */
bool matInside(matrix *m, uint32_t x, uint32_t y);

/**
 * @brief Sprawdza parametry pola.
 * Sprawdza, czy pole ( @p x , @p y ) należy do macierzy
 * i stoi na nim pionek gracza @p l .
 * @param[in] m     - macierz.
 * @param[in] x     - kolumna.
 * @param[in] y     - wiersz.
 * @param[in] l     - id gracza, którego pionka szukamy.
 * @return  Wartość @p true, jeśli pole spełnia warunki, a @p false,
 *          w przeciwnym wypadku lub któryś z parametrów jest niepoprawny.
 */
bool matNear(matrix *m, uint32_t x, uint32_t y, uint32_t l);

/**
 * @brief Sprawdza, czy jest obok pole o odpowiedniej wartości.
 * Sprawdza, czy pole ( @p x , @p y ) sąsiaduje z polem
 * z pionkiem gracza @p l .
 * @param[in] m     - macierz.
 * @param[in] x     - kolumna.
 * @param[in] y     - wiersz.
 * @param[in] l     - id gracza, którego pionka szukamy.
 * @return  Wartość @p true, jeśli pole sąsiaduje z polem zajętym przez szukanego gracza, a @p false,
 *          w przeciwnym wypadku lub któryś z parametrów jest niepoprawny.
 */
bool matAround(matrix *m, uint32_t x, uint32_t y, uint32_t l);

/**
 * @brief DFS po polach gracza.
 * Przeszukuje w głąb po macierzy @p m w poszukiwaniu pionków gracza @p l ,
 * wykorzystując macierz odwiedzonych @p odw .
 * @param[in] m - macierz
 * @param[in] odw - macierz odwiedzonych
 * @param[in] x - nr kolumny aktualnego pola
 * @param[in] y - nr wiersza aktualnego pola
 * @param[in] l - id gracza, którego pionków szukamy.
 */
void matDFS(matrix *m, matrix *odw, uint32_t x, uint32_t y, uint32_t l);

/**
 * @brief Sprawdza liczbę połączonych obszarów.
 * Sprawdza, ile obszarów zostanie połączonych,
 * gdy postawimy pionek na polu ( @p x , @p y ),
 * wliczając w to powstały obszar przy wstawianiu danego pola.
 * @param[in] m     - macierz.
 * @param[in] odw   - macierz odwiedzonych do wewnętrznego DFSa (na start zostanie wyczyszczona).
 * @param[in] x     - kolumna.
 * @param[in] y     - wiersz.
 * @param[in] l     - id gracza, który stawia pionek.
 * @return  Liczba połączonych obszarów w przypadku postawienia pionka, lub zero,
 *          jeśli któryś z parametrów jest niepoprawny.
 */
uint32_t matCheck(matrix *m, matrix *odw, uint32_t x, uint32_t y, uint32_t l);



#endif
