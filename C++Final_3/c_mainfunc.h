#pragma once
#include"c_global.h"
#include"c_database.h"

//ͨ�ź���
SOCKET socket_init(SOCKADDR_IN addrSrv);//��ͨ��ģʽ���Զ�����һ�������׽���
enum stateCode { ERR_CODE, WORD_SYNC, USER_REGIST, USER_LOGIN, PLAYER_RESULT, TESTER_RESULT=6, USER_QUERY };
//״̬�м����һ��5�ţ���Ϊ��TesterLogin��PlayerLogin�ϲ��ˡ�
int state_socket(stateCode,string& myInfo,SOCKET sockClient);//���������ֱ��ת���ַ���������
int state_socket(stateCode, vector<string>& wordList, SOCKET sockClient);//���дʿ�ͬ��ʱ��Ҫ����һ������


//ע��״̬����user_register.cpp�У�
void state_register(SOCKADDR_IN addrSrv);

//��¼������login.cpp��
int player_login(player& nowPlayer, SOCKADDR_IN addrSrv);
int tester_login(tester& nowTester, SOCKADDR_IN addrSrv);

//��Ϸ״̬��game.cpp��
int state_game(vector<string>& wordList);
void flush_player(player& nowPlayer, int RoundReward, SOCKADDR_IN addrSrv);

//����״̬��testmake.cpp��
int state_testmake(vector<string>& wordList,vector<string>& wordAddList);
void flush_tester(tester& nowTester, vector<string>& wordAddList, SOCKADDR_IN addrSrv);

//��ѯ״̬��search.cpp��
void state_query(SOCKADDR_IN addrSrv);

//������������init.cpp�У�
void show_main_info();

//��������
//�ַ����ָ������c_database.cpp�У�
void string_split( std::string& s, std::vector<std::string>& v,  const std::string& c);
//�ַ����ȽϺ�������c_database.cpp�У�
bool string_cmp( string&x,  string&y);
//������򷽷�����c_database.cpp�У�
bool player_name_cmp(player&p1, player&p2);//����������
bool player_level_cmp(player& p1, player&p2);//���ȼ�����
bool player_best_round_cmp(player& p1, player&p2);//����óɼ�����
//���������򷽷�����c_database.cpp�У�
bool tester_name_cmp(tester&p1, tester&p2);//����������
bool tester_level_cmp(tester&p1, tester&p2);//���ȼ�����
bool tester_problem_num_cmp(tester&p1, tester&p2);//������������