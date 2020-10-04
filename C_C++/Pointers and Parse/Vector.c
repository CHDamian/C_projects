//
// Created by damia on 2/25/2020.
//

#include "Vector.h"

Vector* VecInit()
{
    Vector *V = malloc(sizeof(Vector));
    if(V==NULL)return NULL;
    V->S=malloc(16* sizeof(Single));
    if(V->S==NULL)
    {
        free(V);
        return NULL;
    }
    V->Size=0;
    V->mSize=16;
    return V;

}
void VecDel(Vector *V)
{
    for(unsigned i=0;i<V->mSize;i++);
}
int VecInc(Vector *V)
{
    V->mSize*=2;
    V->S=realloc(V->S, V->mSize * sizeof(Single));
    if(V->S==NULL)return 0;
    return 1;
}
int VecPush(Vector *V, Single *S)
{
    if(V->Size+1==V->mSize)
    {
        int b = VecInc(V);
        if(b==0)return 0;
    }
    SinTrans(S,&V->S[V->Size]);
    V->Size++;
    return 1;
}
char* VecGet(Vector *V, unsigned i)
{
    if(i>=V->Size)return NULL;
    return V->S[i].c;
}
int VecSet(Vector *V, Single *S, unsigned i)
{
    if(i>=V->Size)return 0;
    SinTrans(S,&V->S[i]);
    return 1;
}
void VecClear(Vector *V)
{
    V->Size=0;
}

