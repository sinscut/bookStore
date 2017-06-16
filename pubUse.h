#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<cstdlib>
using namespace std;
const string stock = "d:\\stock.dat";//库存信息文件名
const string managers = "d:\\managers.dat";//管理员信息文件名
const string saleLogs = "d:\\salelog.dat";//销售记录文件名
const string notifications = "d:\\notificaiton.txt";//通知文件名
const int cat = 0;
const int name = 1;
const int author = 2;
const int all = 3;
const int guanliyuan = 4;
const int kucun = 5;
const int tongzhi = 6;
const int xiaoshou = 7;
bool inStock(book toBeFound);//判断库存中是否有要查找的书籍
int commonFind(int flag);//通用查找,flag为查询方式
void initial(int flag);//初始化,flag为初始化方式,库存,管理员,通知,销售记录,全部
enum category
{
	literature = 1,
	art,
	technology,
	industry,
};
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
	book() { TP = "0"; category = "0"; name = "0"; author = "0"; intro = "0"; pos = "0"; price = 0; balance = 0; saled = 0; }
	void show()//显示详细信息,与其他内容以空行分割
	{
		cout << "\n类别: " << category << "书名: " << "《" << name << "》" << "作者: " << author << endl;
		cout << "书号: " << TP << "位置: " << pos << "价格:" << price << endl;
		cout << "简介: " << intro<<"\n\n";
		return;
	}
	void showSimple()
	{
		cout << "\n书号: " << TP << "书名: " << "《" << name << "》" << "作者: " << author << endl;
	}
	void set()
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
};

//const book bookEnd;//文件结束标记
int endMark(book bookT)
{
	if (bookT.TP == "0")
		return 1;
	return 0;
}

//从库存中查找对应书籍,返回在文件中的位置
//多本同名书和同名作者如何处理? find函数用处不大, 考虑在需要查找位置功能的函数中逐一实现
/*long find(book toBeFound)
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
}*/

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


//cat-分类,name-书名,author-作者,all-全部
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
		{	
			if (temp.category == answer)
			{
				temp.show();
				none = 0;
			}
			break;
		}
		case name:
		{
			if (temp.name == answer)
			{
				temp.show();
				none = 0;
			}
			break;
		}
		case author:
		{
			if (temp.author == answer)
			{
				temp.show();
				none = 0;
			}
			break;
		}
		case all:
		{
			if (!endMark(temp))
			{
				temp.show();
				none = 0;
			}
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
	}
	case kucun:
	{
		book temp;
		fstream file(stock, ios::out | ios::trunc|ios::binary);
		file.seekp(0, ios::beg);
		file.write((char*)&temp, sizeof(book));
		break;
	}
	case tongzhi:
	{
		fstream file(notifications, ios::out | ios::trunc);
		break;//暂时先不管文件结束的问题
	}
	case guanliyuan:
	{
		manager temp;
		fstream file(managers, ios::out | ios::trunc|ios::binary);
		file.write((char*)&temp, sizeof(manager));
		break;
		//初始化成功,按任意键重启程序
	}
	case xiaoshou:
	{
		//清空销售日志
		//日志文件还是用TXT吧
	}
	}
}