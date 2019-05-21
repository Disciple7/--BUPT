#pragma once
#include"s_global.h"
#include"s_database.h"
//通信函数(s_sock_server)
enum stateCode { ERR_CODE, WORD_SYNC, USER_REGIST, USER_LOGIN, PLAYER_RESULT, TESTER_RESULT=6, USER_QUERY };
void state_socket(SOCKET sockClient, vector<string>* wordListPtr, vector<player>* playerListPtr, vector<tester>* testerListPtr);//服务端子线程函数。使用有限自动机模型

//注册状态（在s_user_register.cpp中）
int state_register(vector<string>& tmpUser,vector<player>& playerList, vector<tester>& testerList);

//登录函数（s_login.cpp）
int state_login(vector<string>&tmpUser, vector<player>& playerList, vector<tester>& testerList);

//刷新用户成绩（s_player_result.cpp)
int state_player_result(vector<string>&tmpUser,vector<player>&playerList);//返回1则成功，否则失败

//刷新出题者成绩(s_tester_result)
int state_tester_result(string name, vector<string>& wordAddList,vector<string>& wordList, vector<tester>& testerList);

//查询状态（s_search.cpp）
void state_query(vector<string>& tmpInfo,vector<player>& playerList, vector<tester>& testerList);

//程序启动（在s_init.cpp中）
void wordList_init(vector<string>& wordList);
void playerList_init(vector<player>& playerList);
void testerList_init(vector<tester>& testerList);
void show_main_info();

//其他函数
//字符串分割函数（在s_database.cpp中）
void string_split( std::string& s, std::vector<std::string>& v,  const std::string& c);
//字符串比较函数（在s_database.cpp中）
bool string_cmp( string&x,  string&y);
//玩家排序方法（在s_database.cpp中）
bool player_name_cmp(string&p1, string&p2);//按名称排序
bool player_level_cmp(string& p1, string&p2);//按等级排序
bool player_best_round_cmp(string& p1, string&p2);//按最好成绩排序
//出题者排序方法（在s_database.cpp中）
bool tester_name_cmp(string&p1, string&p2);//按名称排序
bool tester_level_cmp(string&p1, string&p2);//按等级排序
bool tester_problem_num_cmp(string&p1, string&p2);//按出题数排序