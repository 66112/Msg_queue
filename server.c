#include "comm.h"  //服务器端
int main()
{
	int msgid=CreateMsgQueue();   //创建消息队列
	if(msgid<0){
		perror("create");
		return -1;
	}
	char buf[1024]={0};          //缓冲区
	while(1){
		RecvMsg(msgid,CLIENT_TYPE,buf);   //接收消息（标识码，用户类型，放到缓冲区）
		if(!strcmp(buf,"q")){             //收到q,则退出
			printf("client# %s\n",buf);
			printf("client quit! i quit too!\n");
			break;
		}
		printf("client# %s\n",buf);
		printf("Please stdin!\nserver# ");
		fflush(stdout);
		ssize_t s=read(0,buf,sizeof(buf)-1);  //读输入到缓冲区中
		if(s<0){
			perror("read");
			return -1;
		}
		buf[s-1]=0;
		SendMsg(msgid,SERVER_TYPE,buf);   //发送消息 （标识码，服务器类型，从哪发）
		printf("send done! Wait recv...\n");
	}
	DestoryMsgQueue(msgid);       //销毁消息队列 （标识码）
	return 0;
}

