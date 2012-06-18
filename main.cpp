#include <QApplication>
#include<QSplashScreen>
//#include"manager.h"
//#include"register.h"
//#include"userinfor.h"
#include "mainwindow.h"
//#include"user.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSplashScreen splash;
    QPixmap pixmap("imgs/1.png");
    splash.setPixmap(pixmap);
    splash.showMessage(QObject::tr("<h2>Welcome to the library</h2>"),Qt::AlignTop);
    splash.show();
    app.processEvents();
    MainWindow mainWin;
    mainWin.show();
    //manager* mainmanager = new manager;
    //Register rig(&mainWin,mainmanager);
    //rig.show();
    //user* usr = new user;
    //userinfor usrwindow(&mainWin,mainmanager,usr);
    //usrwindow.show();
    splash.finish(&mainWin);
    return app.exec();
}
