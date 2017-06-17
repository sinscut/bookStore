#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<conio.h>
#include<cstdlib>
#include<list>//STL链表
#include<algorithm>//STL算法库
#include"bookStruct.h"
#include"manager.h"
using namespace std;
const string stock = "d:\\stock.dat";//库存信息文件名
const string managers = "d:\\managers.dat";//管理员信息文件名
const string saleLogs = "d:\\salelog.txt";//销售记录文件名
const string notifications = "d:\\notificaiton.txt";//通知文件名
const int cat = 0;
const int name = 1;
const int author = 2;
const int all = 3;
const int guanliyuan = 4;
const int kucun = 5;
const int tongzhi = 6;
const int xiaoshou = 7;
const int add = 1;
const int amend = 2;
const int cutOut = 3;
int endMark(book bookT);//判断库存文件尾
bool inStock(book toBeFound);//判断库存中是否有要查找的书籍
int commonFind(int flag);//通用查找,flag为查询方式
//void initial(int flag);//初始化,flag为初始化方式,库存,管理员,通知,销售记录,全部
void edit(int flag);//通用编辑
void cleanScreen();//清屏
void checkSales();//查看销售日志
void getTime(string &now);//获取时间戳
