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
	string tmpString = nowTester.get_name();
	for (int i = wordAddList.size() - 1; i >= 0; i--)
	{
		tmpString = tmpString + "," + wordAddList[i];
	}
	SOCKET sockClient = socket_init(addrSrv);
	int flush_flag = state_socket(TESTER_RESULT, tmpString, sockClient);//����������Ϣ�������û����͵����б����ϳ�һ���ַ�����
	closesocket(sockClient);
	for (int i = 0; flush_flag != 0 && i < 3; i++)
	{
		cout << "Reconnecting......" << endl;
		sockClient = socket_init(addrSrv);
		flush_flag = state_socket(TESTER_RESULT, tmpString, sockClient);
		closesocket(sockClient);
	}
	if (flush_flag == 0)cout << "Result Upload Success" << endl;
	else cout << "Result Upload Failure" << endl;
	return;
}
