#include <winsock.h>
#include <stdio.h>
#include "protoinfo.h"
#include "MSTcpIP.h"
#include "WS2tcpip.h"
#pragma comment(lib,"ws2_32.lib")

int main()
{
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)	return 0;
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1) 
	{
		WSACleanup();
		return 0;
	}

	SOCKET sock;
	sock = WSASocket(AF_INET, SOCK_RAW, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);
	
	BOOL flag = true;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&flag, sizeof(flag));
	setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (CHAR*)&flag, sizeof(flag));

	/*获取主机名*/
	char hostName[128];
	gethostname(hostName, 100);
	/*获取本地IP地址*/
	hostent * pHostIP;
	pHostIP = gethostbyname(hostName);
	/*填充SOCKADDR_IN结构的内容*/
	sockaddr_in addr_in;
	addr_in.sin_addr = *(in_addr *)pHostIP->h_addr_list[0];
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(6000);

	bind(sock, (PSOCKADDR)&addr_in, sizeof(addr_in));

	DWORD dwBufferLen[10];
	DWORD dwBufferInLen = 1;
	DWORD dwBytesReturned = 0;
	WSAIoctl(sock, SIO_RCVALL, &dwBufferInLen, sizeof(dwBufferInLen),
		&dwBufferLen, sizeof(dwBufferLen), &dwBytesReturned, NULL, NULL);

	int m, i, n;

#define BUFFER_SIZE 65535
	char buffer[BUFFER_SIZE];           //设置缓冲区
	for (m = 0; m<10; m++)                 //准备收10个包
	{
		n = recv(sock, buffer, BUFFER_SIZE, 0);        //接收一个数据包

		if (err == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				continue;              //如果错误为阻塞，那么将继续接收
			break;                                                    //如是其它错误，则退出循环
		}

		/*然后是处理显示接收的IP包中的字节*/
		printf("(%d) ", m + 1);
		for (i = 0; i < n; i++)
		{
			printf("%02x ", (unsigned char)buffer[i]);
				//可以在此处快速解析接收的IP包；也可将IP信包内容拷贝进一个供解析的内//存缓冲区，待10个IP信包全部收齐后，再逐个进行详细解析。
		}
		printf("\n\n");
	}

	typedef struct _IP_HEADER        //定义IP头
	{
		union
		{
			BYTE Version;            //版本（前4位）
			BYTE HdrLen;             //报头长度（后4位），IP头的双字长度
		};
		BYTE ServiceType;            //服务类型
		WORD TotalLen;               //IP信包字节总长度
		WORD ID;                         //IP信包标识号
		union
		{
			WORD Flags;             //标志位（前3位：0，DF，MF）
			WORD FragOff;         //分段偏移（后13位，以8字节为单位）
		};
		BYTE TimeToLive;            //生命期TTL值
		BYTE Protocol;                  //高层协议号（TCP:6，UDP:17，ICMP:1，IGMP:2）
		WORD HdrChksum;           //头校验和
		DWORD SrcAddr;              //源IP地址
		DWORD DstAddr;              //目的IP地址
		BYTE Options;                    //选项
	} IP_HEADER;

	IP_HEADER ip = *(IP_HEADER*)buffer;

	closesocket(sock);
	WSACleanup();


	return 0;
}