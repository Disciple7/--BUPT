#include"s_mainfunc.h"

SOCKET socket_init(SOCKADDR_IN addrSrv)
{
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	int connectResult = connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//与服务器进行连接
	if (connectResult == -1)
	{
		cout << "Connection Fucked Up" << endl;
		return;
	}
	else if (connectResult == 0)
		cout << "Connect Successfully" << endl;
	return;
}