#include"manage.h"
//��ѯ
void Inquire(string filename)
{
	char choice;
	bookData book;
	string key;
	fstream file(filename, ios::in | ios::binary);
	cout << "***************��ѯ***************\n";
	while (true)
	{
		cout << "���������ѡ��\n"
			<< "1:����Ų�ѯ\t" << "2:��ʾ������Ŀ\t" << "Q:�˳�\n";
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
				cout << book.TP << '\t' << book.name << '\t' << book.balance << endl;
			else
			{
				cout << "δ�ڿ�����ҵ������Ŷ�Ӧ���鼮";
				continue;
			}
			break;
		}
		case '2':
		{
			file.seekg(0, ios::beg);
			do
			{
				file.read((char*)&book, sizeof(bookData));
				if(!endMark(book))
					cout << book.TP << '\t' << book.name << '\t' << book.balance << endl;
			} while (!endMark(book));
			break;
		}
		case 'Q':
		case 'q':return;
		}//switch
	}//while
	file.close();
}
//��һ������ӱ༭����