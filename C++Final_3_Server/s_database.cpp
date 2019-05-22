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
	if (this->best_round < bestRound)//若本次回合数大于历史最佳回合数则更新
		best_round = bestRound;
	while (exp / (10 * (level + 1)) > 0)//每升一级，需要10倍（等级+1）的经验再升级
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
		level++;//每升1级，升级需要单词数变为级数+1。0级1个单词，1级2个单词，以此类推。单词总数不像Exp一样会自减，因此递推得到等级与单词总数的关系。
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
//玩家排序方法
bool player_name_cmp(string&p1, string&p2)//按名称排序
{
	vector<string>tmp1, tmp2;
	string_split(p1, tmp1, "\t");
	string_split(p2, tmp2, "\t");
	return tmp1[0] < tmp2[0];
}
bool player_level_cmp(string& p1, string&p2)//按等级排序
{
	vector<string>tmp1, tmp2;
	string_split(p1, tmp1, "\t\t\t");
	string_split(p2, tmp2, "\t\t\t");
	return atoi(tmp1[1].data())< atoi(tmp2[1].data());
}
bool player_best_round_cmp(string& p1, string&p2)//按最好成绩排序
{
	vector<string>tmp1, tmp2;
	string_split(p1, tmp1, "\t\t\t");
	string_split(p2, tmp2, "\t\t\t");
	return atoi(tmp1[2].data())< atoi(tmp2[2].data());
}
//出题者排序方法
bool tester_name_cmp(string&p1, string&p2)//按名称排序
{
	vector<string>tmp1, tmp2;
	string_split(p1, tmp1, "\t\t\t");
	string_split(p2, tmp2, "\t\t\t");
	return tmp1[0]< tmp2[0];
}
bool tester_level_cmp(string&p1, string&p2)//按等级排序
{
	vector<string>tmp1, tmp2;
	string_split(p1, tmp1, "\t\t\t");
	string_split(p2, tmp2, "\t\t\t");
	return atoi(tmp1[1].data())< atoi(tmp2[1].data());
}
bool tester_problem_num_cmp(string&p1, string&p2)//按出题数排序
{
	vector<string>tmp1, tmp2;
	string_split(p1, tmp1, "\t\t\t");
	string_split(p2, tmp2, "\t\t\t");
	return atoi(tmp1[2].data())< atoi(tmp2[2].data());
}

