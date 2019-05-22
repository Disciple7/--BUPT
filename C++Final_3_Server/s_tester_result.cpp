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
		for (; wordIter != wordList.end(); wordIter++)//����һ�����ʺ��ڵ��ʱ�����һ��
		{
			if (myWord == *wordIter)
				break;
		}
		if (wordIter == wordList.end())//δ��鵽��ͬ���ʣ���Iter��ָ��end()����ʱ�ɰѵ���д�뵽wordList��wordFile��
		{
			wordList.push_back(myWord);
			wordFile << myWord << endl;
		}
	}
	//����¼����ɺ󣬸��¶�Ӧ���û�
	//����testerList
	tester nowTester("NULL", "NULL");
	vector<tester>::iterator testerIter = testerList.begin();
	for (;testerIter != testerList.end();)//����testerList
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
	//����testerFile
	string tmptesterInfo;
	vector<string> tmpInfoList;//����������������ȡ�ļ���ÿһ�е��û���Ϣ
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
	streamoff tmpFptr = testerFile.tellg();//��ÿ��ͷ����һ�е�ĩβ����һ����ַ�����������һ������Ϣ��Ҫ�޸ĵģ��ص����ͷ�����޸���Ϣ��
	while (testerFile && !(testerFile.peek() == EOF))
	{
		getline(testerFile, tmptesterInfo);//ȡ�ļ�һ�У������ֽ��user������
		string_split(tmptesterInfo, tmpInfoList, ",");
		if (tmpInfoList[0] == nowTester.get_name())
		{
			testerFile.seekp(tmpFptr);
			testerFile << nowTester.get_name() << "," << nowTester.get_password() << "," << nowTester.get_level() << "," << nowTester.get_problem_num() << endl;
			break;
		}
		tmpInfoList.clear();//tmpInfoListҪ������Ϊstring_split�õ���push_back���������������
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