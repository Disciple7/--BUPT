#include"s_mainfunc.h"

int state_player_result(vector<string>&tmpUser, vector<player>&playerList)
{
	string name = tmpUser[0];
	int bestRound = atoi(tmpUser[1].c_str());
	player nowPlayer("NULL", "NULL");
	if (bestRound == 0)
	{
		cout << "string transfer err 04" << endl;
		return 0;//如果一个人的最佳成绩为0，则没有更新的必要。如果是字符串转换出错，也不能更新。
	}
	//更新playerList
	vector<player>::iterator playerIter = playerList.begin();
	for (; playerIter != playerList.end();)//更新playerList
	{
		if (playerIter->get_name() == name)
		{
			(*playerIter).rewards(bestRound);
			nowPlayer = *playerIter;
			break;
		}
		else
			playerIter++;
	}
	//更新playerFile
	string tmpPlayerInfo;
	vector<string> tmpInfoList;
	fstream playerFile;
	if (DEV_MODE)
		playerFile.open("D:\\coding\\C++Final\\C++Final_3\\Debug\\playerList.csv", ios::in | ios::out);
	else
		playerFile.open("playerList.csv", ios::in | ios::out);

	if (!playerFile)
	{
		cout << "playerList.csv open failed! " << endl;
		abort();
	}
	playerFile.seekp(0);
	getline(playerFile, tmpPlayerInfo);
	streamoff tmpFptr = playerFile.tellg();//在每行头（上一行的末尾）设一个地址。如果读完上一行行信息是要修改的，回到这个头，并修改信息。
	while (playerFile && !(playerFile.peek() == EOF))
	{
		getline(playerFile, tmpPlayerInfo);//取文件一行，把它分解成user的数据
		string_split(tmpPlayerInfo, tmpInfoList, ",");
		if (tmpInfoList[0] == nowPlayer.get_name())
		{
			playerFile.seekp(tmpFptr);
			playerFile << "\n" << nowPlayer.get_name() << "," << nowPlayer.get_password() << "," << nowPlayer.get_level() << "," << nowPlayer.get_exp() << "," << nowPlayer.get_best_round() << endl;
			break;
		}
		tmpInfoList.clear();//tmpInfoList要清理，因为string_split用的是push_back，不检查容器内容
		tmpFptr = playerFile.tellg();
	}
	if ((playerIter != playerList.end()) && (!playerFile.eof()))
	{
		playerFile.close();
		return 1;
	}
	else
	{
		playerFile.close();
		cout << "player flush err 04" << endl;
		return 0;
	}
}