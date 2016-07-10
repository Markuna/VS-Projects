#include<stdio.h>
#include<WINSOCK.H>
#pragma comment(lib,"Ws2_32.lib")


USHORT checksum(USHORT* buffer, int size)
{
	unsigned long cksum = 0;
	// 将数据以字为单位累加到cksum中
	while (size > 1)
	{
		cksum += *buffer++;
		size -= sizeof(USHORT);
	}
	// 如果为奇数，将最后一个字节扩展到双字，再累加到cksum中
	if (size)
	{
		cksum += *(UCHAR*)buffer;
	}
	// 将cksum的高16位和低16位相加，取反后得到校验和
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	return (USHORT)(~cksum);
}

typedef struct ip_hdr //定义IP首部 
{
	unsigned char h_verlen; //4位首部长度,4位IP版本号 
	unsigned char tos; //8位服务类型TOS 
	unsigned short total_len; //16位总长度（字节） 
	unsigned short ident; //16位标识 
	unsigned short frag_and_flags; //3位标志位 
	unsigned char ttl; //8位生存时间 TTL 
	unsigned char proto; //8位协议 (TCP, UDP 或其他) 
	unsigned short checksum; //16位IP首部校验和 
	unsigned int sourceIP; //32位源IP地址 
	unsigned int destIP; //32位目的IP地址 
}IPHeader;

typedef struct icmp_hdr
{
	unsigned char icmp_type;  // 消息类型
	unsigned char icmp_code;  // 代码
	unsigned short icmp_checksum;  // 校验和
								   // 下面是回显头
	unsigned short icmp_id; // 用来惟一标识此请求的ID号，通常设置为进程ID
	unsigned short icmp_sequence;  // 序列号
	unsigned long icmp_timestamp; // 时间戳
} ICMP_HDR, *PICMP_HDR;

BOOL SetTimeout(SOCKET s, int nTime, BOOL bRecv)
{
	int ret = ::setsockopt(s, SOL_SOCKET,bRecv ? SO_RCVTIMEO : SO_SNDTIMEO, (char*)&nTime, sizeof(nTime));
	return ret != SOCKET_ERROR;
}

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


	// 目的IP地址，即要Ping的IP地址
	char szDestIp[] = "127.0.0.1";
	// 创建原始套接字
	SOCKET sRaw = ::socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	// 设置接收超时
	SetTimeout(sRaw, 1000, TRUE);
	// 设置目的地址
	SOCKADDR_IN dest;
	dest.sin_family = AF_INET;
	dest.sin_port = htons(0);
	dest.sin_addr.S_un.S_addr = inet_addr(szDestIp);
	// 创建ICMP封包
	char buff[sizeof(ICMP_HDR) + 32];
	ICMP_HDR* pIcmp = (ICMP_HDR*)buff;
	// 填写ICMP封包数据
	pIcmp->icmp_type = 8; // 请求一个ICMP回显
	pIcmp->icmp_code = 0;
	pIcmp->icmp_id = (USHORT)::GetCurrentProcessId();
	pIcmp->icmp_checksum = 0;
	pIcmp->icmp_sequence = 0;
	// 填充数据部分，可以为任意
	memset(&buff[sizeof(ICMP_HDR)], 'E', 32);
	// 开始发送和接收ICMP封包
	USHORT nSeq = 0;
	char recvBuf[1024];
	SOCKADDR_IN from;
	int nLen = sizeof(from);
	while (TRUE)
	{
		static int nCount = 0;
		int nRet;
		if (nCount++ == 4) break;
		pIcmp->icmp_checksum = 0;
		pIcmp->icmp_timestamp = ::GetTickCount();
		pIcmp->icmp_sequence = nSeq++;
		pIcmp->icmp_checksum = checksum((USHORT*)buff, sizeof(ICMP_HDR) + 32);                           
		nRet = ::sendto(sRaw, buff, sizeof(ICMP_HDR) + 32, 0, (SOCKADDR *)&dest, sizeof(dest));
		if (nRet == SOCKET_ERROR)
		{
			printf(" sendto() failed: %d \n", ::WSAGetLastError());
			return -1;
		}
		nRet = ::recvfrom(sRaw, recvBuf, 1024, 0, (sockaddr*)&from, &nLen);
		if (nRet == SOCKET_ERROR)
		{
			if (::WSAGetLastError() == WSAETIMEDOUT)
			{
				printf(" timed out\n");
				continue;
			}
			printf(" recvfrom() failed: %d\n", ::WSAGetLastError());
			return -1;
		}
		// 下面开始解析接收到的ICMP封包
		int nTick = ::GetTickCount();
		if (nRet < sizeof(IPHeader) + sizeof(ICMP_HDR))
		{
			printf(" Too few bytes from %s \n", ::inet_ntoa(from.sin_addr));
		}
		ICMP_HDR* pRecvIcmp = (ICMP_HDR*)(recvBuf + sizeof(IPHeader));
		if (pRecvIcmp->icmp_type != 0)  // 回显
		{
			printf(" nonecho type %d recvd \n", pRecvIcmp->icmp_type);
			return -1;
		}
		if (pRecvIcmp->icmp_id != ::GetCurrentProcessId())
		{
			printf(" someone else's packet! \n");
			return -1;
		}
		printf(" %d bytes from %s:", nRet, inet_ntoa(from.sin_addr));
		printf(" icmp_seq = %d. ", pRecvIcmp->icmp_sequence);
		printf(" time: %d ms", nTick - pRecvIcmp->icmp_timestamp);
		printf(" \n");
		::Sleep(1000);
	}
	return 0;
}