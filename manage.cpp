#include"manage.h"
//�������˵�,ѡ�����
const string filename = "d:\\booksFile.dat";//  "\\"��һ����ת���
int main()
{
	char choice;
	while (true)
	{
		cout << "***************������***************\n���������ѡ��\n"
			<< "1:���\t" << "2:�۳�\t" << "3:��ѯ\t" 
			<< "4:�����ı��ļ�\t" << "0:��ʼ��\t" << "Q:�˳�\n";
		cin >> choice;
		switch (choice)
		{
		case '1':Append(filename); break;
		case '2':Sale(filename); break;
		case '3':Inquire(filename); break;
		case '4':CreateTxt(filename); break;
		case '0':Initial(filename); break;
		case 'q':
		case 'Q':cout << "�˳�ϵͳ\n"; return 0;//��һ�¿ɲ�������||-----������
		default:cout << "�������,����������\n";
		}
	}
}
//��һ��������û�������