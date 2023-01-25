#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <linux/input.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

static int fd;

void catch_signal(int signal) 
{ 
    if(signal == SIGINT || signal == SIGQUIT)
    {
        printf("\n\nProcess terminated by user.\n");
        exit(0);
        close(fd); 
    }
}

int main(int argc, char* argv[])
{
    const char* path = "/dev/input/by-path/pci-0000:00:14.0-usb-0:4:1.0-event-kbd";//path to kbd file
    fd_set rfds;//for select
    int res,version=-1,ioret=-1;
    unsigned numevs, c;
    unsigned char buffer[sizeof(struct input_event)*3];
    struct input_event* currev;
    char* device_name;
    struct sigaction sighandler;
    memset(&sighandler,0,sizeof(sighandler));
    sighandler.sa_handler = catch_signal;
    sigaction(SIGINT, &sighandler, NULL);
    sigaction(SIGQUIT, &sighandler, NULL);
    
    FD_ZERO(&rfds);
    fd = open(path, O_RDONLY | O_NONBLOCK);
    if(fd == -1) { printf("unable to read from mice\n");exit(-1); }

    ioret = ioctl(fd, EVIOCGNAME(sizeof(device_name)),device_name);
    ioret = ioctl(fd,EVIOCGRAB, 1);
    ioret = ioctl(fd,EVIOCGRAB, 0);

    if(ioret == -1) { printf("ioctl error\n"); exit(-1); }

    FD_SET(fd, &rfds);

    for(;;)
    {
        res = select(fd+1,&rfds,NULL,NULL,NULL);
        if(res == -1 && errno == EINTR) {continue;}
        else if(res == -1)
        {
            printf("res error\n");
            return -1;
        }
        if(FD_ISSET(fd,&rfds))
        {
            res = read(fd,buffer, sizeof(buffer));
            if(res == -1)
            {
                printf("error reading data\n");
                return -1;
            }
            numevs = (res / sizeof(struct input_event));
            for(c=0; c<numevs; c++)
            {
                currev = (struct input_event*)(buffer+(sizeof(struct input_event)*c));
                printf("Key %d: value = %d\n",currev->code,currev->value);
            }
        }
        else
        {
            printf("odd ... no data and we only listen in 1 fd\n");
        }
    }

    return 0;
}