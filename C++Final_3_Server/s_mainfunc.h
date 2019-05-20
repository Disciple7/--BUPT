#pragma once
#include"s_global.h"
#include"s_database.h"
//ͨ�ź���
SOCKET socket_init(SOCKADDR_IN addrSrv);//��ͨ��ģʽ���Զ�����һ�������׽���
enum stateCode { ERR_CODE, WORD_SYNC, USER_REGIST, USER_LOGIN, PLAYER_RESULT, USER_LOGIN, TESTER_RESULT, USER_QUERY };


//ע��״̬����user_register.cpp�У�
int state_register(vector<string>& tmpUser,vector<player>& playerList, vector<tester>& testerList);

//��¼������login.cpp��
int state_login(vector<string>&tmpUser, vector<player>& playerList, vector<tester>& testerList);

//��Ϸ״̬��game.cpp��
int state_game(vector<string>& wordList);
void flush_player(int nowUserPos, int expReward, vector<player>& playerList);

//����״̬��testmake.cpp��
int state_testmake(vector<string>& wordList);
void flush_tester(int nowUserPos, int problemNumReward, vector<tester>& testerList);

//��ѯ״̬��search.cpp��
void state_query(vector<player>& playerList, vector<tester>& testerList);

//������������init.cpp�У�
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
bool player_name_cmp(player&p1, player&p2);//����������
bool player_level_cmp(player& p1, player&p2);//���ȼ�����
bool player_best_round_cmp(player& p1, player&p2);//����óɼ�����
//���������򷽷�����s_database.cpp�У�
bool tester_name_cmp(tester&p1, tester&p2);//����������
bool tester_level_cmp(tester&p1, tester&p2);//���ȼ�����
bool tester_problem_num_cmp(tester&p1, tester&p2);//������������