#include "guest.h"
#include"pubUse.h"


guest::guest()
{
	name = "noname";
	TEL = "0";
}
void guest::want()
{
	book temp;
	string temp;
	cout<< "��������ϣ���ϼܵ��鼮��Ϣ...\n"
		<<"����\n$";
	cin >> temp.name;
	cout<< "����\n$";
	cin >> temp.author;
	
}
