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

void catch_signal(int signal) { if(signal == SIGINT || signal == SIGQUIT) exit(0);close(fd); }

int main(int argc, char* argv[])
{
    char* path = "/dev/input/by-path/pci-0000:00:14.0-usb-0:4:1.0-event-kbd";-
    fd_set rfds; 
    int res;
    int version = -1, ioret = -1; 
    unsigned numevs, c;
    unsigned char read_buffer[sizeof(struct input_event)*3]; /* max 3 events per read */
    struct input_event *currev;
    char device_name[1024];

    struct sigaction sighandler;
    memset(&sighandler, 0, sizeof(sighandler));
    sighandler.sa_handler = catch_signal;
    sigaction(SIGINT, &sighandler, NULL);//CTRL-C exit
    sigaction(SIGQUIT, &sighandler, NULL);

    /*if ( argc < 2 ) 
    { 
        fprintf(stderr, "Device needed\n");
        return -1;
    }*/

    FD_ZERO(&rfds);
    fd = open(path, O_RDONLY | O_NONBLOCK);
    if (fd == -1) 
    {
        fprintf(stderr, "unable to read from mice\n");
        return -1;
    }
    
    ioret = ioctl(fd, EVIOCGVERSION, &version);
    ioret = ioctl(fd, EVIOCGNAME(sizeof(device_name)), device_name);
    getchar();
    ioret = ioctl(fd, EVIOCGRAB, (void*)1);//grab input from kbd
    ioret = ioctl(fd, EVIOCGRAB, NULL);//ungrab input from kbd
    
    if (ioret == -1) 
    {
        perror("ioctl()");
    }
    fprintf(stdout, "ver: %d, ret = %d\n", version, ioret);
    printf("device name is: %s\n", device_name);
    
    FD_SET(fd, &rfds);
    while(1)
    {
        res = select(fd + 1, &rfds, NULL, NULL, NULL);
        if (res == -1 && errno == EINTR) 
        {
            continue;
        }
        if (res == -1) 
        {
            perror("select() failed");
            fprintf(stderr, "failed to select, fd is %d\n", fd);
            return -1;
        }
        if (FD_ISSET(fd, &rfds)) //if key released
        {
            fprintf(stdout, "got some data\n");
            res = read(fd, read_buffer, sizeof(read_buffer));
            if (res == -1) 
            {
                fprintf(stderr, "error reading data\n");
                return -1;
            }
            fprintf(stdout, "got %d bytes\n", res);
            numevs = ( res / sizeof(struct input_event) ); /* get how many input events we got */
            fprintf(stdout, "got %u events\n", numevs);
            for (c = 0; c < numevs; c++) 
            {
                currev = (struct input_event *)(read_buffer + (sizeof(struct input_event) * c));
                fprintf(stdout, "event type = %hd, code = %hd, value = %d\n", currev->type, currev->code, currev->value);
            }
        } 
        else 
        {
            fprintf(stderr, "odd ... no data and we only listen in 1 fd\n");
        }
    }
    return 0;
}