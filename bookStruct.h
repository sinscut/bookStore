#pragma once
#include<string>
using namespace std;
struct book
{
	string TP;
	string category;
	string name;
	string author;
	string intro;//¼ò½é
	string pos;//Î»ÖÃ,ÀýÈç1A¼Ü01²ã
	int price;
	int balance;
	int saled;
	book();
	void show();
	void showSimple();
	void set();
};
