#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
const string stock = "d:\\stock.dat";//库存信息文件名
const string manager = "d:\\manager.dat";//管理员信息文件名
const string saleLog = "d:\\salelog.dat";//销售记录文件名
const string notification = "d:\\notificaiton.txt";//通知文件名

struct book
{
	string TP;//顾客界面不显示书号
	string category;
	string name;
	string author;
	string intro;//简介
	string pos;//位置,例如1A架01层
	int balance;
	book() { TP = "0"; category = "0"; name = "0"; author = "0"; intro = "0"; pos = "0"; balance = 0; }
};

const book mark;//文件结束标记
int endMark(book book)
{
	if (book.TP == "0")
		return 1;
	return 0;
}

//从库存中查找对应书籍,返回在文件中的位置
//多本同名书和同名作者如何处理? find函数用处不大, 考虑在需要查找位置功能的函数中逐一实现
long find(book toBeFound)
{
	book temp;
	long pos;
	fstream file(stock, ios::in | ios::binary);//打开库存文件
	file.seekg(0, ios::beg);
	do
	{
		file.read((char*)&temp, sizeof(book));
	} while (temp.name != toBeFound.name||temp.author!=toBeFound.author && !endMark(temp));
	file.close();
	if (temp.name == toBeFound.name || temp.author == toBeFound.author)
	{
		pos = file.tellg() - streampos(1);
		return pos;
	}
	else
	{
		cout << "根据所给条件未找到该书\n";
		return -1;
	}
}
//判断库存中是否有要查找的书
void inStock()