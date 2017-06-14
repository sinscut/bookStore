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
	cout<< "请输入你希望上架的书籍信息...\n"
		<<"书名\n$";
	cin >> temp.name;
	cout<< "作者\n$";
	cin >> temp.author;
	
}
