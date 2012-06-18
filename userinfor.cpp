#include"userinfor.h"
#include"user.h"
#include"manager.h"
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QGridLayout>
#include<QMessageBox>
#include<QString>
#include<QInputDialog>

userinfor::userinfor(QWidget *parent,manager *&mmanager,user *&usr)
	: QWidget(parent)
{
	rmanager = mmanager;
	rusr = usr;
	setWindowTitle(tr("User information"));
	nameLabel = new QLabel(tr("*Name:"),this);
	studentNumberLabel = new QLabel(tr("&StudenNumber:"),this);
	emailLabel = new QLabel(tr("&Email:"),this);     
	keyLabel = new QLabel(tr("&Key:"),this);
	nameEdit = new QLineEdit(usr->getname(),this);
	nameEdit->setStyleSheet("background-color:rgb(230,230,230)");
	nameEdit->setReadOnly(true);
	nameLabel->setBuddy(nameLabel);
	studentNumberEdit = new QLineEdit(usr->getnumber(),this);
	studentNumberLabel->setBuddy(studentNumberEdit);
	emailEdit = new QLineEdit(usr->getemail(),this);
	emailLabel->setBuddy(emailEdit);
	keyEdit = new QLineEdit(this);
	keyEdit->setStatusTip(tr("input your current key to change your key"));
	keyLabel->setStatusTip(tr("input your current key to change your key"));
	keyLabel->setBuddy(keyEdit);
	passwdButton = new QPushButton(tr("Change &password"),this);
	passwdButton->setEnabled(false);
	connect(keyEdit,SIGNAL(textChanged(const QString &)),this,SLOT(on_lineEdit_textChanged()));
	connect(passwdButton,SIGNAL(clicked()),this,SLOT(changekey()));
	keyEdit->setEchoMode(QLineEdit::Password);//不显示密码
	changeButton = new QPushButton(tr("Chan&ge"),this);
	cancelButton = new QPushButton(tr("&Cancel"),this);

	mainLayout = new QGridLayout(this);
	mainLayout->addWidget(nameLabel,0,0);
	mainLayout->addWidget(nameEdit,0,1);
	mainLayout->addWidget(studentNumberLabel,1,0);
	mainLayout->addWidget(studentNumberEdit,1,1);
	mainLayout->addWidget(emailLabel,2,0);
	mainLayout->addWidget(emailEdit,2,1);
	mainLayout->addWidget(keyLabel,3,0);
	mainLayout->addWidget(keyEdit,3,1);
	mainLayout->addWidget(passwdButton,3,2);
	mainLayout->addWidget(changeButton,4,1);
	mainLayout->addWidget(cancelButton,4,2);
	
	setLayout(mainLayout);	

	connect(changeButton,SIGNAL(clicked()),this,SLOT(change()));
	connect(cancelButton,SIGNAL(clicked()),this,SLOT(whencancel()));
}

//改变信息
void userinfor::change()
{
	rmanager->updateusr(rusr,studentNumberEdit->text(),emailEdit->text());
	QMessageBox::information(this,tr("Successful"),tr("you have change your imformation"),QMessageBox::Ok);
}

//改变密码
void userinfor::changekey()
{
	if(!rmanager->userkey(rusr,keyEdit->text()))
		QMessageBox::warning(this,tr("Wrong key"),tr("the password is not correct!"),QMessageBox::Ok);
	else//输入新密码的输入对话框
	{
		bool ok;
	     	QString newkey = QInputDialog::getText(this, tr("Input new key"),tr("New password:"), QLineEdit::Password,"", &ok);
	          if (ok && !newkey.isEmpty())
		  {
			  QMessageBox::information(this,tr("Successful"),tr("you have change your password"),QMessageBox::Ok);
			  rmanager->updateusr(rusr,rusr->getnumber(),rusr->getemail(),newkey);
		  }
	}
	passwdButton->setEnabled(false);
}

//keyEdit有输入时，按钮有效
void userinfor::on_lineEdit_textChanged()
{
	passwdButton->setEnabled(keyEdit->hasAcceptableInput());
}

void userinfor::whencancel()
{
	studentNumberEdit->setText(rusr->getnumber());
	emailEdit->setText(rusr->getemail());
	keyEdit->setText("");
	passwdButton->setEnabled(false);
}
