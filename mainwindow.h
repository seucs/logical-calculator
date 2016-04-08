#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMimeData>
#include <QDebug>
#include <QDragEnterEvent>
//#include <QList>
//#include <QUrl>
#include <QDropEvent>
#include <iconhelper.h>
#include <qm.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initStyle();
protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    Ui::MainWindow *ui;
    QM* qm;
    bool logical_cal;
    QPoint mousePoint;
    bool mousePressed;
    bool max;
    QRect location;

signals:

public slots:
    void cal();
    void reloadExcel(QString path);
    void showAbout();
    void ChangeToLogicalStatus();
    void ChangeToCoderStatus();

};

#endif // MAINWINDOW_H
