#include "editcategory_window.h"
#include "ui_editcategory_window.h"

editcategory_window::editcategory_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editcategory_window)
{
    ui->setupUi(this);
}

editcategory_window::~editcategory_window()
{
    delete ui;
}

void editcategory_window::showWithString(Category c)
{
    ui->name_EditCategory->setText(c.Name());
    category = c;
    this->show();
}

void editcategory_window::on_cancel_Button_clicked()
{
    this->close();
}

void editcategory_window::on_editCategory_Button_clicked()
{
    category.Name(ui->name_EditCategory->text());
    emit editCategory(category);
}

void editcategory_window::categoryEdited(bool b, QString s)
{
    if (b)
    {
        ui->freespace2->setStyleSheet("color: rgb(0,255,0)");
        ui->name_EditCategory->clear();
    }
    else
        ui->freespace2->setStyleSheet("color: rgb(255,0,0");

    ui->freespace2->setText(s);
}
