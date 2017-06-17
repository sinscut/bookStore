#include"manage.h"
//入库操作,如果是新书目,则在文件末尾追加一条记录;
//如果是已有书目,则增加库存量.
extern const bookData mark;
void Append(string filename)
{
	char choice;
	bookData book;
	string key;
	long num;
	fstream file(filename, ios::in | ios::out | ios::binary);//以读/写方式打开文件
	if(!file)
	{
		cout << "账目文件不存在,请进行初始化操作\n";
		return;
	}
	cout << "***************入库登记***************\n";
	while(true)
	{
		cout << "请输入操作选择\n";
		cout << "1:新书号\t" << "2:旧书号\t" << "Q:退出\n";
		cin >> choice;
		switch (choice)
		{
		default:cout << "输入错误,请重新输入\n";
			break;
		case '1':
		{
			file.seekg(0, ios::beg);
			do
			{
				//读一个记录
				file.read((char*)&book, sizeof(bookData));
			} while (!endMark(book));//判断是否是结束标志,查找文件尾,不过这样查的话二进制文件的优势就没有了
			//置写指针位置,当前(结束标志下一位)位置前一位,即覆盖结束标志;
			file.seekp(-long(sizeof(bookData)), ios::cur);
			cout << "分行输入书号(TP),书名,数量\n?";
			cin >> book.TP;
			cout << '$';
			cin >> book.name;
			cout << '$';
			cin >> book.balance;
			file.write((char*)&book, sizeof(bookData));//写入记录
			file.write((char*)&mark, sizeof(bookData));//写入结束标志
			break;
		};
		case '2':
		{
			file.seekg(0, ios::beg);
			cout << "输入书号:\n?";
			cin >> key;//按书号查找
			do
			{
				file.read((char*)&book, sizeof(bookData));
			} while (book.TP != key && !endMark(book));
			//判断是否找到记录
			if (book.TP == key)
			{
				cout << "当前状态\n";
				cout << book.TP << '\t' << book.name << '\t' << book.balance << endl;
				cout << "输入入库数量:\n";
				cin >> num;
				if (num > 0)
					book.balance += num;
				else
				{
					cout << "入库数需为正值\n";
					continue;//测试一下会跳到哪里,进入下一个while循环
				}
				//置写指针位置
				file.seekp(-long(sizeof(bookData)), ios::cur);
				//将修改写入文件
				file.write((char*)&book, sizeof(bookData));
				cout << "现库存量:\t\t" << book.balance << endl;
			}
			else
				cout << "未在库存中查找到该书号对应的书籍,请检查书号\n";
			break;
		}
		case 'Q':
		case 'q':return;//返回主菜单
		}//switch
	}//while(true)
	file.close();
}