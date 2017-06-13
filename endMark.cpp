#include"manage.h"
//判断是否为空标志记录
int endMark(bookData book)
{
	if (book.TP == "0")
		return 1;
	return 0;
}