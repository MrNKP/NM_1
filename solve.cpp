#include "solve.h"
#include "ui_solve.h"

#include <QMessageBox>

#include <vector>
#include <cmath>

using namespace std;

//Input
vector<double> getValues(QString src)
{
    vector<double> result;

    int lastPos = 0;
    double value = 0.0;
    QString tmp;
    for (int i = 0; i < src.size(); i++)
    {
        if (src[i] == ' ')
        {
            tmp = src.mid(lastPos, i-lastPos);
            value = tmp.toDouble();
            result.push_back(value);
            lastPos = i;
        }
    }
    tmp = src.mid(lastPos, src.size()-lastPos);
    value = tmp.toDouble();
    result.push_back(value);

    return result;
}

//2 degree
vector<double> countTable(vector<double> src)
{
    vector<double> result;
    double value;
    unsigned int last = src.size()-1;

    for (unsigned int i=0; i<last-1; i++)
    {
        value = 3.0*src[i]/8.0 + 3.0*src[i+1]/4.0 - src[i+2]/8.0;
        result.push_back(value);
    }

    value = -1.0*src[last-2]/8.0 + 3.0*src[last-1]/4.0 + 3.0*src[last]/8.0;
    result.push_back(value);
    return result;
}

//3 degree
vector<double> countAccuracy(vector<double> src)
{
    vector<double> result;
    double value;
    unsigned int last = src.size()-1;

    for (unsigned int i=0; i<last-2; i++)
    {
        value = 5.0*src[i]/16.0 + 15.0*src[i+1]/16.0 - 5.0*src[i+2]/16.0 + src[i+3]/16.0;
        result.push_back(value);
    }

    value = -1.0*src[last-3]/16.0 + 9.0*src[last-2]/16.0 + 9.0*src[last-1]/16.0 - src[last]/16.0;
    result.push_back(value);
    value = 1.0*src[last-3]/16.0 - 5.0*src[last-2]/16.0 + 15.0*src[last-1]/16.0 + 5.0*src[last]/16.0;
    result.push_back(value);
    return result;
}

Solve::Solve(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Solve)
{
    ui->setupUi(this);
}

Solve::~Solve()
{
    delete ui;
}

void Solve::on_pushButton_3_clicked()
{
    this->close();
}

void Solve::on_pushButton_2_clicked()
{
    ui->label_8->clear();
    ui->listWidget->clear();
    ui->listWidget_2->clear();
}

void Solve::on_pushButton_clicked()
{
    if (ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "")
    {
        QMessageBox::critical(this, "Error", "Not Enough Input Data", QMessageBox::Ok);
        ui->label_8->setText("No Data");
    }
    else
    {
        QString tmp = ui->lineEdit->text();
        int N_input = tmp.toInt();
        tmp = ui->lineEdit_2->text();
        vector<double> Values_input = getValues(tmp);
        int Values_input_size = Values_input.size();
        if (N_input == Values_input_size && N_input >= 4)
        {
            /*for (unsigned int i=0; i<Values_input.size(); i++)
                ui->listWidget_2->addItem(QString::number(Values_input[i]));*/
            vector<double> new2Table = countTable(Values_input);
            for (unsigned int i=0; i<new2Table.size(); i++)
                ui->listWidget->addItem(QString::number(new2Table[i]));
            vector<double> new3Table = countAccuracy(Values_input);
            /*for (unsigned int i=0; i<new3Table.size(); i++)
                ui->listWidget_2->addItem(QString::number(new3Table[i]));
            QMessageBox::information(this, "Pause", "Pause", QMessageBox::Ok);
            ui->listWidget_2->clear();*/
            vector<double> Accuracy;
            for (unsigned int i=0; i<new2Table.size(); i++)
                Accuracy.push_back(fabs(new2Table[i]-new3Table[i]));
            for (unsigned int i=0; i<Accuracy.size(); i++)
                ui->listWidget_2->addItem(QString::number(Accuracy[i]));
                //ui->listWidget_2->addItem(QString::number(new3Table[i]));
            ui->label_8->setText("0");
        }
        else
        {
            QMessageBox::critical(this, "Error", "Bad Input", QMessageBox::Ok);
            ui->label_8->setText("1");
        }
    }
}
