/*图书类的实现
 * by ya
 */
#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED
#include<string>

class manager;

using namespace std;


class book
{
private:
    friend class manager;
    string bkname;
    string author;
    string isbn;
    string state;
public:
    book();
    book(const string& name);
    book(const string& name, const string& ibn, const string& ath);
    book(const string& name, const string& ibn, const string& ath, const string& st);
    book(const book& bk);//复制构造函数
    book& operator=(const book& bk);//赋值操作符
    void getinfor();
    string getbkname() const;
    string getauthor() const;
    string getisbn() const;
    void getstate();
    void setstate(const string& state);
    void setbkname(const string& name);
    void setauthor(const string& author);
    void setisbn(const string& isbn);
};

#endif // BOOK_H_INCLUDED
