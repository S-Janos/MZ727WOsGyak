//
// Created by Szamurajpalanta on 2021. 04. 19..
//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() {
    int child;

    mkfifo("MZ727W", S_IRUSR | S_IWUSR);
    child = fork();

    if(child > 0) {
        char s[1024];
        int fd;

        fd = open("MZ727W", O_RDONLY);
        read(fd, s, sizeof(s));
        printf("%s", s);
        close(fd);
        unlink("MZ727W");

    } else if(child == 0) {
        int fd = open("MZ727W", O_WRONLY);
        write(fd, "Simonyák János\n", 24);
        close(fd);

    }
    return 0;
}