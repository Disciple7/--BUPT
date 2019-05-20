#include"s_database.h"

user::user(string newName, string newPassword)
{
	name = newName;
	password = newPassword;
};
user::~user()
{
};
string user::get_name()
{
	return name;
}
string user::get_password()
{
	return password;
}

player::player(string newName, string newPassword,int newExp,int newLevel,int newbestRound) : user(newName,newPassword)
{
	exp = newExp;
	level = newLevel;
	best_round = newbestRound;
};
player::~player()
{
}
int player::get_exp() { return exp; }
int player::get_level() { return level; }
int player::get_best_round() { return best_round; }
void player::rewards(int bestRound)
{
	exp += 5*bestRound*bestRound;
	if (this->best_round < bestRound)//�����λغ���������ʷ��ѻغ��������
		best_round = bestRound;
	while (exp / (10 * (level + 1)) > 0)//ÿ��һ������Ҫ10�����ȼ�+1���ľ���������
	{
		exp -= 10 * (level + 1); 
		level++;
	}
}

tester::tester(string newName, string newPassword,int newProblemNum, int newLevel) :user(newName, newPassword)
{
	level = newProblemNum;
	problemNum = newProblemNum;
}
tester::~tester()
{
}
short tester::get_level() { return level; }
int tester::get_problem_num() { return problemNum; }
void tester::rewards(int wordAdd)
{
	problemNum += wordAdd;
	while (problemNum >= ((level + 1)*(level + 2) / 2))
		level++;//ÿ��1����������Ҫ��������Ϊ����+1��0��1�����ʣ�1��2�����ʣ��Դ����ơ�������������Expһ�����Լ�����˵��Ƶõ��ȼ��뵥�������Ĺ�ϵ��
};

void string_split(std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

bool string_cmp(string&x, string&y)
{
	return x.length() > y.length();
}
//������򷽷�
bool player_name_cmp(string&p1, string&p2)//����������
{
	vector<string>tmp1, tmp2;
	string_split(p1, tmp1, "\t");
	string_split(p2, tmp2, "\t");
	return tmp1[0] < tmp2[0];
}
bool player_level_cmp(string& p1, string&p2)//���ȼ�����
{
	vector<string>tmp1, tmp2;
	string_split(p1, tmp1, "\t\t\t");
	string_split(p2, tmp2, "\t\t\t");
	return atoi(tmp1[1].data())< atoi(tmp2[1].data());
}
bool player_best_round_cmp(string& p1, string&p2)//����óɼ�����
{
	vector<string>tmp1, tmp2;
	string_split(p1, tmp1, "\t\t\t");
	string_split(p2, tmp2, "\t\t\t");
	return atoi(tmp1[2].data())< atoi(tmp2[2].data());
}
//���������򷽷�
bool tester_name_cmp(string&p1, string&p2)//����������
{
	vector<string>tmp1, tmp2;
	string_split(p1, tmp1, "\t\t\t");
	string_split(p2, tmp2, "\t\t\t");
	return tmp1[0]< tmp2[0];
}
bool tester_level_cmp(string&p1, string&p2)//���ȼ�����
{
	vector<string>tmp1, tmp2;
	string_split(p1, tmp1, "\t\t\t");
	string_split(p2, tmp2, "\t\t\t");
	return atoi(tmp1[1].data())< atoi(tmp2[1].data());
}
bool tester_problem_num_cmp(string&p1, string&p2)//������������
{
	vector<string>tmp1, tmp2;
	string_split(p1, tmp1, "\t\t\t");
	string_split(p2, tmp2, "\t\t\t");
	return atoi(tmp1[2].data())< atoi(tmp2[2].data());
}

