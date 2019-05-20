#include"s_mainfunc.h"

extern HANDLE hMutex;
SOCKET socket_init(SOCKADDR_IN addrSrv)
{
	SOCKET sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	int connectResult = connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//���������������
	if (connectResult == -1)
	{
		cout << "Connection Fucked Up" << endl;
		return INVALID_SOCKET;
	}
	else if (connectResult == 0)
		cout << "Connect Successfully" << endl;
	return sockClient;
}

void state_socket(SOCKET sockClient, vector<string> *wordListPtr, vector<player>* playerListPtr, vector<tester>* testerListPtr)
{
	WaitForSingleObject(hMutex, INFINITE);
	//����5����5
	Sleep(100);
	int test_flag = send(sockClient, "CEST1", 5, 0);
	if (test_flag<0)cout << "test_flag err 20" << endl;
	char test_flag_buf[5];
	test_flag = recv(sockClient, test_flag_buf, 5, 0);
	if (test_flag>0)printf("%s", test_flag_buf);
	else cout << "test_flag err 10" << endl;

	vector<string>& wordList = *wordListPtr;
	vector<player>& playerList = *playerListPtr;
	vector<tester>& testerList = *testerListPtr;
	if (sockClient == INVALID_SOCKET)cout << "INVALID_SOCKET" << endl;
	char recvBuf[512]="\0";//����ͨ�ŵĽ��ջ�����
	int accurateStateBytes = recv(sockClient, recvBuf, MaxSize, 0);//�������ӿͻ��˽���״̬�룬�жϽ�����һ������
	if (accurateStateBytes != 1)
	{
		cout << "Recv State Err" << endl;
		closesocket(sockClient);
		return;
	}
	stateCode state = (stateCode)(recvBuf[0] - '0');
	switch (state)
	{
	case WORD_SYNC://״̬��Ϊ1�����������ĵ����б����ͻ���
	{
		int accurateByte = 0;
		for (unsigned int i = 0; i < wordList.size(); i++)
		{
			accurateByte = send(sockClient, wordList[i].c_str(), wordList[i].length(), 0);
			if (accurateByte != wordList[i].length())
			{
				cout << "WORD_SYNC 01" << endl;
				break;
			}
		}
		break;
	}
	case USER_REGIST://״̬��Ϊ2������һ���ַ�����"�˻�����,�û���,����"��
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
		string_split(tmpString, tmpUser, ",");//tmpUserӦ����3��Ԫ�أ��˻����ͣ��û���������
		int reg_flag = state_register(tmpUser, playerList, testerList);
		if (reg_flag == 0 || reg_flag == 1 || reg_flag == 2)
		{
			tmpString = std::to_string(reg_flag).c_str();
			accurateByte = send(sockClient, tmpString.c_str(), tmpString.length(), 0);
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
		int accurateByte = recv(sockClient, recvBuf, MaxSize, 0);//�����˻����ͣ��û���������
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
		tmpString = std::to_string(login_flag).c_str();
		accurateByte = send(sockClient, tmpString.c_str(), tmpString.length(), 0);
		if (accurateByte != 2)
		{
			cout << "USER_LOGIN ERR 03_3" << endl;
		}
		break;
	}
	case PLAYER_RESULT:
	{
		int accurateByte = recv(sockClient, recvBuf, MaxSize, 0);//�����û�����������Ϸ�ɼ�
		if (accurateByte <= 0)
		{
			cout << "PLAYER_RESULT ERR 04_1" << endl;
			closesocket(sockClient);
			return;
		}
		string tmpString = recvBuf;
		vector<string>tmpUser;//tmpUserӦ��ֻ��2��Ԫ�أ��û����ͱ�����Ϸ����
		string_split(tmpString, tmpUser, ",");
		int flush_flag = state_player_result(tmpUser, playerList);
		if (flush_flag != 1)cout << "PLAYER_RESULT ERR 04_2" << endl;
		break;
	}
	case TESTER_RESULT:
	{
		int accurateByte = recv(sockClient, recvBuf, MaxSize, 0);//�����û���
		if (accurateByte <= 0)
		{
			cout << "TESTER_RESULT ERR 06_1" << endl;
			break;
		}
		string name = recvBuf;
		vector<string> wordAddList;
		string tmpString;
		accurateByte = recv(sockClient, recvBuf, MaxSize, 0);//�����µ���
		while (accurateByte > 0)
		{
			tmpString = recvBuf;
			wordAddList.push_back(tmpString);
			accurateByte = recv(sockClient, recvBuf, MaxSize, 0);//�����µ���
		}
		int tester_flag = state_tester_result(name, wordAddList, wordList, testerList);
		if (tester_flag != 1)cout << "TESTER_RESULT ERR 06_2" << endl;
		break;
	}
	case USER_QUERY:
	{
		int accurateByte = recv(sockClient, recvBuf, MaxSize, 0);//�����û���
		if (accurateByte <= 0)
		{
			cout << "USER_QUERY ERR 07_1" << endl;
			break;
		}
		string tmpString = recvBuf;
		vector<string> tmpInfo;
		string_split(tmpString, tmpInfo, ",");
		if (tmpInfo.size() != 2)
		{
			cout << "USER_QUERY ERR 07_2" << endl;
			break;
		}
		state_query(tmpInfo, playerList, testerList);//state_query�Ѳ�ѯ������Ϣ�ŵ�tmpInfo��
		accurateByte = send(sockClient, tmpInfo[0].c_str(), tmpInfo[0].length(), 0);
		for (unsigned int i = 1; i < tmpInfo.size(); i++)
		{
			accurateByte = send(sockClient, tmpInfo[i].c_str(), tmpInfo[i].length(), 0);
			if (accurateByte <= 0)
			{
				cout << "USER_QUERY ERR 07_3" << endl;
				break;
			}
		}
		break;
	}
	default:
	{
		cout << "state code err 00" << endl;
		break;
	}
	closesocket(sockClient);
	return;
	}
}