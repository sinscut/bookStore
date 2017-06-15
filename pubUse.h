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
	string TP;//�˿ͽ��治��ʾ���
	string category;
	string name;
	string author;
	string intro;//���
	string pos;//λ��,����1A��01��
	int balance;
	book() { TP = "0"; category = "0"; name = "0"; author = "0"; intro = "0"; pos = "0"; balance = 0; }
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
long find(book toBeFound)
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
}
//�жϿ�����Ƿ���Ҫ���ҵ���
void inStock()