#include"manage.h"
//������,���������Ŀ,�����ļ�ĩβ׷��һ����¼;
//�����������Ŀ,�����ӿ����.
extern const bookData mark;
void Append(string filename)
{
	char choice;
	bookData book;
	string key;
	long num;
	fstream file(filename, ios::in | ios::out | ios::binary);//�Զ�/д��ʽ���ļ�
	if(!file)
	{
		cout << "��Ŀ�ļ�������,����г�ʼ������\n";
		return;
	}
	cout << "***************���Ǽ�***************\n";
	while(true)
	{
		cout << "���������ѡ��\n";
		cout << "1:�����\t" << "2:�����\t" << "Q:�˳�\n";
		cin >> choice;
		switch (choice)
		{
		default:cout << "�������,����������\n";
			break;
		case '1':
		{
			file.seekg(0, ios::beg);
			do
			{
				//��һ����¼
				file.read((char*)&book, sizeof(bookData));
			} while (!endMark(book));//�ж��Ƿ��ǽ�����־,�����ļ�β,����������Ļ��������ļ������ƾ�û����
			//��дָ��λ��,��ǰ(������־��һλ)λ��ǰһλ,�����ǽ�����־;
			file.seekp(-long(sizeof(bookData)), ios::cur);
			cout << "�����������(TP),����,����\n?";
			cin >> book.TP;
			cout << '$';
			cin >> book.name;
			cout << '$';
			cin >> book.balance;
			file.write((char*)&book, sizeof(bookData));//д���¼
			file.write((char*)&mark, sizeof(bookData));//д�������־
			break;
		};
		case '2':
		{
			file.seekg(0, ios::beg);
			cout << "�������:\n?";
			cin >> key;//����Ų���
			do
			{
				file.read((char*)&book, sizeof(bookData));
			} while (book.TP != key && !endMark(book));
			//�ж��Ƿ��ҵ���¼
			if (book.TP == key)
			{
				cout << "��ǰ״̬\n";
				cout << book.TP << '\t' << book.name << '\t' << book.balance << endl;
				cout << "�����������:\n";
				cin >> num;
				if (num > 0)
					book.balance += num;
				else
				{
					cout << "�������Ϊ��ֵ\n";
					continue;//����һ�»���������,������һ��whileѭ��
				}
				//��дָ��λ��
				file.seekp(-long(sizeof(bookData)), ios::cur);
				//���޸�д���ļ�
				file.write((char*)&book, sizeof(bookData));
				cout << "�ֿ����:\t\t" << book.balance << endl;
			}
			else
				cout << "δ�ڿ���в��ҵ�����Ŷ�Ӧ���鼮,�������\n";
			break;
		}
		case 'Q':
		case 'q':return;//�������˵�
		}//switch
	}//while(true)
	file.close();
}