#include"manage.h"
//��ʼ����Ŀ�ļ�,����ֻ��һ����־��¼�Ŀ��ļ�
extern const bookData mark;//extern ��ʾmarkΪȫ�ֱ���,���Ժ�˵��,������һ���ļ���˵��
void Initial(string filename)
{//��д��ʽ��,�������ļ�
	fstream file(filename, ios::out | ios::binary);
	cout << "����Ŀ�ļ�����,�����ԭ������,ȷ��Ҫ��ʼ��ϵͳ��?(Y/N)\n";
	char answer;
	cin >> answer;
	if (answer == 'Y' || answer == 'y')
	{
		file.seekp(0, ios::beg);
		file.write((char*)&mark, sizeof(bookData));//�����в���(char*)&mark��ָ����ֽ�����,�ڶ��������ƶ��ֽ���
		cout << "�ļ��ѳ�ʼ��.\n";
	}
	else cout << "�����ϼ��˵�.\n";
	file.close();
}