#include"mainfunc.h"

int player_login(vector<player>& playerList)//获得名称在列表中的对应位置，以及验证其密码。验证成功则返回位置，否则返回-1
{
	int login_flag = -1;
	string name;
	string password;
	cout << "Login:\nPlease input your username:" << endl;
	cin >> name;
	for (vector<player>::iterator playerIter = playerList.begin(); playerIter != playerList.end();)
	{
		if (playerIter->get_name() == name)
		{
			cout << "Please input your password:" << endl;
			cin >> password;
			if (playerIter->get_password() == password)
			{
				login_flag = (int)(playerIter - playerList.begin());
			}
			playerIter = playerList.end();
		}
		else
			playerIter++;
	}
	if (login_flag == -1)
		cout << "Login Failure.\nHint: Is your username or password wrong ?" << endl;
	else
		cout << "Player Successful Login!\n" << endl;
	return login_flag;
}

int tester_login(vector<tester>& testerList)
{
	int login_flag = -1;
	string name;
	string password;
	cout << "Login:\nPlease input your username:" << endl;
	cin >> name;
	for (vector<tester>::iterator testerIter = testerList.begin(); testerIter != testerList.end();)
	{
		if (testerIter->get_name() == name)
		{
			cout << "Please input your password:" << endl;
			cin >> password;
			if (testerIter->get_password() == password)
			{
				login_flag = (int)(testerIter - testerList.begin());
			}
			testerIter = testerList.end();
		}
		else
			testerIter++;
	}
	if (login_flag == -1)
		cout << "Login Failure.\nHint: Is your username or password wrong ?" << endl;
	else
		cout << "Tester Successful Login!\n" << endl;
	return login_flag;
}