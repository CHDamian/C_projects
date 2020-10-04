/// Author: Damian Chanko 394127

#include "single.h"

Single* SinInit(char *c)
{
    Single *S = malloc(sizeof(Single));
    if(S == NULL)return NULL;
    S->c = c;
    return S;
}

void SinDel(Single *S)
{
    if(S == NULL) return;
    free(S->c);
    free(S);
}

void SinSet(Single *S, char *c)
{
    if(S == NULL) return;
    free(S->c);
    S->c = c;
}
void SinTrans(Single *From, Single *To)
{
    if(From == NULL || To == NULL) return;
    SinSet(To,From->c);
    free(From);
}
