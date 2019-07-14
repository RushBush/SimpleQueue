#include <stdio.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>

struct msgbuf
{
    long type;
    char msg[15];
};

int main()
{
    int msgid;
    key_t key;
    struct msgbuf bufp,rec;
    bufp.type=2;
    strncpy(bufp.msg,"Hi!",15);

    key=ftok("server",'a');

    msgid=msgget(key,0);


    msgrcv(msgid,&rec,15*sizeof(char),1,IPC_NOWAIT);
    printf("Receive: %s\n", rec.msg );


    msgsnd(msgid,&bufp,15*sizeof(char),0);
    printf("Send: %s\n",bufp.msg);
    


    return 0;
}
