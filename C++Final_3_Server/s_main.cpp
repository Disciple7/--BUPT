#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll
#include"s_mainfunc.h"

HANDLE hMutex;
struct state_socket_Param
{
	vector<string>* wordList;
	vector<player>* playerList;
	vector<tester>* testerList;
	string targetIP;
};

int main() {
	vector<player> playerList;
	vector<tester> testerList;
	vector<string>wordList;
	playerList_init(playerList);//���ﶨ��û�ˣ���Ҫȥ��һ��
	testerList_init(testerList);
	wordList_init(wordList);

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	int SockInit = 0;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData); //����0���ɹ���������Ǵ�����
	if (err != 0)
	{
		printf("WinSock DLL�汾����Ҫ��n");
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
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);    //htol�������ֽ���long��ת��Ϊ�����ֽ���
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(4827);                      //htos�������˿�ת�����ַ���1024���ϵ����ּ���

	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, 0);           //�������ӵĿɿ��Է���SOCK_STRAM
	bind(sockServer, (SOCKADDR*)&addrServer, sizeof(SOCKADDR)); //��socket�󶨵���Ӧ��ַ�Ͷ˿���
	listen(sockServer, 5);                                  //�ȴ������е���󳤶�Ϊ5

	printf("Welcome,the Host %s is running!Now Wating for someone comes in!\n", inet_ntoa(addrServer.sin_addr));

	int len = sizeof(SOCKADDR);
	SOCKADDR_IN addrClient;

	while (1)
	{
		SOCKET sockClient = accept(sockServer, (SOCKADDR*)&addrClient, &len); //�������ý���ֱ���µ����ӳ���
		if (sockClient == INVALID_SOCKET)
		{
			cout << "Acception Fucked Up" << endl;
			Sleep(1000);
			continue;
		}
		cout << "New Client Joins In." << endl;
		state_socket_Param Param1;
		Param1.playerList = &playerList;
		Param1.testerList = &testerList;
		Param1.wordList = &wordList;
		//����5����5
		int test_flag = send(sockClient, "SEST", 5, 0);
		char test_flag_buf[5];
		test_flag = recv(sockClient, test_flag_buf, 5, 0);
		printf("%s", test_flag_buf);

		HANDLE hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)state_socket,(LPVOID)&Param1 , 0, 0);
		if (hThread != NULL)
		{
			CloseHandle(hThread);
		}
		Sleep(100);
	}
	WSACleanup();
	return 0;
}
