#include"c_mainfunc.h"

int state_testmake(vector<string>& wordList,vector<string>& wordAddList)
{
	fstream wordFile;
	if (DEV_MODE)
		wordFile.open("D:\\coding\\C++Final\\C++Final_2\\Debug\\wordList.csv", ios::in | ios::out | ios::app);
	else
		wordFile.open("wordList.csv");
	if (!wordFile)
	{
		cout << "wordList.csv open failed!" << endl;
		abort();
	}

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
		if (wordIter == wordList.end())//δ��鵽��ͬ���ʣ���Iter��ָ��end()����ʱ�ɰѵ���д�뵽wordList��wordFile��
		{
			wordList.push_back(myWord);
			wordFile << myWord << endl;
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
	string tmpString = nowTester.get_name();
	state_socket(TESTER_RESULT, tmpString, sockClient);
	for (int i = wordAddList.size()-1; i>=0; i--)
	{
		state_socket(TESTER_RESULT, wordAddList[i], sockClient);
		wordAddList.pop_back();
	}
	closesocket(sockClient);
	return;
}
