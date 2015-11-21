#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
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
    void reloadExcel();
    void showAbout();
    void ChangeToLogicalStatus();
    void ChangeToCoderStatus();

protected:
//    bool eventFilter(QObject *obj, QEvent *event);
//    void mouseMoveEvent(QMouseEvent *e);
//    void mousePressEvent(QMouseEvent *e);
//    void mouseReleaseEvent(QMouseEvent *);

private slots:
//    void on_btnMenu_Close_clicked();

//    void on_btnMenu_Max_clicked();

//    void on_btnMenu_Min_clicked();

//    void on_pushButton_clicked();

//    void on_pushButton_2_clicked();

//    void on_pushButton_3_clicked();

};

#endif // MAINWINDOW_H
