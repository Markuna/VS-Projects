#include<stdio.h>
#include<WINSOCK.H>
#pragma comment(lib,"Ws2_32.lib")
#include<iostream>

using namespace std;

void main()
{
	WORD wVersionRequested;  //定义winsock版本号
	WSADATA wsaData;         //存放winsock信息

	int err;                 //接收加载Winsock时WSAStartup函数的返回值，用于判断是否加载成功
	wVersionRequested = MAKEWORD(1, 1);  //定义版本号，高字节与低字节均为1

	err = WSAStartup(wVersionRequested, &wsaData);//加载Winsock
	if (err != 0) { return;}//加载Winsock失败，程序返回

	//用户不能接收由wVersion返回的版本，调用WSACleanup清除对Winsock的加载
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return;
	}
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//建立一个服务器流式套接字

	SOCKADDR_IN addrSrv;   //定义一个地址结构体，用于存放服务器地址信息
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//设置地址信息
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(789);//设置服务器监听端口

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//是服务器套接字与地址信息绑定

	listen(sockSrv, 5);//开启服务器监听程序
	SOCKADDR_IN addrClient;//设置客户端地址结构体
	int len = sizeof(SOCKADDR);

	int connetnumber = 0;//定义连接次数
	while (1)//循环处理客户端的请求
	{
		//开启接收程序，当监听到连接时，获取连接信息，返回套接字信息
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		if (sockConn < 0)//判断连接是否成功
		{
			printf("Failed accept!");
			continue;
		}
		else
		{
			printf("Accept a connection:\n");
			connetnumber++;
		}
		char recvBuf[50];//定义接收缓冲区
		recv(sockConn, recvBuf, 50, 0);//接收从客户端发送来的消息
		printf("massage:%s \n", recvBuf);//打印消息
		
		//获取客户端IP地址
		int len = sizeof(addrSrv);
		if (!getpeername(sockConn, (struct sockaddr *)&addrSrv, &len))
		{
			cout << "IP:" << inet_ntoa(addrSrv.sin_addr) << endl;//打印IP地址
		}               
		
		//向请求的客户端发送消息
		
		char butf[50];
		sprintf_s(butf, "You are the %dth visits\n", connetnumber);//发送缓存区
		
		send(sockConn, butf, 50, 0);

		closesocket(sockConn);//关闭客户端连接套接字
	}



}