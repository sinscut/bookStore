#pragma once //��ֹ�ض���,������#ifndef��ͬ,�ɱ�����֧��(�궨��������֧��,�����Ը���)
#include"pubUse.h"
#if(1)
struct bookData //��Ŀ�ṹ
{
	string TP;//���
	string name;
	long balance;
};
const bookData mark = { "0","noName\0",0 };//ȫ�ֱ���,�ձ�־��¼
void Initial(const string filename);//��Ŀ�ļ���ʼ��
void Append(const string filename);//���
void Sale(const string filename);//����
void Inquire(const string filename);//��ѯ
void CreateTxt(const string filename);//�����ı��ļ�
int endMark(bookData book);//�жϿձ�־��¼,���ж��ļ�����
#endif // !0