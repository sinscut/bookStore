#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
const string stock = "d:\\stock.dat";//�����Ϣ�ļ���
const string manager = "d:\\manager.dat";//����Ա��Ϣ�ļ���
const string saleLog = "d:\\salelog.dat";//���ۼ�¼�ļ���
const string notification = "d:\\notificaiton.txt";//֪ͨ�ļ���

struct book
{
	string TP;
	string category;
	string name;
	string author;
	string intro;//���
	string pos;//λ��,����1A��01��
	int balance;
	book() { TP = "0"; category = "0"; name = "0"; author = "0"; intro = "0"; pos = "0"; balance = 0; }
	void show()//��ʾȫ����Ϣ,�����������Կ��зָ�
	{
		cout << "\n���: " << category << "����: " << "��" << name << "��" << "����: " << author << endl;
		cout <<"���: " << TP << "λ��: " << pos << endl;
		cout << "���: " << intro<<"\n\n";
		return;
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
		cout << "$���: ";
		cin >> intro;
	}
};

const book mark;//�ļ��������
int endMark(book book)
{
	if (book.TP == "0")
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
const int cat = 0;
const int name = 1;
const int author = 2;
//flagΪ��ѯ��ʽ
void commonFind(int flag)
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
	if (none) cout << "δ�ҵ�����鼮...\n";
}