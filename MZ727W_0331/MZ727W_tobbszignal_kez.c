#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handleSignals(int signum);

int main() {
    void(*sigHandlerInterrupt)(int);
    void(*sigHandlerQuit)(int);
    void(*sigHandlerReturn)(int);
    sigHandlerInterrupt = sigHandlerQuit = handleSignals;
    sigHandlerReturn = signal(SIGINT, sigHandlerInterrupt);

    if (sigHandlerReturn == SIG_ERR) {
        perror("Something happened");
        return 1;
    }

    sigHandlerReturn = signal(SIGQUIT, sigHandlerQuit);

    if (sigHandlerReturn == SIG_ERR) {
        perror("Something happened");
        return 1;
    }
    for(;;) {
        printf("\nA program leállításához végezze el a következő lépéseket: \n");
        printf("1. Nyisson meg egy másik terminál ablakot!\n");
        printf("2. Futtassa a \"kill %d\" paracnsot! \n", getpid());
        sleep(10);
    }
    return 0;
}

void handleSignals(int signum) {
    switch(signum) {
        case SIGINT:
            printf("\n CTRL+C vagyok.\n");
            signal(SIGINT, SIG_DFL);
            break;
        case SIGQUIT:
            printf("SIGQUIT vagyok.\n");
            break;
        default:
            printf("\nFogadott jel száma: %d\n", signum);
            break;
    }
}