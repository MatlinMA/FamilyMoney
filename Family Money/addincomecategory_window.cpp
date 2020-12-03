#include "addincomecategory_window.h"
#include "ui_addincomecategory_window.h"

addincomecategory_window::addincomecategory_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addincomecategory_window)
{
    ui->setupUi(this);
}

addincomecategory_window::~addincomecategory_window()
{
    delete ui;
}

void addincomecategory_window::showClear()
{
    ui->freespace2->clear();
    this->show();
}

void addincomecategory_window::incomeCategoryAdded(bool b, QString s)
{
    if (b)
        ui->freespace2->setStyleSheet("color: rgb(0,255,0)");
    else
        ui->freespace2->setStyleSheet("color: rgb(255,0,0");

    ui->freespace2->setText(s);

    ui->Name_addincomecategory->clear();
}

void addincomecategory_window::on_addIncomeCategory_Button_clicked()
{
    IncomeCategory c;
    c.Name(ui->Name_addincomecategory->text());
    emit addIncomeCategory(c);
}

void addincomecategory_window::on_cancel_Button_clicked()
{
    ui->label_2->clear();
    ui->Name_addincomecategory->clear();
    this->close();
}
