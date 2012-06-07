/* manager是整个程序的控制类，通过该类对读者和书籍进行控制管理
 * by ya
 */
#ifndef MANAGER_H_INCLUDED
#define MANAGER_H_INCLUDED
#include<string>
#include "redblacktree.h"

class Author;
class user;
class book;

using namespace std;

class manager
{
private:
    int booknum;//书的数目
    int usernum;//用户数量
    string managerkey;//管理员密码
    string bookfilename;
    string userfilename;
    redblacktree<string,book> booktree;//图书指针的红黑树
    redblacktree<string,Author> Authortree;//作者的红黑树
    redblacktree<string,user> usertree;//用户的红黑树
public:
    bool searchbook(const string& bookname,book*& srbook) const;//搜索图书，按照书名搜索
    bool searchbook(const string& bookname) const;
    bool searchAuthor(const string& athname, Author*& srAuthor) const;//搜索作者
    void searchkey(node<string,book>* root, node<string,book>* nill,string& key, string::size_type& pos);
    bool searchuser(const string& usrname,user*& srusr) const;//搜寻用户
    bool searchuser(const string& usrname) const;
    bool userkey(user* ur) const;//验证用户的密码
    bool loadfileprocess();//加载数据
    void addusr(const string& uname, const string& unumber, const string& uemail, const string& ukey);
    void savebook();
    void saveuser();
    void savebook(node<string,book>* root, node<string,book>* nill);
    void saveuser(node<string,user>* root, node<string,user>* nill);
    manager();
    void loadfile();
    void load();
    void searchbook();//查找书籍
    void searchbykey();//按照关键字查找
    void searchAuthor();//查找作者
    void getuserinfo();//得到用户的信息
    void addusr();//加入用户
    void deluser();//用户注销账号
    bool ismanagerkey() const;//验证管理员密码
    void addbook();//往书库里添书
    void delbook();//从书库里面删除书
    void borrowbook();//借书
    void returnbook();//还书
    void getlibraryinfo();//得到图书馆的信息
    void savechanges();//保存库的变化
};
#endif // MANAGER_H_INCLUDED
