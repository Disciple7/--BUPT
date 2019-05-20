#include"s_mainfunc.h"

int state_player_result(vector<string>&tmpUser, vector<player>&playerList)
{
	string name = tmpUser[0];
	int bestRound = atoi(tmpUser[1].data());
	player nowPlayer("NULL", "NULL");
	if (bestRound == 0)
	{
		cout << "string transfer err 04" << endl;
		return 0;//���һ���˵���ѳɼ�Ϊ0����û�и��µı�Ҫ��������ַ���ת������Ҳ���ܸ��¡�
	}
	//����playerList
	vector<player>::iterator playerIter = playerList.begin();
	for (; playerIter != playerList.end();)//����playerList
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
	//����playerFile
	string tmpPlayerInfo;
	vector<string> tmpInfoList;
	fstream playerFile;
	if (DEV_MODE)
		playerFile.open("D:\\coding\\C++Final\\C++Final_2\\Debug\\playerList.csv", ios::in | ios::out);
	else
		playerFile.open("playerList.csv", ios::in | ios::out);

	if (!playerFile)
	{
		cout << "playerList.csv open failed! " << endl;
		abort();
	}
	playerFile.seekp(0);
	getline(playerFile, tmpPlayerInfo);
	streamoff tmpFptr = playerFile.tellg();//��ÿ��ͷ����һ�е�ĩβ����һ����ַ�����������һ������Ϣ��Ҫ�޸ĵģ��ص����ͷ�����޸���Ϣ��
	while (playerFile && !(playerFile.peek() == EOF))
	{
		getline(playerFile, tmpPlayerInfo);
		string_split(tmpPlayerInfo, tmpInfoList, ",");
		if (tmpInfoList[0] == nowPlayer.get_name())
		{
			playerFile.seekp(tmpFptr);
			playerFile << nowPlayer.get_name() << "," << nowPlayer.get_password() << "," << nowPlayer.get_level() << "," << nowPlayer.get_exp() << "," << nowPlayer.get_best_round();
			break;
		}
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