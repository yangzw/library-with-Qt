#include<iostream>
#include<fstream>
#include<sstream>
#include "manager.h"
#include "Author.h"
#include "user.h"
#include "book.h"

manager::manager()
{
    usernum = 0;
    booknum = 0;
    managerkey = "manager";
    bookfilename = userfilename = "none";
};


void manager::loadfile()
{
    cout << "Input the bookfile's name: " << endl;
    getline(cin, bookfilename);
    cout << "Input the userfile's name: " << endl;
    getline(cin, userfilename);
    load();
}

void manager::load()
{
    if(loadfileprocess())
        cout << "Data load sucessfully!" << endl;
    else
        cout << "Faile to load file" << endl;
}

bool manager::loadfileprocess()
{
    fstream inbkfile;
    inbkfile.open(bookfilename.c_str(), ios::in);
    int flag(0);//��־��������һ���ļ�����ɹ�����Ϊ1;
    if(!inbkfile)
    {
        cout << "error:unable to open bookfile!" << endl;
    }
    else
    {
        string tmp;
        flag = 1;
        while(getline(inbkfile,tmp))
        {
            stringstream ss(tmp);
            string bkname;
            string bknametmp;
            string isbn;
            string author;
            string state;
            ss >> isbn;
            ss >> author;
            ss >> state;
            /*��������*/
            ss >> bkname;
            while(ss >> bknametmp)
                bkname = bkname + " " + bknametmp;
            book newbk(bkname,isbn,author,state);
            node<string,book>* tmp = booktree.RB_insert(newbk,newbk.bkname);
            book* nbk = &tmp->data;
            booknum++;
            Author* ath = NULL;
            if(searchAuthor(newbk.author,ath))
                ath->addbook(nbk);
            else
            {
                Author auth(nbk);
                Authortree.RB_insert(auth,newbk.author);
            }
        }
    }
    inbkfile.close();
    fstream inurfile;
    inurfile.open(userfilename.c_str(), ios::in);
    if(!inurfile)
    {
        cout << "erro:ubable to open userfile!" << endl;
    }
    else
    {
        string tmp;
        flag = 1;
        while(getline(inurfile,tmp))
        {
            stringstream ss(tmp);
            string name;
            string number;
            string email;
            string key;
            int bknum;
            ss >> name;
            ss >> number;
            ss >> email;
            ss >> key;
            ss >> bknum;
            user* usr = new user(name,number,email,key);
            string tmpbk;
            for(int i = 0; i < bknum; i++)
            {
                getline(inurfile, tmpbk);
                book* bk(0);
                booktree.search(tmpbk,bk);
                usr->addbook(bk);
            }
            usertree.RB_insert(*usr,usr->name);
            usernum++;
        }
    }
    return flag;
}

bool manager::searchbook(const string& bookname,book*& srbook) const
{
    return booktree.search(bookname,srbook);
}

bool manager::searchbook(const string& bookname) const
{
    return booktree.search(bookname);
}

bool manager::searchAuthor(const string& athname, Author*& srAuthor) const
{
    return Authortree.search(athname,srAuthor);
}


void manager::searchbook()
{
    cout << "Input the book' name�� ";
    string bookname;
    getline(cin, bookname);
    book* srbook = NULL;
    if(searchbook(bookname,srbook))
        srbook->getinfor();
    else
        cout << "Can't find such book!" << endl;
}

void manager::searchbykey()
{
    cout << "Input the key: ";
    string key;
    getline(cin, key);
    cout << "Here is the results:" << endl;
    node<string,book>* nill = booktree.nill;
    node<string,book>* root = booktree.root;
    string::size_type pos = string::npos;
    searchkey(root,nill,key,pos);
}

void manager::searchkey(node<string,book>* root, node<string,book>* nill,string& key, string::size_type& pos)
{
    if(root != nill)
    {
        string bk = root->data.getbkname();
        pos = bk.find(key);
        if(pos != string::npos)
            cout << bk << endl;
        searchkey(root->leftchild,nill,key,pos);
        searchkey(root->rightchild,nill,key,pos);
    }
}

void manager::searchAuthor()
{
    cout << "Input the author: ";
    string athname;
    getline(cin, athname);
    Author* srAuthor = NULL;
    if(searchAuthor(athname,srAuthor))
    {
        cout << "The books of " << athname << " are as follows:" << endl;
        srAuthor->show();
    }
    else
        cout << "Can't find such author!" << endl;
}

bool manager::searchuser(const string& usrname, user*& sruser) const
{
    return usertree.search(usrname, sruser);
}

bool manager::searchuser(const string& usrname) const
{
    return usertree.search(usrname);
}

void manager::getuserinfo()
{
    cout << "Please input your name: " << endl;
    string usrname;
    getline(cin, usrname);
    user* sruser = NULL;
    if(searchuser(usrname, sruser))
    {
        if(userkey(sruser))
        {
            cout << "Here is your information" << endl;
            sruser->showinfo();
        }
    }
    else
        cout << "The name is not registed yet!" << endl;
}

void manager::addusr()
{
    user usr;
    cout << "Input your name: ";
    string tmp;
    getline(cin,tmp);
    while(searchuser(tmp))
    {
        cout << "Sorry, the name is already token" << endl;
        cout << "Input again? input y or n " << endl;
        char choice;
        cin >> choice;
        getchar();
        if(choice == 'y')
        {
            cout << "Input your name: ";
            getline(cin, tmp);
        }
        else
            return;
    }
    usr.setname(tmp);
    cout << "Input your student number: ";
    getline(cin, tmp);
    usr.setnumber(tmp);
    cout << "Input your email: ";
    getline(cin, tmp);
    usr.setemail(tmp);
    cout <<"Input your key: ";
    getline(cin,usr.key);
    cout << "Congratulations! you finish the register!" << endl;
    usernum++;
    usertree.RB_insert(usr,usr.name);
}

void manager::addusr(const string& uname,const string& unumber,const string& uemail,const string& ukey)
{
	user usr;
	usr.setname(uname);
	usr.setnumber(unumber);
	usr.setemail(uemail);
	usr.key = ukey;
	usertree.RB_insert(usr,usr.name);
}

//�û���������֤
bool manager::userkey(user* ur) const
{
    cout << "input your key:" << endl;
    string ukey;
    getline(cin,ukey);
    while(ukey != ur->key)
    {
        cout << "wrong key!" << endl;
        cout << "Input again? input y or n " << endl;
        char choice;
        cin >> choice;
        getchar();
        if(choice == 'y')
        {
            cout << "Input your key: ";
            getline(cin,ukey);
        }
        else
            return false;
    }
    return true;
}

//�û���ע��
void manager::deluser()
{
    string delusr;
    cout << "Input your name:";
    getline(cin, delusr);
    user* usr(0);
    if(!searchuser(delusr,usr))
        cout << "can't find your name" << endl;
    else
    {
        if(userkey(usr))
        {
            if(usr->booknum)
                cout << "you have some book not returned yet!" << endl;
            else
            {
                usertree.RB_DELETE(delusr);
                usernum--;
                cout << "user deleted!" << endl;
            }
        }
    }
}

//��֤����Ա����
bool manager::ismanagerkey() const
{
    cout << "Please input manager key: ";
    string inkey;
    getline(cin,inkey);
    while(inkey != managerkey)
    {
        cout << "wrong key!" << endl;
        cout << "Input again? input y or n " << endl;
        char choice;
        cin >> choice;
        getchar();
        if(choice == 'y')
        {
            cout << "Input your key: ";
            getline(cin,inkey);
        }
        else
            return false;
    }
    return true;
}

//����Ա����ͼ��
void manager::addbook()
{
    if(ismanagerkey())
    {
        book bk;
        cout << "Input the book's name: ";
        string tmp;
        getline(cin, tmp);
        while(searchbook(tmp))
        {
            cout << "Sorry, the book is already in the library" << endl;
            cout << "Input again? input y or n " << endl;
            char choice;
            cin >> choice;
            getchar();
            if(choice == 'y')
            {
                cout << "Input the book's name: ";
                getline(cin, tmp);
            }
            else
                return;
        }
        bk.setbkname(tmp);
        cout << "Input isbn: ";
        getline(cin, tmp);
        bk.setisbn(tmp);
        cout << "Input the author: ";
        getline(cin, tmp);
        bk.setauthor(tmp);
        booknum++;
        node<string,book>* nod = booktree.RB_insert(bk, bk.bkname);
        book* bkk = &nod->data;
        Author* ath = NULL;
        if(searchAuthor(bk.author,ath))
            ath->addbook(bkk);
        else
        {
            Author auth(bkk);
            Authortree.RB_insert(auth,bk.author);
        }
        cout << "Done" << endl;
    }
}

//����Աɾ��ͼ��
void manager::delbook()
{
    if(ismanagerkey())
    {
        string delbk;
        cout << "Input the book's name:";
        getline(cin, delbk);
        book* bk(0);
        if(!searchbook(delbk,bk))
            cout << "can't find the book" << endl;
        else
        {
            if(bk->state == "borrowed")
                cout << "the book is not returned yet!" << endl;
            else
            {
                Author* au = NULL;
                if(searchAuthor(bk->getauthor(),au))
                {
                    au->delbook(bk);
                    if(au->getbknum() == 0)
                        Authortree.RB_DELETE(au->getauthor());
                }
                booktree.RB_DELETE(delbk);
                booknum--;
                cout << "Done!" << endl;
            }
        }
    }
}

//����
void manager::borrowbook()
{
    string bbk;
    cout << "Input the book's name:";
    getline(cin, bbk);
    book* bk(0);
    if(!searchbook(bbk,bk))
        cout << "can't find the book" << endl;
    else
    {
        string busr;
        cout << "Input your name:";
        getline(cin, busr);
        user* usr(0);
        if(!searchuser(busr,usr))
            cout << "can't find your name" << endl;
        else
        {
            if(!usr->isbookfull())
            {
                if(userkey(usr))
                {
                    usr->addbook(bk);
                    bk->setstate("borrowed");
                    cout << "Done!" << endl;
                }
            }
            else
                cout << "You have borrowed enough book" << endl;
        }
    }
}

//����
void manager::returnbook()
{
    string rbk;
    cout << "Input the book's name:";
    getline(cin, rbk);
    book* bk(0);
    if(!searchbook(rbk,bk))
        cout << "can't find the book" << endl;
    else
    {
        string rusr;
        cout << "Input your name:";
        getline(cin, rusr);
        user* usr(0);
        if(!searchuser(rusr,usr))
            cout << "can't find user name" << endl;
        else
        {
            usr->returnbook(bk);
            bk->setstate("clean");
            cout << "Done!" << endl;
        }
    }
}

//�õ�ͼ��ݵ���Ϣ
void manager::getlibraryinfo()
{
    cout << "The whole library has "<< endl;
    cout << booknum << " books and" << endl;
    cout << usernum << " users" << endl;
}


void manager::savechanges()
{
    if(bookfilename == "none")
    {
        cout << "It seems that you don't have a bookfile yet, please name your bookfile(file formate 'txt')" << endl;
        getline(cin, bookfilename);
    }
    savebook();
    if(userfilename == "none")
    {
        cout << "It seems that you don't have a userfile yet, Please name your userfile(file formate 'txt')" << endl;
        getline(cin, userfilename);
    }
    saveuser();
    cout << "Done!" << endl;
}

fstream outbkfile;//����ȫ�ֱ���
void manager::savebook()
{
    outbkfile.open(bookfilename.c_str(), ios::out);
    savebook(booktree.root, booktree.nill);
    outbkfile.close();
}

//����д��
void manager::savebook(node<string,book>* root, node<string,book>* nill)
{
    if(root != nill)
    {
        outbkfile << root->data.isbn  << " " << root->data.author << " " << root->data.state << " " << root->data.bkname << endl;
        savebook(root->leftchild,nill);
        savebook(root->rightchild,nill);
    }
}


fstream outurfile;//ȫ�ֱ���
void manager::saveuser()
{
    outurfile.open(userfilename.c_str(), ios::out);
    saveuser(usertree.root, usertree.nill);
    outurfile.close();
}

void manager::saveuser(node<string,user>* root, node<string,user>* nill)
{
    if(root != nill)
    {
        outurfile << root->data.name << " " << root->data.number << " " << root->data.email << " " << root->data.key << " " << root->data.booknum << endl;
        for(int i = 0; i < root->data.booknum; i++)
        {
            outurfile << root->data.mybook[i]->bkname << endl;
        }
        saveuser(root->leftchild,nill);
        saveuser(root->rightchild,nill);
    }
}
