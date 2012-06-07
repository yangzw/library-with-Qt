/*用户类的实现
 * by ya
 */
#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#define BORROWBOOKLIMIT 5
#include"manager.h"
class book;

using namespace std;

class user
{
    friend class manager;
private:
    string name;//姓名
    string number;//学号
    string email;//邮箱
    book* mybook[BORROWBOOKLIMIT];//借的书
    int booknum;//借书的数量
    string key;//密码
    bool isbookfull() const;//判断是否已经借满了书
public:
    user();
    user(const string& name);
    user(const string& name, const string& number, const string& email, const string& key);
    user(const user &usr);//复制构造函数
    user& operator=(const user &usr);//赋值操作符
    void showinfo();
    string getname() const;
    string getnumber() const;
    string getemail() const;
    //void getbookinfor();
    void setname(const string& name);
    void setnumber(const string& number);
    void setemail(const string& email);
    bool addbook(book* newbook);//用户借书
    int getbooknumb() const;
    void returnbook(book* rbook);//用户还书
};

#endif // USER_H_INCLUDED
