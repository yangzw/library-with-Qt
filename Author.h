/*�����࣬�������������ߵĲ���
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
    void addbook(book*& bk);//����ͼ���Ĵ���
    void  show();//��ʾͼ��
    void delbook(book*& bk);//ɾ��ͼ��
    int getbknum();
    string getauthor() const;
};

#endif // AUTHOR_H_INCLUDED
