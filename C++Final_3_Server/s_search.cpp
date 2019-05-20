#include"s_mainfunc.h"

void state_query(vector<string>& tmpInfo,vector<player>& playerList, vector<tester>& testerList)
{
	int order =atoi(tmpInfo[0].c_str());
	if (order == 0)
	{
		cout << "state_query err 07_4" << endl;
		return;
	}
	string userName = tmpInfo[1];
	string tmpString;
	tmpInfo.clear();
	switch (order)
	{
	case 1:
	{
		tmpInfo.push_back("Name\t\t\tLevel\t\t\tBestRound\t\t\tExp");
		for (unsigned int i = 0; i < playerList.size(); i++)
		{
			tmpString = playerList[i].get_name() + "\t\t\t" + std::to_string(playerList[i].get_level()) 
				+ "\t\t\t" + std::to_string(playerList[i].get_best_round()) + "\t\t\t" + std::to_string(playerList[i].get_exp()) + "\n";
			tmpInfo.push_back(tmpString);
		}
		order = atoi(userName.c_str());
		if (order == 3)
			sort(tmpInfo.begin() + 1, tmpInfo.end(), player_best_round_cmp);//可能会遇到同时访问的问题，就把排序改了一下，变得有点奇怪了......
		else if (order == 2)
			sort(tmpInfo.begin() + 1, tmpInfo.end(), player_level_cmp);
		else if (order == 1)
			sort(tmpInfo.begin() + 1, tmpInfo.end(), player_name_cmp);
		else
			cout << "player query code err 07_5" << endl;
		break;
	}
	case 2:
	{
		tmpInfo.push_back("Name\t\t\tLevel\tProblemNum");
		for (unsigned int i = 0; i < testerList.size(); i++)
		{
			tmpString = testerList[i].get_name() + "\t\t\t" + std::to_string(testerList[i].get_level()) 
				+ "\t\t\t" + std::to_string(testerList[i].get_problem_num()) + "\n";
			tmpInfo.push_back(tmpString);
		}
		order = atoi(userName.c_str());
		if (order == 3)
			sort(tmpInfo.begin() + 1, tmpInfo.end(), tester_problem_num_cmp);
		else if (order == 2)
			sort(tmpInfo.begin() + 1, tmpInfo.end(), tester_level_cmp);
		else if (order == 1)
			sort(tmpInfo.begin() + 1, tmpInfo.end(), tester_name_cmp);
		else
			cout << "tester query code err 07_6" << endl;
		break;
	}
	case 3:
	{
		vector<player>::iterator playerIter = playerList.begin();
		for (; playerIter != playerList.end(); playerIter++)
		{
			if (playerIter->get_name() == userName)
			{
				tmpInfo.push_back("PlayerInfo:\nName\t\t\tLevel\t\t\tBestRound\t\t\tExp\n");
				tmpInfo.push_back(playerIter->get_name() + "\t\t\t" + std::to_string(playerIter->get_level()) + "\t\t\t" 
					+ std::to_string(playerIter->get_best_round()) + "\t\t\t" + std::to_string(playerIter->get_exp()) + "\n");
				break;
			}
		}
		vector<tester>::iterator testerIter = testerList.begin();
		for (; testerIter != testerList.end(); testerIter++)
		{
			if (testerIter->get_name() == userName)
			{
				tmpInfo.push_back("testerInfo:\nName\t\t\tLevel\t\t\tProblemNum\n");
				tmpInfo.push_back(testerIter->get_name() + "\t\t\t" + std::to_string(testerIter->get_level()) + "\t\t\t" 
					+ std::to_string(testerIter->get_problem_num()) + "\n");
				break;
			}
		}
		if (playerIter == playerList.end() && testerIter == testerList.end())
			tmpInfo.push_back("This user does not exist.\n");
		break;
	}
	default:
		break;
	}
	return;
}