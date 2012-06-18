#ifndef SEARCHWINDOW_H
#define SEARCHWINDOW_H

#include<QSplitter>
#include<list>
using namespace std;

class QGridLayout;
class QPushButton;
class QLabel;
class QLineEdit;
class QSplitter;
class QTableView;
class QGroupBox;
class QVBoxLayout;
class QStandardItemModel;
class manager;
class book;
class user;

class SearchWindow : public QSplitter
{
	Q_OBJECT
	public:
		SearchWindow(QWidget *parent, manager*& mmanager, user *& usr,bool isuser, bool ismanager);
		void refresh();
	private slots:
		void on_lineEdit_textChanged();
		void searchbybkname();
		void searchbykey();
		void searchbyauthor();
		void rowselected();
		void borrowbook();
		void deletebook();
		void updatebook();
		void updatebkprocess();
	private:
		manager* rmanager;
		user* rusr;
		bool isuser;
		bool ismanager;
		QSplitter *buttomspliter;
		QGridLayout *mainlayout;
		QLabel *bybknameLabel;
		QLabel *bykeyLabel;
		QLabel *byauthorLabel;
		QLineEdit *bybknameEdit;
		QLineEdit *bykeyEdit;
		QLineEdit *byauthorEdit;
		QPushButton *bybknameButton;
		QPushButton *bykeyButton;
		QPushButton *byauthorButton;
		QPushButton *borrowbutton;
		QPushButton *delbutton;
		QPushButton *updatebutton;
		QGroupBox *buttomrightgroup;
		QVBoxLayout *buttomrightlayout;
		QGroupBox* topwidget;
		QTableView *bookTableView;
		QStandardItemModel *model;
		QGroupBox *updatebkwin;
		QLabel *bknamelable;
		QLabel *isbnlabel;
		QLabel *authorlabel;
		QLineEdit *bknameedit;
		QLineEdit *isbnedit;
		QLineEdit *authoredit;
		QPushButton *okupdatebutton;
		QPushButton *cancelbutton;
		QGridLayout *updatelayout;

		void createsearchwidget();
		void createresultable();
		void show(list<book*> &bklist);
		void refreshtable();
};
#endif //SERACHWINDOW_H
