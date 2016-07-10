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

	/*��ȡ������*/
	char hostName[128];
	gethostname(hostName, 100);
	/*��ȡ����IP��ַ*/
	hostent * pHostIP;
	pHostIP = gethostbyname(hostName);
	/*���SOCKADDR_IN�ṹ������*/
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
	char buffer[BUFFER_SIZE];           //���û�����
	for (m = 0; m<10; m++)                 //׼����10����
	{
		n = recv(sock, buffer, BUFFER_SIZE, 0);        //����һ�����ݰ�

		if (err == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				continue;              //�������Ϊ��������ô����������
			break;                                                    //���������������˳�ѭ��
		}

		/*Ȼ���Ǵ�����ʾ���յ�IP���е��ֽ�*/
		printf("(%d) ", m + 1);
		for (i = 0; i < n; i++)
		{
			printf("%02x ", (unsigned char)buffer[i]);
				//�����ڴ˴����ٽ������յ�IP����Ҳ�ɽ�IP�Ű����ݿ�����һ������������//�滺��������10��IP�Ű�ȫ������������������ϸ������
		}
		printf("\n\n");
	}

	typedef struct _IP_HEADER        //����IPͷ
	{
		union
		{
			BYTE Version;            //�汾��ǰ4λ��
			BYTE HdrLen;             //��ͷ���ȣ���4λ����IPͷ��˫�ֳ���
		};
		BYTE ServiceType;            //��������
		WORD TotalLen;               //IP�Ű��ֽ��ܳ���
		WORD ID;                         //IP�Ű���ʶ��
		union
		{
			WORD Flags;             //��־λ��ǰ3λ��0��DF��MF��
			WORD FragOff;         //�ֶ�ƫ�ƣ���13λ����8�ֽ�Ϊ��λ��
		};
		BYTE TimeToLive;            //������TTLֵ
		BYTE Protocol;                  //�߲�Э��ţ�TCP:6��UDP:17��ICMP:1��IGMP:2��
		WORD HdrChksum;           //ͷУ���
		DWORD SrcAddr;              //ԴIP��ַ
		DWORD DstAddr;              //Ŀ��IP��ַ
		BYTE Options;                    //ѡ��
	} IP_HEADER;

	IP_HEADER ip = *(IP_HEADER*)buffer;

	closesocket(sock);
	WSACleanup();


	return 0;
}