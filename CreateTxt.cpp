#include"manage.h"
//�����������ļ�,��һ����ʽд���ı��ļ���
const string filetxt = "d:\\booksFile.txt";//�����ı��ļ��洢·��
void CreateTxt(string filedat)
{
	fstream fdat(filedat, ios::in | ios::binary);
	fstream ftxt(filetxt, ios::out);
	fdat.seekg(0, ios::beg);//�������ļ���ָ���Ƶ��ļ�ͷ
	bookData book;
	cout << "***************�����ı��ļ�***************\n";
	do
	{
		fdat.read((char*)&book, sizeof(bookData));
		if (!endMark(book))
			ftxt << book.TP << '\t' << book.name << '\t' << book.balance << '\n';//����¼д���ı��ļ�
	} while (!endMark(book));
	ftxt.close();
	cout << "�ı��ļ��ѽ���,Ҫ����ļ���?(Y/N)\n";
	//��ȡ�ı��ļ�
	char flag, line[80];
	cin >> flag;
	if (flag == 'Y' || flag == 'y')
	{
		ftxt.open(filetxt, ios::in);//���������ļ�
		while (!ftxt.eof())
		{
			ftxt.getline(line, 80);
			cout << line << endl;
		}
		ftxt.close();
	}
	fdat.close();
}