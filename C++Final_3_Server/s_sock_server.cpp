#include"s_mainfunc.h"

SOCKET socket_init(SOCKADDR_IN addrSrv)
{
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	int connectResult = connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//���������������
	if (connectResult == -1)
	{
		cout << "Connection Fucked Up" << endl;
		return;
	}
	else if (connectResult == 0)
		cout << "Connect Successfully" << endl;
	return;
}