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
	cout << "*************************登录*************************\n";
	file.seekg(0, ios::beg);
	file.read((char*)&temp, sizeof(manager));
	if (temp.ID == "0")
	{
		cout << "首次登录需要配置超级用户信息...\n";
		cout << "$用户名:";
		cin >> ID;
		cout << "$密码:";
		cin >> password;
		rights = 2;
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

void manager::logOut()
{
	ID = "0";
	password = "0";
	rights = 0;
}

void manager::sale()
{
	char choice;//选择
	book bookTemp;//临时变量
	string key;//查找书号
	long num;//销量
	fstream file(stock, ios::in | ios::out | ios::binary);//以读/写方式打开
	while (true)
	{
		cout << "\n***********************销售*************************\n";
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
					string now;
					getTime(now);//获取时间戳
					fstream sales(saleLogs, ios::app);
					sales << now << "卖出 " << bookTemp.name << " " << num << "本." << "售价 " << bookTemp.price << "@";
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
		cleanScreen();
	}//while
}

void manager::notification()
{
	cout << "**************************通知*****************************\n";
	char choice;
	string line;
	fstream noti(notifications, ios::in);
	if(!noti.eof())
		getline(noti, line, '@');//@消息结束标记
	else
	{
		cout << "无通知,按任意键退出...\n";
		system("pause");
		return;
	}
	cout << line << endl;
	cout << "请选择操作:" << "1:下一条\t" << "2:清空\t"<<"3:退出\n$";
	while(!noti.eof())//文件未结束
	{
		cin >> choice;
		switch (choice)
		{
		default:
			cout << "输入错误请重新输入...\n$";
			break;
		case 1:
			getline(noti, line, '@');//如何判断到达文件尾呢?初始化时加一行"#@"?
			cout << line << endl;
			break;
		case 2:
			initial(tongzhi);
			cout << "无通知,按任意键退出...\n";
			system("pause");
			return;
		case 3:
			return;
		}
	}
	cout << "已显示全部通知,按任意键退出...\n";
	system("pause");
	return;
}
//查看,增加,修改,删除,清空库存.除查看外都需要高级权限
void manager::viewStock()
{
	int choice;
	book temp;
	while(true)
	{
		cout << "***************************库存管理****************************\n";
		cout << "请选择操作:"//不如先全部读到链表里
			<< "1:查看\n"
			<< "2:增加\n"
			<< "3:修改\n"
			<< "4:删除\n"
			<< "5:清空\n"
			<< "6:退出\n\n$";
		cin >> choice;
		if (choice <= 6 && choice >= 1)
			system("cls");
		switch (choice)
		{
		default:cout << "输入错误,请重新输入...\n";
			break;
		case 1:commonFind(all); break;
		case 2:
			if(rights==2)
				edit(add);
			else cout << "需要超级用户权限!\n";
			break;
		case 3:
			if (rights == 2)
				edit(amend);
			else cout << "需要超级用户权限!\n";
			break;
		case 4:
			if (rights == 2)
				edit(cutOut);
			else cout << "需要超级用户权限!\n";
			break;
		case 5:initial(kucun); break;
		case 6:return;
		}
		cleanScreen();
	}
}
//统计销量最佳,总销售额,最畅销分类
void manager::analyse()
{
	cout << "*************************统计**************************\n";
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
	cout << "销售日志在d:\\salelog.txt, 要浏览吗?(0/1)\n";
	int choice;
	cin >> choice;
	if (choice)
		checkSales();
}
//用户管理, 修改密码, 增加用户, 删除用户(权限降为0)
void manager::user()
{
	int choice;
	string tempID;
	manager temp;
	fstream file(managers, ios::in | ios::out | ios::binary);
	while (true)
	{
		file.seekg(0, ios::beg);
		cout << "***********************用户管理***********************\n"
			<< "请选择操作:\n"
			<< "1.修改密码\n"
			<< "2.增加用户\n"
			<< "3.删除用户\n"
			<< "4.退出";
		cin >> choice;
		switch (choice)
		{
		default:
			break;
		case 1:
			if(rights==1||rights==2)
			{
				do
				{
					file.read((char*)&temp, sizeof(manager));
				} while (temp.ID != ID);
				cout << "请输入新密码:\n$";
				cin >> temp.password;
				file.seekp(-long(sizeof(manager)), ios::cur);
				file.write((char*)&temp, sizeof(manager));
				cout << "修改密码成功!\n";
			}
			break;
		case 2:
			if (rights == 2)
			{
				file.seekp(-long(sizeof(manager)), ios::end);//这里指针该退几步还要试一下
				cout << "$输入用户名:";
				cin >> temp.ID;
				cout << "$输入密码:";
				cin >> temp.password;
				cout << "配置权限,1为普通用户,2为超级用户\n$";
			L:
				cin >> choice;
				if (choice != 1 || choice != 2)
				{
					cout << "输入错误!\n$请重新输入:";
					goto L;
				}
				else
				{
					temp.rights = choice;
					file.write((char*)&temp, sizeof(manager));
					cout << "增加用户" << temp.ID << "成功!\n";
				}
			}
			else cout << "需要超级用户权限!\n";
			break;
		case 3:
			if (rights == 2)
			{
				cout << "$输入要删除的ID:";
				cin >> tempID;
				do
				{
					file.read((char*)&temp, sizeof(manager));
				} while (temp.ID != tempID&&temp.ID!="0");
				if(temp.ID!="0")
				{
					temp.rights = 0;
					file.seekp(-long(sizeof(manager)), ios::cur);
					file.write((char*)&temp, sizeof(manager));
					cout << "删除用户" << temp.ID << "成功!\n";
				}
				else cout << "该用户不存在!\n";
			}
			else cout << "需要超级用户权限!\n";
			break;
		case 4:
			return;
		}
		cleanScreen();
	}

}
int manager::getRights() { return rights; }

//all=3,guanliyuan=4,kucun=5,tongzhi=6,xiaoshou=7
void initial(int flag)
{
	switch (flag)
	{
	default:
		break;
	case all:
	{
		initial(kucun);
		initial(tongzhi);
		initial(xiaoshou);
		initial(guanliyuan);
		break;
	}
	case kucun:
	{
		book temp;
		fstream file(stock, ios::out | ios::trunc | ios::binary);
		file.seekp(0, ios::beg);
		file.write((char*)&temp, sizeof(book));
		cout << "已初始化库存!\n";
		break;
	}
	case tongzhi:
	{
		fstream file(notifications, ios::out | ios::trunc);
		cout << "已清空通知!\n";
		break;//暂时先不管文件结束的问题
	}
	case guanliyuan:
	{
		manager tempM;
		fstream file(managers, ios::out | ios::trunc | ios::binary);
		file.write((char*)&tempM, sizeof(manager));
		//初始化成功,按任意键重启程序
		cout << "初始化成功,请重新启动程序\n"
			<< "按任意键继续...\n";
		system("pause");
		exit(0);
	}
	case xiaoshou:
	{
		//清空销售日志
		fstream file(saleLogs, ios::out | ios::trunc);
		cout << "已清空销售日志!\n";
	}
	}
}