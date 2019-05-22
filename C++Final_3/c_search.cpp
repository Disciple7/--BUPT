#include"c_mainfunc.h"

void state_query(SOCKADDR_IN addrSrv)//查询状态，可以根据各种条件查询，如名称，等级，类型。
{
	int order = 4;
	string userName = "\0";
	cout << "Qurey mode : Please input your order.\n(1)Show All Player Rank\n(2)Show All Tester Rank\n(3)Search Certain User\n(0)Quit" << endl;
	cin >> order;
	switch (order)
	{
	case 1:
	{
		cout << "Switch mode (default : by Name) :\n(1)Rank by Name\n(2)Rank by Level\n(3)Rank by Best Round" << endl;
		cin >> order;
		SOCKET sockClient = socket_init(addrSrv);
		string tmpString = std::to_string(1) + "," + std::to_string(order);
		state_socket(USER_QUERY, tmpString, sockClient);
		closesocket(sockClient);
		break;
	}
	case 2:
	{
		cout << "Switch mode (default : by Name) :\n(1)Rank by Name\n(2)Rank by Level\n(3)Rank by Problem Num" << endl;
		cin >> order;
		SOCKET sockClient = socket_init(addrSrv);
		string tmpString = std::to_string(2) + "," + std::to_string(order);
		state_socket(USER_QUERY, tmpString, sockClient);
		closesocket(sockClient);
		break;
	}
	case 3:
	{
		cout << "Type username you want to search : " << endl;
		cin >> userName;
		SOCKET sockClient = socket_init(addrSrv);
		string tmpString = std::to_string(3) + "," + userName;
		state_socket(USER_QUERY, tmpString, sockClient);
		closesocket(sockClient);
		break;
	}
	default:
		break;
	}
	cin.clear();
	cin.ignore(INT_MAX, '\n');
	return;
}