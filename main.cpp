#include <QApplication>
#include<QSplashScreen>
#include"manager.h"
#include"register.h"

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("/imgs/1.png"));
    splash->show();
    MainWindow mainWin;
    mainWin.show();
    manager* mainmanager = new manager;
    Register rig(&mainWin,mainmanager);
    rig.show();
    splash->finish(&mainWin);
    return app.exec();
}
