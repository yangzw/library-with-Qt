#include<string>
#include"book.h"
#include<iostream>
#include"user.h"

user::user()
{
    booknum = 0;
    for(int i = 0; i < BORROWBOOKLIMIT; ++i)
        mybook[i] = NULL;
}

user::user(const string& name)
{
    this->name = name;
    booknum = 0;
    for(int i = 0; i < BORROWBOOKLIMIT; ++i)
        mybook[i] = NULL;
}

user::user(const string& name, const string& number, const string& email, const string& key)
{
    this->name = name;
    this->number = number;
    this->email = email;
    this->key = key;
    booknum = 0;
    for(int i = 0; i < BORROWBOOKLIMIT; ++i)
        mybook[i] = NULL;
}

//���ƹ��캯��
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

void user::showinfo()
{
    cout << "Name: " << name << endl;
    cout << "Xuehao: " << number << endl;
    cout << "Email: " << email << endl;
    cout << "Borrowed BookNumber: " << booknum << endl;
    int i(0);
    cout << "The book you have borrowed is:" << endl;
    while(mybook[i])
        cout << mybook[i++]->getbkname() << endl;
}

string user::getname() const
{
    return name;
}

string user::getnumber() const
{
    return number;
}

string user::getemail() const
{
    return email;
}

void user::setname(const string& name)
{
    this->name = name;
}

void  user::setnumber(const string& number)
{
    this->number = number;
}

void user::setemail(const string& email)
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

void user::returnbook(book* rbook)
{
    int i(0);
    while(i < BORROWBOOKLIMIT)
    {
        if(mybook[i] == rbook)
        {
            mybook[i] = mybook[--booknum];
            mybook[booknum] = NULL;
            return;
        }
        i++;
    }
    cout << "error, can't return the book!" << endl;
}
