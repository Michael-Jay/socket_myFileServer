/*************************************************************************
> File Name: server.c
> Author: Michael Jay
> mail: xuchuanwork@foxmail.com
> Created Time: 2016年07月07日 星期四 21时56分06秒
> Function: 
	基于TCP的文件服务器
	list/help/download/upload/
 ************************************************************************/
#include "server.h"

#define BUFFSIZE 4096 
#define IP "127.0.0.1"
#define PORT 9888


void clearZ(int sig)
{
	while(waitpid(-1, NULL, WNOHANG)>0);
	return;
}

	
int main(int argc, char* argv[])
{
	int listenfd,connfd,nread;
	SAIN servaddr, cliaddr;
	socklen_t clilen;
	MSG databuf;

	listenfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr(IP);

	Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
	
	Listen(listenfd, 10);

	//忽略SIGCHILD，避免僵尸
	signal(SIGCHLD, clearZ);

	clilen = sizeof(cliaddr);

	while(1)
	{
		printf("parent: Waiting....\n");
		connfd = Accept(listenfd, (SA*) &cliaddr, &clilen);
		printf("Connection from [%s:%d] \n", inet_ntoa(cliaddr.sin_addr),
				ntohs(cliaddr.sin_port));

		while(1)
		{
			if((nread = Recv(connfd, &databuf, sizeof(databuf), 0)) >0)
			{
				printf("recv: sockfd = %d, sig = %d.\n", databuf.sockfd, databuf.sig);
				int recvsig  = (*databuf).sig;
				switch (recvsig){
					case LIST:	cmdList(MSG* databuf, int connfd);
								break;
					case DLOAD:	cmdDownload();
								break;
					case ULOAD:	cmdUpload();
								break;
					case HELP:	cmdHelp();
								break;
					case QUIT: cmdQuit();
								break;
				}
				
			}

		}
		sleep(1);
	}

	close(connfd);
	close(listenfd);
	
    exit(0);
}


void cmdList(MSG *databuf, int connfd)
{
	printf("list cmd..............\n");
	//读取当前目录，如果打开成功，将返回值databuf->sig=SUCCESS
	//然后将读取的目录信息发送给client
	
	struct dirent *dirbuf;	//用于保存打开的目录结构体
	dirbuf = readdir("\.");	//先打开当前目录把
	if( dirbuf == NULL)
	{
		perror("opendir");
		initMSG(databuf);
		databuf->sig = FAIL;
		
		Send(connfd, databuf, sizeof(databuf), 0);
		printf("warning msg had sent to client...\n");
		return;
	}
	else
	{
		initMSG(databuf);
		databuf->sockfd = connfd;
		databuf->sig = SUCCESS;
		databuf->msg = &dirbuf;

		Send(connfd, databuf, sizeof(databuf), 0);
		printf("Msg had sent to client...\n");
		return;
	}
}

void cmdHelp()
{
	printf("Help cmd\n");
}

void cmdDownload()
{
	printf("down cmd\n");
}

void cmdUpload()
{
	printf("up cmd\n");
}

void cmdQuit()
{
	printf("quit cmd\n");
}

void initMSG(MSG *databuf)
{
	databuf->sockfd = -1;
	databuf->sig = -1;
	data->msgbuf = NULL;
}
