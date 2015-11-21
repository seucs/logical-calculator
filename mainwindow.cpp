#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("QM计算器");
    qm = new QM();
    logical_cal = true;
   // this->initStyle();

    connect(ui->cal_btn,SIGNAL(clicked(bool)),this,SLOT(cal()));
    connect(ui->a_Excel,SIGNAL(triggered(bool)),this,SLOT(reloadExcel()));
    connect(ui->a_about,SIGNAL(triggered(bool)),this,SLOT(showAbout()));
    connect(ui->a_coder,SIGNAL(triggered(bool)),this,SLOT(ChangeToCoderStatus()));
    connect(ui->a_logical,SIGNAL(triggered(bool)),this,SLOT(ChangeToLogicalStatus()));

    for(int i=0;i<qm->getSheetCount();i++)
    {
        ui->WorkSheetBox->addItem(qm->getWorkSheets()[i]);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete qm;
}

void MainWindow::cal()
{
    int index = ui->WorkSheetBox->currentIndex()+1;
    ui->resultText->setText(qm->readExcel(index));
}

void MainWindow::reloadExcel()
{
    ui->resultText->setText("");
    for(int i=qm->getSheetCount()-1;i>=0;i--)
    {
         ui->WorkSheetBox->removeItem(i);
    }
    delete qm;
    qm = new QM();
    for(int i=0;i<qm->getSheetCount();i++)
    {
        ui->WorkSheetBox->addItem(qm->getWorkSheets()[i]);
    }
}

void MainWindow::showAbout()
{
    QMessageBox::information(this,tr("关于QM计算器"),
                             tr("Based on Qt 5.5.1 (MSVC 2013, 32 bit)  \n    404 Not Found 版权所有！     ") );
}

void MainWindow::ChangeToLogicalStatus()
{
    ui->a_logical->setChecked(true);
    ui->a_coder->setChecked(false);
    if(!logical_cal)
    {
        logical_cal=!logical_cal;
    }


}

void MainWindow::ChangeToCoderStatus()
{
    ui->a_logical->setChecked(false);
    ui->a_coder->setChecked(true);
    if(logical_cal)
    {
        logical_cal=!logical_cal;
    }
}

void MainWindow::initStyle()
{
    //设置窗体标题栏隐藏
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);
    location = this->geometry();
    max = false;
    mousePressed = false;

    //安装事件监听器,让标题栏识别鼠标双击
    //ui->lab_Title->installEventFilter(this);

//    IconHelper::Instance()->SetIcon(ui->btnMenu_Close, QChar(0xf00d), 10);
//    IconHelper::Instance()->SetIcon(ui->btnMenu_Max, QChar(0xf096), 10);
//    IconHelper::Instance()->SetIcon(ui->btnMenu_Min, QChar(0xf068), 10);
//    IconHelper::Instance()->SetIcon(ui->btnMenu, QChar(0xf0c9), 10);
//    IconHelper::Instance()->SetIcon(ui->lab_Ico, QChar(0xf015), 12);
}
