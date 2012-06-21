#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class QLabel;
class QPushButton;
class QLineEdit;
class QAction;
class QMenu;
class userWindow;
class QStackedWidget;
class Register;
class QHBoxLayout;
class QVBoxLayout;
class manager;
class QDialog;
class Register;
class ManagerWindow;
class SearchWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
	void regis();
	void ulogin();
	void rmain();
	void managerlog();
	void search();
	void open();
	void openusrfile();
	void openbkfile();
	void okopen();
	void about();
	void whenexit();
	void save();
	void saveas();
	void saveasusrfile();
	void saveasbkfile();
	void oksaveas();
private:
    void createAction();
    void createMenu();
    void createCenter();
    void createStatusBar();
    bool isuser;
    bool ismanager;

    manager* mainmanager;
    Register* rig;
    ManagerWindow* manawidget;
    SearchWindow* searchwin;
    QString usrfilename;
    QString bkfilename;
    QString susrfilename;
    QString sbkfilename;
    QPushButton *userLoginButton;
    QPushButton *MainWindowButton;
    QPushButton *registerButton;
    QPushButton *exitButton;
    QPushButton *searchButton;
    QPushButton *managerButton;
    QPushButton *usrfilebutton;
    QPushButton *bkfilebutton;
    QPushButton *susrfilebutton;
    QPushButton *sbkfilebutton;
    QPushButton *oktoopen;
    QPushButton *oktosaveas;
    QAction *openfileAction;
    QAction *exitAction;
    QAction *aboutLibraryAction;
    QAction *aboutQtAction;
    QAction *saveaction;
    QAction *saveasaction;
    QMenu *fileMenu;
    QMenu *helpMenu;
    userWindow *usrwidget;
    QStackedWidget *swidget;
    QHBoxLayout *toplayout;
    QHBoxLayout *buttomlayout;
    QVBoxLayout *vlayout;
    QVBoxLayout *welcomelayout;
    QLabel *usrfilelabel;
    QLabel *bkfilelabel;
    QLabel *susrfilelabel;
    QLabel *sbkfilelabel;
    QLineEdit *usrfileedit;
    QLineEdit *bkfileedit;
    QLineEdit *susrfileedit;
    QLineEdit *sbkfileedit;
    QDialog *opendialog;
    QDialog *saveasdialog;
};

#endif // MAINWINDOW_H
