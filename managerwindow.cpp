#include<QStackedWidget>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QGridLayout>
#include<QListWidget>
#include<QLabel>
#include<QGroupBox>
#include<QLineEdit>
#include<QPushButton>
#include<QMessageBox>
#include<QTableView>
#include<QStandardItemModel>
#include"managerwindow.h"
#include"user.h"
#include"manager.h"
#include"searchwindow.h"

ManagerWindow::ManagerWindow(QWidget *parent, manager *&mmanager)
	: QDialog(parent)
{
	rmanager = mmanager;
	list = new QListWidget(this);
	list->insertItem(0,tr("Add"));
	list->insertItem(1,tr("Search&&Delete"));
	list->insertItem(2,tr("check library"));

	imglabel = new QLabel(this);
        QPixmap icon(":/imgs/2.png");
	imglabel->setPixmap(icon);
	namelabel = new QLabel("Manager",this);
	leftlayout = new QVBoxLayout;
	lefttoplayout =new QHBoxLayout;
	lefttoplayout->addWidget(imglabel);
	lefttoplayout->addWidget(namelabel);
	leftlayout->addLayout(lefttoplayout);
	leftlayout->addWidget(list);

	user* tmpusr = NULL;
	searchwin = new SearchWindow(this,rmanager,tmpusr,false,true);
	createaddwindow();
	createinforwindow();


	stack = new QStackedWidget(this);
	stack->addWidget(addgroup);
	stack->addWidget(searchwin);
	stack->addWidget(inforgroup);
	mainlayout = new QHBoxLayout(this);
	mainlayout->addLayout(leftlayout);
	mainlayout->addStretch();
	mainlayout->addWidget(stack);
	connect(list,SIGNAL(currentRowChanged(int)),this,SLOT(setCurrent(int)));
}

void ManagerWindow::createaddwindow()
{
	bknamelabel = new QLabel(tr("Book &Name:"));
	isbnlabel = new QLabel(tr("&ISBN:"));
	authorlabel = new QLabel(tr("&Author:"));
	bknameedit = new QLineEdit;
	isbnedit = new QLineEdit;
	authoredit = new QLineEdit;
	bknamelabel->setBuddy(bknameedit);
	isbnlabel->setBuddy(isbnedit);
	authorlabel->setBuddy(authoredit);
	addbutton = new QPushButton(tr("Add"));
	addbutton->setEnabled(false);
	canceladdbutton = new QPushButton(tr("Cancel"));
	connect(addbutton,SIGNAL(clicked()),this,SLOT(addbook()));
	connect(canceladdbutton,SIGNAL(clicked()),this,SLOT(remain()));
	connect(bknameedit,SIGNAL(textChanged(const QString &)),this,SLOT(on_lineEdit_textChanged()));

	addlayout = new QGridLayout;
	addlayout->addWidget(bknamelabel,0,0);
	addlayout->addWidget(bknameedit,0,1);
	addlayout->addWidget(isbnlabel,1,0);
	addlayout->addWidget(isbnedit,1,1);
	addlayout->addWidget(authorlabel,2,0);
	addlayout->addWidget(authoredit,2,1);
	addlayout->addWidget(addbutton,3,1);
	addlayout->addWidget(canceladdbutton,3,2);

	addgroup = new QGroupBox;
	addgroup->setLayout(addlayout);
}

void ManagerWindow::setCurrent(int index)
{
	if(index == 0)
		cleanaddwindow();
	if(index == 1)
		searchwin->refresh();
	if(index == 2)
		updateinfor();
	stack->setCurrentIndex(index);
}

void ManagerWindow::addbook()
{
	QString bkname = bknameedit->text();
	if(rmanager->searchbook(bkname))
		QMessageBox::warning(this,tr("Error"),tr("There is already such a book"),QMessageBox::Ok);
	else
	{
		rmanager->addbook(bkname,isbnedit->text(),authoredit->text());
		QMessageBox::information(this,tr("Success"),tr("Done"),QMessageBox::Ok);
	}
}

void ManagerWindow::remain()
{
	cleanaddwindow();
	stack->setCurrentIndex(0);
}

void ManagerWindow::fresh()
{
	remain();
}

void ManagerWindow::cleanaddwindow()
{
	bknameedit->clear();
	isbnedit->clear();
	authoredit->clear();
}
void ManagerWindow::on_lineEdit_textChanged()
{
	addbutton->setEnabled(!bknameedit->text().isEmpty());
}

void ManagerWindow::createinforwindow()
{
	inforgroup = new QGroupBox;
	userinforlabel = new QLabel;
	bookinforlabel = new QLabel;
	updateinfor();
	userdetailbutton = new QPushButton("Details");
	bookdetailbutton = new QPushButton("Details");
	inforlayout = new QGridLayout;
	inforlayout->addWidget(userinforlabel,0,1);
	inforlayout->addWidget(bookinforlabel,1,1);
	inforlayout->addWidget(userdetailbutton,0,2);
	inforlayout->addWidget(bookdetailbutton,1,2);
	inforgroup->setLayout(inforlayout);
	connect(userdetailbutton,SIGNAL(clicked()),this,SLOT(showalluser()));
	connect(bookdetailbutton,SIGNAL(clicked()),this,SLOT(showallbook()));
}

void ManagerWindow::updateinfor()
{
	QVariant usernumber(rmanager->getusernumber());
	QVariant booknumber(rmanager->getbooknumber());
	userinforlabel->setText("There are "+ usernumber.toString() + " Users in the library");
	bookinforlabel->setText("There are " + booknumber.toString()  + " Books in the library");
}

void ManagerWindow::showalluser()
{
	alluserwidget = new QWidget;
	alluserwidget->setWindowTitle("Show all users");
	QVBoxLayout *alluserlayout = new QVBoxLayout(alluserwidget);
	QPushButton *closebutton = new QPushButton("Close");
	allusertableview = new QTableView;
	allusermodel = new QStandardItemModel;
	allusermodel->setColumnCount(3);
	allusermodel->setHeaderData(0, Qt::Horizontal, tr("UserName"));
	allusermodel->setHeaderData(1, Qt::Horizontal, tr("StudentNumver"));
	allusermodel->setHeaderData(2, Qt::Horizontal, tr("BookNumber"));
	rmanager->getalluser(allusermodel);
	allusertableview->setModel(allusermodel);
	allusertableview->setSelectionBehavior(QAbstractItemView::SelectRows);
	allusertableview->setSelectionMode(QAbstractItemView::SingleSelection);
	alluserlayout->addWidget(closebutton);
	alluserlayout->addWidget(allusertableview);
	alluserwidget->show();
	connect(closebutton,SIGNAL(clicked()),this,SLOT(closealluser()));
}

void ManagerWindow::closealluser()
{
	alluserwidget->close();
	delete alluserwidget;
	alluserwidget = NULL;
}

void ManagerWindow::showallbook()
{
	allbookwidget = new QWidget;
	allbookwidget->setWindowTitle("Show all books");
	QVBoxLayout *allbooklayout = new QVBoxLayout(allbookwidget);
	QPushButton *closebutton = new QPushButton("Close");
	allbooktableview = new QTableView;
	allbookmodel = new QStandardItemModel;
	allbookmodel->setColumnCount(4);
	allbookmodel->setHeaderData(0, Qt::Horizontal, tr("BoookName"));
	allbookmodel->setHeaderData(1, Qt::Horizontal, tr("ISBN"));
	allbookmodel->setHeaderData(2, Qt::Horizontal, tr("Author"));
	allbookmodel->setHeaderData(3, Qt::Horizontal, tr("State"));
	rmanager->getallbook(allbookmodel);
	allbooktableview->setModel(allbookmodel);
	allbooktableview->setSelectionBehavior(QAbstractItemView::SelectRows);
	allbooktableview->setSelectionMode(QAbstractItemView::SingleSelection);
	allbooklayout->addWidget(closebutton);
	allbooklayout->addWidget(allbooktableview);
	allbookwidget->show();
	connect(closebutton,SIGNAL(clicked()),this,SLOT(closeallbook()));
}

void ManagerWindow::closeallbook()
{
	allbookwidget->close();
	delete allbookwidget;
	allbookwidget = NULL;
}
