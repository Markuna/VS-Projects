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
	
	SOCKET sockrecv = socket(AF_INET, SOCK_DGRAM, 0);

	printf(" 开始接收广播数据... \n");

	SOCKADDR_IN addrRemote;
	//addrRemote.sin_addr.S_un.S_addr= inet_addr("255.255.255.255");
	addrRemote.sin_addr.S_un.S_addr = INADDR_ANY;
	addrRemote.sin_family = AF_INET;
	addrRemote.sin_port = htons(8880);

	if (bind(sockrecv, (sockaddr*)&addrRemote, sizeof(addrRemote)) == SOCKET_ERROR)
	{
		printf("error");
		return 0;
	}

	//connect(sockrecv,(SOCKADDR*)&addrRemote,sizeof(SOCKADDR));

	int nLen = sizeof(addrRemote);
	char sz[256];
	while (1)
	{
		int nRet = recvfrom(sockrecv, sz, 256, 0, (sockaddr*)&addrRemote, &nLen);
		if (nRet > 0)
		{
			sz[nRet] = '\0';
			printf(sz);
			//sz[nRet] = '\0';
		}
	}

	closesocket(sockrecv);

	return 0;
}