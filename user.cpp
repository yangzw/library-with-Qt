#include<QString>
#include"book.h"
#include<iostream>
#include"user.h"

user::user()
{
    booknum = 0;
    for(int i = 0; i < BORROWBOOKLIMIT; ++i)
        mybook[i] = NULL;
}

user::user(const QString& name)
{
    this->name = name;
    booknum = 0;
    for(int i = 0; i < BORROWBOOKLIMIT; ++i)
        mybook[i] = NULL;
}

user::user(const QString& name, const QString& number, const QString& email, const QString& key)
{
    this->name = name;
    this->number = number;
    this->email = email;
    this->key = key;
    booknum = 0;
    for(int i = 0; i < BORROWBOOKLIMIT; ++i)
        mybook[i] = NULL;
}

//复制构造函数
user::user(const user &usr)
{
    name = usr.name;
    number = usr.number;
    email = usr.email;
    key = usr.key;
    booknum = usr.booknum;
    for(int i = 0; i < BORROWBOOKLIMIT; ++i)
        mybook[i] = usr.mybook[i];
}

user& user::operator=(const user &usr)
{
    name = usr.name;
    number = usr.number;
    email = usr.email;
    key = usr.key;
    booknum = usr.booknum;
    for(int i = 0; i < BORROWBOOKLIMIT; ++i)
        mybook[i] = usr.mybook[i];
    return *this;
}

bool user::isbookfull() const
{
    return booknum == BORROWBOOKLIMIT;
}

QString user::getname() const
{
    return name;
}

QString user::getnumber() const
{
    return number;
}

QString user::getemail() const
{
    return email;
}


void user::setname(const QString& name)
{
    this->name = name;
}

void  user::setnumber(const QString& number)
{
    this->number = number;
}

void user::setemail(const QString& email)
{
    this->email = email;
}


bool user::addbook(book* newbook)
{
    if(isbookfull())
        return false;
    else
    {
        mybook[booknum++] = newbook;
        return true;
    }
}

int user::getbooknumb() const
{
    return booknum;
}

book** user::getbooklist()
{
	return mybook;
}

bool user::returnbook(book* rbook)
{
    int i(0);
    while(i < BORROWBOOKLIMIT)
    {
        if(mybook[i] == rbook)
        {
            mybook[i] = mybook[--booknum];
            mybook[booknum] = NULL;
            return true;
        }
        i++;
    }
    return false;
}
