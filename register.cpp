#include"register.h"
#include"user.h"
#include"manager.h"
#include<QLabel>
#include<QPushButton>
#include<QLineEdit>
#include<QGridLayout>
#include<QMessageBox>
#include<string>

Register::Register(QWidget *parent,manager *&mmanager)
	: QDialog(parent)
{
	rmanager = mmanager;
	setWindowTitle(tr("Input Your imformation"));

	nameLabel = new QLabel(tr("*&Name:"),this);
	studentNumberLabel = new QLabel(tr("&StudenNumber:"),this);
	emailLabel = new QLabel(tr("&Email:"),this);     
	keyLabel = new QLabel(tr("&Key:"),this);
	nameEdit = new QLineEdit(this);
	nameLabel->setBuddy(nameLabel);
	studentNumberEdit = new QLineEdit(this);
	studentNumberLabel->setBuddy(studentNumberEdit);
	emailEdit = new QLineEdit(this);
	emailLabel->setBuddy(emailEdit);
	keyEdit = new QLineEdit(this);
	keyLabel->setBuddy(keyEdit);
	keyEdit->setEchoMode(QLineEdit::Password);//²»ÏÔÊ¾ÃÜÂë
	okButton = new QPushButton(tr("&Ok"),this);
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
	mainLayout->addWidget(okButton,4,1);
	mainLayout->addWidget(cancelButton,4,2);

	connect(okButton,SIGNAL(clicked()),this,SLOT(Commit()));
	connect(cancelButton,SIGNAL(clicked()),this,SLOT(close()));
}

void Register::Commit()
{
	int choice(0);
	if(nameEdit->text().isEmpty())
	{
		choice =  QMessageBox::warning(this,tr("Not input name"),tr("you havn't input your username.\nDo you want to cancel the process?"),QMessageBox::Yes|QMessageBox::No);
		if(choice == QMessageBox::Yes)
			close();
	}
	else
	{
		std::string usrname = nameEdit->text().toStdString();
		if(rmanager->searchuser(usrname))
		{
			choice = QMessageBox::warning(this,tr("Same name"),tr("the is already registed\nDo you want to try again"),QMessageBox::Yes|QMessageBox::No);
			if(choice == QMessageBox::No)
				close();
		}
		else if(keyEdit->text().isEmpty())
			QMessageBox::warning(this,tr("Not Finished"),tr("you haven't input your key"),QMessageBox::Ok);
		else
		{
		rmanager->addusr(nameEdit->text().toStdString(),studentNumberEdit->text().toStdString(),emailEdit->text().toStdString(),keyEdit->text().toStdString());
		QMessageBox::information(this,tr("Successful"),tr("Congratulations!"),QMessageBox::Ok);
		close();
		}
	}
}
