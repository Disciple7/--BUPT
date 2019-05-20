#pragma once
#include"c_global.h"
#include"c_database.h"

//通信函数
SOCKET socket_init(SOCKADDR_IN addrSrv);//短通信模式。自动生成一个可用套接字
enum stateCode { ERR_CODE, WORD_SYNC, USER_REGIST, USER_LOGIN, PLAYER_RESULT, TESTER_RESULT=6, USER_QUERY };
//状态中间空了一个5号，因为把TesterLogin和PlayerLogin合并了。
int state_socket(stateCode,string& myInfo,SOCKET sockClient);//其他情况下直接转成字符串传就行
int state_socket(stateCode, vector<string>& wordList, SOCKET sockClient);//进行词库同步时需要传入一个容器


//注册状态（在user_register.cpp中）
void state_register(SOCKADDR_IN addrSrv);

//登录函数（login.cpp）
int player_login(player& nowPlayer, SOCKADDR_IN addrSrv);
int tester_login(tester& nowTester, SOCKADDR_IN addrSrv);

//游戏状态（game.cpp）
int state_game(vector<string>& wordList);
void flush_player(player& nowPlayer, int RoundReward, SOCKADDR_IN addrSrv);

//出题状态（testmake.cpp）
int state_testmake(vector<string>& wordList,vector<string>& wordAddList);
void flush_tester(tester& nowTester, vector<string>& wordAddList, SOCKADDR_IN addrSrv);

//查询状态（search.cpp）
void state_query(SOCKADDR_IN addrSrv);

//程序启动（在init.cpp中）
void show_main_info();

//其他函数
//字符串分割函数（在c_database.cpp中）
void string_split( std::string& s, std::vector<std::string>& v,  const std::string& c);
//字符串比较函数（在c_database.cpp中）
bool string_cmp( string&x,  string&y);
//玩家排序方法（在c_database.cpp中）
bool player_name_cmp(player&p1, player&p2);//按名称排序
bool player_level_cmp(player& p1, player&p2);//按等级排序
bool player_best_round_cmp(player& p1, player&p2);//按最好成绩排序
//出题者排序方法（在c_database.cpp中）
bool tester_name_cmp(tester&p1, tester&p2);//按名称排序
bool tester_level_cmp(tester&p1, tester&p2);//按等级排序
bool tester_problem_num_cmp(tester&p1, tester&p2);//按出题数排序