#include <unistd.h>
#include <signal.h>
#define SECOND 1

void do_nothing();
void do_int();

main() {
    printf("%d vagyok.\n", getpid());
    int i;
    unsigned second = 1;

    signal(SIGINT, do_int);

    for (i=1;i<8;i++) {
        alarm(second);
        signal(SIGALRM, do_nothing);
        printf("%d másodperceig várakoztam.\n",i);
        pause();
    }
}
void do_nothing(){ ;}

void do_int() {
    printf("\nAu, SIGINTet kaptam.\n");
    signal(SIGINT,SIG_IGN);
}