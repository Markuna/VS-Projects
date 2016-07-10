#include<stdio.h>
#include<WINSOCK.H>
#pragma comment(lib,"Ws2_32.lib")
#include<iostream>

using namespace std;

void main()
{
	WORD wVersionRequested;  //����winsock�汾��
	WSADATA wsaData;         //���winsock��Ϣ

	int err;                 //���ռ���WinsockʱWSAStartup�����ķ���ֵ�������ж��Ƿ���سɹ�
	wVersionRequested = MAKEWORD(1, 1);  //����汾�ţ����ֽ�����ֽھ�Ϊ1

	err = WSAStartup(wVersionRequested, &wsaData);//����Winsock
	if (err != 0) { return;}//����Winsockʧ�ܣ����򷵻�

	//�û����ܽ�����wVersion���صİ汾������WSACleanup�����Winsock�ļ���
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return;
	}
	SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);//����һ����������ʽ�׽���

	SOCKADDR_IN addrSrv;   //����һ����ַ�ṹ�壬���ڴ�ŷ�������ַ��Ϣ
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);//���õ�ַ��Ϣ
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(789);//���÷����������˿�

	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//�Ƿ������׽������ַ��Ϣ��

	listen(sockSrv, 5);//������������������
	SOCKADDR_IN addrClient;//���ÿͻ��˵�ַ�ṹ��
	int len = sizeof(SOCKADDR);

	int connetnumber = 0;//�������Ӵ���
	while (1)//ѭ������ͻ��˵�����
	{
		//�������ճ��򣬵�����������ʱ����ȡ������Ϣ�������׽�����Ϣ
		SOCKET sockConn = accept(sockSrv, (SOCKADDR*)&addrClient, &len);
		if (sockConn < 0)//�ж������Ƿ�ɹ�
		{
			printf("Failed accept!");
			continue;
		}
		else
		{
			printf("Accept a connection:\n");
			connetnumber++;
		}
		char recvBuf[50];//������ջ�����
		recv(sockConn, recvBuf, 50, 0);//���մӿͻ��˷���������Ϣ
		printf("massage:%s \n", recvBuf);//��ӡ��Ϣ
		
		//��ȡ�ͻ���IP��ַ
		int len = sizeof(addrSrv);
		if (!getpeername(sockConn, (struct sockaddr *)&addrSrv, &len))
		{
			cout << "IP:" << inet_ntoa(addrSrv.sin_addr) << endl;//��ӡIP��ַ
		}               
		
		//������Ŀͻ��˷�����Ϣ
		
		char butf[50];
		sprintf_s(butf, "You are the %dth visits\n", connetnumber);//���ͻ�����
		
		send(sockConn, butf, 50, 0);

		closesocket(sockConn);//�رտͻ��������׽���
	}



}