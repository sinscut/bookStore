#include"manage.h"
//销售登记. 根据书号查找书目,如果找到,则用销售数修改库存
void Sale(string filename)
{
	char choice;//选择
	bookData book;//临时变量
	string key;//查找书号
	long num;//销量
	fstream file(filename, ios::in | ios::out | ios::binary);//以读/写方式打开
	cout << "***************销售登记***************\n";
	while (true)
	{
		cout << "请输入操作选择\n";
		cout << "1:销售登记\t" << "Q:退出\n";
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
			{
				cout << book.TP << '\t' << book.name << '\t' << book.balance << endl;
				cout << "销售数量:\n?";
				cin >> num;
				if (num > 0 && book.balance >= num)
					book.balance -= num;
				else
				{
					cout << "库存不足或数量不是正数\n";
					continue;
				}
				file.seekp(-long(sizeof(bookData)), ios::cur);//写指针复位
				file.write((char*)&book, sizeof(bookData));
				cout << "现库存量\t\t" << book.balance << endl;
			}//if
			else
				cout << "未在库存中查找到该书号对应的书籍,请检查书号\n";
			break;
		}//case1
		case 'Q':
		case 'q':return;
		}//switch
	}//while
	file.close();
}
//下一步将添加卖完后删除的功能