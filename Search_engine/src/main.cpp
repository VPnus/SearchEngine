#include "mainwindow.h"
#include "include/converter.h"
#include "include/inverted_index.h"
#include "include/server.h"
#include <iostream>
#include <QApplication>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(600,600);
    w.show();
    return a.exec();
}




