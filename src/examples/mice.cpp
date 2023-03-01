#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>

#include "../lib/cuit.hpp"

struct mevnt {
    unsigned char event, x, y;
};

struct kevnt {
    unsigned char key;
};

int Code1,Code2,Code3,Code4,Code5,Code6;
mevnt m;
kevnt k;

void capture()
{
    for( ; ; )
    {
        Code1 = getchar();
        Code2 = getchar();
        if(Code1 == 27) // ESC
        {
            Code3 = getchar();
            if(Code3 == '[' && Code3 == 'M') // MOUSE EVENT
            {
                m.event = getchar();
                m.x = getchar();
                m.y = getchar();
            }
            else if(Code2 == 'O') // F1 - 4 Spec Keys
            {
                if()
            }
        }   
        else // KEYS
        {
            k.key = Code1;
        }
    }
}

enum keys : short
{
    SOH,
    STX,
    ETX,
    EOT,
    ENQ,
    ACK,
    BEL,
    BS,
    HT,
    LF,
    VT,
    FF,
    CR,
    SO,
    SI,
    DLW,
    DC1,
    DC2,
    DC3,
    DC4,
    NAK,
    SYM,
    ETB,
    CAN,
    EM,
    SUB,
    ESC,
    PS,
    GS,
    RS,
    US
};

int main()
{
    // 27 91 77 67 37 54 MOUSE
    // 27 91 49 53 126 F?

    // SHIFT: 1;2   ALT: 1;3   Ctrl: 1;5

    // setbuf(stdout,NULL); // turn off terninal bufferization

    struct termios oldterm, newterm;
    tcgetattr(STDIN_FILENO, &oldterm ); // get current term attrs
    newterm = oldterm; // set current term attrs to fill new variable
    newterm.c_lflag &= ~( ICANON | ECHO ); // change variable attrs
    tcsetattr(STDIN_FILENO, TCSANOW, &newterm); // set new term attrs

    printf("\e[?1003h"); // SET MOUSE REPORT
    printf("\e[?25l"); // HIDE CURSOR

    window w({15,15,1},{4,4,1});

    int d = 0;

    w.settings.fill = ' ';

    for(;;) {
        d = getchar();
        // if(m.e == 64) // IF LMB PUSHED WRITE
        // {
        //     //printf("\e[%d;%dH\e[%dm###\e[m", m.y-32, m.x-32, rand() % 8 + 30);
        //     printf("\e[222;222H\e[1J"); // CLEAR SCREEN
        //     w.position.setPos(m.x-32,m.y-32,0);
        //     w.show(1);
        //     usleep(1000);
        // }
        // else if(m.e == 96) {
        //     printf("\e[222;222H\e[1J"); // CLEAR SCREEN
        // }
        // else if(m.e == 34) // IF RMB PUSHED EXIT
        //     break;

        printf("%c = (%d)\n", d, d);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldterm); // set old term attrs

    printf("\e[?1003l"); // UNSET MOUSE REPORT

    printf("\e[?25h"); // SHOW CURSOR

    return 0;
}