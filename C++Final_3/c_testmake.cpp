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
		for (; wordIter != wordList.end(); wordIter++)//输入一个单词后，在单词表里检查一遍
		{
			if (myWord == *wordIter)
				break;
		}
		if (wordIter == wordList.end())//未检查到相同单词，则Iter会指到end()，此时可把单词写入到wordList和wordAddList中
		{
			wordList.push_back(myWord);
			wordAddList.push_back(myWord);
			wordCount++;
		}
		else//单词已存在时输出一个提示
		{
			cout << "This word has already been in the c_database." << endl;
		}
		cin >> myWord;//如果输入是:q，会直接退出
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
	int flush_flag = state_socket(TESTER_RESULT, tmpString, sockClient);//发送所有信息，包括用户名和单词列表（整合成一个字符串）
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
