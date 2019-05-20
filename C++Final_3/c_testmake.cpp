#include"c_mainfunc.h"

int state_testmake(vector<string>& wordList,vector<string>& wordAddList)
{
	cout << "Please input your word (input \":q\" to quit ) : " << endl;
	int wordCount = 0;
	string myWord;
	cin >> myWord;
	while (myWord != ":q")
	{
		vector<string>::iterator wordIter = wordList.begin();
		for (; wordIter != wordList.end(); wordIter++)//����һ�����ʺ��ڵ��ʱ�����һ��
		{
			if (myWord == *wordIter)
				break;
		}
		if (wordIter == wordList.end())//δ��鵽��ͬ���ʣ���Iter��ָ��end()����ʱ�ɰѵ���д�뵽wordList��wordAddList��
		{
			wordList.push_back(myWord);
			wordAddList.push_back(myWord);
			wordCount++;
		}
		else//�����Ѵ���ʱ���һ����ʾ
		{
			cout << "This word has already been in the c_database." << endl;
		}
		cin >> myWord;//���������:q����ֱ���˳�
	}
	cout << "You contributed " << wordCount << " word(s) !" << endl;
	return wordCount;
}

void flush_tester(tester& nowTester, vector<string>& wordAddList, SOCKADDR_IN addrSrv)
{
	SOCKET sockClient = socket_init(addrSrv);
	int accurateBytes = 0;
	accurateBytes = send(sockClient, "6", 2, 0);
	//����״̬6״̬��
	if (accurateBytes <= 0)
	{
		cout << "send error 06_1" << endl;
		return;
	}
	string tmpString = nowTester.get_name();
	state_socket(TESTER_RESULT, tmpString, sockClient);//TESTER_RESULT����£�state_socketֻ�Ƿ���һ�����ʣ��������û�����Ҳ�����ǵ��ʣ�
	for (int i = wordAddList.size()-1; i>=0; i--)
	{
		state_socket(TESTER_RESULT, wordAddList[i], sockClient);
		wordAddList.pop_back();
	}
	closesocket(sockClient);
	return;
}
