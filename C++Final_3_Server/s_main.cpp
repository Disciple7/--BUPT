#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
#include"s_mainfunc.h"
#define MaxSize 1024
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

void state_socket(SOCKET sockClient,vector<string>& wordList,vector<player>& playerList,vector<tester>& testerList)
{
	char stateBuf[2];
	char recvBuf[MaxSize];
	int accurateStateBytes = recv(sockClient, recvBuf, MaxSize, 0);//服务器从客户端接受状态码，判断进行哪一个操作
	if (accurateStateBytes != 2)
	{
		cout << "Recv State Err" << endl;
		closesocket(sockClient);
		return;
	}
	stateCode state = (stateCode)(recvBuf[0] - '0');
	switch (state)
	{
	case WORD_SYNC://状态码为1，将服务器的单词列表发给客户端
	{
		int accurateByte = 0;
		for (int i = 0; i < wordList.size(); i++)
		{
			accurateByte = send(sockClient, wordList[i].data(), wordList[i].length(), 0);
			if (accurateByte != wordList[i].length())cout << "WORD_SYNC 01" << endl;
		}
		break;
	}
	case USER_REGIST://状态码为2，接收一个字符串："账户类型,用户名,密码"；
	{
		int accurateByte = recv(sockClient, recvBuf, MaxSize, 0);
		if (accurateByte <= 0)
		{
			cout << "USER_REGIST ERR 02_1" << endl;
			closesocket(sockClient);
			return;
		}
		string tmpString = recvBuf;
		vector<string>tmpUser;
		string_split(tmpString, tmpUser, ",");
		int reg_flag = state_register(tmpUser, playerList, testerList);
		if (reg_flag == 0 || reg_flag == 1 || reg_flag == 2)
		{
			tmpString = std::to_string(reg_flag).data();
			accurateByte = send(sockClient, tmpString.data(), tmpString.length(), 0);
			if (accurateByte <= 0)
			{
				cout << "USER_REGIST ERR 02_2" << endl;
				closesocket(sockClient);
				return;
			}
		}
		break;
	}
	case USER_LOGIN:
	{
		int accurateByte = recv(sockClient, recvBuf, MaxSize, 0);
		if (accurateByte <= 0)
		{
			cout << "USER_LOGIN ERR 03_1" << endl;
			closesocket(sockClient);
			return;
		}
		string tmpString = recvBuf;
		vector<string>tmpUser;
		string_split(tmpString, tmpUser, ",");
		int login_flag = state_login(tmpUser, playerList, testerList);
		if (login_flag == 0 || login_flag == 1 || login_flag == 2)
		{
			tmpString = std::to_string(login_flag).data();
			accurateByte = send(sockClient, tmpString.data(), tmpString.length(), 0);
			if (accurateByte <= 0)
			{
				cout << "USER_LOGIN ERR 03_3" << endl;
				closesocket(sockClient);
				return;
			}
		}
		break;
	}
	case PLAYER_RESULT:
	{
		int accurateByte = recv(sockClient, recvBuf, MaxSize, 0);
		if (accurateByte <= 0)
		{
			cout << "PLAYER_RESULT ERR 04_1" << endl;
			closesocket(sockClient);
			return;
		}
		string tmpString = recvBuf;
		vector<string>tmpUser;
		string_split(tmpString, tmpUser, ",");

		break;
	}
	case TESTER_RESULT:
	{
		break;
	}
	case USER_QUERY:
	{
		break;
	}
	default:
	{
		cout << "state code Err" << endl;
		break;
	}
	closesocket(sockClient);
	return;
}