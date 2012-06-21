#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include<QDialog>

class QStackedWidget;
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QListWidget;
class QLabel;
class QGroupBox;
class QLineEdit;
class QPushButton;
class QStandardItemModel;
class QTableView;

class manager;
class SearchWindow;

class ManagerWindow : public QDialog
{
	Q_OBJECT	
	public:
		ManagerWindow(QWidget *parent, manager *&mainmanager);
		void fresh();
	private slots:
		void setCurrent(int index);
		void addbook();
		void remain();
		void on_lineEdit_textChanged();
		void showalluser();
		void showallbook();
		void closealluser();
		void closeallbook();
		void changepassword();
	private:
		manager *rmanager;
		SearchWindow *searchwin;

		QStackedWidget *stack;
		QListWidget *list;
		QHBoxLayout *mainlayout;
		QHBoxLayout *lefttoplayout;
		QVBoxLayout *leftlayout;
		QLabel *imglabel;
                //QLabel *namelabel;
		QLabel *tmp;
		QGroupBox *addgroup;
		QGridLayout *addlayout;
		QLabel *bknamelabel;
		QLabel *isbnlabel;
		QLabel *authorlabel;
		QLineEdit *bknameedit;
		QLineEdit *isbnedit;
		QLineEdit *authoredit;
		QPushButton *addbutton;
		QPushButton *canceladdbutton;
		QGroupBox *inforgroup;
		QGridLayout *inforlayout;
		QLabel *userinforlabel;
		QLabel *bookinforlabel;
		QPushButton *userdetailbutton;
		QPushButton *bookdetailbutton;
		QWidget *alluserwidget;
		QWidget *allbookwidget;
		QTableView *allusertableview;
		QTableView *allbooktableview;
		QStandardItemModel *allusermodel;
		QStandardItemModel *allbookmodel;
		QGroupBox *chanebox;
		QLabel *oldpasslabel;
		QLabel *newpasslabel;
		QLineEdit *oldpassedit;
		QLineEdit *newpassedit;
		QPushButton *okpassbutton;
		QPushButton *cancelpassbutton;
		QGridLayout *changelayout;

		void createaddwindow();
		void cleanaddwindow();
		void createinforwindow();
		void updateinfor();
		void createchangewindow();
};
#endif //MANAGERWINDOW_H
