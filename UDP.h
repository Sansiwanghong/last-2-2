#pragma once
#include <stdio.h>
#include<string.h>

#include <winsock2.h>   
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

class UDP
{
public:
    
	UDP();
	~UDP();
	void getIn();
	void command();
	char sendDATA[255] = {NULL};//�ӿ���̨д�룬����controlCenter���ʣ�
private:
	char DATAbuf[255] = {NULL};//���棬�ȴ�UDP������
	


};

