//IPͷ�����ܳ���20�ֽ�   
typedef struct IPHeader{
	unsigned char bVerAndHLen;	// �汾��Ϣ��ǰ4λ����ͷ���ȣ���4λ��
	unsigned char bTypeOfService;	// �������� 8bit
	unsigned short nTotalLength;	// ���ݰ�����16bit
	unsigned short nID;			// ���ݰ���ʶ16bit
	unsigned short nReserved;		// 0,��Ƭ��־λDF��MF��1λ��Ƭƫ��13λ
	unsigned char bTTL;			// ����ʱ��8bit
	unsigned char bProtocol;		// Э������8bit
	unsigned short nCheckSum;		// У���16bit
	unsigned int nSourIp;			// ԴIP32bit
	unsigned int nDestIp;			// Ŀ��IP32bit
}IP_HEADER,*PIPHeader;

//TCPͷ�����ܳ���20�ֽ�   
typedef struct TCPHeader{
	unsigned short nSourPort;		// Դ�˿ں�16bit
	unsigned short nDestPort;		// Ŀ�Ķ˿ں�16bit
	unsigned int nSequNum;			// ���к�32bit
	unsigned int nAcknowledgeNum;	// ȷ�Ϻ�32bit
	unsigned short nHLenAndFlag;	// ǰ4λ:TCPͷ���ȣ���6λ:��������6λ:��־λ��URG,ACK,PSH,RST,SYN,FIN��
	unsigned short nWindowSize; 	// ���ڴ�С16bit
	unsigned short nCheckSum;		// �����16bit
	unsigned short nrgentPointer;	// ��������ƫ����16bit
}TCP_HEADER,*PTCPHeader;

//UDPͷ�����ܳ���8�ֽ�   
typedef struct UDPHeader{
	unsigned short nSourPort;		// Դ�˿ں�16bit
	unsigned short nDestPort;		// Ŀ�Ķ˿ں�16bit
	unsigned short nLength;			// ���ݰ�����16bit
	unsigned short nCheckSum;		// У���16bit
}UDP_HEADER,*PUDPHeader;

//ICMPͷ�����ܳ���4�ֽ�
typedef struct ICMPHeader{
	unsigned char nIcmpType;		// ����
	unsigned char nCode;			// ����
	unsigned short nCheckSum;		// 16λ�����
      //����32λ�ֶθ���ICMP���Ͳ�ͬ����Ҳ��һ������ECHO IN��ECHO OUT����ʱ(��ping����ʱ)�������£�
      //unsigned short nIdentifier;             // ��ʶ��ID 16bit
      //unsigned short nSequenceNum;            // ���к�16bit
      //unsigned int nTimeStamp;                // ʱ���32bit
}ICMP_HEADER,*PICMPHeader; 

