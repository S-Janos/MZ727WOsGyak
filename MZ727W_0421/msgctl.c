/* 	msgctl.c 	 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

#define MSGKEY 654321L

main()
{
    int id, flag, rtn;
    key_t key;
    key = MSGKEY;
    flag = 00666 | IPC_CREAT;
    id = msgget(key, flag);

    rtn = msgctl(id, IPC_RMID, NULL);	/* torlom az uzenetsort */
    printf ("\nVisszatért: %d\n", rtn);

    exit(0);
}
