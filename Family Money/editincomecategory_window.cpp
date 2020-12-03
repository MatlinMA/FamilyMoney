#include "editincomecategory_window.h"
#include "ui_editincomecategory_window.h"

editincomecategory_window::editincomecategory_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editincomecategory_window)
{
    ui->setupUi(this);
}

editincomecategory_window::~editincomecategory_window()
{
    delete ui;
}

void editincomecategory_window::showWithString(IncomeCategory c)
{
    ui->name_EditIncomeCategory->setText(c.Name());
    incomeCategory = c;
    this->show();
}

void editincomecategory_window::on_cancel_Button_clicked()
{
    this->close();
}

void editincomecategory_window::on_editIncomeCategory_Button_clicked()
{
    incomeCategory.Name(ui->name_EditIncomeCategory->text());
    emit editIncomeCategory(incomeCategory);
}

void editincomecategory_window::incomeCategoryEdited(bool b, QString s)
{
    if (b)
    {
        ui->freespace2->setStyleSheet("color: rgb(0,255,0)");
        ui->name_EditIncomeCategory->clear();
    }
    else
        ui->freespace2->setStyleSheet("color: rgb(255,0,0");

    ui->freespace2->setText(s);
}
