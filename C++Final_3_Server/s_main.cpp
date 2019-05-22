#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
#include"s_mainfunc.h"

struct state_socket_Param
{
	SOCKET sockClient;
};

int main() {
	vector<player> playerList;
	vector<tester> testerList;
	vector<string>wordList;
	playerList_init(playerList);//这里定义没了，还要去找一下
	testerList_init(testerList);
	wordList_init(wordList);

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	int SockInit = 0;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData); //返回0，成功，否则就是错误码
	if (err != 0)
	{
		printf("WinSock DLL版本不足要求n");
		SockInit = 0;
	}
	else if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		WSACleanup();
		SockInit = 0;
	}
	if (SockInit != 0)
		SockInit = 1;
	SOCKADDR_IN addrServer;
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);    //htol将主机字节序long型转换为网络字节序
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(4827);                      //htos用来将端口转换成字符，1024以上的数字即可

	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, 0);           //面向连接的可靠性服务SOCK_STRAM
	bind(sockServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR)); //将socket绑定到相应地址和端口上
	listen(sockServer, 5);                                  //等待队列中的最大长度为5

	printf("Welcome,the Host %s is running!Now Wating for someone comes in!\n", inet_ntoa(addrServer.sin_addr));

	int len = sizeof(SOCKADDR);
	SOCKADDR_IN addrClient;

	while (1)
	{
		SOCKET sockClient = accept(sockServer, (SOCKADDR*)&addrClient, &len); //阻塞调用进程直至新的连接出现
		if (sockClient == INVALID_SOCKET)
		{
			cout << "Acception Fucked Up" << endl;
			Sleep(1000);
			continue;
		}
		cout << "New Client Joins In." << endl;
		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)state_socket, (LPVOID)sockClient, 0, 0);
		if (hThread != NULL)
		{
			CloseHandle(hThread);
			Sleep(1000);
		}
	}
	WSACleanup();
	return 0;
}
