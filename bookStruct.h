#pragma once
#include<string>
using namespace std;
struct book
{
	char TP[20];
	char category[20];
	char name[40];
	char author[40];
	char intro[200];//���
	char pos[40];//λ��,����1A��01��
	int price;
	int balance;
	int saled;
	book();
	void show();
	void showSimple();
	void set();
};
