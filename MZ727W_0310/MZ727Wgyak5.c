#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    int pid;
    int status;

    if ((pid = fork()) < 0) {
        perror("Fork error");
        exit(7);
    }
    else if (pid == 0)
       abort();
    
    if(wait(&status)!=pid)
        perror("Wait error");
    
    if(WIFEXITED(status))
        printf("Successful");

    return 0;
}