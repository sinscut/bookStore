#pragma once
#include"pubUse.h"
class manager
{
	char ID[20];
	char password[20];
	int rights;//0,δ��¼,1,��ͨ�û�,2,�����û�
public:
	manager();
	~manager();
	void logIn();//������Ա�ļ�����ʼ��,����¼.
	void logOut();
	void sale();//����.�ͼ�Ȩ��
	void notification();//֪ͨ����,�������߷���,��������.�ͼ�Ȩ��
	void viewStock();//�鿴,����,�޸�,ɾ��,��տ��.���鿴�ⶼ��Ҫ�߼�Ȩ��
	void analyse();//ͳ������,�����۶�,�������
	void user();//�û�����,����,ɾ���û�,�����û�Ȩ��.��Ҫ�߼�Ȩ��
	int getRights();
	friend void initial(int);
};