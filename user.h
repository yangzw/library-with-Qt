/*用户类的实现
 * by ya
 */
#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#define BORROWBOOKLIMIT 5
#include"manager.h"
class book;
class QString;

using namespace std;

class user
{
    friend class manager;
private:
    QString name;//姓名
    QString number;//学号
    QString email;//邮箱
    book* mybook[BORROWBOOKLIMIT];//借的书
    int booknum;//借书的数量
    QString key;//密码
    bool isbookfull() const;//判断是否已经借满了书
public:
    user();
    user(const QString& name);
    user(const QString& name, const QString& number, const QString& email, const QString& key);
    user(const user &usr);//复制构造函数
    user& operator=(const user &usr);//赋值操作符
    //void showinfo();
    QString getname() const;
    QString getnumber() const;
    QString getemail() const;
    void setname(const QString& name);
    void setnumber(const QString& number);
    void setemail(const QString& email);
    bool addbook(book* newbook);//用户借书
    int getbooknumb() const;
    book** getbooklist();
    bool returnbook(book* rbook);//用户还书
};

#endif // USER_H_INCLUDED
