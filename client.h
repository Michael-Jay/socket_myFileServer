/*************************************************************************
> File Name: client.h
> Author: Michael Jay
> mail: xuchuanwork@foxmail.com
> Created Time: 2016年07月12日 星期二 10时56分49秒
> Function: 
************************************************************************/
#ifndef _CLIENT_H
#define _CLIENT_H

#include "myhead.h"

//通用消息信号
#define LIST	1
#define DLOAD	2
#define ULOAD	3

#define HELP	8
#define QUIT	9
#define SUCCESS	10
#define FAIL	11

//交互数据包
typedef struct _tag_dataPackage{
	int sockfd;	//通信通道
	int sig;	//宏定义的消息信号
	void *msgbuf;	//填充附加的信息内容
}MSG;


//print menu for user 
void printMenu();

//将用户输入的命令转换成宏定义的消息信号
int cmd2num(char *cmdbuf);

void initMSG(MSG* databuf);

int cli_list(int sockfd, MSG* databuf);

int cli_download(int sockfd, MSG* databuf);

int cli_upload(int sockfd, MSG* databuf);

//打印帮助信息
int cli_help();

#endif
