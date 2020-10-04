#include "game_inter.h"
#include <string.h>

uint32_t numLen(uint32_t x)
{
    if(x == 0) return 1;
    uint32_t wyn = 0;
    while(x > 0)
    {
        wyn++;
        x /= 10;
    }
    return wyn;
}

void switchColor(int x)
{
    switch (x)
    {
        case BLUE_COLOR:
            printf("\033[0;36m");
            break;

        case RED_COLOR:
            printf("\033[1;31m");
            break;

        case GREEN_COLOR:
            printf("\033[0;32m");
            break;

        case YELLOW_COLOR:
            printf("\033[0;33m");
            break;

        case DARK_BLUE_COLOR:
            printf("\033[0;34m");
            break;

        default:
            printf("\033[0m");
    }
}

void interBoard()
{
    matrix *board = gamma_get_matrix(game);
    if(board == NULL)exit(1);
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
            if(i == (board->y - staty.y - 1) && j == staty.x) switchColor(RED_COLOR);
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

    uint64_t bf = gamma_busy_fields(game, staty.lastPlayer);
    uint64_t ff = gamma_free_fields(game, staty.lastPlayer);
    switchColor(DARK_BLUE_COLOR);
    printf("PLAYER: %u\n", staty.lastPlayer);
    switchColor(GREEN_COLOR);
    printf("Busy fields: %"PRIu64"\n", bf);
    printf("Free fields: %"PRIu64"\n", ff);

    if(gamma_golden_possible(game, staty.lastPlayer)) 
    {
        switchColor(YELLOW_COLOR);
        printf("Golden move available\n");
    }

    switchColor(WHITE_COLOR);
    printf("Controls:\n");
    printf("    Arrows: Move\n");
    printf("    Spacebar: Place\n");
    printf("    G: Golden\n");
    printf("    C: Pass\n");
    printf("    CTRL D: End game\n");

}

void interFind()
{
    uint32_t next = staty.lastPlayer+1;
    next %= gamma_get_par(game)->len+1;
    if(next==0) next++;
    while(next != staty.lastPlayer)
    {
        if(gamma_free_fields(game, next)!=0 || gamma_golden_possible(game, next))
        {
            staty.lastPlayer=next;
            return;
        }

        // Wartość bazpiecznie modulowana
        next ++;
        next %= gamma_get_par(game)->len+1;
        if(next==0) next++;
    }
    if(gamma_free_fields(game, next)==0 && !gamma_golden_possible(game, next)) staty.someoneActive = false;
}

void interSwitch(int x)
{
    if(x==1)
    {
        if(staty.y+1<gamma_get_matrix(game)->y)
        {
            staty.y++;
            interBoard();
        }
    }
    else if(x==2)
    {
        if(staty.y!=0)
        {
            staty.y--;
            interBoard();
        }
    }
    else if(x==3)
    {
        if(staty.x+1<gamma_get_matrix(game)->x)
        {
            staty.x++;
            interBoard();
        }
    }
    else if(staty.x!=0)
    {
        staty.x--;
        interBoard();
    }
}

void interMove()
{
    int ar = 0;
    while(staty.someoneActive)
    {
        char c;
        if(read(STDIN_FILENO, &c, 1) == -1)exit(1);
        if(ar == 0 && c == 27)
        {
            ar++;
            continue;
        }
        else if(ar == 1 && c == 91)
        {
            ar++;
            continue;
        }
        else if(ar == 2 && c == 65) interSwitch(1);
        else if(ar == 2 && c == 66) interSwitch(2);
        else if(ar == 2 && c == 67) interSwitch(3);
        else if(ar == 2 && c == 68) interSwitch(4);
        else if(c == 'c' || c == 'C')
        {
            interFind();
            interBoard();
        }
        else if(c == 'g' || c == 'G')
        {
            if(gamma_golden_move(game, staty.lastPlayer, staty.x, staty.y))
            {
                interFind();
                interBoard();
            }
        }
        else if(c == 32)
        {
            if(gamma_move(game, staty.lastPlayer, staty.x, staty.y))
            {
                interFind();
                interBoard();
            }
        }
        else if(c == 4)staty.someoneActive = false;
        ar = 0;
    }
}

void RawModeOFF() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &original) == -1)exit(1);
    printf("\e[?25h");
}

void RawModeON() {
    if (tcgetattr(STDIN_FILENO, &original) == -1) exit(1);
    atexit(RawModeOFF);
    struct termios new = original;
    new.c_lflag &= ~(ECHO | ICANON | ISIG);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &new) == -1) exit(1);
    printf("\e[?25l");
}
