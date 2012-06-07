#include "mainwindow.h"

//测试系统,来调用系统的sleep函数
#if defined Q_OS_WIN32  
#include <windows.h>  
void sleep(unsigned long nSeconde)  
{  
    Sleep(nSeconde)*1000);  
}  
#endif  
#if defined Q_OS_LINUX  
#include  <unistd.h>  
#endif   

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	sleep(2);
}

MainWindow::~MainWindow()
{

}
