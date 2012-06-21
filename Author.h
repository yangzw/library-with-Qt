/*作者类，用于来进行作者的查找
 */
#ifndef AUTHOR_H_INCLUDED
#define AUTHOR_H_INCLUDED
#include<list>
#include<QString>

class book;
class manager;

using namespace std;

class Author
{
	friend class manager;
private:
    QString Authorname;
    list<book*> bklist;
    int bknum;
public:
    Author();
    Author(book*& bk);
    void addbook(book*& bk);//加入图书后的处理
    void delbook(book*& bk);//删除图书
    int getbknum();
    QString getauthor() const;
};

#endif // AUTHOR_H_INCLUDED
