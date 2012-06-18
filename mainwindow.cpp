#include<QAction>
#include<QMenuBar>
#include<QStatusBar>
#include<QApplication>
#include<QMenu>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include<QStackedWidget>
#include<QMessageBox>
#include<QLabel>
#include<QDialog>
#include<QInputDialog>
#include<QFileDialog>
#include "mainwindow.h"
#include"userinfor.h"
#include"register.h"
#include"manager.h"
#include"user.h"
#include"userwindow.h"
#include"managerwindow.h"
#include"searchwindow.h"

//测试系统,来调用系统的sleep函数
#if defined Q_OS_WIN32  
#include <windows.h>  
void sleep(unsigned long nSeconde)  
{  
    Sleep((nSeconde)*1000);  
}  
#endif  
#if defined Q_OS_LINUX  
#include  <unistd.h>  
#endif   

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	isuser = false;
	ismanager = false;
	sleep(2);
   	mainmanager = new manager;
	mainmanager->loadfileprocess();
	createAction();
	createMenu();
	createCenter();
	createStatusBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createAction()
{
	openfileAction = new QAction(tr("&Open file"),this);
        openfileAction->setIcon(QIcon(":/imgs/open.png"));
	openfileAction->setShortcut(QKeySequence::Open);
	openfileAction->setStatusTip(tr("Open a new library database file"));
	connect(openfileAction,SIGNAL(triggered()),this,SLOT(open()));
	exitAction = new QAction(tr("E&xit"),this);
	exitAction->setShortcut(tr("Ctr+Q"));
	exitAction->setStatusTip(tr("Exit the applicatino"));
	connect(exitAction,SIGNAL(triggered()),this,SLOT(whenexit()));
	aboutLibraryAction = new QAction(tr("About &Library"),this);
	aboutLibraryAction->setStatusTip(tr("Show this application's about box"));
	connect(aboutLibraryAction,SIGNAL(triggered()),this,SLOT(about()));
	aboutQtAction = new QAction(tr("&About Qt"),this);
	aboutQtAction->setStatusTip(tr("Show the QT library's about box"));
	connect(aboutQtAction,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
}

void MainWindow::createMenu()
{
	fileMenu = menuBar()->addMenu(tr("&File")); 
	fileMenu->addAction(openfileAction);
	fileMenu->addAction(exitAction);

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutLibraryAction);
	helpMenu->addAction(aboutQtAction);
}

void MainWindow::createCenter()
{
	userLoginButton = new QPushButton("userLogin",this);
	userLoginButton->setStatusTip(tr("login if your are the user"));
	registerButton = new QPushButton("Register",this);
	registerButton->setStatusTip(tr("register a new user!"));
	searchButton = new QPushButton(tr("search book"),this);
	searchButton->setStatusTip(tr("search books"));
	managerButton = new QPushButton(tr("manager"),this);
	managerButton->setStatusTip(tr("login as a manager"));
	exitButton = new QPushButton(tr("Exit"),this);
	exitButton->setStatusTip(tr("exit the applications"));
	MainWindowButton = new QPushButton("mainwindow",this);
	MainWindowButton->setVisible(false);
	MainWindowButton->setStatusTip(tr("return the welcome window"));

	QWidget *welcome = new QWidget(this);
	QLabel *img = new QLabel(welcome);
        img->setStyleSheet("border-image:url(:/imgs/1.jpg)");
	img->setStatusTip(tr("Welcome to the library"));
	toplayout = new QHBoxLayout;
	toplayout->addWidget(registerButton);
	toplayout->addWidget(userLoginButton);
	toplayout->addWidget(searchButton);
	toplayout->addWidget(managerButton);
	toplayout->addWidget(exitButton);
	welcomelayout = new QVBoxLayout(welcome);
	welcomelayout->addWidget(img);
	welcomelayout->addLayout(toplayout);
	welcome->setLayout(welcomelayout);

    	rig = new Register(this,mainmanager);
	manawidget = new ManagerWindow(this,mainmanager);
	user* tmpusr = NULL;
	searchwin = new SearchWindow(this,mainmanager,tmpusr,false,false);

	swidget = new QStackedWidget;
	swidget->addWidget(welcome);
	swidget->addWidget(rig);
	swidget->addWidget(manawidget);
	swidget->addWidget(searchwin);
	connect(registerButton,SIGNAL(clicked()),SLOT(regis()));
	connect(userLoginButton,SIGNAL(clicked()),SLOT(ulogin()));
	connect(MainWindowButton,SIGNAL(clicked()),SLOT(rmain()));
	connect(managerButton,SIGNAL(clicked()),SLOT(managerlog()));
	connect(searchButton,SIGNAL(clicked()),SLOT(search()));
	connect(rig,SIGNAL(isexit()),this,SLOT(rmain()));
	QWidget *mainwidget = new QWidget(this);
	buttomlayout = new QHBoxLayout;
	vlayout = new QVBoxLayout;
	buttomlayout->addStretch();
	buttomlayout->addWidget(MainWindowButton);
	vlayout->addWidget(swidget);
	vlayout->addLayout(buttomlayout);
	mainwidget->setLayout(vlayout);
	connect(exitButton,SIGNAL(clicked()),this,SLOT(whenexit()));
	setCentralWidget(mainwidget);
}


void MainWindow::createStatusBar()
{
	statusBar()->show();
}

void MainWindow::regis()
{
	swidget->setCurrentIndex(1);
	rig->fresh();
	MainWindowButton->setVisible(true);
}

void MainWindow::ulogin()
{
	bool ok;
	QString usrname = QInputDialog::getText(this, tr("Input your name"),tr("Name:"), QLineEdit::Normal,"", &ok);
	user *usr;
	if (ok && !usrname.isEmpty())
	{
		isuser = true;
		bool i = mainmanager->searchuser(usrname,usr);
	if(!i)
		QMessageBox::warning(this,tr("Error"),tr("You are not register yet!"),QMessageBox::Ok);
	else	
	{
		bool ok1;
		QString usrkey = QInputDialog::getText(this,tr("Input your password"),tr("Password:"),QLineEdit::Password,"",&ok1);
		if(ok1 && !usrkey.isEmpty())
		{
			if(!mainmanager->userkey(usr,usrkey))
					QMessageBox::warning(this,tr("Error"),tr("Your password is not correct!"),QMessageBox::Ok);
			else{
		usrwidget = new userWindow(this,mainmanager,usr);
		swidget->addWidget(usrwidget);
		swidget->setCurrentWidget(usrwidget);
		MainWindowButton->setVisible(true);
		connect(usrwidget,SIGNAL(isexit()),this,SLOT(rmain()));
		}
		}
	else if(ok1 && usrkey.isEmpty())
	{
		QMessageBox::warning(this,tr("Error"),tr("You haven't input your password"),QMessageBox::Ok);
	}
	}
	}
	else if(ok &&usrname.isEmpty())
	{
		QMessageBox::warning(this,tr("Error"),tr("You haven't input your name"),QMessageBox::Ok);
	}
}

void MainWindow::rmain()
{
	if(isuser)
	{
		swidget->removeWidget(usrwidget);
		userWindow *tmp = usrwidget;
		delete tmp;
		usrwidget = NULL;
		isuser = false;
	}
	if(ismanager)
	{
		ismanager = false;
		manawidget->fresh();
	}
	swidget->setCurrentIndex(0);
	MainWindowButton->setVisible(false);
}

void MainWindow::open()
{
	if(!ismanager)
	{
		QMessageBox::information(this, tr("Not entitled"), tr("You are not manager,you have no rights to open a file."),QMessageBox::Ok); 
		return;
	}
	opendialog = new QDialog(this);
	usrfilelabel = new QLabel(tr("userfile"));
	usrfileedit = new QLineEdit("");
	usrfileedit->setReadOnly(true);
	usrfilebutton = new QPushButton("open");
	bkfilelabel = new QLabel(tr("bookfile"));
	bkfileedit = new QLineEdit("");
	bkfileedit->setReadOnly(true);
	bkfilebutton = new QPushButton("open");
	oktoopen = new QPushButton("Ok");
	QGridLayout layout;
	layout.addWidget(usrfilelabel,0,0);
	layout.addWidget(usrfileedit,0,1);
	layout.addWidget(usrfilebutton,0,2);
	layout.addWidget(bkfilelabel,1,0);
	layout.addWidget(bkfileedit,1,1);
	layout.addWidget(bkfilebutton,1,2);
	layout.addWidget(oktoopen,2,3);
	opendialog->setLayout(&layout);
	connect(usrfilebutton,SIGNAL(clicked()),this,SLOT(openusrfile()));
	connect(bkfilebutton,SIGNAL(clicked()),this,SLOT(openbkfile()));
	connect(oktoopen,SIGNAL(clicked()),this,SLOT(okopen()));
	opendialog->show();
}

void MainWindow::openusrfile()
{
		usrfilename = QFileDialog::getOpenFileName(this,tr("Open userfile"),".",tr("txtfile(*.txt)"));
		if(usrfilename.isEmpty())
			QMessageBox::information(opendialog, tr("Error"), tr("You didn't select any files."),QMessageBox::Ok); 
		else
			usrfileedit->setText(usrfilename);
}

void MainWindow::openbkfile()
{
		bkfilename = QFileDialog::getOpenFileName(this,tr("Open bookfile"),".",tr("txtfile(*.txt)"));
		if(bkfilename.isEmpty())
			QMessageBox::information(opendialog, tr("Error"), tr("You didn't select any files."),QMessageBox::Ok); 
		else
			bkfileedit->setText(bkfilename);
}

void MainWindow::okopen()
{
	if(!usrfileedit->text().isEmpty() && !bkfileedit->text().isEmpty())
	{
		mainmanager->setdafaultfile(bkfilename,usrfilename);
		QMessageBox::information(this,tr("Success"),tr("File loaded"),QMessageBox::Ok);
	}
	else
		QMessageBox::warning(this,tr("Error"),tr("You didn't  chose any files to open !"),QMessageBox::Ok);
	opendialog->close();
}

void MainWindow::about()
{
	QMessageBox::about(this,tr("About Library"),tr("<h2>Library</h2>"
				"<p>the library is based in redblacktree and Qt</p>"
				"copyright@yang_zw 2012"));
}

void MainWindow::managerlog()
{
	ismanager = true;
		bool ok;
		QString manakey = QInputDialog::getText(this,tr("Input manager password"),tr("Password:"),QLineEdit::Password,"",&ok);
		if(ok && !manakey.isEmpty())
		{
			if(!mainmanager->ismanagerkey(manakey))
					QMessageBox::warning(this,tr("Error"),tr("Your password is not correct!"),QMessageBox::Ok);
			else{
	swidget->setCurrentIndex(2);
	MainWindowButton->setVisible(true);
	ismanager = true;
			}
		}
}

void MainWindow::search()
{
	swidget->setCurrentIndex(3);
	searchwin->refresh();
	MainWindowButton->setVisible(true);
}

void MainWindow::whenexit()
{
	mainmanager->savechanges();
	close();
}
