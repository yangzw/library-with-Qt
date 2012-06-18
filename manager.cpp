#include<QString>
#include<QFile>
#include<QTextStream>
#include<QStringList>
#include<QStandardItemModel>
#include<QVariant>
#include "manager.h"
#include "Author.h"
#include "user.h"
#include "book.h"

manager::manager()
{
    usernum = 0;
    booknum = 0;
    managerkey = "manager";
    bookfilename = "book.txt";
    userfilename = "user.txt";
};

//选择载入文件
void manager::setdafaultfile(const QString& bkfilem, const QString& usrfilem)
{
	bookfilename = bkfilem;
	userfilename = usrfilem;
	booktree.clear();
	usertree.clear();
	Authortree.clear();
	loadfileprocess();
}
//
//
////void manager::loadfile()
////{
// //   cout << "Input the bookfile's name: " << endl;
//  //  getline(cin, bookfilename);
//   // cout << "Input the userfile's name: " << endl;
//    //getline(cin, userfilename);
//    //load();
////}
//
////void manager::load()
////{
////    if(loadfileprocess())
////        cout << "Data load sucessfully!" << endl;
////    else
////        cout << "Faile to load file" << endl;
////}
//
void manager::loadfileprocess()
{
	QFile bkfile(bookfilename);
	bkfile.open(QFile::ReadOnly);
    QTextStream inbkfile(&bkfile);
    //inbkfile.open(bookfilename.c_str(), ios::in);
    //int flag(0);//标志，至少有一个文件读入成功就设为1;
    //if(!inbkfile)
    //{
     //   cout << "error:unable to open bookfile!" << endl;
    //}
    //else
    //{
        QString line;
     //   flag = 1;
        while(!inbkfile.atEnd())
        {
		line = inbkfile.readLine();
		QStringList fields = line.split("_");
            QString isbn;
            QString author;
            QString state;
            QString bkname;
		if(fields.size() >= 4)
		{
            isbn = fields.takeFirst();
            author = fields.takeFirst();
            state = fields.takeFirst();
            bkname = fields.takeFirst();
		}
            book newbk(bkname,isbn,author,state);
            node<QString,book>* tmp = booktree.RB_insert(newbk,newbk.bkname);
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
    //}
    //inbkfile.close();
    //fstream inurfile;
    //inurfile.open(userfilename.c_str(), ios::in);
    //if(!inurfile)
    //{
     //   cout << "erro:ubable to open userfile!" << endl;
    //}
    //else
    //{
    	bkfile.close();
	QFile usrfile(userfilename);
	usrfile.open(QFile::ReadOnly);
    QTextStream inusrfile(&usrfile);
        QString usrline;
    //    flag = 1;
        while(!inusrfile.atEnd())
        {
        usrline = inusrfile.readLine();
		QStringList usrfields = usrline.split("_");
            QString name;
            QString number;
            QString email;
            QString key;
            int bknum(0);
		if(usrfields.size() >= 4)
		{
            name= usrfields.takeFirst();
            number= usrfields.takeFirst();
            email= usrfields.takeFirst();
            key= usrfields.takeFirst();
            bknum= usrfields.takeFirst().toInt();
		}
            user* usr = new user(name,number,email,key);
            QString tmpbk;
            for(int i = 0; i < bknum; i++)
            {
		    tmpbk = inusrfile.readLine();
                book* bk(0);
                booktree.search(tmpbk,bk);
                usr->addbook(bk);
            }
            usertree.RB_insert(*usr,usr->name);
            usernum++;
        }
	usrfile.close();
    //}
}

bool manager::searchbook(const QString& bookname,book*& srbook) const
{
    return booktree.search(bookname,srbook);
}

bool manager::searchbook(const QString& bookname) const
{
    return booktree.search(bookname);
}

bool manager::searchAuthor(const QString& athname, Author*& srAuthor) const
{
    return Authortree.search(athname,srAuthor);
}

bool manager::searchAuthor(const QString& athname) const
{
	return	Authortree.search(athname);
}

list<book*> manager::getauthorbklist(Author *&auth)
{
	return auth->bklist;
}
//
//
////void manager::searchbook()
////{
////    cout << "Input the book' name： ";
////    QString bookname;
////    getline(cin, bookname);
////    book* srbook = NULL;
////    if(searchbook(bookname,srbook))
////        srbook->getinfor();
////    else
////        cout << "Can't find such book!" << endl;
////}
//
void manager::searchbykey(const QString& key,list<book*>& bklist)
{
    node<QString,book>* nill = booktree.nill;
    node<QString,book>* root = booktree.root;
    searchkey(root,nill,key,bklist);
}

void manager::searchkey(node<QString,book>* root, node<QString,book>* nill,const QString& key,list<book*> &bklist)
{
    if(root != nill)
    {
        QString bk = root->data.getbkname();
	if(bk.contains(key))
		bklist.push_back(&(root->data));
        searchkey(root->leftchild,nill,key,bklist);
        searchkey(root->rightchild,nill,key,bklist);
    }
}
//
////void manager::searchAuthor()
////{
////    cout << "Input the author: ";
////    QString athname;
////    getline(cin, athname);
////    Author* srAuthor = NULL;
////    if(searchAuthor(athname,srAuthor))
////    {
////        cout << "The books of " << athname << " are as follows:" << endl;
////        srAuthor->show();
////    }
////    else
////        cout << "Can't find such author!" << endl;
////}
//
bool manager::searchuser(const QString& usrname, user*& sruser) const
{
   return usertree.search(usrname, sruser);
}

bool manager::searchuser(const QString& usrname) const
{
    return usertree.search(usrname);
}

////void manager::getuserinfo()
////{
////    cout << "Please input your name: " << endl;
////    QString usrname;
////    getline(cin, usrname);
////    user* sruser = NULL;
////    if(searchuser(usrname, sruser))
////    {
////        if(userkey(sruser))
////        {
////            cout << "Here is your information" << endl;
////            sruser->showinfo();
////        }
////    }
////    else
////        cout << "The name is not registed yet!" << endl;
////}
////
////void manager::addusr()
////{
////    user usr;
////    cout << "Input your name: ";
////    QString tmp;
////    getline(cin,tmp);
////    while(searchuser(tmp))
////    {
////        cout << "Sorry, the name is already token" << endl;
////        cout << "Input again? input y or n " << endl;
////        char choice;
////        cin >> choice;
////        getchar();
////        if(choice == 'y')
////        {
////            cout << "Input your name: ";
////            getline(cin, tmp);
////        }
////        else
////            return;
////    }
////    usr.setname(tmp);
////    cout << "Input your student number: ";
////    getline(cin, tmp);
////    usr.setnumber(tmp);
////    cout << "Input your email: ";
////    getline(cin, tmp);
////    usr.setemail(tmp);
////    cout <<"Input your key: ";
////    getline(cin,usr.key);
////    cout << "Congratulations! you finish the register!" << endl;
////    usernum++;
////    usertree.RB_insert(usr,usr.name);
////}
//
void manager::addusr(const QString& uname,const QString& unumber,const QString& uemail,const QString& ukey)
{
	user usr;
	usr.setname(uname);
	usr.setnumber(unumber);
	usr.setemail(uemail);
	usr.key = ukey;
	usertree.RB_insert(usr,usr.name);
}

void manager::updateusr(user *& usr, const QString& unumber, const QString& uemail, const QString& ukey)
{
	usr->setemail(uemail);
	usr->setnumber(unumber);
	usr->key = ukey;
}

void manager::updateusr(user*& usr, const QString& unumber, const QString& uemail)
{
	usr->setemail(uemail);
	usr->setnumber(unumber);
}

//用户的密码验证
bool manager::userkey(user*& ur,const QString& inkey) const
{
	if(inkey != ur->key)
            return false;
    	return true;
}

//用户的注销
void manager::deluser(user *&delusr)
{
                usertree.RB_DELETE(delusr->getname());
                usernum--;
}
//
//验证管理员密码
bool manager::ismanagerkey(const QString &inputkey) const
{
   	if(inputkey != managerkey)
            return false;
    	return true;
}
//
//管理员增加图书
void manager::addbook(const QString& bkname, const QString& isbn, const QString& author)
{
        book bk(bkname,isbn,author);
        booknum++;
        node<QString,book>* nod = booktree.RB_insert(bk, bk.bkname);
        book* bkk = &nod->data;
        Author* ath = NULL;
        if(searchAuthor(bk.author,ath))
            ath->addbook(bkk);
        else
        {
            Author auth(bkk);
            Authortree.RB_insert(auth,bk.author);
        }
}
//
//管理员删除图书
bool manager::delbook(QString& bkname)
{
        book* bk(0);
        searchbook(bkname,bk);
        if(bk->state == "borrowed")
		return false;
         else
         {
              Author* au = NULL;
              if(searchAuthor(bk->getauthor(),au))
              {
                    au->delbook(bk);
                    if(au->getbknum() == 0)
                     Authortree.RB_DELETE(au->getauthor());
                }
                booktree.RB_DELETE(bkname);
                booknum--;
		return true;
            }
}
//
//借书
int manager::borrowbook(user *&usr, const QString& bkname)
{
    book* bk(0);
    searchbook(bkname,bk);
    if(bk->getstate() == "borrowed")
	    return 1;
    else
    {
	  if(usr->isbookfull())
		  return 2;
            else
            {
                    usr->addbook(bk);
                    bk->setstate("borrowed");
		    return 0;
            }
    }
}

//还书
void manager::returnbook(user *&usr, const QString& bkname)
{
    	    book* bk(0);
    	    searchbook(bkname,bk);
            usr->returnbook(bk);
            bk->setstate("clean");
}
//
////得到图书馆的信息
//void manager::getlibraryinfo()
//{
//    cout << "The whole library has "<< endl;
//    cout << booknum << " books and" << endl;
//    cout << usernum << " users" << endl;
//}
//
//
void manager::savechanges()
{
//    if(bookfilename == "none")
//    {
//        cout << "It seems that you don't have a bookfile yet, please name your bookfile(file formate 'txt')" << endl;
//        getline(cin, bookfilename);
//    }
    savebook();
//    if(userfilename == "none")
//    {
//        cout << "It seems that you don't have a userfile yet, Please name your userfile(file formate 'txt')" << endl;
//        getline(cin, userfilename);
//    }
    saveuser();
//    cout << "Done!" << endl;
}


void manager::savebook()
{
	QFile outbfile(bookfilename);
	outbfile.open(QFile::WriteOnly);
	QTextStream outbkfile(&outbfile);
    	savebook(booktree.root, booktree.nill,outbkfile);
    	outbfile.close();
}

//中序写入
void manager::savebook(node<QString,book>* root, node<QString,book>* nill, QTextStream& outbkfile)
{
    if(root != nill)
    {
        outbkfile << root->data.isbn  << "_" << root->data.author << "_" << root->data.state << "_" << root->data.bkname << endl;
        savebook(root->leftchild,nill,outbkfile);
        savebook(root->rightchild,nill,outbkfile);
    }
}


void manager::saveuser()
{
	QFile outusrfile(userfilename);
	outusrfile.open(QFile::WriteOnly);
	QTextStream outurfile(&outusrfile);
    	saveuser(usertree.root, usertree.nill,outurfile);
    	outusrfile.close();
}

void manager::saveuser(node<QString,user>* root, node<QString,user>* nill, QTextStream& outurfile)
{
    if(root != nill)
    {
        outurfile << root->data.name << "_" << root->data.number << "_" << root->data.email << "_" << root->data.key << "_" << root->data.booknum << endl;
        for(int i = 0; i < root->data.booknum; i++)
        {
            outurfile << root->data.mybook[i]->bkname << endl;
        }
        saveuser(root->leftchild,nill,outurfile);
        saveuser(root->rightchild,nill,outurfile);
    }
}

int manager::getusernumber()
{
	return usernum;
}

int manager::getbooknumber()
{
	return booknum;
}

void manager::getalluser(QStandardItemModel *&usermodel)
{
    	getalluser(usertree.root, usertree.nill,usermodel);
}

void manager::getalluser(node<QString,user>* root, node<QString,user>* nill, QStandardItemModel *&usermodel)
{
    if(root != nill)
    {
		QStandardItem* item0 = new QStandardItem(root->data.getname());  
		QStandardItem* item1 = new QStandardItem(root->data.getnumber());  
		QVariant usrbooknumber(root->data.getbooknumb());
		QStandardItem* item2 = new QStandardItem(usrbooknumber.toString());  
		QList<QStandardItem*> items;  
		items << item0 << item1 << item2;  
		usermodel->appendRow(items);  
        getalluser(root->leftchild,nill,usermodel);
        getalluser(root->rightchild,nill,usermodel);
    }
}

void manager::getallbook(QStandardItemModel *&bookmodel)
{
    	getallbook(booktree.root, booktree.nill,bookmodel);
}

void manager::getallbook(node<QString,book>* root, node<QString,book>* nill, QStandardItemModel *&bookmodel)
{
    if(root != nill)
    {
	QStandardItem* item0 = new QStandardItem(root->data.getbkname());  
	QStandardItem* item1 = new QStandardItem(root->data.getisbn());  
	QStandardItem* item2 = new QStandardItem(root->data.getauthor());  
	QStandardItem* item3 = new QStandardItem(root->data.getstate());  
	QList<QStandardItem*> items;  
	items << item0 << item1 << item2 << item3;  
	bookmodel->appendRow(items);
        getallbook(root->leftchild,nill,bookmodel);
        getallbook(root->rightchild,nill,bookmodel);
    }
}
