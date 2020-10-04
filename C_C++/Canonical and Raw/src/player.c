/** @file
 * Gracz gry gamma - implementacja.
 *
 * @author Damian Chańko <dc394127@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.04.2020
 */


#include "player.h"

player_t* playInit(uint32_t id)
{
    player_t *p = malloc(sizeof(player_t));
    if(p == NULL)return NULL;
    p->id = id;
    p->areas = 0;
    p->fields = 0;
    p->gold = false;
    return p;
}

participants* parInit(uint32_t len)
{
    participants *p = malloc(sizeof(participants));
    if(p == NULL)return NULL;
    p->len = len;
    p->arr = malloc(sizeof(player_t*)*len);
    for(uint32_t i = 0; i < len; i++)
    {
        p->arr[i] = playInit(i+1);
        if(p->arr[i] == NULL)return NULL;
    }
    return p;
}

void parDel(participants *p)
{
    if(p == NULL)return;
    for(uint32_t i = 0; i < p->len; i++)
    {
        free(p->arr[i]);
    }
    free(p->arr);
    free(p);
}
player_t* parGet(participants *p, uint32_t i)
{
    if(p == NULL)return NULL;
    if(i == 0 || i > p->len)return NULL;
    return p->arr[i-1];
}