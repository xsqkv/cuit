#include<stdio.h>

int main()
{
    const size_t buff_sz = 512;
    

    // printf("\e="); // application keypad mode
    // printf("\e>"); // number keypad mode

    setbuf(stdin,NULL); // turn off terninal bufferization

    printf("\e[?1003h");

    for(;;)
    {
        int r = getchar();

        if(r == '\n') break;

        char buff[buff_sz];
        
        snprintf(buff,buff_sz,r);
    }

    printf("\e[?1003l");

    return 0;
}