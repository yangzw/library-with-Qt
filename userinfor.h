#ifndef USERINFOR_H
#define USERINFOR_H

#include<QWidget>

class QLabel;
class QPushButton;
class QGridLayout;
class QLineEdit;
class manager;
class user;

class userinfor : public QWidget
{
	Q_OBJECT
	public:
		userinfor(QWidget *parent,manager *&mmanager,user *&usr);
	private slots:
		void on_lineEdit_textChanged();
		void change();
		void changekey();
		void whencancel();
	private:
	manager *rmanager;
	user *rusr;
	QLabel *nameLabel;
	QLabel *studentNumberLabel;
	QLabel *emailLabel;
	QLabel *keyLabel;
	QLineEdit *nameEdit;
	QLineEdit *studentNumberEdit;
	QLineEdit *emailEdit;
	QLineEdit *keyEdit;
	QPushButton *passwdButton;
	QPushButton *changeButton;
	QPushButton *cancelButton;
	QGridLayout *mainLayout;
};
#endif
