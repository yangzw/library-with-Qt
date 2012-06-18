#ifndef USERWINDOW_H
#define USERWINDOW_H
#include<QDialog>

class QStackedWidget;
class QVBoxLayout;
class QHBoxLayout;
class QListWidget;
class QLabel;
class user;
class manager;
class userinfor;
class SearchWindow;
class QDialog;
class QStandardItemModel;
class QTableView;
class QPushButton;


class userWindow : public QDialog
{
	Q_OBJECT
	public:
		userWindow(QWidget *parent, manager*& mmanager, user *&usr);
	private slots:
		void delusr();
		void remain();
		void updatemybook();
		void setCurrent(int index);
		void rowselected();
		void returnbook();
        signals:
		void isexit();
		void viewmybook();
	private:
		void createdelwindow();
		void createbookwindow();
		user * rusr;
		manager *rmanager;
		QStackedWidget *stack;
		QHBoxLayout *mainlayout;
		QHBoxLayout *lefttoplayout;
		QVBoxLayout *leftlayout;
		QLabel *imglabel;
		QLabel *namelabel;
		QListWidget *list;
		QDialog *deleteAccount;
		QDialog *bookview;
		QStandardItemModel *model;
		QTableView *booktable;
		userinfor *imfor;
		SearchWindow *searchwin;
		QPushButton *returnbutton;
};
#endif // USERWINDOW_H
