#include"manage.h"
//初始化账目文件,建立只有一个标志记录的空文件
extern const bookData mark;//extern 表示mark为全局变量,在稍后说明,或在另一个文件中说明
void Initial(string filename)
{//以写方式打开,建立新文件
	fstream file(filename, ios::out | ios::binary);
	cout << "若账目文件存在,将清除原有数据,确定要初始化系统吗?(Y/N)\n";
	char answer;
	cin >> answer;
	if (answer == 'Y' || answer == 'y')
	{
		file.seekp(0, ios::beg);
		file.write((char*)&mark, sizeof(bookData));//向流中插入(char*)&mark所指向的字节序列,第二个参数制定字节数
		cout << "文件已初始化.\n";
	}
	else cout << "返回上级菜单.\n";
	file.close();
}