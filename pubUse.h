#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<cstdlib>
#include<list>//��׼��, ����
#include<algorithm>//STL�㷨��
using namespace std;
const string stock = "d:\\stock.dat";//�����Ϣ�ļ���
const string managers = "d:\\managers.dat";//����Ա��Ϣ�ļ���
const string saleLogs = "d:\\salelog.txt";//���ۼ�¼�ļ���
const string notifications = "d:\\notificaiton.txt";//֪ͨ�ļ���
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
bool inStock(book toBeFound);//�жϿ�����Ƿ���Ҫ���ҵ��鼮
int commonFind(int flag);//ͨ�ò���,flagΪ��ѯ��ʽ
void initial(int flag);//��ʼ��,flagΪ��ʼ����ʽ,���,����Ա,֪ͨ,���ۼ�¼,ȫ��
void edit(int flag);//ͨ�ñ༭
void cleanScreen();//����
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


//cat=0,name=1,author=2,all=3
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
				temp.showSimple();
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
		cout << "�ѳ�ʼ�����!\n";
		break;
	}
	case tongzhi:
	{
		fstream file(notifications, ios::out | ios::trunc);
		cout << "�����֪ͨ!\n";
		break;//��ʱ�Ȳ����ļ�����������
	}
	case guanliyuan:
	{
		manager temp;
		fstream file(managers, ios::out | ios::trunc|ios::binary);
		file.write((char*)&temp, sizeof(manager));
		//��ʼ���ɹ�,���������������
		cout << "��ʼ���ɹ�,��������������\n"
			<< "�����������...\n";
		system("pause");
		exit(0);
	}
	case xiaoshou:
	{
		//���������־
		//��־�ļ�������TXT��
		cout << "�����������־!\n";
	}
	}
}
//��find_if�ж��õĽṹ��(α����),Ҳ��������==,������Ϊ�ж�ֵ, �ο�http://blog.csdn.net/learnhard/article/details/5692104
typedef struct findBook

{
	findBook(string t): TP(t){}
	bool operator()(book*p)
	{
		return (TP == p->TP);
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
			fileOp.push_back(temp);//���ļ��е����ݸ��Ƶ�����
	} while (!endMark(temp));
	switch (flag)
	{
	default:
		break;
	case add:
		temp.saled = 0;//�Է���һ, ��Ϊbook::set()��������saled;
		cout << "¼���鼮��Ϣ:\n$";
		temp.set();
		fileOp.push_back(temp);
		break;
	case amend:
		cout << "����Ҫ�޸���Ϣ�����:\n$";
		cin >> tempTP;
		//�������
		p = find_if(fileOp.begin(), fileOp.end(), finder(tempTP));//find_if()�����������Ǻ���ָ��(������)
		if (p != fileOp.end())
		{
			cout << "ֻ���޸ļ۸�(��ǰ�۸�Ϊ:"<<p->price<<"),������۸�:\n$";
			int tempPrice;
			cin >> tempPrice;
			p->price = tempPrice;
			cout << "�޸ļ۸�Ϊ" << p->price << "�ɹ�!\n";
		}
		else cout << "��Ŵ���,������.\n";
		break;
	case cutOut:
		cout << "����Ҫɾ���鼮�����:\n$";
		cin >> tempTP;
		//�������
		p = find_if(fileOp.begin(), fileOp.end(), finder(tempTP));//find_if()�����������Ǻ���ָ��(������)
		if (p != fileOp.end())
		{
			fileOp.erase(p);
			cout << "ɾ���ɹ�!\n";
		}
		else cout << "��Ŵ���,������.\n";
	}
	//�������е���Ϣ����д���ļ�
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

//	����
void cleanScreen()
{
	cout << "�����������...";
	system("pause");
	system("cls");
}