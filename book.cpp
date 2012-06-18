#include"book.h"
#include<QString>
#include<iostream>

book::book()
{
    state = "clean";
}

book::book(const QString& name):bkname(name),state("clean") {};

book::book(const QString& name, const QString& ibn, const QString& ath)
{
    bkname = name;
    isbn = ibn;
    author = ath;
    state = "clean";
    //:bkname(name),isbn(ibn),author(ath),state(clean)
};

book::book(const QString& name, const QString& ibn, const QString& ath, const QString& st)
{
    bkname = name;
    isbn = ibn;
    author = ath;
    state = st;
    //:bkname(name),isbn(ibn),author(ath),state(clean)
};

book::book(const book& bk)
//:bkname(bk.bkname),isbn(bk.isbn),author(bk.author),state(bk.state){};
{
    bkname = bk.bkname;
    isbn = bk.isbn;
    author = bk.author;
    state = bk.state;
}

book& book::operator=(const book& bk)
{
    bkname = bk.bkname;
    isbn = bk.isbn;
    author = bk.author;
    state = bk.state;
    return *this;
}

//void book::getinfor()
//{
 //   cout << "Bookname: " << bkname << endl;
  //  cout << "Author: " << author << endl;
   // cout << "Isbn: " << isbn << endl;
    //cout << "State: " << state << endl;
//}

QString book::getbkname() const
{
    return bkname;
}

QString book::getauthor() const
{
    return author;
}

QString book::getisbn() const
{
    return isbn;
}

QString book::getstate() const
{
	return state;
}

void book::setstate(const QString& state)
{
    this->state = state;
}

void book::setbkname(const QString& bkname)
{
    this->bkname = bkname;
}

void book::setauthor(const QString& author)
{
    this->author = author;
}

void book::setisbn(const QString& isbn)
{
    this->isbn = isbn;
}
