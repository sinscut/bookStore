#include"manage.h"
//查询
void Inquire(string filename)
{
	char choice;
	bookData book;
	string key;
	fstream file(filename, ios::in | ios::binary);
	cout << "***************查询***************\n";
	while (true)
	{
		cout << "请输入操作选择\n"
			<< "1:按书号查询\t" << "2:显示所有书目\t" << "Q:退出\n";
		cin >> choice;
		switch (choice)
		{
		default:cout << "输入错误,请重新输入\n";
			break;
		case '1':
		{
			file.seekg(0, ios::beg);
			cout << "书号(TP):\n?";
			cin >> key;
			do
			{
				file.read((char*)&book, sizeof(bookData));
			} while (book.TP != key && !endMark(book));//查找记录
			if (book.TP == key)
				cout << book.TP << '\t' << book.name << '\t' << book.balance << endl;
			else
			{
				cout << "未在库存中找到与该书号对应的书籍";
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
//下一步将添加编辑功能