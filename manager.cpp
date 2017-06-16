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
	cout << "****************��¼********************\n";
	file.seekg(0, ios::beg);
	file.read((char*)&temp, sizeof(manager));
	if (temp.ID == "0")
	{
		cout << "�״ε�¼��Ҫ���ó����û���Ϣ...\n";
		cout << "$�û���:";
		cin >> ID;
		cout << "$����:";
		cin >> password;
		rights = 0;
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

void manager::sale()
{
	char choice;//ѡ��
	book bookTemp;//��ʱ����
	string key;//�������
	long num;//����
	fstream file(stock, ios::in | ios::out | ios::binary);//�Զ�/д��ʽ��
	cout << "\n***************����***************\n";
	while (true)
	{
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
	}//while
}

void manager::notification()
{
	char choice;
	string line;
	fstream noti(notifications, ios::in);
	getline(noti, line, '@');//��Ϣ�������
	//if(line=="#")//�ļ��������
	
	cout << "��ѡ�����:" << "1:��һ��\t" << "2:���\t"<<"3:�˳�\n$";
	while(true)
	{
		cin >> choice;
		switch (choice)
		{
		default:cout << "�����������������...\n$";
			break;
		case 1:
			getline(noti, line, '@');//����жϵ����ļ�β��?��ʼ��ʱ��һ��"#@"?
			cout << line;
		case 2:initial(tongzhi);
		case 3:return;
		}
	}
}

void manager::viewStock()
{
	int choice;
	book temp;
	while(true)
	{
		cout << "***************************�鿴****************************\n";
		cout << "��ѡ�����:" << "1:�鿴���\t" << "2:���\t" << "3:�˳�\n$";
		cin >> choice;
		switch (choice)
		{
		default:cout << "�������,����������...\n";
			break;
		case 1:commonFind(all); break;
		case 2:initial(kucun); break;
		case 3:return;
		}
		system("pause");
		system("cls");
	}
}
//ͳ���������,�����۶�,�������
void manager::analyse()
{
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

}
//Ȩ�޻���ͳһ�����������ư�,����ֻд����
void manager::user()
{

}