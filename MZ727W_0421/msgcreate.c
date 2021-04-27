#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

#define MSGKEY 654321L

struct msgbuf1 {
    long mtype;
    char mtext[512];
} sndbuf, *msgp;		/* message buffer es pointere */

int main()
{
    int id;		/* uzenetsor azonosito */
    key_t key;		/* kulcs az uzenetsorhoz */
    int flag;		/* flag a kreaciohoz, uzenetkuldeshez */
    int rtn, size;		/* return es meret */

    key = MSGKEY;
    flag = 00666 | IPC_CREAT;
    id = msgget( key, flag);
    if ( id == -1) {
        perror("\n Az msgget hivas nem valósult meg.");
        exit(-1);
    }

    printf("\n A msgid %d, %x:", id, id);

    msgp = &sndbuf;
    msgp->mtype = 1;   			/* tipus = text */
    strcpy(msgp->mtext,"Üzenet vagyok.");
    size = strlen(msgp->mtext) + 1;	/* az uzenet hossza */

    /* es elkuldom: */

    rtn = msgsnd(id,(struct msgbuf *) msgp, size, flag);
    printf("\n Az 1. msgsnd() ezt adta vissza: %d", rtn);
    printf("\n A kiküldött üzenet: %s", msgp->mtext);

    strcpy(msgp->mtext,"Én is.");
    size = strlen(msgp->mtext) + 1;
    rtn = msgsnd(id,(struct msgbuf *) msgp, size, flag);
    printf("\n A 2. msgsnd() ezt adta vissza: %d", rtn);
    printf("\n Az üzenet: %s", msgp->mtext);
    printf("\n");

    exit(0);
}
