#pragma once
#include"global.h"
#include"database.h"


//注册状态（在user_register.cpp中）
void state_register(vector<player>& playerList, vector<tester>& testerList);

//登录函数（login.cpp）
int player_login(vector<player>& playerList);
int tester_login(vector<tester>& testerList);

//游戏状态（game.cpp）
int state_game(vector<string>& wordList);
void flush_player(int nowUserPos, int expReward, vector<player>& playerList);

//出题状态（testmake.cpp）
int state_testmake(vector<string>& wordList);
void flush_tester(int nowUserPos, int problemNumReward, vector<tester>& testerList);

//查询状态（search.cpp）
void state_query(vector<player>& playerList, vector<tester>& testerList);

//程序启动（在init.cpp中）
void wordList_init(vector<string>& wordList);
void playerList_init(vector<player>& playerList);
void testerList_init(vector<tester>& testerList);
void show_main_info();

//其他函数
//字符串分割函数（在database.cpp中）
void string_split( std::string& s, std::vector<std::string>& v,  const std::string& c);
//字符串比较函数（在database.cpp中）
bool string_cmp( string&x,  string&y);
//玩家排序方法（在database.cpp中）
bool player_name_cmp(player&p1, player&p2);//按名称排序
bool player_level_cmp(player& p1, player&p2);//按等级排序
bool player_best_round_cmp(player& p1, player&p2);//按最好成绩排序
//出题者排序方法（在database.cpp中）
bool tester_name_cmp(tester&p1, tester&p2);//按名称排序
bool tester_level_cmp(tester&p1, tester&p2);//按等级排序
bool tester_problem_num_cmp(tester&p1, tester&p2);//按出题数排序