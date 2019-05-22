#include"s_mainfunc.h"

int state_tester_result(string name, vector<string>& wordAddList,vector<string>& wordList, vector<tester>& testerList)
{
	fstream wordFile;
	if (DEV_MODE)
		wordFile.open("D:\\coding\\C++Final\\C++Final_3\\Debug\\wordList.csv", ios::in | ios::out | ios::app);
	else
		wordFile.open("wordList.csv");
	if (!wordFile)
	{
		cout << "wordList.csv open failed!" << endl;
		abort();
	}

	unsigned int wordCount = 0;
	string myWord;
	for(wordCount =0;wordCount<wordAddList.size();wordCount++)
	{
		myWord = wordAddList[0];
		vector<string>::iterator wordIter = wordList.begin();
		for (; wordIter != wordList.end(); wordIter++)//输入一个单词后，在单词表里检查一遍
		{
			if (myWord == *wordIter)
				break;
		}
		if (wordIter == wordList.end())//未检查到相同单词，则Iter会指到end()，此时可把单词写入到wordList和wordFile中
		{
			wordList.push_back(myWord);
			wordFile << myWord << endl;
		}
	}
	//单词录入完成后，更新对应的用户
	//更新testerList
	tester nowTester("NULL", "NULL");
	vector<tester>::iterator testerIter = testerList.begin();
	for (;testerIter != testerList.end();)//更新testerList
	{
		if (testerIter->get_name() == name)
		{
			(*testerIter).rewards(wordCount);
			nowTester = (*testerIter);
			break;
		}
		else
			testerIter++;
	}
	//更新testerFile
	string tmptesterInfo;
	vector<string> tmpInfoList;//这两个变量用于提取文件中每一行的用户信息
	fstream testerFile;
	if (DEV_MODE)
		testerFile.open("D:\\coding\\C++Final\\C++Final_3\\Debug\\testerList.csv", ios::in | ios::out);
	else
		testerFile.open("testerList.csv");
	if (!testerFile)
	{
		cout << "testerList.csv open failed! " << endl;
		abort();
	}
	testerFile.seekp(0);
	getline(testerFile, tmptesterInfo);
	streamoff tmpFptr = testerFile.tellg();//在每行头（上一行的末尾）设一个地址。如果读完上一行行信息是要修改的，回到这个头，并修改信息。
	while (testerFile && !(testerFile.peek() == EOF))
	{
		getline(testerFile, tmptesterInfo);//取文件一行，把它分解成user的数据
		string_split(tmptesterInfo, tmpInfoList, ",");
		if (tmpInfoList[0] == nowTester.get_name())
		{
			testerFile.seekp(tmpFptr);
			testerFile << nowTester.get_name() << "," << nowTester.get_password() << "," << nowTester.get_level() << "," << nowTester.get_problem_num() << endl;
			break;
		}
		tmpInfoList.clear();//tmpInfoList要清理，因为string_split用的是push_back，不检查容器内容
		tmpFptr = testerFile.tellg();
	}
	if ((testerIter != testerList.end()) && (!testerFile.eof()))
	{
		testerFile.close();
		return 1;
	}
	else
	{
		testerFile.close();
		cout << "tester flush err 04" << endl;
		return 0;
	}
}