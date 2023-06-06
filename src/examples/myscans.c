#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <linux/kd.h>
#include <linux/keyboard.h>
#include <sys/ioctl.h>

int fd;
struct termios old;
int oldkbmode;

static void getMode(void)
{
    if(ioctl(fd,KDGKBMODE,&oldkbmode)) perror("KDGKBMODE");
    
    if(oldkbmode == K_RAW)            printf("K_RAW");
    else if(oldkbmode == K_XLATE)     printf("K_XLATE");
    else if(oldkbmode == K_MEDIUMRAW) printf("K_MEDIUMRAW");
    else if(oldkbmode == K_UNICODE)   printf("K_UNICODE");
    else                              printf("UNKNOWN");

    printf("\n");
}

static void cleanup(void)
{
    if(ioctl(fd,KDSKBMODE,oldkbmode)) perror("KDSKBMODE");
    if(tcsetattr(fd,0,&old) == -1) perror("tcsetattr");
    close(fd);
}

static int
isConsole(int fd) {
	char arg;
	arg = 0;
	return (ioctl(fd, KDGKBTYPE, &arg) == 0
		&& ((arg == KB_101) || (arg == KB_84)));
}

static int openConsole(const char* fname)
{
    int fd;
	fd = open(fname, O_RDWR);
	if (fd < 0 && errno == EACCES)
		fd = open(fname, O_WRONLY);
	if (fd < 0 && errno == EACCES)
		fd = open(fname, O_RDONLY);
	if (fd < 0)
		return -1;
	if (!isConsole(fd)) {
		close(fd);
		return -1;
	}
	return fd;
}

int getFd(const char* fname)
{
    int fd;
	if (fname) {
		fd = openConsole(fname);
		if (fd >= 0)
			return fd;
		fprintf(stderr, "Couldnt open %s\n", fname);
		exit(1);
	}
	fd = openConsole("/dev/tty");
	if (fd >= 0)
		return fd;
	fd = openConsole("/dev/tty0");
	if (fd >= 0)
		return fd;
	fd = openConsole("/dev/vc/0");
	if (fd >= 0)
		return fd;
	fd = openConsole("/dev/console");
	if (fd >= 0)
		return fd;
	for (fd = 0; fd < 3; fd++)
		if (isConsole(fd))
			return fd;
	fprintf(stderr, "Couldnt get a file descriptor referring to the console\n");
	exit(1);		/* total failure */
}

int main()
{
    struct termios new;
    unsigned char buffer[16];
    int i,n;
    
    fd = getFd(NULL);
    getMode();

    if(tcgetattr(fd, &old) == -1) perror("tcgetattr"); // GET CURRENT OPTIONS
    if(tcgetattr(fd, &new) == -1) perror("tcgetattr"); // GET CURRENT OPTIONS

    new.c_lflag &= ~ (ICANON | ECHO | ISIG); // DELETE FLAGS
	new.c_iflag = 0; // DELETE ALL
	new.c_cc[VMIN] = sizeof(buffer); // SET 
	new.c_cc[VTIME] = 1;	/* 0.1 sec intercharacter timeout */

    if(tcsetattr(fd,TCSAFLUSH,&new) == -1) perror("tcsetattr"); // изменяет значения, когда текущий вывод завершен, но отбрасывает любой ввод, доступный в текущий момент и все еще не возвращенный вызовом read.

    if(ioctl(fd, KDSKBMODE, K_RAW)) perror("KDSKBMODE"); /* Raw (scancode) mode */

    printf("Press any key...\n");
    
    for(;;)
    {
        n = read(fd,buffer,sizeof(buffer));
        for(i = 0; i < n; ++i) printf("0x%02x ",buffer[i]);
        printf("\n"); // MUST HAVE
    }

    cleanup();

    return 0;
}