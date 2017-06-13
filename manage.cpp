#include"manage.h"
//建立主菜单,选择操作
const string filename = "d:\\booksFile.dat";//  "\\"有一个是转义符
int main()
{
	char choice;
	while (true)
	{
		cout << "***************书库管理***************\n请输入操作选择\n"
			<< "1:入库\t" << "2:售出\t" << "3:查询\t" 
			<< "4:导出文本文件\t" << "0:初始化\t" << "Q:退出\n";
		cin >> choice;
		switch (choice)
		{
		case '1':Append(filename); break;
		case '2':Sale(filename); break;
		case '3':Inquire(filename); break;
		case '4':CreateTxt(filename); break;
		case '0':Initial(filename); break;
		case 'q':
		case 'Q':cout << "退出系统\n"; return 0;//试一下可不可以用||-----不可以
		default:cout << "输入错误,请重新输入\n";
		}
	}
}
//下一步将添加用户管理功能