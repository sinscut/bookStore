#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<conio.h>
#include<cstdlib>
#include<list>//STL链表
#include<algorithm>//STL算法库
#include"bookStruct.h"
#include"manager.h"
using namespace std;
const string stock = "d:\\stock.dat";//库存信息文件名
const string managers = "d:\\managers.dat";//管理员信息文件名
const string saleLogs = "d:\\salelog.txt";//销售记录文件名
const string notifications = "d:\\notificaiton.txt";//通知文件名
const int cat = 0;
const int name = 1;
const int author = 2;
const int all = 3;
const int guanliyuan = 4;
const int kucun = 5;
const int tongzhi = 6;
const int xiaoshou = 7;
const int add = 1;
const int amend = 2;
const int cutOut = 3;
bool inStock(book toBeFound);//判断库存中是否有要查找的书籍
int commonFind(int flag);//通用查找,flag为查询方式
void initial(int flag);//初始化,flag为初始化方式,库存,管理员,通知,销售记录,全部
void edit(int flag);//通用编辑
void cleanScreen();//清屏
void checkSales();//查看销售日志
void getTime(string &now);//获取时间戳


//判断库存中是否有要查找的书
bool inStock(book toBeFound)
{
	book temp;
	fstream file(stock, ios::in | ios::binary);//打开库存文件
	file.seekg(0, ios::beg);
	do
	{
		file.read((char*)&temp, sizeof(book));
		if (temp.name == toBeFound.name && temp.author == toBeFound.author)
			return true;
	} while (!endMark(temp));
	return false;
	//file生存期结束应该会自动关闭文件
}


//cat=0,name=1,author=2,all=3
int commonFind(int flag)
{
	book temp;
	int none = 1;
	string answer;//搜索项
	if (flag == cat)
		cout << "你可以输入以下分类:\n"
			<< "文学\t艺术\t科技\t工业\n$";
	if (flag == name)
		cout << "$输入书名:";
	if (flag == author)
		cout << "$输入作者名:";
	cin >> answer;
	fstream file(stock, ios::in | ios::binary);//打开库存文件
	file.seekg(0, ios::beg);
	do
	{
		file.read((char*)&temp, sizeof(book));
		switch (flag)//查找方式
		{
		default:
			break;
		case cat:	
			if (temp.category == answer)
			{
				temp.show();
				none = 0;
			}
			break;
		case name:
			if (temp.name == answer)
			{
				temp.show();
				none = 0;
			}
			break;
		case author:
			if (temp.author == answer)
			{
				temp.show();
				none = 0;
			}
			break;
		case all:
			if (!endMark(temp))
			{
				temp.showSimple();
				none = 0;
			}
		}//switch
	} while (!endMark(temp));
	if (none) cout << "未找到相关书籍...\n";
	return none;
}
//all=3,guanliyuan=4,kucun=5,tongzhi=6,xiaoshou=7
void initial(int flag)
{
	switch (flag)
	{
	default:
		break;
	case all:
	{
		initial(kucun);
		initial(tongzhi);
		initial(xiaoshou);
		initial(guanliyuan);
		break;
	}
	case kucun:
	{
		book temp;
		fstream file(stock, ios::out | ios::trunc|ios::binary);
		file.seekp(0, ios::beg);
		file.write((char*)&temp, sizeof(book));
		cout << "已初始化库存!\n";
		break;
	}
	case tongzhi:
	{
		fstream file(notifications, ios::out | ios::trunc);
		cout << "已清空通知!\n";
		break;//暂时先不管文件结束的问题
	}
	case guanliyuan:
	{
		manager tempM;
		fstream file(managers, ios::out | ios::trunc|ios::binary);
		file.write((char*)&tempM, sizeof(manager));
		//初始化成功,按任意键重启程序
		cout << "初始化成功,请重新启动程序\n"
			<< "按任意键继续...\n";
		system("pause");
		exit(0);
	}
	case xiaoshou:
	{
		//清空销售日志
		fstream file(saleLogs, ios::out | ios::trunc);
		cout << "已清空销售日志!\n";
	}
	}
}
//给find_if判断用的结构体(伪函数),也可以重载==,用类作为判断值, 参考http://blog.csdn.net/learnhard/article/details/5692104
typedef struct findBook

{
	findBook(string t): TP(t){}
	bool operator()(book p)
	{
		return (TP == p.TP);
	}
	string	TP;
}finder;
//add=1,amend=2,cutOut=3
void edit(int flag)
{
	string tempTP;
	book temp;
	list<book>  fileOp;
	list<book>::iterator p;
	fstream file(stock, ios::in | ios::out | ios::binary);
	file.seekg(0, ios::beg);
	do
	{
		file.read((char*)&temp, sizeof(book));
		if(!endMark(temp))
			fileOp.push_back(temp);//将文件中的数据复制到链表
	} while (!endMark(temp));
	switch (flag)
	{
	default:
		break;
	case add:
		temp.saled = 0;//以防万一, 因为book::set()不能设置saled
		cout << "录入书籍信息:\n$";
		temp.set();
		fileOp.push_back(temp);
		break;
	case amend:
		cout << "输入要修改信息的书号:\n$";
		cin >> tempTP;
		//查找书号
		p = find_if(fileOp.begin(), fileOp.end(), finder(tempTP));//find_if()第三个参数是函数指针(函数名)
		if (p != fileOp.end())
		{
			cout << "只能修改价格(当前价格为:"<<p->price<<"),请输入价格:\n$";
			int tempPrice;
			cin >> tempPrice;
			p->price = tempPrice;
			cout << "修改价格为" << p->price << "成功!\n";
		}
		else cout << "书号错误,请重试.\n";
		break;
	case cutOut:
		cout << "输入要删除书籍的书号:\n$";
		cin >> tempTP;
		//查找书号
		p = find_if(fileOp.begin(), fileOp.end(), finder(tempTP));//find_if()第三个参数是函数指针(函数名)
		if (p != fileOp.end())
		{
			fileOp.erase(p);
			cout << "删除成功!\n";
		}
		else cout << "书号错误,请重试.\n";
	}
	//将链表中的信息重新写回文件
	p = fileOp.begin();
	file.seekp(0, ios::beg);
	for (p; p != fileOp.end(); ++p)
	{
		temp = *p;
		file.write((char*)&temp, sizeof(book));
	}
	const book end;
	file.write((char*)&end, sizeof(book));
}

//	清屏
void cleanScreen()
{
	cout << "按任意键继续...";
	system("pause");
	system("cls");
}

//查看销售日志
void checkSales()
{
	string line;
	fstream file(saleLogs, ios::in);
	if (!file.eof())
		getline(file, line, '@');//@消息结束标记
	else
	{
		cout << "无销售记录,按任意键退出...\n";
		system("pause");
		return;
	}
	cout << line << endl;
	while (!file.eof())
	{
		getline(file, line, '@');
		cout << line << endl;
	}
}
void getTime(string &now)
{
	time_t t;
	char tme[32];
	t = time(NULL);//获取当前时间
	ctime_s(tme, 32, &t);
	now = tme;
}