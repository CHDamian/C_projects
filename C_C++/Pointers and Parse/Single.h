/// Author: Damian Chanko 394127

#ifndef LIBS_SINGLE_H
#define LIBS_SINGLE_H

#include <stdlib.h>

/********************************************************
 * Implementation of structure Single,
 * that is used in my implementations of other structures
 * such as Vector, List, etc.
 *
 * Structure helps change data, that is in data structures
 * without modify them.
 *
 * For example once it has array of chars,
 * another time it has two ints.
 ********************************************************/


struct Single /// Structure.
{
    char *c;
};
typedef struct Single Single;

Single* SinInit(char *c); /// Initialization.
void SinDel(Single *S); /// Delete.
void SinSet(Single *S, char *c); /// Set new values.

/// Transfer data from one struct to other.
/// Frees struct From.
void SinTrans(Single *From, Single *To);

#endif //LIBS_SINGLE_H
