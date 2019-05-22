#include"s_mainfunc.h"

void wordList_init(vector<string>& wordList)
{
	string tmpString;
	fstream wordFile;
	if (DEV_MODE)
		wordFile.open("D:\\coding\\C++Final\\C++Final_3\\Debug\\wordList.csv", ios::out | ios::in);
	else
		wordFile.open("wordList.csv", ios::out | ios::in);

	while (wordFile && !(wordFile.peek() == EOF))//当wordFile存在，且不为结尾时。如果直接使用wordFile.eof()会造成最后一行读取两次。
	{
		wordFile >> tmpString;
		wordList.push_back(tmpString);
	}
	sort(wordList.begin(), wordList.end(), string_cmp);
	wordFile.close();
}
void playerList_init(vector<player>& playerList)
{
	string tmpPlayerInfo;
	vector<string> tmpInfoList;
	fstream playerFile;
	if (DEV_MODE)
		playerFile.open("D:\\coding\\C++Final\\C++Final_3\\Debug\\playerList.csv", ios::out | ios::in);
	else
		playerFile.open("playerList.csv", ios::out | ios::in);
	while (playerFile && !(playerFile.peek() == EOF))
	{
		playerFile >> tmpPlayerInfo;
		string_split(tmpPlayerInfo, tmpInfoList, ",");
		player tmpPlayer(tmpInfoList[0], tmpInfoList[1], stoi(tmpInfoList[2]), stoi(tmpInfoList[3]), stoi(tmpInfoList[4]));
		playerList.push_back(tmpPlayer);
		tmpInfoList.clear();
	}
	playerFile.close();
}
void testerList_init(vector<tester>& testerList)
{
	string tmpTesterInfo;
	vector<string> tmpInfoList;
	fstream testerFile;
	if (DEV_MODE)
		testerFile.open("D:\\coding\\C++Final\\C++Final_3\\Debug\\testerList.csv", ios::out | ios::in);
	else
		testerFile.open("testerList.csv", ios::out | ios::in);

	while (testerFile && !(testerFile.peek() == EOF))
	{
		testerFile >> tmpTesterInfo;
		string_split(tmpTesterInfo, tmpInfoList, ",");
		tester tmpTester(tmpInfoList[0], tmpInfoList[1], stoi(tmpInfoList[2]), stoi(tmpInfoList[3]));
		testerList.push_back(tmpTester);
		tmpInfoList.clear();
	}
	testerFile.close();
}