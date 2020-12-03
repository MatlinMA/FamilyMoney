#include "addcategory_window.h"
#include "ui_addcategory_window.h"

addcategory_window::addcategory_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addcategory_window)
{
    ui->setupUi(this);
}

addcategory_window::~addcategory_window()
{
    delete ui;
}

void addcategory_window::showClear()
{
    ui->freespace2->clear();
    this->show();
}

void addcategory_window::categoryAdded(bool b, QString s)
{
    if (b)
        ui->freespace2->setStyleSheet("color: rgb(0,255,0)");
    else
        ui->freespace2->setStyleSheet("color: rgb(255,0,0");

    ui->freespace2->setText(s);

    ui->Name_addcategory->clear();
}

void addcategory_window::on_addCategory_Button_clicked()
{
    Category c;
    c.Name(ui->Name_addcategory->text());
    emit addCategory(c);
}

void addcategory_window::on_cancel_Button_clicked()
{
    ui->Name_addcategory->clear();
    this->close();
}
