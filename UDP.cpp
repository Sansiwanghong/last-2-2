#include "UDP.h"
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<iostream>
#include<string>
#include<time.h>
//include<vector>

using namespace std;

 struct PKG_HEADER
{
	SHORT h_verlen;//8bit版本号
	SHORT password;//8bit校验码
	SHORT   len;//数据包长度
	SHORT tp_command;//2个字节命令类型
	SHORT end;//包尾校验
};

UDP::UDP()
{
	PKG_HEADER header;

	//填充数据包首部
	header.h_verlen = 0x11;
	header.password = 0x01;
	header.len = 0x02;
	header.tp_command = 0x03;
	header.end =0x12;
	memset(DATAbuf, 0, 255);
	memcpy(DATAbuf, &header, sizeof(PKG_HEADER));



	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		printf("初始化失败");
		//return 0;//Failed;
	}

	SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serSocket == INVALID_SOCKET)
	{
		printf("socket error !");
		//return 0;
	}

	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	serAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(serSocket, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("bind error !");
		closesocket(serSocket);
		//return 0;
	}

	sockaddr_in remoteAddr;
	//新添加的指定地址client
	sockaddr_in remoteAddr2;
	//remoteAddr2.sin_family = AF_INET;
	//remoteAddr2.sin_port = htons(8888);

	//inet_pton(AF_INET, "192.168.155.136", (void*)&remoteAddr.sin_addr.S_un.S_addr);
	inet_pton(AF_INET, "192.168.155.135", (void*)&remoteAddr2.sin_addr.S_un.S_addr);//点十进制转换为二进制给第三个参数
	//???

	int nAddrLen = sizeof(remoteAddr);
	int nAddrLen2 = sizeof(remoteAddr2);
	//检测连接上的客户端
	char recvData[255];
	int ret = recvfrom(serSocket, recvData, 255, 0, (sockaddr*)&remoteAddr, &nAddrLen);
	if (ret > 0)
	{
		recvData[ret] = 0x00;
		char sendBuf[20] = { '\0' };
		//打印客户端的IP
		printf("接受到一个连接：%s \r\n", inet_ntop(AF_INET, (void*)&remoteAddr.sin_addr, sendBuf, 16));
		printf(recvData);
	}
	//检测连接上的客户端
	//char recvData2[255];
	//int ret2 = recvfrom(serSocket, recvData2, 255, 0, (sockaddr*)&remoteAddr2, &nAddrLen2);
	//if (ret2 > 0)
	//{
	//	recvData2[ret2] = 0x00;
	//	char sendBuf2[20] = { '\0' };
	//	//打印客户端的IP
	//	printf("接受到一个连接：%s \r\n", inet_ntop(AF_INET, (void*)&remoteAddr2.sin_addr, sendBuf2, 16));
	//	printf(recvData2);
	//}

	


	while (true)
	{
		
		//服务器发出的数据包
		char sendData[255];
	
		//getIn();
		
		//sendData[255] =DATAbuf;
		memcpy(sendData, DATAbuf, 255);
		//sendData2 = DATAbuf;
		//printf("%d",strlen(sendData));
		sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr *)&remoteAddr, nAddrLen);
		
		//sendto(serSocket, sendData, strlen(sendData), 0, (sockaddr *)&remoteAddr2, nAddrLen2);
		
	}
	closesocket(serSocket);
	WSACleanup();
}

UDP::~UDP()
{
}
void UDP::getIn()
{

	//cout << "请输入要发送信息:\n";//发送字符长度不超过255
	//string DATAstr;
	//cin >> DATAstr;
	//int len;
	//len = DATAstr.length();
	//DATAstr.copy(sendDATA, len, 0);

 //   sendDATA[len] = 0x00;
	command();
	//DATAbuf[255] = sendDATA;
	Sleep(1000);
}
void UDP::command()
{
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	//char tmp[64] = { NULL };
	
	//strftime(tmp, 64, "%Y-%m-%d %H:%M:%S-%d", sys);
	sprintf_s(DATAbuf, "%4d-%02d-%02d %02d:%02d:%02d ms:%03d\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
	cout << DATAbuf << endl;
	/*for (int i = 0; i < sizeof(tmp); i++)
	{
		DATAbuf[i] = tmp[i];
	}*/
	//DATAbuf[255]=tmp;
	
	



	
}
