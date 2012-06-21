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
    bookfilename = "book.bk";
    userfilename = "user.usr";
};

//选择载入文件
void manager::setdafaultfile(const QString& bkfilem, const QString& usrfilem)
{
	bookfilename = bkfilem;
	userfilename = usrfilem;
	booktree.clear();
	booktree.root = booktree.nill;
	usertree.clear();
	usertree.root = usertree.nill;
	Authortree.clear();
	Authortree.root = Authortree.nill;
	loadfileprocess();
}

void manager::loadfileprocess()
{
	QFile bkfile(bookfilename);
	bkfile.open(QFile::ReadOnly);
    QTextStream inbkfile(&bkfile);
        QString line;
	managerkey = inbkfile.readLine();//读入管理员密码
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
    	bkfile.close();
	QFile usrfile(userfilename);
	usrfile.open(QFile::ReadOnly);
    QTextStream inusrfile(&usrfile);
        QString usrline;
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

bool manager::searchuser(const QString& usrname, user*& sruser) const
{
   return usertree.search(usrname, sruser);
}

bool manager::searchuser(const QString& usrname) const
{
    return usertree.search(usrname);
}


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

void manager::savechanges()
{
    savebook();
    saveuser();
}


void manager::savebook()
{
	QFile outbfile(bookfilename);
	outbfile.open(QFile::WriteOnly);
	QTextStream outbkfile(&outbfile);
	outbkfile << managerkey << endl;//读入管理员密码
    	savebook(booktree.root, booktree.nill,outbkfile);
    	outbfile.close();
}

//中序写入
void manager::savebook(node<QString,book>*& root, node<QString,book>*& nill, QTextStream& outbkfile)
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

void manager::saveuser(node<QString,user>*& root, node<QString,user>*& nill, QTextStream& outurfile)
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


void manager::saveas(const QString& bkfilename, const QString& usrfilename)
{
	QString tmp = bookfilename;
	bookfilename = bkfilename;
	savebook();
	bookfilename = tmp;
	tmp = userfilename;
	userfilename = usrfilename;
	saveuser();
	userfilename = tmp;
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

void manager::changemanagerpassword(const QString& password)
{
	managerkey = password;
}
