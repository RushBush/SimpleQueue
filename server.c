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

    bufp.type=1;
    strncpy(bufp.msg,"Hello!",15);

    key=ftok("server",'a');

    if ((msgid=msgget(key,0666|IPC_CREAT))<0)
    {
        printf("Can't create queue\n");
        return -1;
    }

    if (0!=msgsnd(msgid,&bufp,15*sizeof(char),IPC_NOWAIT))
    {
        printf("Can't send message\n");
        return -2;
    }
    else
    {
        printf("Send: %s\n",bufp.msg);
    }

    msgrcv(msgid,&rec,15*sizeof(char),2,0);

    printf("Receive: %s\n",rec.msg);


    return 0;
}
