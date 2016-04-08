#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("QM计算器");
    qm = new QM("d:\test.xlsx");
    logical_cal = true;
   // this->initStyle();



    connect(ui->cal_btn,SIGNAL(clicked(bool)),this,SLOT(cal()));
    //connect(ui->a_Excel,SIGNAL(triggered(bool)),this,SLOT(reloadExcel()));
    connect(ui->a_about,SIGNAL(triggered(bool)),this,SLOT(showAbout()));
    connect(ui->a_coder,SIGNAL(triggered(bool)),this,SLOT(ChangeToCoderStatus()));
    connect(ui->a_logical,SIGNAL(triggered(bool)),this,SLOT(ChangeToLogicalStatus()));

    for(int i=0;i<qm->getSheetCount();i++)
    {
        ui->WorkSheetBox->addItem(qm->getWorkSheets()[i]);
    }
    ui->resultText->setFont(QFont("宋体",10));
    ui->resultText->setAcceptDrops(true);

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

void MainWindow::reloadExcel(QString path)
{
    ui->resultText->setText("");
    for(int i=qm->getSheetCount()-1;i>=0;i--)
    {
         ui->WorkSheetBox->removeItem(i);
    }
    delete qm;
    qm = new QM(path);
    for(int i=0;i<qm->getSheetCount();i++)
    {
        ui->WorkSheetBox->addItem(qm->getWorkSheets()[i]);
    }
}

void MainWindow::showAbout()
{
    QMessageBox::information(this,tr("关于QM计算器"),
                             tr("Based on Qt 5.5.1 (MSVC 2013, 32 bit)  \n    朴智新 版权所有！     ") );
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

}

//当用户拖动文件到窗口部件上时候，就会触发dragEnterEvent事件
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

//当用户放下这个文件后，就会触发dropEvent事件
void MainWindow::dropEvent(QDropEvent *event)
{
    //注意：这里如果有多文件存在，意思是用户一下子拖动了多个文件，而不是拖动一个目录
    //如果想读取整个目录，则在不同的操作平台下，自己编写函数实现读取整个目录文件名
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;

    //往文本框中追加文件名
    foreach(QUrl url, urls) {
        QString file_name = url.toLocalFile();
        textEdit->append(file_name);
    }
     ui->resultText->setText("123");
}
