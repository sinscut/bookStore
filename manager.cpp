#include "manager.h"

manager::manager()
{
	ID = "0";
	password = "0";
	rights = 0;
}

manager::~manager()
{
}
void manager::logIn()
{
	manager temp;
	int num = 3;//记录登录次数
	fstream file(managers, ios::in | ios::out | ios::binary);
	//判断是否需要初始化
	if (!file)
	{
		cout << "管理员信息丢失,请初始化...\n";//还是单独放到初始化函数里吧,这里只负责登录验证..初始化要能分类初始化和全部初始化
		initial(guanliyuan);
		return;
	}
	cout << "****************登录********************\n";
	file.seekg(0, ios::beg);
	file.read((char*)&temp, sizeof(manager));
	if (temp.ID == "0")
	{
		cout << "首次登录需要配置超级用户信息...\n";
		cout << "$用户名:";
		cin >> ID;
		cout << "$密码:";
		cin >> password;
		rights = 0;
		file.seekp(-long(sizeof(manager)), ios::cur);
		file.write((char*)this, sizeof(manager));
		cout << "配置成功!";
		cout << "按任意键返回上一级...\n";
		system("pause");
		return;
	}
	while(num)
	{
		cout << "$用户名:";
		cin >> ID;
		cout << "$密码:";
		cin >> password;
		file.seekg(0, ios::beg);
		do
		{
			file.read((char*)&temp, sizeof(manager));
			if (ID == temp.ID&&password == temp.password)
			{
				rights = temp.rights;
				cout << "登录成功!\n";
				return;
			}
		} while (temp.rights != 0);
		cout << "用户名或密码错误!\n";
	}
	cout << "你已连续3次登录失败,请稍后重试!\n";
}

void manager::sale()
{
	char choice;//选择
	book bookTemp;//临时变量
	string key;//查找书号
	long num;//销量
	fstream file(stock, ios::in | ios::out | ios::binary);//以读/写方式打开
	cout << "\n***************销售***************\n";
	while (true)
	{
		cout << "请选择操作:"<< "1:销售登记\t" << "Q:退出\n$";
		cin >> choice;
		switch (choice)
		{
		default:cout << "输入错误,请重新输入\n";
			break;
		case '1':
		{
			file.seekg(0, ios::beg);
			cout << "书号(TP):\n$";
			cin >> key;
			do
			{
				file.read((char*)&bookTemp, sizeof(book));
			} while (bookTemp.TP != key && !endMark(bookTemp));//查找记录
			if (bookTemp.TP == key)
			{
				cout << bookTemp.TP << '\t' << bookTemp.name << '\t' << bookTemp.balance << endl;
				cout << "销售数量:\n$";
				cin >> num;
				if (num > 0 && bookTemp.balance >= num)
				{
					bookTemp.balance -= num;
					if (bookTemp.balance == 0)
					{
						fstream noti(notifications, ios::app);
						noti <<"\n"<< bookTemp.TP << '\t' << "《" << bookTemp.name << "》" << "已售罄\n"
							<<"@\n";//消息结束标志
					}
				}
				else
				{
					cout << "库存不足或销售数量不是正数\n";
					continue;
				}
				file.seekp(-long(sizeof(book)), ios::cur);//写指针复位
				file.write((char*)&bookTemp, sizeof(book));
				cout << "现库存量:\t" << bookTemp.balance << endl;
			}//if
			else
				cout << "未在库存中查找到该书号对应的书籍,请检查书号\n";
			break;
		}//case1
		case 'Q':
		case 'q':return;
		}//switch
	}//while
}

void manager::notification()
{
	char choice;
	string line;
	fstream noti(notifications, ios::in);
	getline(noti, line, '@');//消息结束标记
	//if(line=="#")//文件结束标记
	
	cout << "请选择操作:" << "1:下一条\t" << "2:清空\t"<<"3:退出\n$";
	while(true)
	{
		cin >> choice;
		switch (choice)
		{
		default:cout << "输入错误请重新输入...\n$";
			break;
		case 1:
			getline(noti, line, '@');//如何判断到达文件尾呢?初始化时加一行"#@"?
			cout << line;
		case 2:initial(tongzhi);
		case 3:return;
		}
	}
}

void manager::viewStock()
{
	int choice;
	book temp;
	while(true)
	{
		cout << "***************************查看****************************\n";
		cout << "请选择操作:" << "1:查看库存\t" << "2:清空\t" << "3:退出\n$";
		cin >> choice;
		switch (choice)
		{
		default:cout << "输入错误,请重新输入...\n";
			break;
		case 1:commonFind(all); break;
		case 2:initial(kucun); break;
		case 3:return;
		}
		system("pause");
		system("cls");
	}
}
//统计销量最佳,总销售额,最畅销分类
void manager::analyse()
{
	book temp;
	book popular;
	string popCat;
	int sales=0;
	//文学\t艺术\t科技\t工业\n
	int literature=0;
	int art=0;
	int technology=0;
	int industry=0;
	fstream file(stock, ios::in|ios::binary);
	file.seekg(0, ios::beg);
	do
	{
		file.read((char*)&temp, sizeof(book));
		if (popular.saled < temp.saled)
			popular = temp;
		sales += temp.saled*temp.balance;
		if (temp.category == "文学")
			literature++;
		if (temp.category == "艺术")
			art++;
		if (temp.category == "科技")
			technology++;
		if (temp.category == "工业")
			industry++;
	} while (!endMark(temp));
	cout << "总销售额为:\t" << sales << endl;
	cout << "最畅销书籍为:\n";
	popular.showSimple();
	cout << "最畅销分类为:";
	//求4个变量的最大值,再对应到分类T^T
	int temp1 = literature, temp2 = technology;
	if (literature < art)
		temp1 = art;
	if (technology < industry)
		temp2 = industry;
	if (temp1 < temp2)
		temp1 = temp2;
	if (temp1 == literature)
		cout << "文学\t";
	if (temp1 == art)
		cout << "艺术\t";
	if (temp1 == technology)
		cout << "科技\t";
	if (temp1 == industry)
		cout << "工业\t";
	cout << endl;

}
//权限还是统一在主函数控制吧,这里只写功能
void manager::user()
{

}