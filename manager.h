/* manager是整个程序的控制类，通过该类对读者和书籍进行控制管理
 * by ya
 */
#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED
#include "redblacktree.h"
#include<list>
using namespace std;

class Author;
class user;
class book;
class QString;
class QTextStream;
class QStandardItemModel;

using namespace std;

class manager
{
private:
    int booknum;//书的数目
    int usernum;//用户数量
    QString managerkey;//管理员密码
    QString bookfilename;
    QString userfilename;
    redblacktree<QString,book> booktree;//图书指针的红黑树
    redblacktree<QString,Author> Authortree;//作者的红黑树
    redblacktree<QString,user> usertree;//用户的红黑树
public:
    bool searchbook(const QString& bookname,book*& srbook) const;//搜索图书，按照书名搜索
    bool searchbook(const QString& bookname) const;
    bool searchAuthor(const QString& athname, Author*& srAuthor) const;//搜索作者
    bool searchAuthor(const QString& athname) const;
    list<book*> getauthorbklist(Author *&auth);
    void searchbykey(const QString& key,list<book*> &bklist);//按照关键字查找
    void searchkey(node<QString,book>* root, node<QString,book>* nill,const QString& key,list<book*> &bklist);
    bool searchuser(const QString& usrname,user*& srusr) const;//搜寻用户
    bool searchuser(const QString& usrname) const;
    bool userkey(user*& ur,const QString& inkey) const;//验证用户的密码
    void addusr(const QString& uname, const QString& unumber, const QString& uemail, const QString& ukey);
    void updateusr(user*& usr, const QString& unumber, const QString& uemail, const QString& ukey);
    void updateusr(user*& usr,const QString& unumber, const QString& uemail);

    void loadfileprocess();//加载数据
    void setdafaultfile(const QString& bkfilem,const QString& usrfilem);
    void savebook();
    void saveuser();
    void savebook(node<QString,book>* root, node<QString,book>* nill,QTextStream& outbkfile);
    void saveuser(node<QString,user>* root, node<QString,user>* nill,QTextStream& outurfile);
    manager();
    //void loadfile();
    //void load();
    //void searchbook();//查找书籍
    //void searchAuthor();//查找作者
    //void getuserinfo();//得到用户的信息
    //void addusr();//加入用户
    void deluser(user *&delusr);//用户注销账号
    bool ismanagerkey(const QString &inputkey) const;//验证管理员密码
    void addbook(const QString& bkname, const QString& isbn, const QString& author);//往书库里添书
    bool delbook(QString& bkname);//从书库里面删除书
    int borrowbook(user *&usr,const QString& bkname);//借书
    void returnbook(user *&usr,const QString& bkname);//还书
    //void getlibraryinfo();//得到图书馆的信息
    void getalluser(QStandardItemModel *&usermodel);
    void getalluser(node<QString,user>* root, node<QString,user>* nill, QStandardItemModel *&usermodel);
    void getallbook(node<QString,book>* root, node<QString,book>* nill, QStandardItemModel *&bookmodel);
    void getallbook(QStandardItemModel *&bookmodel);
    int getusernumber();
    int getbooknumber();
    void savechanges();//保存库的变化
};
#endif // MANAGER_H_INCLUDED
