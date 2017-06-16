#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<cstdlib>
using namespace std;
const string stock = "d:\\stock.dat";//�����Ϣ�ļ���
const string managers = "d:\\managers.dat";//����Ա��Ϣ�ļ���
const string saleLogs = "d:\\salelog.dat";//���ۼ�¼�ļ���
const string notifications = "d:\\notificaiton.txt";//֪ͨ�ļ���
const int cat = 0;
const int name = 1;
const int author = 2;
const int all = 3;
const int guanliyuan = 4;
const int kucun = 5;
const int tongzhi = 6;
const int xiaoshou = 7;
bool inStock(book toBeFound);//�жϿ�����Ƿ���Ҫ���ҵ��鼮
int commonFind(int flag);//ͨ�ò���,flagΪ��ѯ��ʽ
void initial(int flag);//��ʼ��,flagΪ��ʼ����ʽ,���,����Ա,֪ͨ,���ۼ�¼,ȫ��
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
	string intro;//���
	string pos;//λ��,����1A��01��
	int price;
	int balance;
	int saled;
	book() { TP = "0"; category = "0"; name = "0"; author = "0"; intro = "0"; pos = "0"; price = 0; balance = 0; saled = 0; }
	void show()//��ʾ��ϸ��Ϣ,�����������Կ��зָ�
	{
		cout << "\n���: " << category << "����: " << "��" << name << "��" << "����: " << author << endl;
		cout << "���: " << TP << "λ��: " << pos << "�۸�:" << price << endl;
		cout << "���: " << intro<<"\n\n";
		return;
	}
	void showSimple()
	{
		cout << "\n���: " << TP << "����: " << "��" << name << "��" << "����: " << author << endl;
	}
	void set()
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
};

//const book bookEnd;//�ļ��������
int endMark(book bookT)
{
	if (bookT.TP == "0")
		return 1;
	return 0;
}

//�ӿ���в��Ҷ�Ӧ�鼮,�������ļ��е�λ��
//�౾ͬ�����ͬ��������δ���? find�����ô�����, ��������Ҫ����λ�ù��ܵĺ�������һʵ��
/*long find(book toBeFound)
{
	book temp;
	long pos;
	fstream file(stock, ios::in | ios::binary);//�򿪿���ļ�
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
		cout << "������������δ�ҵ�����\n";
		return -1;
	}
}*/

//�жϿ�����Ƿ���Ҫ���ҵ���
bool inStock(book toBeFound)
{
	book temp;
	fstream file(stock, ios::in | ios::binary);//�򿪿���ļ�
	file.seekg(0, ios::beg);
	do
	{
		file.read((char*)&temp, sizeof(book));
		if (temp.name == toBeFound.name && temp.author == toBeFound.author)
			return true;
	} while (!endMark(temp));
	return false;
	//file�����ڽ���Ӧ�û��Զ��ر��ļ�
}


//cat-����,name-����,author-����,all-ȫ��
int commonFind(int flag)
{
	book temp;
	int none = 1;
	string answer;//������
	if (flag == cat)
		cout << "������������·���:\n"
			<< "��ѧ\t����\t�Ƽ�\t��ҵ\n$";
	if (flag == name)
		cout << "$��������:";
	if (flag == author)
		cout << "$����������:";
	cin >> answer;
	fstream file(stock, ios::in | ios::binary);//�򿪿���ļ�
	file.seekg(0, ios::beg);
	do
	{
		file.read((char*)&temp, sizeof(book));
		switch (flag)//���ҷ�ʽ
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
	if (none) cout << "δ�ҵ�����鼮...\n";
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
		break;//��ʱ�Ȳ����ļ�����������
	}
	case guanliyuan:
	{
		manager temp;
		fstream file(managers, ios::out | ios::trunc|ios::binary);
		file.write((char*)&temp, sizeof(manager));
		break;
		//��ʼ���ɹ�,���������������
	}
	case xiaoshou:
	{
		//���������־
		//��־�ļ�������TXT��
	}
	}
}