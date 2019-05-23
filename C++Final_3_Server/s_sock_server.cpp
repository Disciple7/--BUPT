#include"s_mainfunc.h"
extern HANDLE hMutex;//Mutex貌似没有用，是参考别人的程序加进来的
extern vector<SOCKET> socketPool;
/*由于将SOCKET变量作为局部变量传入时，连接会莫名中断，于是使用了全局变量。虽然在线程中的获得的值一模一样，但是就是能跑和不能跑的区别......*/
/*数据容器用指针传入时会指到莫名其妙的地方去，同样不知道为何......因此使用了全局变量*/
extern vector<player> playerList;
extern vector<tester> testerList;
extern vector<string> wordList;


void state_socket()
{

	Sleep(100);
	WaitForSingleObject(hMutex, INFINITE);
	SOCKET test_flag_socketClient = socketPool.back();

	char recvBuf[512];//所有通信的接收缓冲区
	int accurateStateBytes = recv(test_flag_socketClient, recvBuf, MaxSize, 0);//服务器从客户端接受状态码，判断进行哪一个操作
	if (accurateStateBytes != 2)
	{
		cout << "Recv State Err" << endl;
		closesocket(test_flag_socketClient);
		return;
	}
	stateCode state = (stateCode)(recvBuf[0] - '0');
	switch (state)
	{
	case WORD_SYNC://状态码为1，将服务器的单词列表发给客户端
	{
		int accurateByte = 0;
		//OKByte为校验，防止通信过快导致对方缓冲区被刷新。
		for (unsigned int i = 0; i < wordList.size(); i++)
		{
			accurateByte = send(test_flag_socketClient, wordList[i].c_str(), wordList[i].length(), 0);
			if (accurateByte != wordList[i].length())
			{
				cout << "WORD_SYNC 01" << endl;
				closesocket(test_flag_socketClient);
				return;
			}
			int OKByte = 0;
			char OKBuf[5];
			OKByte = recv(test_flag_socketClient, OKBuf, 5, 0);
			if (OKByte != 2)
			{
				cout << "Client Flooded" << endl;
				closesocket(test_flag_socketClient);
				break;
			}
		}
		cout << "WORD_SYNC Success" << endl;
		cout << test_flag_socketClient << " has been closed" << endl;
		closesocket(test_flag_socketClient);
		break;
	}
	case USER_REGIST://状态码为2，接收一个字符串："账户类型,用户名,密码"；
	{
		int OKByte = 0;
		OKByte = send(test_flag_socketClient, "OK", 2, 0);
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(test_flag_socketClient);
			break;
		};//通信前检查信道

		int accurateByte = recv(test_flag_socketClient, recvBuf, MaxSize, 0);
		if (accurateByte <= 0)
		{
			cout << "USER_REGIST ERR 02_1" << endl;
			closesocket(test_flag_socketClient);
			return;
		}
		else recvBuf[accurateByte] = '\0';

		string tmpString = recvBuf;
		vector<string>tmpUser;
		string_split(tmpString, tmpUser, ",");//tmpUser应该有3个元素，账户类型，用户名，密码
		int reg_flag = state_register(tmpUser, playerList, testerList);
		if (reg_flag == 0 || reg_flag == 1 || reg_flag == 2)
		{
			tmpString = std::to_string(reg_flag).c_str();
			accurateByte = send(test_flag_socketClient, tmpString.c_str(), tmpString.length(), 0);
			Sleep(100);
			if (accurateByte != tmpString.length())
			{
				cout << "USER_REGIST ERR 02_2" << endl;
				closesocket(test_flag_socketClient);
				return;
			}
		}
		OKByte = 0;//阻塞线程，防止退出
		char OKBuf[5];
		OKByte = recv(test_flag_socketClient, OKBuf, 5, 0);
		if (OKByte != 2)
		{
			cout << "Client Flooded" << endl;
			closesocket(test_flag_socketClient);
			break;
		}
		cout << test_flag_socketClient << " has been closed" << endl;
		closesocket(test_flag_socketClient);
		break;
	}
	case USER_LOGIN:
	{
		int OKByte = 0;//取走状态码后发送确认信号
		OKByte = send(test_flag_socketClient, "OK", 2, 0);
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(test_flag_socketClient);
			break;
		};
		int accurateByte = recv(test_flag_socketClient, recvBuf, MaxSize, 0);//接收账户类型，用户名，密码
		if (accurateByte <= 0)
		{
			cout << "USER_LOGIN ERR 03_1" << endl;
			closesocket(test_flag_socketClient);
			return;
		}
		else recvBuf[accurateByte] = '\0';

		string tmpString = recvBuf;
		vector<string>tmpUser;
		string_split(tmpString, tmpUser, ",");
		int login_flag = state_login(tmpUser, playerList, testerList);
		tmpString = std::to_string(login_flag).c_str();
		//发送返回的提示信息
		accurateByte = send(test_flag_socketClient, tmpString.c_str(), tmpString.length(), 0);
		if (accurateByte != 1)
		{
			cout << "USER_LOGIN ERR 03_3" << endl;
		}
		cout << test_flag_socketClient << " has been closed" << endl;
		closesocket(test_flag_socketClient);
		break;
	}
	case PLAYER_RESULT:
	{
		int OKByte = 0;//取走状态码后发送确认信号
		OKByte = send(test_flag_socketClient, "OK", 2, 0);
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(test_flag_socketClient);
			break;
		};
		int accurateByte = recv(test_flag_socketClient, recvBuf, MaxSize, 0);//接收用户名，本轮游戏成绩
		if (accurateByte <= 0)
		{
			cout << "PLAYER_RESULT ERR 04_1" << endl;
			closesocket(test_flag_socketClient);
			break;
		}
		else recvBuf[accurateByte] = '\0';
		string tmpString = recvBuf;
		vector<string>tmpUser;//tmpUser应该只有2个元素：用户名和本轮游戏轮数
		string_split(tmpString, tmpUser, ",");
		int flush_flag = state_player_result(tmpUser, playerList);
		if (flush_flag == 1)cout << "PLAYER_RESULT FLUSH Succeeded." << endl;
		else cout << "PLAYER_RESULT ERR 04_2" << endl;
		closesocket(test_flag_socketClient);
		break;
	}
	case TESTER_RESULT:
	{
		int OKByte = 0;//取到状态码后发送确认信号
		OKByte = send(test_flag_socketClient, "OK", 2, 0);
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(test_flag_socketClient);
			break;
		};
		int accurateByte = recv(test_flag_socketClient, recvBuf, MaxSize, 0);//接收用户名+单词列表
		if (accurateByte <= 0)
		{
			cout << "TESTER_RESULT ERR 06_1" << endl;
			closesocket(test_flag_socketClient);
			break;
		}
		else recvBuf[accurateByte] = '\0';
		vector<string> wordAddList;
		string tmpString = recvBuf;
		string_split(tmpString, wordAddList, ",");
		string name = wordAddList[0];
		wordAddList.erase(wordAddList.begin());//把开头的用户名给去掉
		int tester_flag = state_tester_result(name, wordAddList, wordList, testerList);
		if (tester_flag != 1)
		{
			cout << "TESTER_RESULT ERR 06_2" << endl;
			closesocket(test_flag_socketClient);
			break;
		}
		else cout << "TESTER_RESULT FLUSH Succeeded" << endl;
		OKByte = send(test_flag_socketClient, "OK", 2, 0);//取到用户名后发送确认信号
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(test_flag_socketClient);
		};
		break;
	}
	case USER_QUERY:
	{
		int OKByte = 0;//取到状态码后发送确认信号
		OKByte = send(test_flag_socketClient, "OK", 2, 0);
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(test_flag_socketClient);
			break;
		};
		int accurateByte = recv(test_flag_socketClient, recvBuf, MaxSize, 0);//接收指令
		if (accurateByte <= 0)
		{
			cout << "USER_QUERY ERR 07_1" << endl;
			closesocket(test_flag_socketClient);
			break;
		}
		else recvBuf[accurateByte]='\0';
		string tmpString = recvBuf;
		vector<string> tmpInfo;
		string_split(tmpString, tmpInfo, ",");
		if (tmpInfo.size() != 2)
		{
			cout << "USER_QUERY ERR 07_2" << endl;
			closesocket(test_flag_socketClient);
			break;
		}
		state_query(tmpInfo, playerList, testerList);//state_query把查询到的信息放到tmpInfo中
		accurateByte = send(test_flag_socketClient, tmpInfo[0].c_str(), tmpInfo[0].length(), 0);//发送列表头
		if (accurateByte <= 0)
		{
			cout << "USER_QUERY ERR 07_3" << endl;
			closesocket(test_flag_socketClient);
			break;
		}
		char OKBuf[5];
		OKByte = recv(test_flag_socketClient, OKBuf, 5, 0);//接收确认信息
		if (OKByte != 2)
		{
			cout << "Client Flooded" << endl;
			closesocket(test_flag_socketClient);
			break;
		}
		for (unsigned int i = 1; i < tmpInfo.size(); i++)
		{
			accurateByte = send(test_flag_socketClient, tmpInfo[i].c_str(), tmpInfo[i].length(), 0);//发送列表的每行信息
			if (accurateByte <= 0)
			{
				cout << "USER_QUERY ERR 07_4" << endl;
				closesocket(test_flag_socketClient);
				break;
			}
			char OKBuf[5];
			OKByte = recv(test_flag_socketClient, OKBuf, 5, 0);//接收确认信息
			if (OKByte != 2)
			{
				cout << "Client Flooded" << endl;
				closesocket(test_flag_socketClient);
				break;
			}
		}
		cout << "Query Request Satisfied" << endl;
		closesocket(test_flag_socketClient);
		break;
	}
	default:
	{
		cout << "state code err 00" << endl;
		break;
	}
	closesocket(test_flag_socketClient);
	cout << test_flag_socketClient << " has been closed" << endl;
	return;
	}
}