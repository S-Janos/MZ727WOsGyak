#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>


void handle_sigint(int sig)
{
    signal(SIGTERM,SIG_IGN);
    printf("\n%d jelzést kaptam.\n", sig);
    _exit(2);
}

int main()
{
    signal(SIGINT, handle_sigint);
    char s[1024];
    char t[1024];
    char name[] = "output";
    FILE *fp;
    fp = fopen("szavak", "w");
    int fd;
    int sorszam = 1;
    while(1) {
        fd = open(name,O_RDONLY);
        if(fd == -1) {
            printf("Nem létezik \"%s\" nevű fájl.\n", name);
            return 1;
        }
        else {
            strcpy(t, s);
            read(fd,s,sizeof(s));
            if (strcmp(s, t) != 0) {
                printf("\n%d. %s", sorszam, s);
                fprintf(fp, "%d. %s\n", sorszam, s);
                sorszam++;
            }
            close(fd);
        }
    }
}