/// Author: Damian Chanko 394127

#ifndef LIBS_WORDS_H
#define LIBS_WORDS_H

/***********************************************
 * Implementation of my string in c named Words.
 ***********************************************/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "List.h"

struct Words /// Structure.
{
    unsigned mSize; // Max size before realloc.
    size_t Size;
    char* Tab;
};

typedef struct Words Words;


Words* WordsInit(); /// Initialization.
void WordsDel(Words *w); /// Delete.
bool WordsInc(Words *w); /// Increase max size.
bool WordsSet(Words *w, char c, unsigned i); /// Set value c into specific existing place i.
char WordsGet(Words *w, unsigned i); /// Get value from i-place.
bool WordsPush(Words *w, char c); /// Push new element at the end.
bool WordsAppend(Words *W, Words *Old); /// Append two structures (w gets from Old, Old remains the same).
void WordsClear(Words *w); /// Clear structure.

/**
 * Read line from standard input into structure.
 * Function returns:
 * 0 if no problems found,
 * -1 if found end of file,
 * -2 if found problems with memory.
 **/
int WordsReadLine(Words *w);

int endcounter;

List* WordsToList(Words *w); /// Split into single words.

#endif //LIBS_WORDS_H
