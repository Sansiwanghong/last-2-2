//客户端
#include <stdio.h>   
#include <winsock2.h>   
#include<WS2tcpip.h>
#include<iostream>
#pragma comment(lib,"ws2_32.lib")    
using namespace std;

struct PKG_HEADER
{
	SHORT h_verlen;//8bit版本号
	SHORT password;//8bit校验码
	SHORT   len;//数据包长度
	SHORT tp_command;//2个字节命令类型
	SHORT end;//包尾校验
};
int main(int argc, char* argv[])
{
	PKG_HEADER *package;

	//package->h_verlen = 0;
	//package->password = 0;
	//package->len =0;
	//package->tp_command = 0;
	//package->end = 0;

	WORD socketVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(socketVersion, &wsaData) != 0)
	{
		printf("failed to initial client\n");
		return 0;
		
	}
	SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in sin;
	sin.sin_family = AF_INET;//选择IPV4
	sin.sin_port = htons(8888);//端口号 
	sin.sin_addr.S_un.S_addr = inet_addr("192.168.155.136");
	inet_pton(AF_INET, "192.168.155.136", (void*)&sin.sin_addr.S_un.S_addr);//点十进制转换为二进制给第三个参数

	int len = sizeof(sin);

	const char * sendData = "来自客户端的数据包.\n";
	
	sendto(sclient, sendData, strlen(sendData), 0, (sockaddr *)&sin, len);

	while (true)
	{
		char recvData[255];
		//memset(recvData, 0, 255);
		int ret = recvfrom(sclient, recvData, strlen(recvData), 0, (sockaddr *)&sin, &len);
	//	int ret2 = recvfrom(sclient, recvData, 255, 0, (sockaddr *)&sin, &len);
		//printf("ret: %d\n", ret);
		
		if (ret > 0)
		{
			package = (struct  PKG_HEADER *)recvData;
		    //recvData[ret] = 0x00;//添加结束符‘\0’			
			//cout << recvData << endl;
			//printf(recvData);
			printf("h_verlen=%x,password=%x", package->h_verlen,package->password);
			

		}
		
	}
	system("pause");
	closesocket(sclient);
	WSACleanup();
	return 0;
}