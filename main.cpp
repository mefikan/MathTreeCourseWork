#include "mainwindow.h"
#include "Treev4.h"
#include <string>
#include <iostream>
#include <QPixmap>
#include <QApplication>
using namespace std;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //QPixmap ic;
    //ic.load(":/new/prefix1/imgs/pngegg(1).png");
    //w.setWindowIcon(ic);
    w.show();
    return a.exec();
}
