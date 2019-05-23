#include"s_mainfunc.h"
extern HANDLE hMutex;//Mutexò��û���ã��ǲο����˵ĳ���ӽ�����
extern vector<SOCKET> socketPool;
/*���ڽ�SOCKET������Ϊ�ֲ���������ʱ�����ӻ�Ī���жϣ�����ʹ����ȫ�ֱ�������Ȼ���߳��еĻ�õ�ֵһģһ�������Ǿ������ܺͲ����ܵ�����......*/
/*����������ָ�봫��ʱ��ָ��Ī������ĵط�ȥ��ͬ����֪��Ϊ��......���ʹ����ȫ�ֱ���*/
extern vector<player> playerList;
extern vector<tester> testerList;
extern vector<string> wordList;


void state_socket()
{

	Sleep(100);
	WaitForSingleObject(hMutex, INFINITE);
	SOCKET test_flag_socketClient = socketPool.back();

	char recvBuf[512];//����ͨ�ŵĽ��ջ�����
	int accurateStateBytes = recv(test_flag_socketClient, recvBuf, MaxSize, 0);//�������ӿͻ��˽���״̬�룬�жϽ�����һ������
	if (accurateStateBytes != 2)
	{
		cout << "Recv State Err" << endl;
		closesocket(test_flag_socketClient);
		return;
	}
	stateCode state = (stateCode)(recvBuf[0] - '0');
	switch (state)
	{
	case WORD_SYNC://״̬��Ϊ1�����������ĵ����б����ͻ���
	{
		int accurateByte = 0;
		//OKByteΪУ�飬��ֹͨ�Ź��쵼�¶Է���������ˢ�¡�
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
	case USER_REGIST://״̬��Ϊ2������һ���ַ�����"�˻�����,�û���,����"��
	{
		int OKByte = 0;
		OKByte = send(test_flag_socketClient, "OK", 2, 0);
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(test_flag_socketClient);
			break;
		};//ͨ��ǰ����ŵ�

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
		string_split(tmpString, tmpUser, ",");//tmpUserӦ����3��Ԫ�أ��˻����ͣ��û���������
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
		OKByte = 0;//�����̣߳���ֹ�˳�
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
		int OKByte = 0;//ȡ��״̬�����ȷ���ź�
		OKByte = send(test_flag_socketClient, "OK", 2, 0);
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(test_flag_socketClient);
			break;
		};
		int accurateByte = recv(test_flag_socketClient, recvBuf, MaxSize, 0);//�����˻����ͣ��û���������
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
		//���ͷ��ص���ʾ��Ϣ
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
		int OKByte = 0;//ȡ��״̬�����ȷ���ź�
		OKByte = send(test_flag_socketClient, "OK", 2, 0);
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(test_flag_socketClient);
			break;
		};
		int accurateByte = recv(test_flag_socketClient, recvBuf, MaxSize, 0);//�����û�����������Ϸ�ɼ�
		if (accurateByte <= 0)
		{
			cout << "PLAYER_RESULT ERR 04_1" << endl;
			closesocket(test_flag_socketClient);
			break;
		}
		else recvBuf[accurateByte] = '\0';
		string tmpString = recvBuf;
		vector<string>tmpUser;//tmpUserӦ��ֻ��2��Ԫ�أ��û����ͱ�����Ϸ����
		string_split(tmpString, tmpUser, ",");
		int flush_flag = state_player_result(tmpUser, playerList);
		if (flush_flag == 1)cout << "PLAYER_RESULT FLUSH Succeeded." << endl;
		else cout << "PLAYER_RESULT ERR 04_2" << endl;
		closesocket(test_flag_socketClient);
		break;
	}
	case TESTER_RESULT:
	{
		int OKByte = 0;//ȡ��״̬�����ȷ���ź�
		OKByte = send(test_flag_socketClient, "OK", 2, 0);
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(test_flag_socketClient);
			break;
		};
		int accurateByte = recv(test_flag_socketClient, recvBuf, MaxSize, 0);//�����û���+�����б�
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
		wordAddList.erase(wordAddList.begin());//�ѿ�ͷ���û�����ȥ��
		int tester_flag = state_tester_result(name, wordAddList, wordList, testerList);
		if (tester_flag != 1)
		{
			cout << "TESTER_RESULT ERR 06_2" << endl;
			closesocket(test_flag_socketClient);
			break;
		}
		else cout << "TESTER_RESULT FLUSH Succeeded" << endl;
		OKByte = send(test_flag_socketClient, "OK", 2, 0);//ȡ���û�������ȷ���ź�
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(test_flag_socketClient);
		};
		break;
	}
	case USER_QUERY:
	{
		int OKByte = 0;//ȡ��״̬�����ȷ���ź�
		OKByte = send(test_flag_socketClient, "OK", 2, 0);
		if (OKByte != 2)
		{
			cout << "Server Flooded" << endl;
			closesocket(test_flag_socketClient);
			break;
		};
		int accurateByte = recv(test_flag_socketClient, recvBuf, MaxSize, 0);//����ָ��
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
		state_query(tmpInfo, playerList, testerList);//state_query�Ѳ�ѯ������Ϣ�ŵ�tmpInfo��
		accurateByte = send(test_flag_socketClient, tmpInfo[0].c_str(), tmpInfo[0].length(), 0);//�����б�ͷ
		if (accurateByte <= 0)
		{
			cout << "USER_QUERY ERR 07_3" << endl;
			closesocket(test_flag_socketClient);
			break;
		}
		char OKBuf[5];
		OKByte = recv(test_flag_socketClient, OKBuf, 5, 0);//����ȷ����Ϣ
		if (OKByte != 2)
		{
			cout << "Client Flooded" << endl;
			closesocket(test_flag_socketClient);
			break;
		}
		for (unsigned int i = 1; i < tmpInfo.size(); i++)
		{
			accurateByte = send(test_flag_socketClient, tmpInfo[i].c_str(), tmpInfo[i].length(), 0);//�����б��ÿ����Ϣ
			if (accurateByte <= 0)
			{
				cout << "USER_QUERY ERR 07_4" << endl;
				closesocket(test_flag_socketClient);
				break;
			}
			char OKBuf[5];
			OKByte = recv(test_flag_socketClient, OKBuf, 5, 0);//����ȷ����Ϣ
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