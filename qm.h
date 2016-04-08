#ifndef QM_H
#define QM_H

#include <QAxObject>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <string>
#include <list>
#include <map>

using namespace std;

class QM
{
public:
    QM(QString path);
    ~QM();
    QString calLogical(string encode_name,string *decode_name,int num,int width);
    QString readExcel(int index);
    QString* getWorkSheets();
    int getSheetCount();
private:
    QAxObject *workbook;
    QAxObject *workbooks;
    QAxObject *worksheet;
    QAxObject *worksheets;
    QAxObject *excel;
    QString *worksheets_name;
    int sheet_count;
private:
    string B[64][2];
    map<string, int> decimal_map;
    map<int, string> binary_map;
};


#endif // QM_H
