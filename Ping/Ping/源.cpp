#include<stdio.h>
#include<WINSOCK.H>
#pragma comment(lib,"Ws2_32.lib")


USHORT checksum(USHORT* buffer, int size)
{
	unsigned long cksum = 0;
	// ����������Ϊ��λ�ۼӵ�cksum��
	while (size > 1)
	{
		cksum += *buffer++;
		size -= sizeof(USHORT);
	}
	// ���Ϊ�����������һ���ֽ���չ��˫�֣����ۼӵ�cksum��
	if (size)
	{
		cksum += *(UCHAR*)buffer;
	}
	// ��cksum�ĸ�16λ�͵�16λ��ӣ�ȡ����õ�У���
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	return (USHORT)(~cksum);
}

typedef struct ip_hdr //����IP�ײ� 
{
	unsigned char h_verlen; //4λ�ײ�����,4λIP�汾�� 
	unsigned char tos; //8λ��������TOS 
	unsigned short total_len; //16λ�ܳ��ȣ��ֽڣ� 
	unsigned short ident; //16λ��ʶ 
	unsigned short frag_and_flags; //3λ��־λ 
	unsigned char ttl; //8λ����ʱ�� TTL 
	unsigned char proto; //8λЭ�� (TCP, UDP ������) 
	unsigned short checksum; //16λIP�ײ�У��� 
	unsigned int sourceIP; //32λԴIP��ַ 
	unsigned int destIP; //32λĿ��IP��ַ 
}IPHeader;

typedef struct icmp_hdr
{
	unsigned char icmp_type;  // ��Ϣ����
	unsigned char icmp_code;  // ����
	unsigned short icmp_checksum;  // У���
								   // �����ǻ���ͷ
	unsigned short icmp_id; // ����Ωһ��ʶ�������ID�ţ�ͨ������Ϊ����ID
	unsigned short icmp_sequence;  // ���к�
	unsigned long icmp_timestamp; // ʱ���
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


	// Ŀ��IP��ַ����ҪPing��IP��ַ
	char szDestIp[] = "127.0.0.1";
	// ����ԭʼ�׽���
	SOCKET sRaw = ::socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	// ���ý��ճ�ʱ
	SetTimeout(sRaw, 1000, TRUE);
	// ����Ŀ�ĵ�ַ
	SOCKADDR_IN dest;
	dest.sin_family = AF_INET;
	dest.sin_port = htons(0);
	dest.sin_addr.S_un.S_addr = inet_addr(szDestIp);
	// ����ICMP���
	char buff[sizeof(ICMP_HDR) + 32];
	ICMP_HDR* pIcmp = (ICMP_HDR*)buff;
	// ��дICMP�������
	pIcmp->icmp_type = 8; // ����һ��ICMP����
	pIcmp->icmp_code = 0;
	pIcmp->icmp_id = (USHORT)::GetCurrentProcessId();
	pIcmp->icmp_checksum = 0;
	pIcmp->icmp_sequence = 0;
	// ������ݲ��֣�����Ϊ����
	memset(&buff[sizeof(ICMP_HDR)], 'E', 32);
	// ��ʼ���ͺͽ���ICMP���
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
		// ���濪ʼ�������յ���ICMP���
		int nTick = ::GetTickCount();
		if (nRet < sizeof(IPHeader) + sizeof(ICMP_HDR))
		{
			printf(" Too few bytes from %s \n", ::inet_ntoa(from.sin_addr));
		}
		ICMP_HDR* pRecvIcmp = (ICMP_HDR*)(recvBuf + sizeof(IPHeader));
		if (pRecvIcmp->icmp_type != 0)  // ����
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