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
	cout << "*****************书库管理系统(管理员)******************\n\n"
		<< "请选择操作:\n"
		<<"<1>销售\n"
		<<"<2>统计\n"
		<<"<3>通知中心\n"
		<<"<4>库存管理\n"
		<<"<5>用户管理\n"
		<<"<6>初始化\n"
		<<"<7>退出\n\n"
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
		cout << "文件丢失或首次使用, 正在初始化...\n";
		initial(all);
		cleanScreen();
	}
	guest a;
	manager b;
	int choice;
	while (true)
	{
		cout << "*********************书库管理系统********************\n\n"
			<< "请选择操作:\n"
			<< "<1>查询\n"//按分类,按书名,按作者,按书号
			<< "<2>预定\n"//通知信息.txt
			<< "<3>帮助\n"
			<< "<4>登录\n\n"
			<< "******************************************************\n$";
		cin >> choice;
		switch (choice)
		{
		default:
			cout << "输入错误!\n";
			break;
		case 1:
			a.inquire(); break;
		case 2:
			a.want(); break;
		case 3:
			cout << "使用查询功能可以查询书库中是否有你需要的书籍.\n如果没有,可以使用预定功能告诉我们,我们会尽快上架\n";
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