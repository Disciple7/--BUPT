#pragma once
#include"s_global.h"
#include"s_database.h"
//ͨ�ź���(s_sock_server)
enum stateCode { ERR_CODE, WORD_SYNC, USER_REGIST, USER_LOGIN, PLAYER_RESULT, TESTER_RESULT=6, USER_QUERY };
void state_socket(SOCKET sockClient, vector<string>* wordListPtr, vector<player>* playerListPtr, vector<tester>* testerListPtr);//��������̺߳�����ʹ�������Զ���ģ��

//ע��״̬����s_user_register.cpp�У�
int state_register(vector<string>& tmpUser,vector<player>& playerList, vector<tester>& testerList);

//��¼������s_login.cpp��
int state_login(vector<string>&tmpUser, vector<player>& playerList, vector<tester>& testerList);

//ˢ���û��ɼ���s_player_result.cpp)
int state_player_result(vector<string>&tmpUser,vector<player>&playerList);//����1��ɹ�������ʧ��

//ˢ�³����߳ɼ�(s_tester_result)
int state_tester_result(string name, vector<string>& wordAddList,vector<string>& wordList, vector<tester>& testerList);

//��ѯ״̬��s_search.cpp��
void state_query(vector<string>& tmpInfo,vector<player>& playerList, vector<tester>& testerList);

//������������s_init.cpp�У�
void wordList_init(vector<string>& wordList);
void playerList_init(vector<player>& playerList);
void testerList_init(vector<tester>& testerList);
void show_main_info();

//��������
//�ַ����ָ������s_database.cpp�У�
void string_split( std::string& s, std::vector<std::string>& v,  const std::string& c);
//�ַ����ȽϺ�������s_database.cpp�У�
bool string_cmp( string&x,  string&y);
//������򷽷�����s_database.cpp�У�
bool player_name_cmp(string&p1, string&p2);//����������
bool player_level_cmp(string& p1, string&p2);//���ȼ�����
bool player_best_round_cmp(string& p1, string&p2);//����óɼ�����
//���������򷽷�����s_database.cpp�У�
bool tester_name_cmp(string&p1, string&p2);//����������
bool tester_level_cmp(string&p1, string&p2);//���ȼ�����
bool tester_problem_num_cmp(string&p1, string&p2);//������������