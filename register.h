#ifndef REGISTER_H
#define REGISTER_H

#include<QDialog>

class QLabel;
class QPushButton;
class QGridLayout;
class QLineEdit;
class manager;

class Register : public QDialog
{
	Q_OBJECT
	public:
		Register(QWidget *parent,manager *&mmanager);
	private slots:
		void Commit();
	private:
		manager *rmanager;
		QLabel *nameLabel;
		QLabel *studentNumberLabel;
		QLabel *emailLabel;
		QLabel *keyLabel;
		QLineEdit *nameEdit;
		QLineEdit *studentNumberEdit;
		QLineEdit *emailEdit;
		QLineEdit *keyEdit;
		QPushButton *okButton;
		QPushButton *cancelButton;
		QGridLayout *mainLayout;
};
#endif
