#include"c_mainfunc.h"
int state_game(vector<string>& wordList)//����ֵΪ������
{
	int rewards = 0;
	int round = 0;//�ڼ���
	int wordCount =5;
	int size = wordList.size();
	int round_time = 3000;
	int biasA = 0;
	int biasB = biasA + wordList.size() / 2;
	int bonus = 0;//ʱ�佱����ÿ����3��ʱ�佱�����Ի����һ��
	int health = 5;//����5������ֹ��Ϸ

	string targetWord;
	string myWord="\0";
	time_t timer;

	cout << "Game Start ! Type \":q\" to Quit !" << endl;
	while(myWord!=":q"&&health>0)
	{
		if (wordCount == 0)
		{
			round++;//ÿ��round+1�����ʡ����ֵ�����ɺ����ò�������һ�֡�
			wordCount = round+1;
			if (biasA < (size /3)*2)
			{
				biasA++;
				biasB = biasA + (size - biasA) / 2;
			}
			else
			{
				biasB = size - 1;//����ʱ��ȡ�����ʿ��1/3�ĵ���
			}
			round_time = round_time*size / (size + round);//round_time�𽥼���
			cout << "Next Round " << round << " ! " << wordCount << "word(s) left !" << endl;
		}
		targetWord = wordList[biasA+rand()%(biasB-biasA)];//�޶���ȡ��Χ��ȼ��仯
		cout << targetWord;
		Sleep(round_time);
		cout << "\r                   \r";//���һ�У����ѹ���Ƶ���ʼ��
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
	cout << "Your Best Round��" << round << endl;
	return round+bonus/3;
}
void flush_player(player& nowPlayer,int bestRound, SOCKADDR_IN addrSrv)
{
	int flush_flag = -1;
	SOCKET sockClient = socket_init(addrSrv);
	string tmpString = nowPlayer.get_name() + "," + std::to_string(bestRound);
	flush_flag = state_socket(PLAYER_RESULT, tmpString, sockClient);
	closesocket(sockClient);
	for (int i = 0; flush_flag != 0 && i < 2; i++)
	{
		cout << "Reconnecting......" << endl;
		sockClient = socket_init(addrSrv);
		flush_flag = state_socket(PLAYER_RESULT, tmpString, sockClient);
		closesocket(sockClient);
	}
	if (flush_flag == 0)cout << "Result Upload Success" << endl;
	else cout << "Result Upload Failure" << endl;
	//���´��˵ľ��顢�ȼ�������������������һ��ʧ�ܾ��ٷ���һ�Ρ���������ʧ��ʱ�򷵻�ʧ�ܡ�
	return;
}
