#include<stdio.h>
#include<WINSOCK.H>
#pragma comment(lib,"Ws2_32.lib")
#include<iostream>

using namespace std;

void main()
{
	WORD wVersionRequested;  //定义winsock版本号
	WSADATA wsaData;         //存放winsock信息

	int err;//接收加载Winsock时WSAStartup函数的返回值，用于判断是否加载成功

	wVersionRequested = MAKEWORD(1, 1);//定义版本号，高字节与低字节均为1

	err = WSAStartup(wVersionRequested, &wsaData);//加载Winsock
	if (err != 0) { return; }//加载Winsock失败，程序返回

	//用户不能接收由wVersion返回的版本，调用WSACleanup清除对Winsock的加载
	
	
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return;
	}
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);//建立一个服务器流式套接字
	
	SOCKADDR_IN addrSrv;  //定义一个地址结构体，用于存放服务器地址信息
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //设置服务器IP地址
	addrSrv.sin_family = AF_INET;//设置地址簇必须为AF_INET
	addrSrv.sin_port = htons(789);//设置服务器端口号

    //建立客户端套接字与服务器的连接
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	printf("Please put in a message send to the server:\n");

	char message[50];
	cin.getline(message, 50);
	
	send(sockClient,message,50,0);//用strlen()会出现烫烫烫烫烫

	char recvBuf[50];//定义一个接收数据缓冲区
	recv(sockClient, recvBuf, 50, 0);//接收从服务器发送的数据
	printf("%s\n", recvBuf);//打印从服务器接受的数据
	
	getchar();
	getchar();

	closesocket(sockClient);//关闭客户端套接字
	WSACleanup();//清除程序对Winsock的加载
}