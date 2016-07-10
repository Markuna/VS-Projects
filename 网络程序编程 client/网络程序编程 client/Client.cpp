#include<stdio.h>
#include<WINSOCK.H>
#pragma comment(lib,"Ws2_32.lib")
#include<iostream>

using namespace std;

void main()
{
	WORD wVersionRequested;  //����winsock�汾��
	WSADATA wsaData;         //���winsock��Ϣ

	int err;//���ռ���WinsockʱWSAStartup�����ķ���ֵ�������ж��Ƿ���سɹ�

	wVersionRequested = MAKEWORD(1, 1);//����汾�ţ����ֽ�����ֽھ�Ϊ1

	err = WSAStartup(wVersionRequested, &wsaData);//����Winsock
	if (err != 0) { return; }//����Winsockʧ�ܣ����򷵻�

	//�û����ܽ�����wVersion���صİ汾������WSACleanup�����Winsock�ļ���
	
	
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
	{
		WSACleanup();
		return;
	}
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, 0);//����һ����������ʽ�׽���
	
	SOCKADDR_IN addrSrv;  //����һ����ַ�ṹ�壬���ڴ�ŷ�������ַ��Ϣ
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //���÷�����IP��ַ
	addrSrv.sin_family = AF_INET;//���õ�ַ�ر���ΪAF_INET
	addrSrv.sin_port = htons(789);//���÷������˿ں�

    //�����ͻ����׽����������������
	connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	printf("Please put in a message send to the server:\n");

	char message[50];
	cin.getline(message, 50);
	
	send(sockClient,message,50,0);//��strlen()���������������

	char recvBuf[50];//����һ���������ݻ�����
	recv(sockClient, recvBuf, 50, 0);//���մӷ��������͵�����
	printf("%s\n", recvBuf);//��ӡ�ӷ��������ܵ�����
	
	getchar();
	getchar();

	closesocket(sockClient);//�رտͻ����׽���
	WSACleanup();//��������Winsock�ļ���
}