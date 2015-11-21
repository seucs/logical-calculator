#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(QString("./image/blue.css"));
    file.open(QFile::ReadOnly);
    QString qss = QLatin1String(file.readAll());
    a.setStyleSheet(qss);
    a.setPalette(QPalette(QColor("#F0F0F0")));

    MainWindow w;
    w.show();

    return a.exec();
}
