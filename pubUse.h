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
	string TP;
	string category;
	string name;
	string author;
	string intro;//简介
	string pos;//位置,例如1A架01层
	int balance;
	book() { TP = "0"; category = "0"; name = "0"; author = "0"; intro = "0"; pos = "0"; balance = 0; }
	void show()//显示全部信息,与其他内容以空行分割
	{
		cout << "\n类别: " << category << "书名: " << "《" << name << "》" << "作者: " << author << endl;
		cout <<"书号: " << TP << "位置: " << pos << endl;
		cout << "简介: " << intro<<"\n\n";
		return;
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
		cout << "$简介: ";
		cin >> intro;
	}
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
const int cat = 0;
const int name = 1;
const int author = 2;
//flag为查询方式
void commonFind(int flag)
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
		}
		case name:
		{
			if (temp.name == answer)
			{
				temp.show();
				none = 0;
			}
		}
		case author:
		{
			if (temp.author == answer)
			{
				temp.show();
				none = 0;
			}
		}
		}//switch
	} while (!endMark(temp));
	if (none) cout << "未找到相关书籍...\n";
}