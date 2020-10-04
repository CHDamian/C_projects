/** @file
 * Macierz będąca też polem do gry -implementacja
 *
 * @author Damian Chańko <dc394127@students.mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 17.04.2020
 */

#include "matrix.h"
#include <stdio.h>

matrix* matInit(uint32_t x, uint32_t y)
{
    matrix* m = malloc(sizeof(matrix));
    if(m == NULL)return NULL;
    m->arr = malloc(sizeof(uint32_t*)*x);
    if(m->arr == NULL)return NULL;
    for(uint32_t i = 0; i < x; i++)
    {
        m->arr[i] = malloc(sizeof(uint32_t)*y);
        if(m->arr[i] == NULL)return NULL;
        for(uint32_t j = 0; j < y; j++)
        {
            m->arr[i][j] = 0;
        }
    }
    m->x = x;
    m->y = y;
    return m;
}

void matDel(matrix *m)
{
    if(m == NULL)return;
    for(uint32_t i = 0; i < m->x; i++)
    {
        free(m->arr[i]);
    }
    free(m->arr);
    free(m);
}

void matClear(matrix *m)
{
    if(m == NULL)return;
    for(uint32_t i = 0; i < m->x; i++)
    {
        for(uint32_t j = 0; j < m->y; j++)
        {
            m->arr[i][j]=0;
        }
    }
}

bool matInside(matrix *m, uint32_t x, uint32_t y)
{
    if(x >= m->x)return false;
    if(y >= m->y)return false;
    return true;
}

bool matNear(matrix *m, uint32_t x, uint32_t y, uint32_t l)
{
    if(matInside(m, x, y)==false || m->arr[x][y] != l)return false;
    else return true;
}

bool matAround(matrix *m, uint32_t x, uint32_t y, uint32_t l)
{
    if(m == NULL)return false;
    if(matInside(m, x, y)==false)return false;
    if(matNear(m, x-1, y, l))return true;
    if(matNear(m, x+1, y, l))return true;
    if(matNear(m, x, y-1, l))return true;
    if(matNear(m, x, y+1, l))return true;
    return false;
}

void matDFS(matrix *m, matrix *odw, uint32_t x, uint32_t y, uint32_t l)
{
    odw->arr[x][y] = 1;
    if(matNear(m, x-1, y, l) && odw->arr[x-1][y] == 0)matDFS(m, odw, x-1, y, l);
    if(matNear(m, x+1, y, l) && odw->arr[x+1][y] == 0)matDFS(m, odw, x+1, y, l);
    if(matNear(m, x, y-1, l) && odw->arr[x][y-1] == 0)matDFS(m, odw, x, y-1, l);
    if(matNear(m, x, y+1, l) && odw->arr[x][y+1] == 0)matDFS(m, odw, x, y+1, l);
}

uint32_t matCheck(matrix *m, matrix *odw, uint32_t x, uint32_t y, uint32_t l)
{
    uint32_t licz = 0;
    matClear(odw);
    odw->arr[x][y] = 1;
    if(matNear(m, x-1, y, l) && odw->arr[x-1][y] == 0)
    {
        licz++;
        matDFS(m, odw, x-1, y, l);
    }
    if(matNear(m, x+1, y, l) && odw->arr[x+1][y] == 0)
    {
        licz++;
        matDFS(m, odw, x+1, y, l);
    }
    if(matNear(m, x, y-1, l) && odw->arr[x][y-1] == 0)
    {
        licz++;
        matDFS(m, odw, x, y-1, l);
    }
    if(matNear(m, x, y+1, l) && odw->arr[x][y+1] == 0)
    {
        licz++;
        matDFS(m, odw, x, y+1, l);
    }
    return licz;
}