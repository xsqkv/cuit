#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <linux/kd.h> // KDSKBMODE K_RAW K_XLATE
#include <sys/ioctl.h>
#include <sys/types.h>

//#include "../lib/cuit.hpp"

struct mevnt { // MOUSE EVENT
    unsigned char event, x, y;
};

struct kevnt { // KEY EVENT
    unsigned char key;
};

struct skevnt { // SPECIAL KEY EVENT
    unsigned char specKey;
};

int Code1,Code2,Code3,Code4,Code5,Code6;
mevnt m;
kevnt k;
skevnt s;

enum specKeys : short
{
    NUL = 0,
    SOH = 1,
    STX = 2,
    ETX = 3,
    EOT = 4,
    ENQ = 5,
    ACK = 6,
    BEL = 7,
    BS  = 8,
    HT  = 9,
    LF  = 10,
    VT  = 11,
    FF  = 12,
    CR  = 13,
    SO  = 14,
    SI  = 15,
    DLE = 16,
    DC1 = 17,
    DC2 = 18,
    DC3 = 19,
    DC4 = 20,
    NAK = 21,
    SYN = 22,
    ETB = 23,
    CAN = 24,
    EM  = 25,
    SUB = 26,
    ESC = 27,
    FS  = 28,
    GS  = 29,
    RS  = 30,
    US  = 31,

    DEL = 127,

    SPACE,
    //ESC,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    INSERT,
    DELETE,
    HOME,
    END,
    PAGE_UP,
    PAGE_DOWN,
    TAB,
    BACKSPACE,
    ENTER,
    FN,
    MOD,
    UP,
    DOWN,
    RIGHT,
    LEFT,

    SHIFT_,
    ALT_,
    CONTROL_,
    CONTROL_SHIFT,
};

#define CONTROL_SPACE NUL
#define CONTROL_A     SOH
#define CONTROL_B     STX
#define CONTROL_C     ETX
#define CONTROL_D     EOT
#define CONTROL_E     ENQ
#define CONTROL_F     ACK
#define CONTROL_G     BEL
#define CONTROL_H     BS 
#define CONTROL_I     HT 
#define CONTROL_J     LF 
#define CONTROL_K     VT 
#define CONTROL_L     FF 
#define CONTROL_M     CR 
#define CONTROL_N     SO 
#define CONTROL_O     SI 
#define CONTROL_P     DLE
#define CONTROL_Q     DC1
#define CONTROL_R     DC2
#define CONTROL_S     DC3
#define CONTROL_T     DC4
#define CONTROL_U     NAK
#define CONTROL_V     SYN
#define CONTROL_W     ETB
#define CONTROL_X     CAN
#define CONTROL_Y     EM 
#define CONTROL_Z     SUB
#define CONTROL_3     ESC
#define CONTROL_4     FS 
#define CONTROL_5     GS 
#define CONTROL_6     RS 
#define CONTROL_7     US
#define CONTROL_8     DEL

void capture()
{
    for( ; ; )
    {
        Code1 = getchar(); // GET FIRST CHAR
        if(Code1 == 27) // ESC
        {
            Code2 = getchar();
            if(Code2 == '[')
            { 
                Code3 = getchar();
                if(Code3 == 'M') // MOUSE EVENT
                {
                    Code3 = getchar();
                    m.event = getchar();
                    m.x = getchar();
                    m.y = getchar();
                }
                else if(Code3 == '1')
                {

                }
            }
            else if(Code2 == 'O') // F1-4 specKeys
            {
                if(Code3 == 'P')      s.specKey = specKeys::F1;
                else if(Code3 == 'Q') s.specKey = specKeys::F2;
                else if(Code3 == 'R') s.specKey = specKeys::F3;
                else if(Code3 == 'S') s.specKey = specKeys::F4;
            }
            else if(Code2 == '1') // F5-8 specKeys
            {
                if(Code3 == '5')      s.specKey = specKeys::F5;
                else if(Code3 == '7') s.specKey = specKeys::F6;
                else if(Code3 == '8') s.specKey = specKeys::F7;
                else if(Code3 == '9') s.specKey = specKeys::F8;
            }
            else if(Code2 == '2') // F9-12 specKeys
            {
                if(Code3 == '0')      s.specKey = specKeys::F9;
                else if(Code3 == '1') s.specKey = specKeys::F10;
                else if(Code3 == '3') s.specKey = specKeys::F11;
                else if(Code3 == '4') s.specKey = specKeys::F12;
            }
        }   
        else k.key = Code1; // KEYS
    }
}

int main()
{
    // setbuf(stdout,NULL); // turn off terninal bufferization

    struct termios oldterm, newterm;
    tcgetattr(STDIN_FILENO, &oldterm ); // get current term attrs
    newterm = oldterm; // set current term attrs to fill new variable
    newterm.c_lflag &= ~( ICANON | ECHO | ISIG); // change variable attrs
    tcsetattr(STDIN_FILENO, TCSANOW, &newterm); // set new term attrs

    printf("\e[?1003h"); // SET MOUSE REPORT
    printf("\e[?25l"); // HIDE CURSOR

    ioctl(0, KDSKBMODE, K_RAW); // A program can request the raw scancodes

    //window w({15,15,1},{4,4,1});
    //w.settings.fill = ' ';

    unsigned char buffer;

    unsigned long long int code = 0;

    for(;;) {
        read(STDIN_FILENO,&buffer,1);
        printf("%c = %d\n", buffer, buffer);
        if(buffer == CONTROL_C) break;

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
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldterm); // set old term attrs

    printf("\e[?1003l"); // UNSET MOUSE REPORT

    printf("\e[?25h"); // SHOW CURSOR

    ioctl(0, KDSKBMODE, K_XLATE); // Unset raw mode

    //atexit();

    return 0;
}