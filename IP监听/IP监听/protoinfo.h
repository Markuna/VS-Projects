//IP头部，总长度20字节   
typedef struct IPHeader{
	unsigned char bVerAndHLen;	// 版本信息（前4位）和头长度（后4位）
	unsigned char bTypeOfService;	// 服务类型 8bit
	unsigned short nTotalLength;	// 数据包长度16bit
	unsigned short nID;			// 数据包标识16bit
	unsigned short nReserved;		// 0,分片标志位DF、MF各1位，片偏移13位
	unsigned char bTTL;			// 生成时间8bit
	unsigned char bProtocol;		// 协议类型8bit
	unsigned short nCheckSum;		// 校验和16bit
	unsigned int nSourIp;			// 源IP32bit
	unsigned int nDestIp;			// 目的IP32bit
}IP_HEADER,*PIPHeader;

//TCP头部，总长度20字节   
typedef struct TCPHeader{
	unsigned short nSourPort;		// 源端口号16bit
	unsigned short nDestPort;		// 目的端口号16bit
	unsigned int nSequNum;			// 序列号32bit
	unsigned int nAcknowledgeNum;	// 确认号32bit
	unsigned short nHLenAndFlag;	// 前4位:TCP头长度；中6位:保留；后6位:标志位（URG,ACK,PSH,RST,SYN,FIN）
	unsigned short nWindowSize; 	// 窗口大小16bit
	unsigned short nCheckSum;		// 检验和16bit
	unsigned short nrgentPointer;	// 紧急数据偏移量16bit
}TCP_HEADER,*PTCPHeader;

//UDP头部，总长度8字节   
typedef struct UDPHeader{
	unsigned short nSourPort;		// 源端口号16bit
	unsigned short nDestPort;		// 目的端口号16bit
	unsigned short nLength;			// 数据包长度16bit
	unsigned short nCheckSum;		// 校验和16bit
}UDP_HEADER,*PUDPHeader;

//ICMP头部，总长度4字节
typedef struct ICMPHeader{
	unsigned char nIcmpType;		// 类型
	unsigned char nCode;			// 代码
	unsigned short nCheckSum;		// 16位检验和
      //以下32位字段根据ICMP类型不同定义也不一样，若ECHO IN或ECHO OUT类型时(即ping命令时)定义如下：
      //unsigned short nIdentifier;             // 标识号ID 16bit
      //unsigned short nSequenceNum;            // 序列号16bit
      //unsigned int nTimeStamp;                // 时间戳32bit
}ICMP_HEADER,*PICMPHeader; 

