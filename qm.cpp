#include "qm.h"

struct Logical
{
    string exp;
    int mark;
    list<int> list_num;

    Logical()
    {

    }
    Logical(string a)
    {
        exp = a;
    }
    Logical(const Logical& a, int b)
    {
        *this = a;
        mark = b;
    }
    Logical(string a, Logical b, Logical c)
    {
        exp = a;
        AddList_num(b, c);
    }
    Logical(string a, int b)
    {
        exp = a;
        list_num.push_back(b);
    }
    void AddList_num(Logical a, Logical b)
    {
        for (list<int>::iterator itr1 = a.list_num.begin(); itr1 != a.list_num.end(); itr1++)
        {
            list_num.push_back(*itr1);
        }
        for (list<int>::iterator itr2 = b.list_num.begin(); itr2 != b.list_num.end(); itr2++)
        {
            list_num.push_back(*itr2);
        }
    }
    void DeleteList_num(int a)
    {
        for (list<int>::iterator itr = list_num.begin(); itr != list_num.end();)
        {
            if (*itr == a)
            {
                list_num.erase(itr++);
            }
            else
            {
                itr++;
            }
        }
    }
    bool operator<( Logical a)
    {
        int count = list_num.size();
        for (list<int>::iterator itr1 = a.list_num.begin(); itr1 != a.list_num.end(); itr1++)
        {
            for (list<int>::iterator itr2 = list_num.begin(); itr2 != list_num.end(); itr2++)
            {
                if (*itr1 == *itr2)
                {
                    count--;
                }
            }
        }
        if (count == 0)
        {
            return true;
        }
        return false;
    }
};

struct Lowest
{
    int lowest_num;
    list<int> mark_list;
    Lowest(int a)
    {
        lowest_num = a;
    }
    void AddMark(int a)
    {
        mark_list.push_back(a);
    }
    void DeleteMark(int a)
    {
        for (list<int>::iterator itr = mark_list.begin(); itr != mark_list.end();)
        {
            if (*itr == a)
            {
                mark_list.erase(itr++);
            }
            else
            {
                itr++;
            }
        }
    }
    bool HasMark(int a)
    {
        for (list<int>::iterator itr = mark_list.begin(); itr != mark_list.end();itr++)
        {
            if (*itr == a)
            {
                return true;
            }
        }
        return false;
    }
    bool operator<( Lowest a)
    {
        int count = a.mark_list.size();

        for (list<int>::iterator itr1 = a.mark_list.begin(); itr1 != a.mark_list.end(); itr1++)
        {
            for (list<int>::iterator itr2 = mark_list.begin(); itr2 != mark_list.end(); itr2++)
            {
                if (*itr1 == *itr2)
                {
                    count--;
                }
            }
        }
        if (count == 0)
        {
            return true;
        }
        return false;
    }
};

string Merge(string a, string b)
{
    int count = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] + b[i] == 97)
        {
            a[i] = '_';
            count++;
        }
        else if (a[i] != b[i])
        {
            return "0";
        }
    }
    if (count == 1)
    {
        return a;
    }
    return "0";
}

int CountOne(string a)
{
    int count = 0;
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == '1')
        {
            count++;
        }
    }
    return count;
}

bool Check(string a, string b)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (a[i] == '_' || b[i] == '_')
        {
            continue;
        }
        if (a[i] != b[i])
        {
            return false;
        }
    }
    return true;
}

string BeautifulExpression(string res, string a)
{
    string str = "";
    for (int i = a.size() - 1; i >= 0; i--)
    {
        if (a[i] == '0')
        {
            str += "^" + res + "<" + (char)('0' + a.size() - i - 1) + ">";
        }
        if (a[i] == '1')
        {
            str += res + "<" + (char)('0' + a.size() - i - 1) + ">";
        }
    }
    return str;
}

QM::QM()
{

    excel = new QAxObject("Excel.Application");
    excel->dynamicCall("SetVisible (bool Visible)","false");//不显示窗体
    excel->setProperty("DisplayAlerts", false);//不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示


    if (excel->isNull())
    {//网络中很多使用excel==NULL判断，是错误的
        QMessageBox::critical(0, "错误信息", "没有找到EXCEL应用程序");
        return;
    }
    excel->setProperty("Visible",false);

    workbooks = excel->querySubObject("WorkBooks");
    workbook = workbooks->querySubObject("Open (const QString&)",QString("d:/test.xlsx"));
    worksheets = workbook->querySubObject("Sheets");
    worksheet = worksheets->querySubObject("Item(int)",1);//获取第一个工作表

    for (int i = 0; i < 64; i++)
    {
        string str = "000000";
        int x = i;
        int count = 5;
        while (x)
        {
            str[count--] = x % 2 + '0';
            x >>= 1;
        }
        decimal_map[str] = i;
        binary_map[i] = str;
    }
    ///////////////二进制十进制互换表////////////////

    sheet_count = worksheets->property("Count").toInt();
    worksheets_name = new QString[sheet_count];

    for(int i=1;i<=sheet_count;i++)
    {
        worksheets_name[i-1]=worksheets->querySubObject("Item(int)",i)->property("Name").toString();
    }
    /////////////获取EXCEL工作簿情况/////////////////

}

QString QM::calLogical(string encode_name,string *decode_name,int num,int width)
{
    string result = "";
    int T = width;
    while (T--)
    {
        map<string,Logical> map_str[7];
        string A[64][2];

        for (int i = 0; i < 64; i++)
        {
            A[i][0] = binary_map[i];
            A[i][1] = 'x';
        }
        for (int i = 0; i < num; i++)
        {
            A[decimal_map[B[i][0]]][1] = B[i][1][T];
        }
        for (int i = 0; i < 64; i++)
        {
            if (A[i][1] != "0")
            {
                map_str[CountOne(A[i][0])][A[i][0]] = Logical(A[i][0], i);
            }
        }
        /////////////////全部最小项生成///////////////////

        while (true)
        {
            map<string, Logical> map_str2[7];
            int count = 0;

            for (int i = 0; i < 6; i++)
            {
                for (map<string, Logical>::iterator itr = map_str[i].begin(); itr != map_str[i].end(); itr++)
                {
                    int cc = 0;
                    for (map<string, Logical>::iterator itr2 = map_str[i + 1].begin(); itr2 != map_str[i + 1].end(); itr2++)
                    {
                        string a = Merge(itr->first, itr2->first);
                        if (a != "0")
                        {
                            map_str2[i][a] = Logical(a, itr->second, itr2->second);
                            count++;
                            cc++;
                        }
                    }
                    if (cc == 0)
                    {
                        map_str2[i][itr->first] = itr->second;
                    }
                }
            }
            for (int i = 0; i < 7; i++)
            {
                map_str[i] = map_str2[i];
            }
            if (count == 0)
            {
                break;
            }
        }
        //////////////////全部质蕴含项生成//////////////////

        list<Logical> list_primeLogical;
        list<Lowest> list_Lowest;
        int cc = 0;

        for (int i = 0; i < 64; i++)
        {
            if (A[i][1] == "1")
            {
                list_Lowest.push_back(Lowest(i));
            }
        }

        for (int i = 0; i < 7; i++)
        {
            for (map<string, Logical>::iterator itr = map_str[i].begin(); itr != map_str[i].end(); itr++)
            {
                Logical logical(itr->second, cc);
                for (int j = 0; j < 64; j++)
                {
                    if (A[j][1] == "x")
                    {
                        logical.DeleteList_num(j);
                    }
                }
                if (logical.list_num.empty())
                {
                    continue;
                }

                for (list<int>::iterator iitr = logical.list_num.begin(); iitr != logical.list_num.end(); iitr++)
                {
                    for (list<Lowest>::iterator litr = list_Lowest.begin(); litr != list_Lowest.end(); litr++)
                    {
                        if (*iitr == litr->lowest_num)
                        {
                            litr->AddMark(cc);
                        }
                    }
                }

                list_primeLogical.push_back(logical);
                cc++;
            }
        }

        //////////////////全部质蕴含项归入统一链表,删除无关项,建立对应关系//////////////////

        list<Logical> list_finalLogical;
        while (!list_Lowest.empty())
        {
            int count;
            do
            {
                count = 0;

                for (list<Logical>::iterator itr = list_primeLogical.begin(); itr != list_primeLogical.end();)
                {
                    bool itrbreak = false;

                    for (list<Logical>::iterator itr2 = list_primeLogical.begin(); itr2 != list_primeLogical.end(); itr2++)
                    {
                        if (itr == itr2)
                        {
                            continue;
                        }
                        if (*itr < *itr2)
                        {
                            for (list<Lowest>::iterator litr = list_Lowest.begin(); litr != list_Lowest.end(); litr++)
                            {
                                litr->DeleteMark(itr->mark);
                            }

                            list_primeLogical.erase(itr++);
                            itrbreak = true;
                            count++;
                            break;
                        }
                    }
                    if (!itrbreak)
                    {
                        itr++;
                    }
                }
                ////////////////删除劣势行//////////////////

                for (list<Lowest>::iterator litr = list_Lowest.begin(); litr != list_Lowest.end();)
                {
                    bool litrbreak = false;

                    for (list<Lowest>::iterator litr2 = list_Lowest.begin(); litr2 != list_Lowest.end(); litr2++)
                    {
                        if (litr == litr2)
                        {
                            continue;
                        }
                        if (*litr < *litr2)
                        {
                            for (list<Logical>::iterator itr = list_primeLogical.begin(); itr != list_primeLogical.end(); itr++)
                            {
                                itr->DeleteList_num(litr->lowest_num);
                            }

                            list_Lowest.erase(litr++);
                            litrbreak = true;
                            count++;
                            break;
                        }
                    }
                    if (!litrbreak)
                    {
                        litr++;
                    }
                }
                ///////////////删除劣势列//////////////////////
            } while (count);
            ///////////////不断迭代删除劣势行和劣势列///////////////////


            for (list<Lowest>::iterator litr = list_Lowest.begin(); litr != list_Lowest.end();)
            {
                if (litr->mark_list.size() == 1)
                {
                    count++;
                    for (list<Logical>::iterator itr = list_primeLogical.begin(); itr != list_primeLogical.end();)
                    {
                        if (itr->mark == *litr->mark_list.begin())
                        {
                            for (list<Lowest>::iterator litr2 = list_Lowest.begin(); litr2 != list_Lowest.end();)
                            {
                                    if (litr2->HasMark(itr->mark))
                                    {
                                        list_Lowest.erase(litr2++);
                                    }
                                    else
                                    {
                                        litr2++;
                                    }
                            }
                            list_finalLogical.push_back(*itr);
                            list_primeLogical.erase(itr++);
                            break;
                        }
                        else
                        {
                            itr++;
                        }
                    }
                    litr = list_Lowest.begin();
                }
                else
                {
                    litr++;
                }
            }
            //////////////选取必要质蕴含项//////////////////

        }

        int con = 0;
        for (int i = 0; i < num; i++)
        {
            if (B[i][1][T] == '1')
            {
                for (list<Logical>::iterator itr = list_finalLogical.begin(); itr != list_finalLogical.end(); itr++)
                {
                    if (Check(B[i][0], itr->exp))
                    {
                        con++;
                        break;
                    }
                }
                continue;
            }
            con++;
        }
        if (con == num)
        {
            string str = "";
            for (list<Logical>::iterator itr = list_finalLogical.begin(); itr != list_finalLogical.end(); itr++)
            {
                str += BeautifulExpression(encode_name, itr->exp) + " + ";
            }
            str = str.substr(0, str.size() - 3);
            result += decode_name[T] + " = " + str+"\n";
        }
        else
        {
            result += decode_name[T] + " = Oh,false!\n";
        }

    }
    return QString::fromStdString(result);
}

QString QM::readExcel(int index)
{
    worksheet = worksheets->querySubObject("Item(int)",index);

    string encode_name;
    string decode_name[100];
    string real_name[100];
    int num;
    int width=0;
    for(int i=1;;i++)
    {
        QAxObject *range = worksheet->querySubObject("Cells(int,int)",i,1);
        QString strVal = range->dynamicCall("Value2()").toString();
        if(strVal.isEmpty())
        {
            num=i-2;
            break;
        }
        QString qstr="";

        for(int j=1;;j++)
        {
            range = worksheet->querySubObject("Cells(int,int)",i,j); //获取单元格的值
            strVal = range->dynamicCall("Value2()").toString();

            if(strVal.isEmpty())
            {
                if(i>1)
                {
                    B[i-2][1] = qstr.toStdString();
                }
                break;
            }
            else if(i==1)
            {
                if(j==1)
                {
                    encode_name = strVal.toStdString();
                }
                else
                {
                    real_name[j] = strVal.toStdString();
                }
            }
            else
            {
                if(i==2 && j>1)
                {
                    int k = width;
                    for(width += strVal.size();k<width;k++)
                    {
                        if(strVal.size()>1)
                        {
                            decode_name[k] = real_name[j] + "<"+QString::number(width-k-1).toStdString() +">";
                        }
                        else
                        {
                            decode_name[k] = real_name[j];
                        }
                    }

                }

                if(j==1)
                {
                    B[i-2][0]=strVal.toStdString();
                }
                else
                {
                    qstr += strVal;
                }
            }
        }
    }

    return calLogical(encode_name,decode_name,num,width);
}

QString* QM::getWorkSheets()
{
    return worksheets_name;
}

int QM::getSheetCount()
{
    return sheet_count;
}

QM::~QM()
{
    workbook->dynamicCall("Close()");//关闭工作簿
    excel->dynamicCall("Quit()");//关闭excel
    delete excel;
    delete worksheets_name;
    excel=NULL;
}
