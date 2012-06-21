#include <QApplication>
#include<QSplashScreen>
#include "mainwindow.h"
#include<QCleanlooksStyle>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle(new QCleanlooksStyle);
    app.setStyleSheet("QPushButton:hover{background-color:#6D8EE8;color:white}");
    QSplashScreen splash;
    QPixmap pixmap(":/imgs/1.png");
    splash.setPixmap(pixmap);
    splash.showMessage(QObject::tr("<h2>Welcome to the library</h2>"),Qt::AlignTop);
    splash.show();
    app.processEvents();
    MainWindow mainWin;
    mainWin.show();
    splash.finish(&mainWin);
    return app.exec();
}
