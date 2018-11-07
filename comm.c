#include "comm.h"
int CreateMsgQueue()      
{
	return CommGetMsgQueue(IPC_CREAT | IPC_EXCL | 0666);   //不存在,则创建，若存在，则错误
}

int OpenMsgQueue()
{
	return CommGetMsgQueue(IPC_CREAT);   //消息队列不存在，则创建，若存在，则打开它
}

int CommGetMsgQueue(int flags)
{
	key_t _key=ftok(PATHNAME,PROJ_ID);
	if(_key<0){
		perror("ftok");
		return -1;
	} 
	int msgid=msgget(_key,flags);    //返回消息队列的标识码
	if(msgid<0){
		perror("msgget");
		return -1;
	}
	return msgid;
}

int SendMsg(int msgid,long whotype,char* msg)  //发送消息，（标识码，什么类型，消息内容）
{
	struct msgbuf buf;       //消息结构体
	buf.mtype=whotype;       
	strcpy(buf.mtext,msg);
	if(msgsnd(msgid,(void*)&buf,sizeof(buf.mtext),0)<0){  //（标识码，消息结构体，消息大小，缺省为0）
		perror("send");
		return -1;
	}
	return 0;
}
int RecvMsg(int msgid,long recvType,char* out)  //接收消息，（标识码，接收类型，存到哪）
{
	struct msgbuf buf;
	ssize_t s=msgrcv(msgid,(void*)&buf,sizeof(buf.mtext),recvType,0);  //（标识码，消息结构体，消息大小，消息类型，缺省为0）
	if(s<0){
		perror("msgrcv");
		return -1;
	}
	strcpy(out,buf.mtext);
	return 0;
}
void DestoryMsgQueue(int msgid)
{
	if(msgctl(msgid,IPC_RMID,NULL)<0){   //（标识码，删除指令，NULL）
		perror("msgctl");
	}
}
