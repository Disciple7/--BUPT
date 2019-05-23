#include"c_mainfunc.h"

int state_socket(stateCode state, string& myInfo, SOCKET sockClient)//其他情况下直接转成字符串传就行
{
	switch (state)
	{
	case USER_REGIST:
	{//发送状态2状态码
		int accurateBytes = 0;
		accurateBytes = send(sockClient, "2", 2, 0);
		if (accurateBytes != 2)
		{
			cout << "send error 02_1" << endl;
			return -1;
		}
		int OKByte = 0;
		char OKBuf[5];
		OKByte = recv(sockClient, OKBuf, 5, 0);
		if (OKByte != 2)
		{
			cout << "Client Flooded" << endl;
			closesocket(sockClient);
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
		if (accurateBytes != 1)
		{
			cout << "recv error 02" << endl;
			return -1;
		}
		else
		{
			OKByte = 0;
			OKByte = send(sockClient, "OK", 2, 0);
			if (OKByte != 2)
			{
				cout << "Server Flooded" << endl;
				closesocket(sockClient);
				return -1;
			};
			recvBuf[accurateBytes] = '\0';
			if(recvBuf[0]=='0')cout << "recv error 02_2";
			else if (recvBuf[0] == '1')cout << "User successfully registers!" << endl;
			else if(recvBuf[0]=='2')cout << "The Username has been registered.Register failed!" << endl;
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
		//等待对方取走状态码并返回确认信号
		int OKByte = 0;
		char OKBuf[5];
		OKByte = recv(sockClient, OKBuf, 5, 0);
		if (OKByte != 2)
		{
			cout << "Client Flooded" << endl;
			closesocket(sockClient);
			break;
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
		//等待对方取走状态码并返回确认信号
		int OKByte = 0;
		char OKBuf[5];
		OKByte = recv(sockClient, OKBuf, 5, 0);
		if (OKByte != 2)
		{
			cout << "Client Flooded" << endl;
			closesocket(sockClient);
			return -1;
		}
		//发送用户名和本轮游戏成绩
		accurateBytes = send(sockClient, myInfo.c_str(), myInfo.length(), 0);
		if (accurateBytes != myInfo.length())
		{
			cout << "send error 04_2" << endl;
			return -1;
		}
		else return 0;
	}
	case TESTER_RESULT:
	{
		int accurateBytes = 0;
		accurateBytes = send(sockClient, "6", 2, 0);
		//发送状态6状态码
		if (accurateBytes <= 0)
		{
			cout << "send error 06_1" << endl;
			return -1;
		}
		int OKByte = 0;
		char OKBuf[5];
		OKByte = recv(sockClient, OKBuf, 5, 0);//获得对方的确认信号
		if (OKByte != 2)
		{
			cout << "Client Flooded" << endl;
			closesocket(sockClient);
			return -1;
		}
		//发送用户名+单词列表
		accurateBytes = send(sockClient, myInfo.c_str(), myInfo.length(), 0);
		if (accurateBytes != myInfo.length())
		{
			cout << "send error 06_2" << endl;
			return -1;
		}
		//接收返回的提示信息
		OKByte = recv(sockClient, OKBuf, 5, 0);//获得对方的确认信号
		if (OKByte != 2)
		{
			cout << "Client Flooded" << endl;
			closesocket(sockClient);
			return -1;
		}
		else return 0;
	}
	case USER_QUERY:
	{
		int accurateBytes = 0;
		accurateBytes = send(sockClient, "7", 2, 0);
		//发送状态7状态码
		if (accurateBytes <= 0)
		{
			cout << "send error 07_1" << endl;
			closesocket(sockClient);
			return -1;
		}
		int OKByte = 0;
		char OKBuf[5];
		OKByte = recv(sockClient, OKBuf, 5, 0);//获得对方的确认信号
		if (OKByte != 2)
		{
			cout << "Client Flooded" << endl;
			closesocket(sockClient);
			return -1;
		}
		accurateBytes = send(sockClient, myInfo.c_str(), myInfo.length(), 0);//发送“选项a，选项b”；a=1或2时b=1或2或3；a=3时b=“用户名”
		if (accurateBytes != myInfo.length())
		{
			cout << "send error 07_2" << endl;
			closesocket(sockClient);
			return -1;
		}
		char recvBuf[1024];
		accurateBytes = recv(sockClient, recvBuf, 1024, 0);//接收对方发来的数据（列表头）
		if (accurateBytes <= 0)
		{
			cout << "recv error 07_4" << endl;
			closesocket(sockClient);
			return -1;
		}
		else recvBuf[accurateBytes] = '\0';
		OKByte = send(sockClient, "OK", 2, 0);//发送一个确认信息
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(sockClient);
			return -1;
		};
		while (accurateBytes >0 )
		{
			string tmpString = recvBuf;
			cout << tmpString << endl;
			accurateBytes = recv(sockClient, recvBuf, 1024, 0);//列表每行的信息
			if (accurateBytes <= 0)
			{
				cout << "All Info Listed" << endl;
				closesocket(sockClient);
				return -1;
			}
			else recvBuf[accurateBytes] = '\0';
			OKByte = send(sockClient, "OK", 2, 0);//发送一个确认信息
			if (OKByte != 2)
			{
				cout << "Server Flooded" << endl;
				closesocket(sockClient);
				return -1;
			};
		}
		return 0;
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
	if (state != WORD_SYNC)
	{
		cout << "state code error 01" << endl;
		return -1;
	}
	int accurateBytes = 0;
	accurateBytes=send(sockClient, "1", 2, 0);
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
		recvBuf[accurateBytes] = '\0';//靠，好多地方忘记封'\0'了
		string tmpString = recvBuf;
		wordList.push_back(tmpString);
		count++;
		int OKByte = 0;
		OKByte = send(sockClient, "OK", 2, 0);
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(sockClient);
			break;
		}
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
	return sockClient;
}

int OKByte_send(SOCKET sockClient)
{
	int OKByte = 0;
	char OKBuf[5];
	OKByte = recv(sockClient, OKBuf, 5, 0);
	if (OKByte != 2)
	{
		cout << "Client Flooded" << endl;
		closesocket(sockClient);
		return -1;
	}
	return 0;
}

int OKByte_recv(SOCKET sockClient)
{
	int OKByte = 0;
	OKByte = send(sockClient, "OK", 2, 0);
	if (OKByte != 2)
	{
		cout << "Server Flooded" << endl;
		closesocket(sockClient);
		return -1;
	}
	return 0;
}