/*************************************************************************
> File Name: client.c
> Author: Michael Jay
> mail: xuchuanwork@foxmail.com
> Created Time: 2016年07月06日 星期三 14时03分34秒
> Function: 
 ************************************************************************/

#include "client.h"

#define PORT 9888
#define IP "127.0.0.1"
#define BUFFSIZE 1024 


int main(int argc, char* argv[])
{
	int sockfd;
	char cmdbuf[10];
	char buf[BUFFSIZE];
	SAIN servaddr;
	//用于发送命令的数据包结构体
	MSG databuf;
	int nread;

	/*build socket */
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	/*init servaddr */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	//servaddr.sin_port = htons(atoi(argv[2]));
	servaddr.sin_addr.s_addr = inet_addr(IP);
	//servaddr.sin_addr.s_addr = inet_addr(argv[1]);

	printMenu();
	Connect(sockfd, (SA*) &servaddr, sizeof(servaddr));
	printf("与服务器连接成功。sockfd = %d \n", sockfd);

	/*  send message to server */
	while(1)
	{
		printf("\ninput>");
		//获取用户命令
		fgets(cmdbuf, BUFFSIZE, stdin);
		cmdbuf[strlen(cmdbuf)-1] = 0;

		switch( cmd2num(cmdbuf) ){

			case LIST:
				/*		printf("与服务器连接成功。sockfd = %d \n", sockfd);
						databuf.sockfd = sockfd;
						databuf.msg = LIST;
						printf("init :sockfd = %d,  databuf->msg= %d \n", databuf.sockfd, databuf.msg);
						printf("databuf size: %d\n", sizeof(databuf));
						Send(sockfd, &databuf, sizeof(databuf), 0 );
				*/
						cli_list(sockfd, &databuf);
						break;
			case DLOAD:	cli_download(sockfd, &databuf);
						break;
			case ULOAD:	cli_upload(sockfd, &databuf);
						break;
			case HELP:	cli_help();
						break;
			case QUIT:	close(sockfd);
						printf("QUITING...\n");
						exit(0);
						break;
			default:	printf("命令错误，如需帮助请输入\"help\" \n");	
						continue;
		}

		bzero(cmdbuf, sizeof(cmdbuf));

		//接收server的消息
		if( (nread = Recv(sockfd, &databuf, sizeof(databuf), 0) ) > 0)
		{
			printf("sockfd = %d, read = %d \n", sockfd, nread);
			printf("respose: sockfd = %d, sig = %d.\n", databuf.sockfd, databuf.sig);
		}

	}
	
	printf("Clinet Exit.\n");
	close(sockfd);
}


//print menu for user 
void printMenu()
{
	system("clear");
	printf("************************\n");
	printf("* list:	 查看当前目录  *\n");
	printf("* dnld:  下载文件      *\n");
	printf("* upld:	 上传文件      *\n");
	printf("* help:  查看帮助信息  *\n");
	printf("* quit:	 退出程序      *\n");
	printf("************************\n \n");
}

//将用户输入的命令转换成宏定义的消息信号
int cmd2num(char *cmdbuf)
{
	if(strcmp("list", cmdbuf) == 0)
		return LIST;
	else if(strcmp("dnld", cmdbuf) == 0)
		return DLOAD;
	else if(strcmp("upld", cmdbuf) == 0)
		return ULOAD;
	else if(strcmp("quit", cmdbuf) == 0)
		return QUIT;
	else if(strcmp("help", cmdbuf) == 0)
		return HELP;
	else
		return FAIL;
}

int cli_list(int sockfd, MSG* databuf)
{
	printf("list.....\n");

	//问题在这里，由于这里传入的参数就是一个地址databuf，因此不需要在取地址！！！
	//Send(sockfd, &databuf, sizeof(databuf), 0 );
	Send(sockfd, databuf, sizeof(databuf), 0 );

	printf("命令发送成功, 等待服务器回复...\n");

	//这里需要判断服务器的回复，并根据回复返回
	

	
	return SUCCESS;
}

int cli_download(int sockfd, MSG* data)
{
	printf("下载\n");

	return 0;
}

int cli_upload(int sockfd, MSG* data)
{
	printf("上传\n");
	return 0;

}

//打印帮助信息
int cli_help()
{
	printMenu();
}

void initMSG(MSG *databuf)
{
	databuf->sockfd = -1;
	databuf->sig = -1;
	databuf->msgbuf = NULL;
}
