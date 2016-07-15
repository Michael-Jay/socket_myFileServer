/*************************************************************************
> File Name: server.h
> Author: Michael Jay
> mail: xuchuanwork@foxmail.com
> Created Time: 2016年07月11日 星期一 20时04分02秒
> Function: 
 ************************************************************************/

#ifndef _SERVER_H
#define _SERVER_H

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

void clearZ(int sig);	//处理僵尸

void initMSG(MSG* databuf);
void cmdList(char *databuf, int connfd);
void cmdHelp();
void cmdDownload();
void cmdUpload();
void cmdQuit();

#endif
