#include "manager.h"

manager::manager()
{
	ID = "0";
	password = "0";
	rights = 0;
}

manager::~manager()
{
}
void manager::logIn()
{
	manager temp;
	int num = 3;//��¼��¼����
	fstream file(managers, ios::in | ios::out | ios::binary);
	//�ж��Ƿ���Ҫ��ʼ��
	if (!file)
	{
		cout << "����Ա��Ϣ��ʧ,���ʼ��...\n";//���ǵ����ŵ���ʼ���������,����ֻ�����¼��֤..��ʼ��Ҫ�ܷ����ʼ����ȫ����ʼ��
		initial(guanliyuan);
		return;
	}
	cout << "*************************��¼*************************\n";
	file.seekg(0, ios::beg);
	file.read((char*)&temp, sizeof(manager));
	if (temp.ID == "0")
	{
		cout << "�״ε�¼��Ҫ���ó����û���Ϣ...\n";
		cout << "$�û���:";
		cin >> ID;
		cout << "$����:";
		cin >> password;
		rights = 2;
		file.seekp(-long(sizeof(manager)), ios::cur);
		file.write((char*)this, sizeof(manager));
		cout << "���óɹ�!";
		cout << "�������������һ��...\n";
		system("pause");
		return;
	}
	while(num)
	{
		cout << "$�û���:";
		cin >> ID;
		cout << "$����:";
		cin >> password;
		file.seekg(0, ios::beg);
		do
		{
			file.read((char*)&temp, sizeof(manager));
			if (ID == temp.ID&&password == temp.password)
			{
				rights = temp.rights;
				cout << "��¼�ɹ�!\n";
				return;
			}
		} while (temp.rights != 0);
		cout << "�û������������!\n";
	}
	cout << "��������3�ε�¼ʧ��,���Ժ�����!\n";
}

void manager::logOut()
{
	ID = "0";
	password = "0";
	rights = 0;
}

void manager::sale()
{
	char choice;//ѡ��
	book bookTemp;//��ʱ����
	string key;//�������
	long num;//����
	fstream file(stock, ios::in | ios::out | ios::binary);//�Զ�/д��ʽ��
	while (true)
	{
		cout << "\n***********************����*************************\n";
		cout << "��ѡ�����:"<< "1:���۵Ǽ�\t" << "Q:�˳�\n$";
		cin >> choice;
		switch (choice)
		{
		default:cout << "�������,����������\n";
			break;
		case '1':
		{
			file.seekg(0, ios::beg);
			cout << "���(TP):\n$";
			cin >> key;
			do
			{
				file.read((char*)&bookTemp, sizeof(book));
			} while (bookTemp.TP != key && !endMark(bookTemp));//���Ҽ�¼
			if (bookTemp.TP == key)
			{
				cout << bookTemp.TP << '\t' << bookTemp.name << '\t' << bookTemp.balance << endl;
				cout << "��������:\n$";
				cin >> num;
				if (num > 0 && bookTemp.balance >= num)
				{
					bookTemp.balance -= num;
					string now;
					getTime(now);//��ȡʱ���
					fstream sales(saleLogs, ios::app);
					sales << now << "���� " << bookTemp.name << " " << num << "��." << "�ۼ� " << bookTemp.price << "@";
					if (bookTemp.balance == 0)
					{
						fstream noti(notifications, ios::app);
						noti <<"\n"<< bookTemp.TP << '\t' << "��" << bookTemp.name << "��" << "������\n"
							<<"@\n";//��Ϣ������־
					}
				}
				else
				{
					cout << "��治�������������������\n";
					continue;
				}
				file.seekp(-long(sizeof(book)), ios::cur);//дָ�븴λ
				file.write((char*)&bookTemp, sizeof(book));
				cout << "�ֿ����:\t" << bookTemp.balance << endl;
			}//if
			else
				cout << "δ�ڿ���в��ҵ�����Ŷ�Ӧ���鼮,�������\n";
			break;
		}//case1
		case 'Q':
		case 'q':return;
		}//switch
		cleanScreen();
	}//while
}

void manager::notification()
{
	cout << "**************************֪ͨ*****************************\n";
	char choice;
	string line;
	fstream noti(notifications, ios::in);
	if(!noti.eof())
		getline(noti, line, '@');//@��Ϣ�������
	else
	{
		cout << "��֪ͨ,��������˳�...\n";
		system("pause");
		return;
	}
	cout << line << endl;
	cout << "��ѡ�����:" << "1:��һ��\t" << "2:���\t"<<"3:�˳�\n$";
	while(!noti.eof())//�ļ�δ����
	{
		cin >> choice;
		switch (choice)
		{
		default:
			cout << "�����������������...\n$";
			break;
		case 1:
			getline(noti, line, '@');//����жϵ����ļ�β��?��ʼ��ʱ��һ��"#@"?
			cout << line << endl;
			break;
		case 2:
			initial(tongzhi);
			cout << "��֪ͨ,��������˳�...\n";
			system("pause");
			return;
		case 3:
			return;
		}
	}
	cout << "����ʾȫ��֪ͨ,��������˳�...\n";
	system("pause");
	return;
}
//�鿴,����,�޸�,ɾ��,��տ��.���鿴�ⶼ��Ҫ�߼�Ȩ��
void manager::viewStock()
{
	int choice;
	book temp;
	while(true)
	{
		cout << "***************************������****************************\n";
		cout << "��ѡ�����:"//������ȫ������������
			<< "1:�鿴\n"
			<< "2:����\n"
			<< "3:�޸�\n"
			<< "4:ɾ��\n"
			<< "5:���\n"
			<< "6:�˳�\n\n$";
		cin >> choice;
		if (choice <= 6 && choice >= 1)
			system("cls");
		switch (choice)
		{
		default:cout << "�������,����������...\n";
			break;
		case 1:commonFind(all); break;
		case 2:
			if(rights==2)
				edit(add);
			else cout << "��Ҫ�����û�Ȩ��!\n";
			break;
		case 3:
			if (rights == 2)
				edit(amend);
			else cout << "��Ҫ�����û�Ȩ��!\n";
			break;
		case 4:
			if (rights == 2)
				edit(cutOut);
			else cout << "��Ҫ�����û�Ȩ��!\n";
			break;
		case 5:initial(kucun); break;
		case 6:return;
		}
		cleanScreen();
	}
}
//ͳ���������,�����۶�,�������
void manager::analyse()
{
	cout << "*************************ͳ��**************************\n";
	book temp;
	book popular;
	string popCat;
	int sales=0;
	//��ѧ\t����\t�Ƽ�\t��ҵ\n
	int literature=0;
	int art=0;
	int technology=0;
	int industry=0;
	fstream file(stock, ios::in|ios::binary);
	file.seekg(0, ios::beg);
	do
	{
		file.read((char*)&temp, sizeof(book));
		if (popular.saled < temp.saled)
			popular = temp;
		sales += temp.saled*temp.balance;
		if (temp.category == "��ѧ")
			literature++;
		if (temp.category == "����")
			art++;
		if (temp.category == "�Ƽ�")
			technology++;
		if (temp.category == "��ҵ")
			industry++;
	} while (!endMark(temp));
	cout << "�����۶�Ϊ:\t" << sales << endl;
	cout << "����鼮Ϊ:\n";
	popular.showSimple();
	cout << "�������Ϊ:";
	//��4�����������ֵ,�ٶ�Ӧ������T^T
	int temp1 = literature, temp2 = technology;
	if (literature < art)
		temp1 = art;
	if (technology < industry)
		temp2 = industry;
	if (temp1 < temp2)
		temp1 = temp2;
	if (temp1 == literature)
		cout << "��ѧ\t";
	if (temp1 == art)
		cout << "����\t";
	if (temp1 == technology)
		cout << "�Ƽ�\t";
	if (temp1 == industry)
		cout << "��ҵ\t";
	cout << endl;
	cout << "������־��d:\\salelog.txt, Ҫ�����?(0/1)\n";
	int choice;
	cin >> choice;
	if (choice)
		checkSales();
}
//�û�����, �޸�����, �����û�, ɾ���û�(Ȩ�޽�Ϊ0)
void manager::user()
{
	int choice;
	string tempID;
	manager temp;
	fstream file(managers, ios::in | ios::out | ios::binary);
	while (true)
	{
		file.seekg(0, ios::beg);
		cout << "***********************�û�����***********************\n"
			<< "��ѡ�����:\n"
			<< "1.�޸�����\n"
			<< "2.�����û�\n"
			<< "3.ɾ���û�\n"
			<< "4.�˳�";
		cin >> choice;
		switch (choice)
		{
		default:
			break;
		case 1:
			if(rights==1||rights==2)
			{
				do
				{
					file.read((char*)&temp, sizeof(manager));
				} while (temp.ID != ID);
				cout << "������������:\n$";
				cin >> temp.password;
				file.seekp(-long(sizeof(manager)), ios::cur);
				file.write((char*)&temp, sizeof(manager));
				cout << "�޸�����ɹ�!\n";
			}
			break;
		case 2:
			if (rights == 2)
			{
				file.seekp(-long(sizeof(manager)), ios::end);//����ָ����˼�����Ҫ��һ��
				cout << "$�����û���:";
				cin >> temp.ID;
				cout << "$��������:";
				cin >> temp.password;
				cout << "����Ȩ��,1Ϊ��ͨ�û�,2Ϊ�����û�\n$";
			L:
				cin >> choice;
				if (choice != 1 || choice != 2)
				{
					cout << "�������!\n$����������:";
					goto L;
				}
				else
				{
					temp.rights = choice;
					file.write((char*)&temp, sizeof(manager));
					cout << "�����û�" << temp.ID << "�ɹ�!\n";
				}
			}
			else cout << "��Ҫ�����û�Ȩ��!\n";
			break;
		case 3:
			if (rights == 2)
			{
				cout << "$����Ҫɾ����ID:";
				cin >> tempID;
				do
				{
					file.read((char*)&temp, sizeof(manager));
				} while (temp.ID != tempID&&temp.ID!="0");
				if(temp.ID!="0")
				{
					temp.rights = 0;
					file.seekp(-long(sizeof(manager)), ios::cur);
					file.write((char*)&temp, sizeof(manager));
					cout << "ɾ���û�" << temp.ID << "�ɹ�!\n";
				}
				else cout << "���û�������!\n";
			}
			else cout << "��Ҫ�����û�Ȩ��!\n";
			break;
		case 4:
			return;
		}
		cleanScreen();
	}

}
int manager::getRights() { return rights; }

//all=3,guanliyuan=4,kucun=5,tongzhi=6,xiaoshou=7
void initial(int flag)
{
	switch (flag)
	{
	default:
		break;
	case all:
	{
		initial(kucun);
		initial(tongzhi);
		initial(xiaoshou);
		initial(guanliyuan);
		break;
	}
	case kucun:
	{
		book temp;
		fstream file(stock, ios::out | ios::trunc | ios::binary);
		file.seekp(0, ios::beg);
		file.write((char*)&temp, sizeof(book));
		cout << "�ѳ�ʼ�����!\n";
		break;
	}
	case tongzhi:
	{
		fstream file(notifications, ios::out | ios::trunc);
		cout << "�����֪ͨ!\n";
		break;//��ʱ�Ȳ����ļ�����������
	}
	case guanliyuan:
	{
		manager tempM;
		fstream file(managers, ios::out | ios::trunc | ios::binary);
		file.write((char*)&tempM, sizeof(manager));
		//��ʼ���ɹ�,���������������
		cout << "��ʼ���ɹ�,��������������\n"
			<< "�����������...\n";
		system("pause");
		exit(0);
	}
	case xiaoshou:
	{
		//���������־
		fstream file(saleLogs, ios::out | ios::trunc);
		cout << "�����������־!\n";
	}
	}
}