#include"c_mainfunc.h"

int state_socket(stateCode state, string& myInfo, SOCKET sockClient)//���������ֱ��ת���ַ���������
{


	switch (state)
	{
	case USER_REGIST:
	{//����״̬2״̬��
		int accurateBytes = 0;
		accurateBytes = send(sockClient, "2", 2, 0);
		if (accurateBytes <= 0)
		{
			cout << "send error 02_1" << endl;
			return -1;
		}
		//�����˻����ͣ��û���������
		accurateBytes = send(sockClient, myInfo.c_str(), myInfo.length(), 0);
		if (accurateBytes != myInfo.length())
		{
			cout << "send error 02_2" << endl;
			return -1;
		}
		//���շ��ص���ʾ��Ϣ
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
		//����״̬3״̬��
		accurateBytes = send(sockClient, "3", 2, 0);
		if (accurateBytes <= 0)
		{
			cout << "send error 03_1" << endl;
			return -1;
		}
		//�����˻����ͣ��û���������
		accurateBytes = send(sockClient, myInfo.c_str(), myInfo.length(), 0);
		if (accurateBytes != myInfo.length())
		{
			cout << "send error 03_2" << endl;
			return -1;
		}
		//���շ��ص���ʾ��Ϣ
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
		//����״̬4״̬��
		accurateBytes = send(sockClient, "4", 2, 0);
		if (accurateBytes <= 0)
		{
			cout << "send error 04_1" << endl;
			return -1;
		}
		//�����û����ͱ�����Ϸ�ɼ�
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
		//TESTER_RESULT��״̬����flush_tester�Լ����͡������״̬�£�ֻ���͵������ʡ�
		int accurateBytes = 0;
		//�����û����򵥴��б���һ��ͨ���У���һ�η���Ϊ�û�����֮��Ϊ���ʡ�
		accurateBytes = send(sockClient, myInfo.c_str(), myInfo.length(), 0);
		if (accurateBytes != myInfo.length())
		{
			cout << "send error 06_2" << endl;
			return -1;
		}
		//���շ��ص���ʾ��Ϣ
		break;
	}
	case USER_QUERY:
	{
		int accurateBytes = 0;
		accurateBytes = send(sockClient, "7", 2, 0);
		//����״̬7״̬��
		if (accurateBytes <= 0)
		{
			cout << "send error 07_1" << endl;
			return -1;
		}
		accurateBytes = send(sockClient, myInfo.c_str(), myInfo.length(), 0);//���͡�ѡ��a��ѡ��b����a=1��2ʱb=1��2��3��a=3ʱb=���û�����
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
int state_socket(stateCode state, vector<string>& wordList, SOCKET sockClient)//���дʿ�ͬ��ʱ��Ҫ����һ������
{
	//����5����5
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
		recvBuf[accurateBytes] = '\0';//�����ö�ط����Ƿ�'\0'��
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
	int connectResult = connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));//���������������
	if (connectResult == -1)
	{
		cout << "Connection Fucked Up" << endl;
		return sockClient;
	}
	else if (connectResult == 0)
		cout << "Connect Successfully" << endl;

	char test_flag_buf[5];//����5����5
	int test_flag = recv(sockClient, test_flag_buf, 5, 0);
	if(test_flag>0)printf("%s", test_flag_buf);
	else cout << "test_flag err 00" << endl;
	test_flag = send(sockClient, "CEST", 5, 0);

	return sockClient;
}