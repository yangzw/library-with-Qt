/*�����࣬�������������ߵĲ���
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
    void addbook(book*& bk);//����ͼ���Ĵ���
    void delbook(book*& bk);//ɾ��ͼ��
    int getbknum();
    QString getauthor() const;
};

#endif // AUTHOR_H_INCLUDED
