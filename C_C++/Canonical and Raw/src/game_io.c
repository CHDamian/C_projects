#include "game_io.h"
#include <string.h>
#include <ctype.h>


bool rightConvert; /**< zmienna informująca o poprawności konwersji  */
const uint32_t almostMax = UINT32_MAX/10; /**< granica dla akt z maxLimit */
const uint32_t lastMax = UINT32_MAX%10; /**< granica dla last z maxLimit */

bool maxLimit(uint32_t act, uint32_t last)
{
    if(act > almostMax)return true;
    if(act == almostMax && lastMax < last)return true;
    return false;
}

uint32_t stToInt32(char* c)
{
    rightConvert=false;
    if(c==NULL)
    {
        return 0;
    }
    size_t siz = strlen(c);
    if(siz > 10)return 0;
    if(siz == 1 && c[0] == '0')
    {
        rightConvert = true;
        return 0;
    }
    if(c[0]<49 || c[0]>57)return 0;
    uint32_t result = 0;
    for(uint32_t i=0; i<siz; i++)
    {
        if(c[i]<48 || c[i]>57)return 0;
        if(i==9 && maxLimit(result, c[i]-48))return 0;
        result *=10;
        result += c[i]-48;
    }
    rightConvert=true;
    return result;
}

bool funParams(elemL *E, uint32_t numbs, bool ifSt)
{
    for(uint32_t i = 0; i < numbs; i++)
    {
        E = E->next;
        uint32_t res = stToInt32(E->S->c);
        if(!rightConvert)return false;
        if(ifSt && res==0)return false;
        params[i] = res;
    }
    return true;
}

int modeFinder()
{
    int mode = MODE_NOT_FOUND;
    
    WordsClear(inputer);
    enl = WordsReadLine(inputer);
    if(enl == -1)return EOF_FOUND;
    if(enl == -2)exit(1);
    if(inputer->Size == 0)return MODE_NOT_FOUND;
    if(isspace(inputer->Tab[0]))return ERROR_FOUND;

    List *L = WordsToList(inputer);
    if(L == NULL)exit(1);
    if(inputer->Tab[0]=='#')
    {
        ListDel(L);
        return MODE_NOT_FOUND;
    }
    if(L->size!=5)
    {
        ListDel(L);
        return ERROR_FOUND;
    }
    char *c = L->begin->S->c;
    if(strlen(c)!= 1)
    {
        ListDel(L);
        return ERROR_FOUND;
    }

    if(c[0]=='B')mode = B_MODE;
    else if(c[0]=='I')mode = I_MODE;
    else
    {
        ListDel(L);
        return ERROR_FOUND;
    }
    if(funParams(L->begin,4,true))
    {
        ListDel(L);
        return mode;
    }
    else
    {
        ListDel(L);
        return ERROR_FOUND;
    }
}

bool tripleData(List *L)
{
    bool ret = funParams(L->begin,3,false);
    if(strlen(L->begin->S->c)!=1)
    {
        ListDel(L);
        return false;
    }
    char c = L->begin->S->c[0];
    ListDel(L);
    if(!ret)return false;
    if(params[0]==0)return false;
    if(c == 'm')printf("%u\n", gamma_move(game,params[0],params[1], params[2]));
    else if(c == 'g')printf("%u\n", gamma_golden_move(game,params[0],params[1], params[2]));
    else ret = false;
    return ret;
}
bool singleData(List *L)
{
    uint32_t pID = stToInt32(L->end->S->c);
    if(strlen(L->begin->S->c)!=1)
    {
        ListDel(L);
        return false;
    }
    char c = L->begin->S->c[0];
    ListDel(L);
    if(pID==0)return false;
    bool ret = true;
    if(c == 'b')printf("%"PRIu64"\n", gamma_busy_fields(game,pID));
    else if(c == 'f')printf("%"PRIu64"\n", gamma_free_fields(game,pID) );
    else if(c == 'q')printf("%u\n", gamma_golden_possible(game,pID) );
    else ret = false;
    return ret;
}

bool batchHandler()
{
    bool ret = true;
    WordsClear(inputer);
    enl = WordsReadLine(inputer);
    if(enl == -2)exit(1);
    if(inputer->Size == 0)return true;
    if(isspace(inputer->Tab[0]))return false;
    List *L = WordsToList(inputer);
    if(L == NULL)exit(1);
    if(L->size==0)
    {
        ListDel(L);
        return false;
    }
    if(inputer->Tab[0]=='#')
    {
        ListDel(L);
        return true;
    }
    if(enl == -1)
    {
        ListDel(L);
        return false;
    }
    if(L->size == 4)return tripleData(L); // Zlapano 4 parametry.
    if(L->size == 2)return singleData(L); // Zlapano 2 parametry.
    if(L->size == 1) // Zlapano 1 parametr, mozliwe gamma_board.
    {
        char *c=L->begin->S->c;
        if(strlen(c)!= 1)ret=false;
        else if(c[0]!='p')ret=false;
        else
        {
            char *bord = gamma_board(game);
            if(bord == NULL)exit(1);
            printf("%s", bord);
            free(bord);
        }
    }
    else ret = false;
    ListDel(L);
    return ret;
}
