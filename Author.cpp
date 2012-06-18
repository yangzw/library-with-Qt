#include"book.h"
#include<iostream>
#include"Author.h"
#include"manager.h"

Author::Author()//QString和list类自带构造函数
{
    bknum = 0;
}

Author::Author(book*& bk)
{
    Authorname = bk->getauthor();
    bknum = 1;
    bklist.push_back(bk);
}

void Author::addbook(book*& bk)
{
    bklist.push_back(bk);
    bknum++;
}

void Author::delbook(book*& bk)
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

//void  Author::show()
//{
 //   for(list<book*>::iterator iter = bklist.begin(); iter != bklist.end(); ++ iter)
  //      cout << (*iter)->getbkname() << endl;
//}

int Author::getbknum()
{
    return bknum;
}

QString Author::getauthor() const
{
    return Authorname;
}
