#pragma once
#include"pubUse.h"
class manager
{
	string ID;
	string password;
	int rights;//0,δ��¼,1,��ͨ�û�,2,�����û�
public:
	manager();
	~manager();
	void logIn();//������Ա�ļ�����ʼ��,����¼.
	void sale();//����.�ͼ�Ȩ��
	void notification();//֪ͨ����,�������߷���,��������.�ͼ�Ȩ��
	void viewStock();//�鿴,����,�޸�,ɾ��,��տ��.���鿴�ⶼ��Ҫ�߼�Ȩ��
	void analyse();//ͳ������,�����۶�,�������
	void user();//�û�����,����,ɾ���û�,�����û�Ȩ��.��Ҫ�߼�Ȩ��
	friend void initial(int);
};
const manager managerEnd;
struct saleLog
{
	string time;
	string bookTP;
	int sales;
};
const saleLog saleLogFile = { "0","0",0 };