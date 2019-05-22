#include"s_mainfunc.h"

int state_register(vector<string>& tmpUser,vector<player>& playerList, vector<tester>& testerList)
{
	if (tmpUser[0] == "1")
	{
		player newPlayer(tmpUser[1], tmpUser[2]);
		for (int i = 0; i < (int)playerList.size(); i++)
		{
			if (playerList[i].get_name() == newPlayer.get_name())
			{
				cout << "The Player-Name has been registered. Register failed!" << endl;
				return 2;
			}
		}
		fstream playerFile;
		if (DEV_MODE)
			playerFile.open("D:\\coding\\C++Final\\C++Final_3\\Debug\\playerList.csv", ios::out | ios::app);
		else
			playerFile.open("playerList.csv");
		if (!playerFile)
		{
			cout << "playerList.csv open failed! " << endl;
			return -1;
		}
		playerFile << "\n" << newPlayer.get_name() << "," << newPlayer.get_password() << ",0,0,0";//换行写在前面。写在最后面会导致读两次。
		playerFile.close();
		playerList.push_back(newPlayer);
		cout << "Player successfully registers!" << endl;
		return 1;
	}
	else if (tmpUser[0] == "2")
	{
		tester newTester(tmpUser[1], tmpUser[2]);
		for (int i = 0; i < (int)testerList.size(); i++)
		{
			if (testerList[i].get_name() == newTester.get_name())
			{
				cout << "The Tester-Name has been registered. Register failed!" << endl;
				return 2;
			}
		}
		fstream testerFile;
		if (DEV_MODE)
			testerFile.open("D:\\coding\\C++Final\\C++Final_3\\Debug\\testerList.csv", ios::out | ios::app);
		else
			testerFile.open("testerFile.csv");
		if (!testerFile)
		{
			cout << "testerList.csv open failed! " << endl;
			return -1;
		}
		testerFile << "\n" << newTester.get_name() << "," << newTester.get_password() << ",0,0";
		testerFile.close();
		testerList.push_back(newTester);
		cout << "Tester successfully registers!" << endl;
		return 1;
	}
	else
	{
		cout << "USER_REGIST ERR 02_2" << endl;
		return 0;
	}
}