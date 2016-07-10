#include<stdio.h>
#include<WINSOCK.H>
#pragma comment(lib,"Ws2_32.lib")
int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { return 0; }
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return 0;
	}
	SOCKET socksend = socket(AF_INET, SOCK_DGRAM, 0);//创建一个数据报套接字用于发送广播信息
	BOOL bBroadcast = true;
	setsockopt(socksend, SOL_SOCKET, SO_BROADCAST, (char*)&bBroadcast, sizeof(BOOL));//设置广播选项，使SO_BROADCAST选项有效

	SOCKADDR_IN bcast;
	bcast.sin_addr.S_un.S_addr = INADDR_BROADCAST;

	//bcast.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	bcast.sin_family = AF_INET;
	bcast.sin_port = htons(8880);
	//bind(socksend, (SOCKADDR*)&bcast, sizeof(SOCKADDR));

	//listen(socksend, 5);

	printf(" 开始向网络中发送广播数据... \n \n");
	char sz[] = "This is just a broadcast test. \n\n";
	//printf(" %s\n",&sz);
	while (1)
	{
		sendto(socksend, sz, strlen(sz), 0, (sockaddr*)&bcast, sizeof(bcast));
		Sleep(5000);
		//printf(" 开始向网络。。\n");
	}
	closesocket(socksend);

	return 0;
}