#include"mainfunc.h"
int state_game(vector<string>& wordList)//返回值为闯关数
{
	int rewards = 0;
	int round = 0;//第几轮
	int wordCount =5;
	int size = wordList.size();
	int round_time = 3000;
	int biasA = 0;
	int biasB = biasA + wordList.size() / 2;
	int bonus = 0;//时间奖励，每积累3次时间奖励可以换算成一关
	int health = 5;//错误5次则终止游戏

	string targetWord;
	string myWord="\0";
	time_t timer;

	sort(wordList.begin(), wordList.end(), string_cmp);
	cout << "Game Start ! Type \":q\" to Quit !" << endl;
	while(myWord!=":q"&&health>0)
	{
		if (wordCount == 0)
		{
			round++;//每轮round+1个单词。本轮单词完成后重置并进入下一轮。
			wordCount = round+1;
			if (biasA < (size /3)*2)
			{
				biasA++;
				biasB = biasA + (size - biasA) / 2;
			}
			else
			{
				biasB = size - 1;//最难时抽取整个词库后1/3的单词
			}
			round_time = round_time*size / (size + round);//round_time逐渐减少
			cout << "Next Round " << round << " ! " << wordCount << "word(s) left !" << endl;
		}
		targetWord = wordList[biasA+rand()%(biasB-biasA)];//限定抽取范围随等级变化
		cout << targetWord;
		Sleep(round_time);
		cout << "\r                   \r";//清除一行，并把光标移到开始处
		timer = time(NULL);
		cin >> myWord;
		if (targetWord == myWord)
		{
			wordCount--;
			timer = time(NULL) - timer;
			cout << "Correct !" << endl;
			if (timer < 3)
			{
				cout << "Fast Type! Bonus! " << endl;
				bonus++;
			}
		}
		else if(myWord !=":q")
		{
			cout << "Wrong !" << endl;
			health--;
		}
	}
	cout << "Your Best Round：" << round << endl;
	return round+bonus/3;
}
void flush_player(int nowUserPos, int bestRound, vector<player>& playerList)
{
	player nowPlayer = playerList[nowUserPos];
	nowPlayer.rewards(bestRound);	//更新此人的经验、等级、最佳轮数

	for (vector<player>::iterator playerIter=playerList.begin(); playerIter!=playerList.end();)//更新playerList
	{
		if (playerIter->get_name() == nowPlayer.get_name())
		{
			playerList.erase(playerIter);
			playerList.push_back(nowPlayer);
			break;
		}
		else
			playerIter++;
	}

	string tmpPlayerInfo;//更新playerFile
	vector<string> tmpInfoList;
	fstream playerFile;
	if(DEV_MODE)
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
	streamoff tmpFptr = playerFile.tellg();//在每行头（上一行的末尾）设一个地址。如果读完上一行行信息是要修改的，回到这个头，并修改信息。
	while (playerFile && !(playerFile.peek()==EOF))
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
	playerFile.close();
	return;
}
