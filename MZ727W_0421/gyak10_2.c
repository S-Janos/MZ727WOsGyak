#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

#define MSGKEY 654321L

struct msgbuf1 {
    long mtype;
    char mtext[256];
} sndbuf, *msgp;


int main()
{
    int id;
    key_t key;
    int flag;
    int rtn, size;
    int ok = 1, count = 1;

    char teszt[256];
    key = MSGKEY;
    flag = 00666 | IPC_CREAT;
    id = msgget( key, flag);
    if ( id == -1) {
        perror("\n Az msgget hívás nem valósult meg.");
        exit(-1);
    }

    do {
        scanf("%s", teszt);
        msgp = &sndbuf;
        msgp->mtype = 1;   			/* tipus = text */
        strcpy(msgp->mtext,teszt);
        size = strlen(msgp->mtext) + 1;	/* az uzenet hossza */

        if(strcmp("exit",teszt) != 0) {
            rtn = msgsnd(id,(struct msgbuf *) msgp, size, flag);
            printf("\n Az %d. msgsnd() ezt adta vissza: %d", count);
            printf("\n A kiküldött üzenet: %s\n", msgp->mtext);
            count++;
        }
        else
        {
            ok = 0;
            printf("\nKilépés...\n");
        }

    } while(ok == 1);
    return 0;
}
