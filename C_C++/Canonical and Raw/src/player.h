/** @file
 * Gracz gry gamma.
 *
 * @author Damian Chańko <dc394127@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.04.2020
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Struktura symbolizująca gracza.
 */

struct player
{
    uint32_t id;         /**< ID gracza */
    uint64_t areas;      /**< zajęte obszary */
    uint64_t fields;     /**< zajęte pola */
    bool gold;           /**< czy wykonano złoty ruch */
};

typedef struct player player_t;


/**
 * @brief Tworzy strukturę symbolizującą gracza.
 * Alokuje pamięć na nową strukturę symbolizującą gracza
 * o indetyfikatorze @p id .
 * @param[in] id    - indetyfikator gracza.
 * @return  Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *          zaalokować pamięci lub któryś z parametrów jest niepoprawny.
 */
player_t* playInit(uint32_t id);

/**
 * Struktura będąca tablicą uczestników.
 */
struct participants
{
    player_t **arr;     /**< tablica */
    uint32_t len;       /**< długość tablicy */
};

typedef struct participants participants;


/**
 * @brief Tworzy tablice uczestników.
 * Alokuje pamięć na nową strukturę trzymającą uczestników gry
 * o ID od 1 do @p len włącznie.
 * @param[in] len   - liczba uczestników
 * @return  Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *          zaalokować pamięci lub któryś z parametrów jest niepoprawny.
 */
participants* parInit(uint32_t len);

/** @brief Usuwa tablice uczestników.
 * Usuwa z pamięci strukturę wskazywaną przez @p p.
 * Nic nie robi, jeśli wskaźnik ten ma wartość NULL.
 * @param[in] p     – wskaźnik na usuwaną strukturę.
 */
void parDel(participants *p);

/**
 * @brief Zwraca uczestnika.
 * Zwraca wskaźnik na uczestnika o id @p i .
 * @param[in] p     - wskaźnik na tablice uczestników.
 * @param[in] i     - ID uczestnika.
 * @return  Wskaźnik na szukanego uczestnika lub NULL,
 *          jeśli któryś z parametrów jest niepoprawny.
 */
player_t* parGet(participants *p, uint32_t i);

#endif
