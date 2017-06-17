#include"pubUse.h"	
//����ļ������ж�
int endMark(book bookT)
{
	if (bookT.TP == "0")
		return 1;
	return 0;
}
//�жϿ�����Ƿ���Ҫ���ҵ���
bool inStock(book toBeFound)
{
	book temp;
	fstream file(stock, ios::in | ios::binary);//�򿪿���ļ�
	file.seekg(0, ios::beg);
	do
	{
		file.read((char*)&temp, sizeof(book));
		if (temp.name == toBeFound.name && temp.author == toBeFound.author)
			return true;
	} while (!endMark(temp));
	return false;
	//file�����ڽ���Ӧ�û��Զ��ر��ļ�
}


//cat=0,name=1,author=2,all=3
int commonFind(int flag)
{
	book temp;
	int none = 1;
	string answer;//������
	if (flag == cat)
		cout << "������������·���:\n"
		<< "��ѧ\t����\t�Ƽ�\t��ҵ\n$";
	if (flag == name)
		cout << "$��������:";
	if (flag == author)
		cout << "$����������:";
	cin >> answer;
	fstream file(stock, ios::in | ios::binary);//�򿪿���ļ�
	file.seekg(0, ios::beg);
	do
	{
		file.read((char*)&temp, sizeof(book));
		switch (flag)//���ҷ�ʽ
		{
		default:
			break;
		case cat:
			if (temp.category == answer)
			{
				temp.show();
				none = 0;
			}
			break;
		case name:
			if (temp.name == answer)
			{
				temp.show();
				none = 0;
			}
			break;
		case author:
			if (temp.author == answer)
			{
				temp.show();
				none = 0;
			}
			break;
		case all:
			if (!endMark(temp))
			{
				temp.showSimple();
				none = 0;
			}
		}//switch
	} while (!endMark(temp));
	if (none) cout << "δ�ҵ�����鼮...\n";
	return none;
}

//��find_if�ж��õĽṹ��(α����),Ҳ��������==,������Ϊ�ж�ֵ, �ο�http://blog.csdn.net/learnhard/article/details/5692104
typedef struct findBook

{
	findBook(string t) : TP(t) {}
	bool operator()(book p)
	{
		return (TP == p.TP);
	}
	string	TP;
}finder;
//add=1,amend=2,cutOut=3
void edit(int flag)
{
	string tempTP;
	book temp;
	list<book>  fileOp;
	list<book>::iterator p;
	fstream file(stock, ios::in | ios::out | ios::binary);
	file.seekg(0, ios::beg);
	do
	{
		file.read((char*)&temp, sizeof(book));
		if (!endMark(temp))
			fileOp.push_back(temp);//���ļ��е����ݸ��Ƶ�����
	} while (!endMark(temp));
	switch (flag)
	{
	default:
		break;
	case add:
		temp.saled = 0;//�Է���һ, ��Ϊbook::set()��������saled
		cout << "¼���鼮��Ϣ:\n$";
		temp.set();
		fileOp.push_back(temp);
		break;
	case amend:
		cout << "����Ҫ�޸���Ϣ�����:\n$";
		cin >> tempTP;
		//�������
		p = find_if(fileOp.begin(), fileOp.end(), finder(tempTP));//find_if()�����������Ǻ���ָ��(������)
		if (p != fileOp.end())
		{
			cout << "ֻ���޸ļ۸�(��ǰ�۸�Ϊ:" << p->price << "),������۸�:\n$";
			int tempPrice;
			cin >> tempPrice;
			p->price = tempPrice;
			cout << "�޸ļ۸�Ϊ" << p->price << "�ɹ�!\n";
		}
		else cout << "��Ŵ���,������.\n";
		break;
	case cutOut:
		cout << "����Ҫɾ���鼮�����:\n$";
		cin >> tempTP;
		//�������
		p = find_if(fileOp.begin(), fileOp.end(), finder(tempTP));//find_if()�����������Ǻ���ָ��(������)
		if (p != fileOp.end())
		{
			fileOp.erase(p);
			cout << "ɾ���ɹ�!\n";
		}
		else cout << "��Ŵ���,������.\n";
	}
	//�������е���Ϣ����д���ļ�
	p = fileOp.begin();
	file.seekp(0, ios::beg);
	for (p; p != fileOp.end(); ++p)
	{
		temp = *p;
		file.write((char*)&temp, sizeof(book));
	}
	const book end;
	file.write((char*)&end, sizeof(book));
}

//	����
void cleanScreen()
{
	cout << "�����������...";
	system("pause");
	system("cls");
}

//�鿴������־
void checkSales()
{
	string line;
	fstream file(saleLogs, ios::in);
	if (!file.eof())
		getline(file, line, '@');//@��Ϣ�������
	else
	{
		cout << "�����ۼ�¼,��������˳�...\n";
		system("pause");
		return;
	}
	cout << line << endl;
	while (!file.eof())
	{
		getline(file, line, '@');
		cout << line << endl;
	}
}
void getTime(string &now)
{
	time_t t;
	char tme[32];
	t = time(NULL);//��ȡ��ǰʱ��
	ctime_s(tme, 32, &t);
	now = tme;
}