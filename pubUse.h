#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<ctime>
#include<conio.h>
#include<cstdlib>
#include<list>//STL����
#include<algorithm>//STL�㷨��
#include"bookStruct.h"
#include"manager.h"
using namespace std;
const string stock = "d:\\stock.dat";//�����Ϣ�ļ���
const string managers = "d:\\managers.dat";//����Ա��Ϣ�ļ���
const string saleLogs = "d:\\salelog.txt";//���ۼ�¼�ļ���
const string notifications = "d:\\notificaiton.txt";//֪ͨ�ļ���
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
int endMark(book bookT);//�жϿ���ļ�β
bool inStock(book toBeFound);//�жϿ�����Ƿ���Ҫ���ҵ��鼮
int commonFind(int flag);//ͨ�ò���,flagΪ��ѯ��ʽ
//void initial(int flag);//��ʼ��,flagΪ��ʼ����ʽ,���,����Ա,֪ͨ,���ۼ�¼,ȫ��
void edit(int flag);//ͨ�ñ༭
void cleanScreen();//����
void checkSales();//�鿴������־
void getTime(string &now);//��ȡʱ���
