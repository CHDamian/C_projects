/** @file
 * Dane gry i potrzebne narzędzia.
 *
 * @author Damian Chańko <dc394127@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 15.05.2020
 */

#ifndef INT_STATUS_H
#define INT_STATUS_H

#include <inttypes.h>
#include "gamma.h"


gamma_t *game; /**< stworzona gra */


/**
 * Struktura przechowująca status trybu interaktywnego.
 */

struct intStatus
{
    uint32_t x; /**< pozycja x kursora */
    uint32_t y; /**< pozycja y kursora */
    uint32_t lastPlayer; /**< ostatni bądź aktualny gracz */
    bool someoneActive; /**< czy jakiś gracz aktywny */
    int color; /**< ostatni kolor szachownicy */
    uint32_t idLen; /**< długość największego ID gracza + 1 */
};

struct intStatus staty; /**< stan interactive mode'a */

#endif
