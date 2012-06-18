#include"searchwindow.h"
#include"manager.h"
#include"user.h"
#include"Author.h"
#include"book.h"
#include<QGridLayout>
#include<QLabel>
#include<QSplitter>
#include<QLineEdit>
#include<QPushButton>
#include<QTableView>
#include<QGroupBox>
#include<QHBoxLayout>
#include<QStandardItemModel>
#include<QMessageBox>

SearchWindow::SearchWindow(QWidget *parent, manager*& mmanager, user*& usr, bool isuser, bool ismanager) : QSplitter(parent)
{
	rmanager = mmanager;
	rusr = usr;
	this->isuser = isuser;
	this->ismanager = ismanager;
	createsearchwidget();
	createresultable();
	setOrientation(Qt::Vertical);
	addWidget(topwidget);
	buttomspliter = new QSplitter;
	buttomspliter->addWidget(bookTableView);
	borrowbutton = new QPushButton("Borrow book");
	borrowbutton->setStatusTip("You can borrow the book when you are login as user");
	delbutton = new QPushButton("Delete the book");
	delbutton->setStatusTip("Only manager have rights to delete books");
	updatebutton = new QPushButton("Update");
	updatebutton->setStatusTip(tr("Update some information of the book"));
	borrowbutton->setEnabled(false);
	delbutton->setEnabled(false);
	updatebutton->setEnabled(false);
	buttomrightgroup = new QGroupBox;
	buttomrightlayout = new QVBoxLayout;
	buttomrightlayout->addWidget(borrowbutton);
	buttomrightlayout->addWidget(updatebutton);
	buttomrightlayout->addWidget(delbutton);
	buttomrightgroup->setLayout(buttomrightlayout);
	buttomspliter->addWidget(buttomrightgroup);
	buttomrightgroup->hide();
	buttomspliter->setStretchFactor(0,85);
	addWidget(buttomspliter);
	connect(bybknameButton,SIGNAL(clicked()),this,SLOT(searchbybkname()));
	connect(bykeyButton,SIGNAL(clicked()),this,SLOT(searchbykey()));
	connect(byauthorButton,SIGNAL(clicked()),this,SLOT(searchbyauthor()));
	connect(borrowbutton,SIGNAL(clicked()),this,SLOT(borrowbook()));
	connect(delbutton,SIGNAL(clicked()),this,SLOT(deletebook()));
	connect(updatebutton,SIGNAL(clicked()),this,SLOT(updatebook()));
	connect(bookTableView,SIGNAL(clicked(QModelIndex)),this,SLOT(rowselected()));
}

//建立查询的界面
void SearchWindow::createsearchwidget()
{
	QLabel *imglabel = new QLabel;
        QPixmap icon(":/imgs/2.png");
	imglabel->setPixmap(icon);

	bybknameLabel = new QLabel(tr("Name:"));
	bybknameEdit = new QLineEdit;
	bybknameEdit->setStatusTip(tr("search the book by it's whole name"));
	bybknameLabel->setBuddy(bybknameEdit);
	bybknameButton = new QPushButton(tr("Search"));
	bybknameButton->setEnabled(false);
	bykeyLabel = new QLabel(tr("KeyWords:")); bykeyEdit = new QLineEdit;
	bykeyEdit->setStatusTip(tr("search the book by it's keywords"));
	bykeyLabel->setBuddy(bykeyEdit);
	bykeyButton = new QPushButton(tr("Search"));
	bykeyButton->setEnabled(false);
	byauthorLabel = new QLabel(tr("Author:"));
	byauthorEdit = new QLineEdit;
	byauthorEdit->setStatusTip(tr("search the book by author's full name"));
	byauthorLabel->setBuddy(byauthorEdit);
	byauthorButton = new QPushButton(tr("Search"));
	byauthorButton->setEnabled(false);
	connect(bybknameEdit,SIGNAL(textChanged(const QString &)),this,SLOT(on_lineEdit_textChanged()));
	connect(bykeyEdit,SIGNAL(textChanged(const QString &)),this,SLOT(on_lineEdit_textChanged()));
	connect(byauthorEdit,SIGNAL(textChanged(const QString &)),this,SLOT(on_lineEdit_textChanged()));

	mainlayout = new QGridLayout;
	mainlayout->addWidget(imglabel,1,0);
	mainlayout->addWidget(bybknameLabel,0,1);
	mainlayout->addWidget(bybknameEdit,0,2);
	mainlayout->addWidget(bybknameButton,0,3);
	mainlayout->addWidget(bykeyLabel,1,1);
	mainlayout->addWidget(bykeyEdit,1,2);
	mainlayout->addWidget(bykeyButton,1,3);
	mainlayout->addWidget(byauthorLabel,2,1);
	mainlayout->addWidget(byauthorEdit,2,2);
	mainlayout->addWidget(byauthorButton,2,3);

	topwidget = new QGroupBox;
	topwidget->setTitle("Search");
	topwidget->setFlat(true);
	topwidget->setLayout(mainlayout);
}

//创建查询结果的表格
void SearchWindow::createresultable()
{
	bookTableView = new QTableView;
	bookTableView->setEditTriggers(QTableView::NoEditTriggers);
	model = new QStandardItemModel();
	model->setColumnCount(4);

	model->setHeaderData(0, Qt::Horizontal, tr("BoookName"));
	model->setHeaderData(1, Qt::Horizontal, tr("ISBN"));
	model->setHeaderData(2, Qt::Horizontal, tr("Author"));
	model->setHeaderData(3, Qt::Horizontal, tr("State"));

	bookTableView->setModel(model);
	bookTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	bookTableView->setSelectionMode(QAbstractItemView::SingleSelection);
}

//Edit有输入时，按钮有效
void SearchWindow::on_lineEdit_textChanged()
{
	bybknameButton->setEnabled(!bybknameEdit->text().isEmpty());
	bykeyButton->setEnabled(!bykeyEdit->text().isEmpty());
	byauthorButton->setEnabled(!byauthorEdit->text().isEmpty());
}


void SearchWindow::searchbybkname()
{
	QString bkname = bybknameEdit->text();
	book* bk = NULL;
	if(!rmanager->searchbook(bkname,bk))
		QMessageBox::information(this,tr("NOT FOUND"),tr("There's no such book\nmaybe you can try search by key"),QMessageBox::Ok);
	else
	{
		buttomrightgroup->show();
		refreshtable();
	QStandardItem* item0 = new QStandardItem(bk->getbkname());  
	QStandardItem* item1 = new QStandardItem(bk->getisbn());  
	QStandardItem* item2 = new QStandardItem(bk->getauthor());  
	QStandardItem* item3 = new QStandardItem(bk->getstate());  
	QList<QStandardItem*> items;  
	items << item0 << item1 << item2 << item3;  
	model->appendRow(items);  
	}
}

void SearchWindow::searchbykey()
{
	QString inputkey = bykeyEdit->text();
	list<book*> bklist;
	rmanager->searchbykey(inputkey,bklist);
	if(bklist.empty())
		QMessageBox::information(this,tr("NOT FOUND"),tr("There's no book'name include such key"),QMessageBox::Ok);
	else
	{
		buttomrightgroup->show();
		show(bklist);
	}
}

void SearchWindow::searchbyauthor()
{
	QString authname = byauthorEdit->text();
	Author *author = NULL;
	if(!rmanager->searchAuthor(authname,author))
		QMessageBox::information(this,tr("NOT FOUND"),tr("There's no such author"),QMessageBox::Ok);
	else
	{
		buttomrightgroup->show();
		list<book*> bklist = rmanager->getauthorbklist(author);
		show(bklist);
	}
}


void SearchWindow::show(list<book*> &bklist)
{
	refreshtable();
    	for(list<book*>::iterator iter = bklist.begin(); iter != bklist.end(); ++ iter)
	{
		QStandardItem* item0 = new QStandardItem((*iter)->getbkname());  
		QStandardItem* item1 = new QStandardItem((*iter)->getisbn());  
		QStandardItem* item2 = new QStandardItem((*iter)->getauthor());  
		QStandardItem* item3 = new QStandardItem((*iter)->getstate());  
		QList<QStandardItem*> items;  
		items << item0 << item1 << item2 << item3;  
		model->appendRow(items);  
	}
}

void SearchWindow::rowselected()
{
	if(ismanager)
	{
		delbutton->setEnabled(true);
		updatebutton->setEnabled(true);
	}
	else if(isuser)
		borrowbutton->setEnabled(true);
}

void SearchWindow::borrowbook()
{
	if(rusr != NULL)
	{
		QModelIndex index = model->index(bookTableView->currentIndex().row(),0);
		QString bkname = model->data(index).toString();
		int r = rmanager->borrowbook(rusr,bkname);
		if(r == 0)
		{
			QMessageBox::information(this,tr("success"),tr("Done!"),QMessageBox::Ok);
			model->setData(index,"borrowed");
			refreshtable();
		}
		else if(r == 1)
			QMessageBox::warning(this,tr("Error"),tr("the book is borrowed"),QMessageBox::Ok);
		else if(r == 2)
			QMessageBox::warning(this,tr("Error"),tr("You have borrowed enough books\n,you can't borrow any more books"),QMessageBox::Ok);
	}
}

void SearchWindow::deletebook()
{
	QModelIndex index = model->index(bookTableView->currentIndex().row(),0);
	QString bkname = model->data(index).toString();
	if(!rmanager->delbook(bkname))
		QMessageBox::warning(this,tr("Error"),tr("This book is not returned yet"),QMessageBox::Ok);
	else
	{
		model->removeRow(index.row());
		QMessageBox::information(this,tr("success"),tr("Done!"),QMessageBox::Ok);
	}
}

book* addbk;
void SearchWindow::updatebook()
{
	QModelIndex index = model->index(bookTableView->currentIndex().row(),0);
	QString bkname = model->data(index).toString();
	rmanager->searchbook(bkname,addbk);
	if(addbk->getstate() == "borrowed")
		QMessageBox::warning(this,tr("Error"),tr("This book is not returned yet"),QMessageBox::Ok);
	else
	{
		updatebkwin = new QGroupBox; 
		bknamelable = new QLabel ("Book name:");
		bknameedit = new QLineEdit(addbk->getbkname());
		bknameedit->setReadOnly(true);
		isbnlabel = new QLabel("&ISBN");
	        isbnedit = new QLineEdit(addbk->getisbn());	
		isbnlabel->setBuddy(isbnedit);
		authorlabel = new QLabel("&Author");
		authoredit = new QLineEdit(addbk->getauthor());
		authorlabel->setBuddy(authoredit);
		okupdatebutton = new QPushButton("Update");
		cancelbutton = new QPushButton("Cancel");
		updatelayout = new QGridLayout;
		updatelayout->addWidget(bknamelable,0,0);
		updatelayout->addWidget(bknameedit,0,1);
		updatelayout->addWidget(isbnlabel,1,0);
		updatelayout->addWidget(isbnedit,1,1);
		updatelayout->addWidget(authorlabel,2,0);
		updatelayout->addWidget(authoredit,2,1);
		updatelayout->addWidget(okupdatebutton,3,1);
		updatelayout->addWidget(cancelbutton,3,2);
		updatebkwin->setLayout(updatelayout);
		updatebkwin->show();
		connect(okupdatebutton,SIGNAL(clicked()),this,SLOT(updatebkprocess()));
		connect(cancelbutton,SIGNAL(clicked()),updatebkwin,SLOT(close()));
	}
}


void SearchWindow::updatebkprocess()
{
	updatebkwin->close();
	addbk->setauthor(authoredit->text());
	addbk->setisbn(isbnedit->text());
	QMessageBox::information(this,tr("success"),tr("Done!"),QMessageBox::Ok);
	QStandardItem* item0 = new QStandardItem(addbk->getbkname());  
	QStandardItem* item1 = new QStandardItem(addbk->getisbn());  
	QStandardItem* item2 = new QStandardItem(addbk->getauthor());  
	QStandardItem* item3 = new QStandardItem(addbk->getstate());  
	QList<QStandardItem*> items;  
	items << item0 << item1 << item2 << item3;  
	int row = bookTableView->currentIndex().row();
	model->insertRow(row,items);
	model->removeRow(row+1);
	delete updatebkwin;
	updatebkwin = NULL;
}

void SearchWindow::refreshtable()
{
	model->clear();
	model->setColumnCount(4);

	model->setHeaderData(0, Qt::Horizontal, tr("BoookName"));
	model->setHeaderData(1, Qt::Horizontal, tr("ISBN"));
	model->setHeaderData(2, Qt::Horizontal, tr("Author"));
	model->setHeaderData(3, Qt::Horizontal, tr("State"));
}

void SearchWindow::refresh()
{
	bykeyEdit->clear();
	byauthorEdit->clear();
	bybknameEdit->clear();
	refreshtable();
}
