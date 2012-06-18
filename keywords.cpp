#include<iostream>
#include"keywords.h"
#include"book.h"

keywords::keywords()
{
	bknum = 0;
}

keywords::keywords(book*& bk, QString& keywd)
{
	key = keywd;
	bknum = 1;
	bklist.push_back(bk);
}

void keywords::addbook(book*& bk)
{
	bklist.push_back(bk);
	bknum++;
}

void keywords::delbook(book*& bk)
{
    for(list<book*>::iterator iter = bklist.begin(); iter != bklist.end(); ++ iter)
    {
        if(*iter == bk)
        {
            bklist.erase(iter);//delete the deleted book
            iter = bklist.begin();
            bknum --;
        }
    }
}

//void keywords::show()
//{
//	for(list<book*>::iterator iter = bklist.begin(); iter != bklist.end(); ++ iter)
//			cout << (*iter)->getbkname() << endl;
//}

int keywords::getbknum()
{
	return bknum;
}

QString keywords::getkeywords() const
{
	return key;
}
