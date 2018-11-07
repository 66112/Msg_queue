#include "comm.h"   //用户端
int main()
{
	int msgid = OpenMsgQueue();    //打开消息队列
	char buf[1024]={0};            //缓冲区
	while(1){
		printf("Please stdin!\nclient# ");
		fflush(stdout);
		ssize_t s=read(0,buf,sizeof(buf)-1);  //从标准输入读到缓冲区
		if(s<0){
			perror("read");
			return -1;
		}
		buf[s-1]=0;  //把换行符覆盖掉
		SendMsg(msgid,CLIENT_TYPE,buf);  //（标识码，用户类型，内容）
		if(!strcmp(buf,"q")){            //如果输入q,则用户端退出 
			printf("i will quit!\n");
			break;
		}
		printf("send done , wait recv...\n");
		
		RecvMsg(msgid,SERVER_TYPE,buf);  //（标识码，服务器类型，放到缓冲区）
		printf("server# %s\n",buf);
		
	}
	return 0;
}





