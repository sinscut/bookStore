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
void book::show()//��ʾ��ϸ��Ϣ,�����������Կ��зָ�
{
	cout << "\n���: " << category << "����: " << "��" << name << "��" << "����: " << author << endl;
	cout << "���: " << TP << "λ��: " << pos << "�۸�:" << price << endl;
	cout << "���: " << intro << "\n\n";
	return;
}
void book::showSimple()
{
	cout << "\n���: " << TP << "����: " << "��" << name << "��" << "����: " << author << endl;
}
void book::set()
{
	cout << "$���: ";
	cin >> category;
	cout << "$����: ";
	cin >> name;
	cout << "$����: ";
	cin >> author;
	cout << "$���: ";
	cin >> TP;
	cout << "$λ��: ";
	cin >> pos;
	cout << "$���:";
	cin >> balance;
	cout << "$�ۼ�:";
	cin >> price;
	cout << "$���: ";
	cin >> intro;
}