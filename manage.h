#pragma once //防止重定义,作用与#ifndef相同,由编译器支持(宏定义由语言支持,兼容性更好)
#include"pubUse.h"
#if(1)
struct bookData //账目结构
{
	string TP;//书号
	string name;
	long balance;
};
const bookData mark = { "0","noName\0",0 };//全局变量,空标志记录
void Initial(const string filename);//账目文件初始化
void Append(const string filename);//入库
void Sale(const string filename);//销售
void Inquire(const string filename);//查询
void CreateTxt(const string filename);//创建文本文件
int endMark(bookData book);//判断空标志记录,即判断文件结束
#endif // !0