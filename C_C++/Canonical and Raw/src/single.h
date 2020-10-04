/** @file
 * Element wewnętrzny struktur danych.
 *
 * @author Damian Chańko <dc394127@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 15.05.2020
 */

#ifndef SINGLE_H
#define SINGLE_H

#include <stdlib.h>

/**
 * Pojedynczy element do struktur danych.
 * Jego cel to zasymulowanie działania szablonów,
 * gdy tworzymy nową stukturę.
 * Budowa pozwala w łatwy sposób zamienić wnetrze pojedynczego elementu,
 * który potem będzie przechowywany w strukturze.
 */
struct Single
{
    char *c; /**< string na potrzebe zadania */
};
typedef struct Single Single;

/** @brief Tworzy pojedynczy element.
 * Alokuje pamięć na nowy element, gotowy do wrzucenia do struktury.
 * @param[in] c     – wskaźnik na stringa do struktury.
 * @return  Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *          zaalokować pamięci.
 */
Single* SinInit(char *c);

/** @brief Usuwa element.
 * Usuwa z pamięci strukturę wskazywaną przez @p S wraz z wnętrzem.
 * Nic nie robi, jeśli wskaźnik ten ma wartość NULL.
 * @param[in] S     – wskaźnik na usuwaną strukturę.
 */
void SinDel(Single *S);

/** @brief Zmienia wnętrze elementu.
 * Zwalnia wnętrze elementu i zastępuje je nowym.
 * Nic nie robi, jeśli @p S ma wartość NULL.
 * @param[in] S     – wskaźnik na element.
 * @param[in] c     – wskaźnik na stringa do zamiany.
 */
void SinSet(Single *S, char *c);

/** @brief Przenosi wnętrze do innego elementu.
 * Przenosi wnętrze do innego elementu
 * jednocześnie zwalniając to, na co wskazuje @p From.
 * Nic nie robi, jeśli któryś z parametrów ma wartość NULL.
 * @param[in] From  – wskaźnik na element do usunięcia.
 * @param[in] To    – wskaźnik na element docelowy.
 */
void SinTrans(Single *From, Single *To);

#endif
