#include"manage.h"
//读出二进制文件,以一定格式写入文本文件中
const string filetxt = "d:\\booksFile.txt";//定义文本文件存储路径
void CreateTxt(string filedat)
{
	fstream fdat(filedat, ios::in | ios::binary);
	fstream ftxt(filetxt, ios::out);
	fdat.seekg(0, ios::beg);//二进制文件读指针移到文件头
	bookData book;
	cout << "***************导出文本文件***************\n";
	do
	{
		fdat.read((char*)&book, sizeof(bookData));
		if (!endMark(book))
			ftxt << book.TP << '\t' << book.name << '\t' << book.balance << '\n';//将记录写入文本文件
	} while (!endMark(book));
	ftxt.close();
	cout << "文本文件已建立,要浏览文件吗?(Y/N)\n";
	//读取文本文件
	char flag, line[80];
	cin >> flag;
	if (flag == 'Y' || flag == 'y')
	{
		ftxt.open(filetxt, ios::in);//重用流打开文件
		while (!ftxt.eof())
		{
			ftxt.getline(line, 80);
			cout << line << endl;
		}
		ftxt.close();
	}
	fdat.close();
}