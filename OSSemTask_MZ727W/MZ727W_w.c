#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<signal.h>


void SignalKezelo(int sig) {
    signal(SIGTERM,SIG_IGN);
    printf("\n% jelzést kaptam.\n", sig);
    fflush(stdout);
    signal(SIGTERM, SIG_DFL);
    _exit(2);
}

int main(){
    int fd;
    signal(SIGINT, SignalKezelo);
    char szoveg[256];
    char name[] = "output";
    mkfifo(name, S_IWUSR | S_IRUSR );

    while(1) {
        scanf("%s", szoveg);
        fd = open(name, O_WRONLY);
        write(fd, szoveg, 12);
        close(fd);
    }
}