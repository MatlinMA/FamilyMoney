#include "editproduct_window.h"
#include "ui_editproduct_window.h"

editproduct_window::editproduct_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editproduct_window)
{
    ui->setupUi(this);
    categoriesVector = new QVector<Category>;
}

editproduct_window::~editproduct_window()
{
    delete categoriesVector;
    delete ui;
}

void editproduct_window::showPage(Product p)
{
    editedProduct = p;
    ui->categories_Combobox->clear();
    ui->label_2->clear();
    ui->name_EditProduct->setText(p.Name());
    emit loadCategoryVector();
    this->show();
}

void editproduct_window::putCategories(QVector<Category> v)
{
    Category c;

    *categoriesVector = v;

    foreach(c, v)
    {
        ui->categories_Combobox->addItem(c.Name());
    }
    ui->categories_Combobox->setCurrentText(editedProduct.CategoryName());
}

void editproduct_window::productEdited(bool b, QString s)
{
    if (b)
    {
        ui->freespace2->setStyleSheet("color: rgb(0,255,0)");
        ui->name_EditProduct->clear();
    }
    else
        ui->freespace2->setStyleSheet("color: rgb(255,0,0");

    ui->freespace2->setText(s);
}

void editproduct_window::on_cancel_Button_clicked()
{
    this->close();
}

void editproduct_window::on_editProduct_Button_clicked()
{
    Product p;
    p.Id(editedProduct.Id());
    p.Name(ui->name_EditProduct->text());
    p.IdCategory((*categoriesVector)[ui->categories_Combobox->currentIndex()].Id());
    emit editProduct(p);
}
