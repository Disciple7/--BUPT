#pragma once
#include "c_global.h"

class user
{
private:
	string name;
	string password;
public:
	user(string newName, string newPassword);
	~user();
	string get_name();
	string get_password();
};
class player : public user
{
private:
	int exp;
	int level;
	int best_round;
public:
	player(string newName, string newPassword,int newExp=0, int newLevel=0,int newbestRound=0);
	~player();
	int get_level();
	int get_exp();
	int get_best_round();
};
class tester : public user
{
private:
	int problemNum;
	int level;
public:
	tester(string newName, string newPassword, int newProblemNum = 0, int newLevel = 0);
	~tester();
	short get_level();
	int get_problem_num();
};