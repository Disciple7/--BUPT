#include"c_mainfunc.h"

void state_register(SOCKADDR_IN addrSrv)
{
	cout << "\nPlease choose your user type (default : quit):\n(1)player\n(2)tester" << endl;
	int type_choice = 0;
	cin >> type_choice;	
	if (cin.fail())//����Ƿ�ʱ
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');//������뻺�����ĵ�ǰ�� 
	}
	if (type_choice == 1)
	{
		cout << "type : player\n" << endl;
	}
	else if (type_choice == 2)
	{
		cout << "type : tester\n" << endl;
	}
	else
		return;
	cout << "Please set your username:" << endl;
	string name;
	cin >> name;
	cout << "Please set your account password:" << endl;
	string password;
	cin >> password;
	//һ�ζ����ӣ������׽��ֲ����ͣ��ر�����
	SOCKET sockClient = socket_init(addrSrv);
	string tmpString = std::to_string(type_choice)+name + "," + password;//����"�˻�����,����,����"����"1,ppp,ppp"
	state_socket(USER_REGIST, tmpString,sockClient);
	closesocket(sockClient);

	cin.clear();
	cin.ignore(INT_MAX, '\n');//������뻺�����ĵ�ǰ�� 
}

