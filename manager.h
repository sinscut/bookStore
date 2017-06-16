#pragma once
#include"pubUse.h"
class manager
{
	string ID;
	string password;
	int rights;//0,未登录,1,普通用户,2,超级用户
public:
	manager();
	~manager();
	void logIn();//检查管理员文件并初始化,检查登录.
	void sale();//销售.低级权限
	void notification();//通知中心,包括读者反馈,售罄提醒.低级权限
	void viewStock();//查看,增加,修改,删除,清空库存.除查看外都需要高级权限
	void analyse();//统计销量,总销售额,最畅销分类
	void user();//用户管理,增加,删除用户,配置用户权限.需要高级权限
	friend void initial(int);
};
const manager managerEnd;
struct saleLog
{
	string time;
	string bookTP;
	int sales;
};
const saleLog saleLogFile = { "0","0",0 };