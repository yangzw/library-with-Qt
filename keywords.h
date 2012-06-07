#ifndef KEYWORDS_H_INCLUDED
#define KEYWORDS_H_INCLUDED
#include<list>
#include<string>
#include"book.h"
using namespace std;


class keywords
{
    private:
    string key;
    list<book*> bklist;
    int bknum;
    public:
    keywords();
    keywords(book*& bk, string& keywd);
    void addbook(book*& bk);//增加关键字所对的图书
    void delbook(book*& bk);
    void show(); //显示含有该关键字的图书
    int getbknum();
    string getkeywords() const;
};

#endif // KEYWORDS_H_INCLUDED
