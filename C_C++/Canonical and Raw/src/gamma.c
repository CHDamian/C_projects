/** @file
 * Implementacja funkcji używanych w grze gamma.
 *
 * @author Damian Chańko <dc394127@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 18.03.2020
 */

#include "gamma.h"
#include "Words.h"

struct gamma
{
    matrix *board; /**< plansza */
    uint32_t maxim; /**< Maksymalna liczba obszarów */
    participants *par; /**< gracze */
    uint64_t free; /**< liczba wolnych miejsc */
    matrix *odw; /**< pomocnicza maciesz do niektórych funkcji */

};


gamma_t* gamma_new(uint32_t width, uint32_t height,
                   uint32_t players, uint32_t areas)
{
    if(width==0 || height==0 || players==0 || areas==0)return NULL;
    gamma_t *g=malloc(sizeof(gamma_t));
    if(g==NULL)   
    {
        return NULL;
    }

    g->maxim=areas;
    g->free=width;
    g->free*=height;

    g->board=matInit(width,height);
    if(g->board==NULL)
    {
        return NULL;
    }

    g->odw=matInit(width,height);
    if(g->odw==NULL)
    {
        return NULL;
    }

    g->par=parInit(players);
    if(g->par==NULL)
    {
        return NULL;
    }

    return g;
}

void gamma_delete(gamma_t *g)
{
    if(g == NULL)return;
    matDel(g -> board);
    matDel(g -> odw);
    parDel(g -> par);
    free(g);
}

bool gamma_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y)
{
    if(g == NULL)
    {
        return false;
    }
    if(player > g->par->len)
    {
        return false;
    }
    if(matInside(g->board, x, y) == false)
    {
        return false;
    }
    if(g->board->arr[x][y] != 0)
    {
        return false;
    }

    player_t *p=parGet(g->par,player);
    uint32_t pom=matCheck(g->board,g->odw,x,y,player);
    if(p->areas+1-pom>g->maxim)   
    {
        return false;
    }

    g -> board -> arr[x][y] = player;
    p -> fields++;
    p -> areas++;
    p -> areas -= pom;
    g -> free--;

    return true;
}

bool gamma_golden_move(gamma_t *g, uint32_t player, uint32_t x, uint32_t y)
{
    if(g==NULL)
    {
        return false;
    }
    if(player>g->par->len)
    {
        return false;
    }
    if(matInside(g->board,x,y)==false)
    {
        return false;
    }
    if(g->board->arr[x][y]==0 || g->board->arr[x][y]==player)
    {
        return false;
    }

    player_t *p1=parGet(g->par,player);
    if(p1->gold)
    {
        return false;
    }
    uint32_t pom1=matCheck(g->board,g->odw,x,y,player);
    if(p1->areas+1-pom1>g->maxim)
    {
        return false;
    }

    player_t *p2=parGet(g->par,g->board->arr[x][y]);
    uint32_t pom2=matCheck(g->board,g->odw,x,y,p2->id);
    if(p2->areas+pom2-1>g->maxim)
    {
        return false;
    }

    g->board->arr[x][y] = player;
    p1->gold = true;
    p1->fields++;
    p1->areas++;
    p1->areas -= pom1;
    p2->fields--;
    p2->areas += pom2;
    p2->areas--;

    return true;
}

uint64_t gamma_free_fields(gamma_t *g, uint32_t player)
{
    if(g == NULL)return 0;
    if(g->par->len < player || player == 0)return 0;
    if(parGet(g->par, player)->areas < g->maxim)return g->free;
    uint64_t licz = 0;
    for(uint32_t i = 0; i<g->board->x; i++)
    {
        for(uint32_t j = 0; j<g->board->y; j++)
        {
            if(g->board->arr[i][j] != 0)continue;
            if(matAround(g->board, i, j, player))licz++;
        }
    }
    return licz;
}

bool gamma_golden_possible(gamma_t *g, uint32_t player)
{
    if(g == NULL)return false;
    if(player > g->par->len)return false;
    bool found = false;
    player_t *p1 = parGet(g->par, player);
    if(p1->gold)return false;
    for(uint32_t i = 0; i < g->board->x; i++)
    {
        for(uint32_t j = 0; j < g->board->y; j++)
        {
            if(g->board->arr[i][j] == 0 || g->board->arr[i][j] == player)continue;

            uint32_t pom1 = matCheck(g->board, g->odw, i, j, player);
            if(p1->areas + 1 - pom1 > g->maxim)continue;

            player_t *p2 = parGet(g->par, g->board->arr[i][j]);
            uint32_t pom2 = matCheck(g->board, g->odw, i, j, p2->id);
            if(p2->areas+pom2-1>g->maxim)continue;

            found = true;
            break;
        }
        if(found == true)break;
    }
    return found;
}

uint64_t gamma_busy_fields(gamma_t *g, uint32_t player)
{
    return parGet(g->par, player)->fields;
}

char* gamma_board(gamma_t *g)
{
    if(g == NULL)return NULL;

    Words *w=WordsInit();
    if(w == NULL)return NULL;
    char c[19];
    unsigned len;

    for(uint32_t j = g->board->y - 1; true; j--)
    {
        for (uint32_t i = 0; i<g->board->x; i++)
        {
            if(g->board->arr[i][j] == 0)
            {
                if(WordsPush(w, '.') == false)return NULL;
            }
            else
            {
                len=0;
                uint32_t var=g->board->arr[i][j];
                while(var != 0)
                {
                    c[len] = (var%10)+48;
                    len++;
                    var /= 10;
                }
                for(unsigned x = len-1; true; x--)
                {
                    if(WordsPush(w,c[x]) == false)return NULL;
                    if(x == 0)break;
                }
            }
        }
        if(WordsPush(w,'\n')==false)return NULL;
        if(j == 0)break;
    }
    if(WordsPush(w,'\0') == false)return NULL;
    char *wyn = WordsToString(w);
    WordsDel(w);
    return wyn;
}

matrix* gamma_get_matrix(gamma_t *g)
{
    if(g == NULL)return NULL;
    return g->board;
}

participants* gamma_get_par(gamma_t *g)
{
    if(g == NULL)return NULL;
    return g->par;
}