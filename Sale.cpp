#include"manage.h"
//���۵Ǽ�. ������Ų�����Ŀ,����ҵ�,�����������޸Ŀ��
void Sale(string filename)
{
	char choice;//ѡ��
	bookData book;//��ʱ����
	string key;//�������
	long num;//����
	fstream file(filename, ios::in | ios::out | ios::binary);//�Զ�/д��ʽ��
	cout << "***************���۵Ǽ�***************\n";
	while (true)
	{
		cout << "���������ѡ��\n";
		cout << "1:���۵Ǽ�\t" << "Q:�˳�\n";
		cin >> choice;
		switch (choice)
		{
		default:cout << "�������,����������\n";
			break;
		case '1':
		{
			file.seekg(0, ios::beg);
			cout << "���(TP):\n?";
			cin >> key;
			do
			{
				file.read((char*)&book, sizeof(bookData));
			} while (book.TP != key && !endMark(book));//���Ҽ�¼
			if (book.TP == key)
			{
				cout << book.TP << '\t' << book.name << '\t' << book.balance << endl;
				cout << "��������:\n?";
				cin >> num;
				if (num > 0 && book.balance >= num)
					book.balance -= num;
				else
				{
					cout << "��治���������������\n";
					continue;
				}
				file.seekp(-long(sizeof(bookData)), ios::cur);//дָ�븴λ
				file.write((char*)&book, sizeof(bookData));
				cout << "�ֿ����\t\t" << book.balance << endl;
			}//if
			else
				cout << "δ�ڿ���в��ҵ�����Ŷ�Ӧ���鼮,�������\n";
			break;
		}//case1
		case 'Q':
		case 'q':return;
		}//switch
	}//while
	file.close();
}
//��һ������������ɾ���Ĺ���