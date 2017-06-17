#pragma once
#include<string>
using namespace std;
struct book
{
	string TP;
	string category;
	string name;
	string author;
	string intro;//简介
	string pos;//位置,例如1A架01层
	int price;
	int balance;
	int saled;
	book();
	void show();
	void showSimple();
	void set();
};

//const book bookEnd;//文件结束标记
int endMark(book bookT)
{
	if (bookT.TP == "0")
		return 1;
	return 0;
}
