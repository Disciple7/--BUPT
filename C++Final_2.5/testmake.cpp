#include"mainfunc.h"

int state_testmake(vector<string>& wordList)
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
		for (; wordIter != wordList.end(); wordIter++)//输入一个单词后，在单词表里检查一遍
		{
			if (myWord == *wordIter)
				break;
		}
		if (wordIter == wordList.end())//未检查到相同单词，则Iter会指到end()，此时可把单词写入到wordList和wordFile中
		{
			wordList.push_back(myWord);
			wordFile << myWord << endl;
			wordCount++;
		}
		else//单词已存在时输出一个提示
		{
			cout << "This word has already been in the database." << endl;
		}
		cin >> myWord;//如果输入是:q，会直接退出
	}
	cout << "You contributed " << wordCount << " word(s) !" << endl;
	return wordCount;
}
void flush_tester(int nowUserPos, int wordAdd, vector<tester>& testerList)
{
	tester nowtester = testerList[nowUserPos];
	nowtester.rewards(wordAdd);	//更新此人的经验、等级、最佳轮数

	for (vector<tester>::iterator testerIter = testerList.begin(); testerIter != testerList.end();)//更新testerList
	{
		if (testerIter->get_name() == nowtester.get_name())
		{
			testerList.erase(testerIter);
			testerList.push_back(nowtester);
			break;
		}
		else
			testerIter++;
	}

	string tmptesterInfo;//更新testerFile
	vector<string> tmpInfoList;
	fstream testerFile;
	if (DEV_MODE)
		testerFile.open("D:\\coding\\C++Final\\C++Final_2\\Debug\\testerList.csv", ios::in | ios::out);
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
	while (testerFile && !(testerFile.peek()==EOF))
	{
		getline(testerFile, tmptesterInfo);
		string_split(tmptesterInfo, tmpInfoList, ",");
		if (tmpInfoList[0] == nowtester.get_name())
		{
			testerFile.seekp(tmpFptr);
			testerFile << nowtester.get_name() << "," << nowtester.get_password() << "," << nowtester.get_level() << "," << nowtester.get_problem_num();
			break;
		}
		tmpFptr = testerFile.tellg();
	}
	testerFile.close();
	return;
}
