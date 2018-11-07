#ifndef __COMM_H__
#define __COMM_H__ 
#include <stdio.h>
#include <sys/ipc.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#define PATHNAME "."
#define PROJ_ID 0x6666

#define SERVER_TYPE 1
#define CLIENT_TYPE 2

struct msgbuf{
	long mtype;
	char mtext[1024];
};

int CreateMsgQueue();
int OpenMsgQueue();
int CommGetMsgQueue(int flags);
int SendMsg(int msgid,long whotype,char* msg);
int RecvMsg(int msgid,long recvType,char* out);
void DestoryMsgQueue(int msgid);

#endif  //__COMM_H__
