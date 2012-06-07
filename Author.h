/*作者类，用于来进行作者的查找
 */
#ifndef AUTHOR_H_INCLUDED
#define AUTHOR_H_INCLUDED
#include<list>

class book;

using namespace std;

class Author
{
private:
    string Authorname;
    list<book*> bklist;
    int bknum;
public:
    Author();
    Author(book*& bk);
    void addbook(book*& bk);//加入图书后的处理
    void  show();//显示图书
    void delbook(book*& bk);//删除图书
    int getbknum();
    string getauthor() const;
};

#endif // AUTHOR_H_INCLUDED
