#pragma once
#include<string>
using namespace std;
struct book
{
	string TP;
	string category;
	string name;
	string author;
	string intro;//���
	string pos;//λ��,����1A��01��
	int price;
	int balance;
	int saled;
	book();
	void show();
	void showSimple();
	void set();
};

//const book bookEnd;//�ļ��������
int endMark(book bookT)
{
	if (bookT.TP == "0")
		return 1;
	return 0;
}
