#include"s_mainfunc.h"

int state_login(vector<string>&tmpUser, vector<player>& playerList, vector<tester>& testerList)
{
	string name = tmpUser[1];
	string password = tmpUser[2];
	int login_flag = 2;
	if (tmpUser[0] == "1")
	{
		for (vector<player>::iterator playerIter = playerList.begin(); playerIter != playerList.end();)
		{
			if (playerIter->get_name() == name)
			{
				if (playerIter->get_password() == password)
				{
					login_flag = 1;
					return login_flag;
				}
				playerIter = playerList.end();
			}
			else
				playerIter++;
		}
	}
	else if (tmpUser[0] == "2")
	{
		for (vector<tester>::iterator testerIter = testerList.begin(); testerIter != testerList.end();)
		{
			if (testerIter->get_name() == name)
			{
				if (testerIter->get_password() == password)
				{
					login_flag = 1;
					return login_flag;
				}
				testerIter = testerList.end();
			}
			else
				testerIter++;
		}
	}
	else
	{
		cout << "userType Err 03_2" << endl;
		return -1;
	}
	return login_flag;
}