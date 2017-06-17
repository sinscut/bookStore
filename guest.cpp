#include "guest.h"
#include"pubUse.h"


guest::guest()
{
	name = "noname";
	TEL = "0";
}
guest::~guest()
{

}
void guest::want()
{
	book temp;
	cout<< "请输入你希望上架的书籍信息...\n"
		<<"书名\n$";
	cin >> temp.name;
	cout<< "作者\n$";
	cin >> temp.author;
	//查询图书是否在库bool inStock(book);
	if (inStock(temp))
		cout << "书库中已经有这本书了哦,试试查询功能吧\n";
	else
	{
		cout << "请留下你的联系方式,该书上架后我们会尽快与你取得联系.\n";
		cout << "$姓名:";
		cin >> name;
		cout << "$电话:";
		cin >> TEL;
		fstream file(notifications, ios::app);
		file << "读者反馈:\n"
			<< "希望上架的图书:" << "《" << temp.name << "》" << "\t" << "作者:" << temp.author << "\n"
			<< "读者信息:\n"
			<< "姓名:\t" << name << "电话:\t" << TEL<<endl
			<<"@\n";//消息结束标志
		cout << "登记成功!";
		//生存期结束自动关闭文件
	}
}
void guest::inquire()
{
	int choice;
	while (true)
	{
		cout << "**************************查询**************************\n";
		cout << "请选择查找方式:\n\n"
			<< "<0>分类查找\n"
			<< "<1>查找书名\n"
			<< "<2>查找作者\n"
			<< "<3>显示全部\n"
			<< "<4>退出";
		cin >> choice;
		if (choice == 4)
			return;
		commonFind(choice);
		cleanScreen();
	}
}
