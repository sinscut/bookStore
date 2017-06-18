#include<iostream>
#include"bookStruct.h"
book::book()
{ 
	TP[0] = '\0'; 
	category[0] = '\0';
	name[0] = '\0'; 
	author[0] = '\0'; 
	intro[0] = '\0'; 
	pos[0] = '\0'; 
	price = 0; 
	balance = 0; 
	saled = 0;
}
void book::show()//显示详细信息,与其他内容以空行分割
{
	cout << "\n类别: " << category << "书名: " << "《" << name << "》" << "作者: " << author << endl;
	cout << "书号: " << TP << "位置: " << pos << "价格:" << price << endl;
	cout << "简介: " << intro << "\n\n";
	return;
}
void book::showSimple()
{
	cout << "\n书号: " << TP << "书名: " << "《" << name << "》" << "作者: " << author << endl;
}
void book::set()
{
	cout << "$类别: ";
	cin >> category;
	cout << "$书名: ";
	cin >> name;
	cout << "$作者: ";
	cin >> author;
	cout << "$书号: ";
	cin >> TP;
	cout << "$位置: ";
	cin >> pos;
	cout << "$库存:";
	cin >> balance;
	cout << "$售价:";
	cin >> price;
	cout << "$简介: ";
	cin >> intro;
}