#include"userwindow.h"
#include<QStackedWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QListWidget>
#include<QLabel>
#include<QInputDialog>
#include<QPushButton>
#include<QMessageBox>
#include<QTableView>
#include<QStandardItemModel>
#include"user.h"
#include"book.h"
#include"manager.h"
#include"userinfor.h"
#include"searchwindow.h"

userWindow::userWindow(QWidget *parent, manager *&mmanager, user *& usr) : QDialog(parent)
{
	rusr = usr;
	rmanager = mmanager;
	list = new QListWidget(this);
	list->insertItem(0,tr("My information"));
	list->insertItem(1,tr("Check my book"));
	list->insertItem(2,tr("Search&&borrow books"));
	list->insertItem(3,tr("Delete my account"));

	imglabel = new QLabel(this);
        QPixmap icon(":/imgs/2.png");
	imglabel->setPixmap(icon);
	namelabel = new QLabel("<h2>"+usr->getname()+"</h2>",this);
	leftlayout = new QVBoxLayout;
	lefttoplayout =new QHBoxLayout;
	lefttoplayout->addWidget(imglabel);
	lefttoplayout->addWidget(namelabel);
	leftlayout->addLayout(lefttoplayout);
	leftlayout->addWidget(list);

	imfor = new userinfor(this,rmanager,rusr);
	searchwin = new SearchWindow(this,rmanager,rusr,true,false);

	createdelwindow();
	createbookwindow();
	stack = new QStackedWidget(this);
	stack->addWidget(imfor);
	stack->addWidget(bookview);
	stack->addWidget(searchwin);
	stack->addWidget(deleteAccount);
	mainlayout = new QHBoxLayout(this);
	mainlayout->addLayout(leftlayout);
	mainlayout->addStretch();
	mainlayout->addWidget(stack);
	connect(list,SIGNAL(currentRowChanged(int)),this,SLOT(setCurrent(int)));
}

void userWindow::createdelwindow()
{
	deleteAccount = new QDialog;
	QLabel *remind = new QLabel(tr("<h2>Are  you sure </h1>\n<h2>you want to delete your account?</h1>"),deleteAccount);
	QPushButton *oktodelet = new QPushButton(tr("Delete"),deleteAccount);
	QPushButton *canceldel = new QPushButton(tr("Cancel"),deleteAccount);
	QGridLayout *dellayout = new QGridLayout;
	dellayout->addWidget(remind,0,0);
	dellayout->addWidget(oktodelet,1,0);
	dellayout->addWidget(canceldel,1,2);
	deleteAccount->setLayout(dellayout);
	connect(oktodelet,SIGNAL(clicked()),this,SLOT(delusr()));
	connect(canceldel,SIGNAL(clicked()),this,SLOT(remain()));
}

void userWindow::delusr()
{
	if(rusr->getbooknumb())
	{
		QMessageBox::warning(this,tr("Error"),tr("You have books not returned yet\n can't delete your account"),QMessageBox::Ok);
		stack->setCurrentWidget(imfor);
	}
	else
	{
		bool ok;
		QString usrkey = QInputDialog::getText(this,tr("Input your password"),tr("Password:"),QLineEdit::Password,"",&ok);
		if(ok && !usrkey.isEmpty())
		{
			if(!rmanager->userkey(rusr,usrkey))
					QMessageBox::warning(this,tr("Error"),tr("Your password is not correct!"),QMessageBox::Ok);
			else
			{
				rmanager->deluser(rusr);
				QMessageBox::information(this,tr("Done"),tr("You have delete your account"),QMessageBox::Ok);
				emit isexit();
				close();
			}
		}
	}
}

void userWindow::createbookwindow()
{
	bookview = new QDialog;
	QLabel *texttable = new QLabel("Here is the book you are borrowing now:");
	returnbutton = new QPushButton("return");
	returnbutton->hide();
	returnbutton->setEnabled(false);
	model = new QStandardItemModel();
	model->setColumnCount(4);

	model->setHeaderData(0, Qt::Horizontal, tr("BoookName"));
	model->setHeaderData(1, Qt::Horizontal, tr("ISBN"));
	model->setHeaderData(2, Qt::Horizontal, tr("Author"));
	model->setHeaderData(3, Qt::Horizontal, tr("State"));
	int i(0);
	while(rusr->getbooklist()[i])//遍历输出所借的书的信息
	{
		QStandardItem* item0 = new QStandardItem(rusr->getbooklist()[i]->getbkname());  
		QStandardItem* item1 = new QStandardItem(rusr->getbooklist()[i]->getisbn());  
		QStandardItem* item2 = new QStandardItem(rusr->getbooklist()[i]->getauthor());  
		QStandardItem* item3 = new QStandardItem(rusr->getbooklist()[i]->getstate());  
		QList<QStandardItem*> items;  
		items << item0 << item1 << item2 << item3;  
		model->appendRow(items);  
		i++;
	}

	booktable = new QTableView;	
	booktable->setModel(model);
	booktable->setEditTriggers(QTableView::NoEditTriggers);
	booktable->setSelectionBehavior(QAbstractItemView::SelectRows);
	booktable->setSelectionMode(QAbstractItemView::SingleSelection);
	QGridLayout *mainlayout = new QGridLayout;
	mainlayout->addWidget(texttable,0,0);
	mainlayout->addWidget(returnbutton,0,2);
	mainlayout->addWidget(booktable);
	bookview->setLayout(mainlayout);
	connect(booktable,SIGNAL(clicked(QModelIndex)),this,SLOT(rowselected()));
	connect(returnbutton,SIGNAL(clicked()),this,SLOT(returnbook()));
}

void userWindow::setCurrent(int index)
{
	stack->setCurrentIndex(index);
	if(index == 1)
		updatemybook();
	else if(index == 2)
		searchwin->refresh();
}
void userWindow::remain()//回到用户信息
{
	stack->setCurrentWidget(imfor);
}


void userWindow::updatemybook()//更新
{
	model->clear();
	model->setColumnCount(4);
	model->setHeaderData(0, Qt::Horizontal, tr("BoookName"));
	model->setHeaderData(1, Qt::Horizontal, tr("ISBN"));
	model->setHeaderData(2, Qt::Horizontal, tr("Author"));
	model->setHeaderData(3, Qt::Horizontal, tr("State"));
	int i(0);
	while(rusr->getbooklist()[i])//遍历输出所借的书的信息
	{
		QStandardItem* item0 = new QStandardItem(rusr->getbooklist()[i]->getbkname());  
		QStandardItem* item1 = new QStandardItem(rusr->getbooklist()[i]->getisbn());  
		QStandardItem* item2 = new QStandardItem(rusr->getbooklist()[i]->getauthor());  
		QStandardItem* item3 = new QStandardItem(rusr->getbooklist()[i]->getstate());  
		QList<QStandardItem*> items;  
		items << item0 << item1 << item2 << item3;  
		model->appendRow(items);  
		i++;
	}
	returnbutton->hide();
}

void userWindow::rowselected()
{
	returnbutton->show();
	returnbutton->setEnabled(true);
}

void userWindow::returnbook()
{
	QModelIndex index = model->index(booktable->currentIndex().row(),0);
	const QString bkname = model->data(index).toString();
	rmanager->returnbook(rusr,bkname);
	QMessageBox::information(this,tr("Success"),tr("Done!"),QMessageBox::Ok);
	updatemybook();
}
