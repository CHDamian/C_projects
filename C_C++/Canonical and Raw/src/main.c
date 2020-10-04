#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "game_io.h"
#include "game_inter.h"

#define MAX_BOARD 100000000

int main() {
    inputer = WordsInit();
    if(inputer == NULL)exit(1);
    int inType = MODE_NOT_FOUND;
    while(inType == MODE_NOT_FOUND)
    {
        line++;
        inType = modeFinder();
        if(inType == ERROR_FOUND)
        {
            fprintf(stderr,"ERROR %u\n", line);
            inType=MODE_NOT_FOUND;
        }
        else if(inType == B_MODE || inType == I_MODE)
        {
            uint64_t boardSize = params[0];
            boardSize *= params[1];
            if(boardSize > MAX_BOARD)
            {
                fprintf(stderr,"ERROR %u\n", line);
                inType=MODE_NOT_FOUND;
            }
        }
    }
    if(inType!= EOF_FOUND)
    {
        game = gamma_new(params[0], params[1], params[2], params[3]);
        printf("OK %u\n", line);
    }
    if(inType==B_MODE)
    {
        while (enl != -1) {
            line++;
            if (!batchHandler())fprintf(stderr,"ERROR %u\n", line);
        }
    }
    else if(inType==I_MODE)
    {
        RawModeON();
        staty.idLen = numLen(params[2]) + 1;
        staty.someoneActive = true;
        staty.x = 0;
        staty.y = 0;
        staty.lastPlayer = 1;
        interBoard();
        interMove();
        matrix *board = gamma_get_matrix(game);
        if(board==NULL)exit(1);
        if(system("clear") == -1)exit(1);
        if(system("clear") == -1)exit(1);
        for(unsigned i=0; i < board->y; i++)
        {
            if(i%2)staty.color = WHITE_COLOR;
            else staty.color = BLUE_COLOR;
            for(unsigned j=0; j < board->x; j++)
            {
                switchColor(staty.color);
                staty.color = (staty.color + 1) % 2;
                uint32_t spacesLeft = staty.idLen;
                if(board->arr[j][board->y - i - 1]==0)
                {
                    printf("*");
                    spacesLeft--;
                }
                else 
                { 
                    printf("%u", board->arr[j][board->y - i - 1]);
                    spacesLeft -= numLen(board->arr[j][board->y - i - 1]);
                }
                while(spacesLeft > 0)
                {
                    printf(" ");
                    spacesLeft--;
                }
            }
            printf("\n");
        }
        switchColor(RED_COLOR);
        for(uint32_t i=1; i <= gamma_get_par(game)->len; i++)
        {
            printf("PLAYER: %u\n", i);
            printf("    result: %"PRIu64" fields\n", gamma_busy_fields(game, i));
        }
        switchColor(YELLOW_COLOR);
        printf("\nThanks for playing!\n");
        switchColor(WHITE_COLOR);
    }
    gamma_delete(game);
    WordsDel(inputer);
    return 0;
}