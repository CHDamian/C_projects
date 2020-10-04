/** @file
 * Lista dwukierunkowa.
 *
 * @author Damian Chańko <dc394127@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 15.05.2020
 */

#ifndef LIST_H
#define LIST_H

#include "single.h"

typedef struct elemL elemL;

/**
 * Element listy.
 */

struct elemL
{
    elemL *prev; /**< poprzedni element */
    elemL *next; /**< następny element */
    Single *S; /**< pojedynczy element przechowywany w liście */
};


/** @brief Tworzy strukture elemL.
 * Alokuje pamięć na nowy element do listy
 * @return  Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *          zaalokować pamięci.
 */
elemL* elInit();

/** @brief Usuwa strukturę elemL.
 * Usuwa z pamięci strukturę wskazywaną przez @p l.
 * Nic nie robi, jeśli wskaźnik ten ma wartość NULL.
 * @param[in] l     – wskaźnik na usuwaną strukturę.
 */
void elDel(elemL *l);


typedef struct List List;

/**
 * Lista dwukierunkowa.
 */

struct List
{
    size_t size; /**< rozmiar */
    elemL *begin; /**< początek listy */
    elemL *end; /**< koniec listy */
};

/** @brief Tworzy strukture List.
 * Alokuje pamięć na nową liste dwukierunkową.
 * @return  Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *          zaalokować pamięci.
 */
List* ListInit();

/** @brief Czyści listę.
 * Czyści listę @p L ze wszystich elementów.
 * Nic nie robi, jeśli wskaźnik ten ma wartość NULL.
 * @param[in] L     – wskaźnik na listę do wyczyszczenia.
 */
void ListClear(List *L); /// Clear all elements of this list.

/** @brief Usuwa strukturę List.
 * Usuwa z pamięci strukturę wskazywaną przez @p L.
 * Nic nie robi, jeśli wskaźnik ten ma wartość NULL.
 * @param[in] L     – wskaźnik na usuwaną strukturę.
 */
void ListDel(List *L);

/**
 * @brief Wstawia element na początek listy.
 * Wstawia element na początek listy. Wnętrze @p S jest przenoszone
 * do nowej struktury, a samo @p S jest zwalniane.
 * @param[in] L     – wskaźnik na listę.
 * @param[in] S     - element do wstawienia.
 * @return  Jeden, jeżeli poprawnie wstawiono element.
 *          Zero, jeżeli jakiś parametr wskazuje na NULL
 *          bądź nie udało się zaalokować pamięci.
 */
int ListPushF(List *L, Single *S);

/**
 * @brief Wstawia element na koniec listy.
 * Wstawia element na koniec listy. Wnętrze @p S jest przenoszone
 * do nowej struktury, a samo @p S jest zwalniane.
 * @param[in] L     – wskaźnik na listę.
 * @param[in] S     - element do wstawienia.
 * @return  Jeden, jeżeli poprawnie wstawiono element.
 *          Zero, jeżeli jakiś parametr wskazuje na NULL
 *          bądź nie udało się zaalokować pamięci.
 */
int ListPushB(List *L, Single *S);

/**
 * @brief Usuwa element z początku listy.
 * Usuwa element z początku listy.
 * Zwalniane jest również wnętrze struktury Single, którą początek zawiera.
 * @param[in] L     – wskaźnik na listę.
 */
void ListRemF(List *L);

/**
 * @brief Usuwa element z końca listy.
 * Usuwa element z końca listy.
 * Zwalniane jest również wnętrze struktury Single, którą koniec zawiera.
 * @param[in] L     – wskaźnik na listę.
 */
void ListRemB(List *L);


#endif
