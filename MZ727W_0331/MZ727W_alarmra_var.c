#include <unistd.h>
#include <signal.h>

void do_nothing();

main () {
	signal(SIGALRM, do_nothing);
	printf("%d vagyok.\n", getpid());
	pause();
    printf("SIGALRM érkezett.\n");
}

void do_nothing(){ ;}