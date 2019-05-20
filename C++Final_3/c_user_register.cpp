#include"c_mainfunc.h"

void state_register(SOCKADDR_IN addrSrv)
{
	cout << "\nPlease choose your user type (default : quit):\n(1)player\n(2)tester" << endl;
	int type_choice = 0;
	cin >> type_choice;	
	if (cin.fail())//输入非法时
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');//清除输入缓冲区的当前行 
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
	//一次短连接：构造套接字并发送，关闭连接
	SOCKET sockClient = socket_init(addrSrv);
	string tmpString = std::to_string(type_choice)+name + "," + password;//发送"账户类型,名称,密码"，如"1,ppp,ppp"
	state_socket(USER_REGIST, tmpString,sockClient);
	closesocket(sockClient);

	cin.clear();
	cin.ignore(INT_MAX, '\n');//清除输入缓冲区的当前行 
}

