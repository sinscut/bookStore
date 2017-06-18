#include"pubUse.h"
#include"guest.h"
#include"manager.h"
int needToInitialize()
{
	fstream file(stock, ios::in | ios::binary);
	if (!file)
		return 1;
	return 0;
}
void managerWindow(manager &b)
{
	cout << "*****************������ϵͳ(����Ա)******************\n\n"
		<< "��ѡ�����:\n"
		<<"<1>����\n"
		<<"<2>ͳ��\n"
		<<"<3>֪ͨ����\n"
		<<"<4>������\n"
		<<"<5>�û�����\n"
		<<"<6>��ʼ��\n"
		<<"<7>�˳�\n\n"
		<< "******************************************************\n$";
	int choice;
	cin >> choice;
	switch (choice)
	{
	default:
		break;
	case 1:b.sale(); break;
	case 2:b.analyse(); break;
	case 3:b.notification(); break;
	case 4:b.viewStock(); break;
	case 5:b.user(); break;
	case 6:
		if (b.getRights() == 2)
			initial(all);
		break;
	case 7:b.logOut(); return;
	}
	cleanScreen();
}

int main()
{
	if (needToInitialize())
	{
		cout << "�ļ���ʧ���״�ʹ��, ���ڳ�ʼ��...\n";
		initial(all);
		cleanScreen();
	}
	guest a;
	manager b;
	int choice;
	while (true)
	{
		cout << "*********************������ϵͳ********************\n\n"
			<< "��ѡ�����:\n"
			<< "<1>��ѯ\n"//������,������,������,�����
			<< "<2>Ԥ��\n"//֪ͨ��Ϣ.txt
			<< "<3>����\n"
			<< "<4>��¼\n\n"
			<< "******************************************************\n$";
		cin >> choice;
		switch (choice)
		{
		default:
			cout << "�������!\n";
			break;
		case 1:
			a.inquire(); break;
		case 2:
			a.want(); break;
		case 3:
			cout << "ʹ�ò�ѯ���ܿ��Բ�ѯ������Ƿ�������Ҫ���鼮.\n���û��,����ʹ��Ԥ�����ܸ�������,���ǻᾡ���ϼ�\n";
			break;
		case 4:
			b.logIn();
			if (b.getRights() != 0)
				managerWindow(b);
			break;
		}
		cleanScreen();
	}
}