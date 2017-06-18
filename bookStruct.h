#pragma once
#include<string>
using namespace std;
struct book
{
	char TP[20];
	char category[20];
	char name[40];
	char author[40];
	char intro[200];//¼ò½é
	char pos[40];//Î»ÖÃ,ÀýÈç1A¼Ü01²ã
	int price;
	int balance;
	int saled;
	book();
	void show();
	void showSimple();
	void set();
};
