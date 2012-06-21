/*图书类的实现
 * by ya
 */
#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED
#include<QString>

class manager;

using namespace std;


class book
{
private:
    friend class manager;
    QString bkname;
    QString author;
    QString isbn;
    QString state;
public:
    book();
    book(const QString& name);
    book(const QString& name, const QString& ibn, const QString& ath);
    book(const QString& name, const QString& ibn, const QString& ath, const QString& st);
    book(const book& bk);//复制构造函数
    book& operator=(const book& bk);//赋值操作符
    QString getbkname() const;
    QString getauthor() const;
    QString getisbn() const;
    QString getstate() const;
    void setstate(const QString& state);
    void setbkname(const QString& name);
    void setauthor(const QString& author);
    void setisbn(const QString& isbn);
};

#endif // BOOK_H_INCLUDED
