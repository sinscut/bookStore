#include "guest.h"
#include"pubUse.h"


guest::guest()
{
	name = "noname";
	TEL = "0";
}
guest::~guest()
{

}
void guest::want()
{
	book temp;
	cout<< "��������ϣ���ϼܵ��鼮��Ϣ...\n"
		<<"����\n$";
	cin >> temp.name;
	cout<< "����\n$";
	cin >> temp.author;
	//��ѯͼ���Ƿ��ڿ�bool inStock(book);
	if (inStock(temp))
		cout << "������Ѿ����Ȿ����Ŷ,���Բ�ѯ���ܰ�\n";
	else
	{
		cout << "�����������ϵ��ʽ,�����ϼܺ����ǻᾡ������ȡ����ϵ.\n";
		cout << "$����:";
		cin >> name;
		cout << "$�绰:";
		cin >> TEL;
		fstream file(notifications, ios::app);
		file << "���߷���:\n"
			<< "ϣ���ϼܵ�ͼ��:" << "��" << temp.name << "��" << "\t" << "����:" << temp.author << "\n"
			<< "������Ϣ:\n"
			<< "����:\t" << name << "�绰:\t" << TEL<<endl
			<<"@\n";//��Ϣ������־
		cout << "�Ǽǳɹ�!";
		//�����ڽ����Զ��ر��ļ�
	}
}
void guest::inquire()
{
	int choice;
	while (true)
	{
		cout << "**************************��ѯ**************************\n";
		cout << "��ѡ����ҷ�ʽ:\n\n"
			<< "<0>�������\n"
			<< "<1>��������\n"
			<< "<2>��������\n"
			<< "<3>��ʾȫ��\n"
			<< "<4>�˳�";
		cin >> choice;
		if (choice == 4)
			return;
		commonFind(choice);
		cleanScreen();
	}
}
