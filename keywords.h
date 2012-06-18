#ifndef KEYWORDS_H_INCLUDED
#define KEYWORDS_H_INCLUDED
#include<list>
#include<QString>
using namespace std;

class book;

class keywords
{
    private:
    QString key;
    list<book*> bklist;
    int bknum;
    public:
    keywords();
    keywords(book*& bk, QString& keywd);
    void addbook(book*& bk);//增加关键字所对的图书
    void delbook(book*& bk);
    //void show(); //显示含有该关键字的图书
    int getbknum();
    QString getkeywords() const;
};

#endif // KEYWORDS_H_INCLUDED
