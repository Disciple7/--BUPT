#include"c_mainfunc.h"

int state_socket(stateCode state, string& myInfo, SOCKET sockClient)//其他情况下直接转成字符串传就行
{


	switch (state)
	{
	case USER_REGIST:
	{//发送状态2状态码
		int accurateBytes = 0;
		accurateBytes = send(sockClient, "2", 2, 0);
		if (accurateBytes <= 0)
		{
			cout << "send error 02_1" << endl;
			return -1;
		}
		//发送账户类型，用户名和密码
		accurateBytes = send(sockClient, myInfo.c_str(), myInfo.length(), 0);
		if (accurateBytes != myInfo.length())
		{
			cout << "send error 02_2" << endl;
			return -1;
		}
		//接收返回的提示信息
		char recvBuf[1024];
		accurateBytes = recv(sockClient, recvBuf, 1024, 0);
		if (accurateBytes != 2)
		{
			cout << "recv error 02" << endl;
			return -1;
		}
		else
		{
			recvBuf[accurateBytes] = '\0';
			if(recvBuf[0]=='0')cout << "recv error 02_2";
			else if (recvBuf[0] == '1')cout << "Player successfully registers!" << endl;
			else if(recvBuf[0]=='2')cout << "The Player - Name has been registered.Register failed!" << endl;
			else cout << "recvBuffer error 02" << endl;
			return 0;
		}
		break;
	}
	case USER_LOGIN:
	{
		int accurateBytes = 0;
		//发送状态3状态码
		accurateBytes = send(sockClient, "3", 2, 0);
		if (accurateBytes <= 0)
		{
			cout << "send error 03_1" << endl;
			return -1;
		}
		//发送账户类型，用户名，密码
		accurateBytes = send(sockClient, myInfo.c_str(), myInfo.length(), 0);
		if (accurateBytes != myInfo.length())
		{
			cout << "send error 03_2" << endl;
			return -1;
		}
		//接收返回的提示信息
		char recvBuf[1024];
		accurateBytes = recv(sockClient, recvBuf, 1024, 0);
		if (accurateBytes <= 0)
		{
			cout << "recv error 03" << endl;
			return -1;
		}
		else
		{
			recvBuf[accurateBytes] = '\0';
			if (recvBuf[0] == '1')return 1;
			else if (recvBuf[0] == '2')return 2;
			else return 0;
		}
		break;
	}
	case PLAYER_RESULT:
	{
		int accurateBytes = 0;
		//发送状态4状态码
		accurateBytes = send(sockClient, "4", 2, 0);
		if (accurateBytes <= 0)
		{
			cout << "send error 04_1" << endl;
			return -1;
		}
		//发送用户名和本轮游戏成绩
		accurateBytes = send(sockClient, myInfo.c_str(), myInfo.length(), 0);
		if (accurateBytes != myInfo.length())
		{
			cout << "send error 04_2" << endl;
			return -1;
		}
		break;
	}
	case TESTER_RESULT:
	{
		//TESTER_RESULT的状态码由flush_tester自己发送。在这个状态下，只发送单个单词。
		int accurateBytes = 0;
		//发送用户名或单词列表。在一次通信中，第一次发送为用户名，之后为单词。
		accurateBytes = send(sockClient, myInfo.c_str(), myInfo.length(), 0);
		if (accurateBytes != myInfo.length())
		{
			cout << "send error 06_2" << endl;
			return -1;
		}
		//接收返回的提示信息
		break;
	}
	case USER_QUERY:
	{
		int accurateBytes = 0;
		accurateBytes = send(sockClient, "7", 2, 0);
		//发送状态7状态码
		if (accurateBytes <= 0)
		{
			cout << "send error 07_1" << endl;
			return -1;
		}
		accurateBytes = send(sockClient, myInfo.c_str(), myInfo.length(), 0);//发送“选项a，选项b”；a=1或2时b=1或2或3；a=3时b=“用户名”
		if (accurateBytes != myInfo.length())
		{
			cout << "send error 07_2" << endl;
			return -1;
		}
		char recvBuf[128];
		accurateBytes = recv(sockClient, recvBuf, 128, 0);
		while (accurateBytes >0 )
		{
			string tmpString = recvBuf;
			cout << tmpString << endl;
			accurateBytes = recv(sockClient, recvBuf, 128, 0);
		}
		return 0;
		break;
	}
	default:
	{
		cout << "state code error 01" << endl;
		break;
	}
	}
	return -2;
}
int state_socket(stateCode state, vector<string>& wordList, SOCKET sockClient)//进行词库同步时需要传入一个容器
{
	//发送5接收5
	char test_flag_buf[5];
	int test_flag = recv(sockClient, test_flag_buf, 5, 0);
	if (test_flag>0)printf("%s\n", test_flag_buf);
	else cout << "test_flag err 10" << endl;
	test_flag = send(sockClient, "CEST1", 5, 0);
	if (test_flag<0)cout << "test_flag err 20" << endl;

	if (state != WORD_SYNC)
	{
		cout << "state code error 01" << endl;
		return -1;
	}
	int accurateBytes = 0;
	accurateBytes=send(sockClient, "1", 1, 0);
	if (accurateBytes <= 0)
	{
		cout << "send err 01" << endl;
		return -1;
	}
	int count = 0;
	char recvBuf[1024];
	accurateBytes = recv(sockClient, recvBuf, 1024, 0);
	while (accurateBytes > 0)
	{
		Sleep(100);
		recvBuf[accurateBytes] = '\0';//靠，好多地方忘记封'\0'了
		string tmpString = recvBuf;
		wordList.push_back(tmpString);
		count++;
		accurateBytes = recv(sockClient, recvBuf, 1024, 0);
	}
	cout << "Word Sync : "<<count<<" words stored" << endl;
	return 0;
}

SOCKET socket_init(SOCKADDR_IN addrSrv)
{
	SOCKET sockClient=socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	int connectResult = connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//与服务器进行连接
	if (connectResult == -1)
	{
		cout << "Connection Fucked Up" << endl;
		return sockClient;
	}
	else if (connectResult == 0)
		cout << "Connect Successfully" << endl;

	char test_flag_buf[5];//接收5发送5
	int test_flag = recv(sockClient, test_flag_buf, 5, 0);
	if(test_flag>0)printf("%s", test_flag_buf);
	else cout << "test_flag err 00" << endl;
	test_flag = send(sockClient, "CEST", 5, 0);

	return sockClient;
}