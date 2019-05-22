#include"c_mainfunc.h"

int player_login(player& nowPlayer, SOCKADDR_IN addrSrv)//获得名称在列表中的对应位置，以及验证其密码。验证成功则返回位置，否则返回-1
{
	int login_flag = -1;
	string name;
	string password;
	cout << "Login:\nPlease input your username:" << endl;
	cin >> name;
	cout << "Please input your password:" << endl;
	cin >> password;

	SOCKET sockClient = socket_init(addrSrv);
	login_flag = state_socket(USER_LOGIN, "1,"+name + "," + password, sockClient);
	closesocket(sockClient);

	if (login_flag == 0)cout << "socket error 03" << endl;
	else if (login_flag == 1)
	{
		cout << "Player Successful Login!\n" << endl;
		player tmpPlayer(name, password);
		nowPlayer = tmpPlayer;
	}
	else if (login_flag == 2)	cout << "Login Failure.\nHint: Is your username or password wrong ?" << endl;
	return login_flag;
}

int tester_login(tester& nowTester, SOCKADDR_IN addrSrv)
{
	int login_flag = -1;
	string name;
	string password;
	cout << "Login:\nPlease input your username:" << endl;
	cin >> name;
	cout << "Please input your password:" << endl;
	cin >> password;

	SOCKET sockClient = socket_init(addrSrv);
	login_flag = state_socket(USER_LOGIN, "2,"+ name + "," + password, sockClient);
	closesocket(sockClient);

	if (login_flag == 0)cout << "socket error 05" << endl;
	else if (login_flag == 1)
	{
		cout << "Tester Successful Login!\n" << endl;
		tester tmpTester(name, password);
		nowTester = tmpTester;
	}
	else if (login_flag == 2)	cout << "Login Failure.\nHint: Is your username or password wrong ?" << endl;
	return login_flag;
}