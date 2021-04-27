/*	msgrcv.c	*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#define MSGKEY 654321L

struct msgbuf1 {
    long mtype;
    char mtext[512];
} rcvbuf, *msgp;		/* message buffer es pointere */

struct msqid_ds ds, *buf;	/* uzenetsorhoz asszocialt struktura
					 es pointere*/

main()
{
    int id;		/* uzenetsor azonosito */
    key_t key;		/* kulcs az uzenetsorhoz */
    int type, flag;	/* tipus, flag */
    int rtn, size;		/* return es meret */

    key = MSGKEY;		/* beallitom a kulcsot */
    flag = 00666 | IPC_CREAT | MSG_NOERROR;

    id = msgget(key, flag);
    if (id == -1) {
        perror("\n A hivas nem valosult meg");
        exit(-1);
    }
    printf("\n Az id: %d", id);

    msgp = &rcvbuf;		/* uzenetfogado buffer cime */
    buf = &ds;		/* uzenetsor jellemzo adataihoz */
    size = 20;		/* max hossz */
    type = 0;		/* minden tipust varok */
    rtn = msgctl(id, IPC_STAT, buf); /* uzenetsor adatokat lekerdezem */
    printf("\n Az uzenetek szama: %d",buf->msg_qnum);

    while (buf->msg_qnum) {		/* van-e uzenet?*/
        /* veszem a kovetkezo uzenetet: */
        rtn = msgrcv(id, (struct msgbuf *)msgp, size, type, flag);
        printf("\n Az rtn: %d,  a vett uzenet:%s\n",rtn, msgp->mtext);
        rtn = msgctl(id, IPC_STAT, buf); /* uzenetsor adatokat lekerdezem,
					benne azt is, hany uzenet van meg */
    }
    exit (0);
}
