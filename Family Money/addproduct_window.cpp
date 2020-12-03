#include "addproduct_window.h"
#include "ui_addproduct_window.h"

addproduct_window::addproduct_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addproduct_window)
{
    categoriesVector = new QVector<Category>;
    ui->setupUi(this);
}

addproduct_window::~addproduct_window()
{
    delete categoriesVector;
    delete ui;
}

void addproduct_window::showClear()
{
    emit loadCategoryVector();
    ui->freespace2->clear();
    this->show();
}

void addproduct_window::putCategories(QVector<Category> v)
{
    ui->category_addProduct->clear();

    Category c;

    *categoriesVector = v;

    foreach(c, v)
    {

        ui->category_addProduct->addItem(c.Name());
    }
}

void addproduct_window::productAdded(bool b, QString s)
{
    if (b)
        ui->freespace2->setStyleSheet("color: rgb(0,255,0)");
    else
        ui->freespace2->setStyleSheet("color: rgb(255,0,0");

    ui->freespace2->setText(s);

    ui->Name_addProduct->clear();
}

void addproduct_window::on_addProduct_Button_clicked()
{
    Product p;
    p.Name(ui->Name_addProduct->text());
    p.IdCategory((*categoriesVector)[ui->category_addProduct->currentIndex()].Id());
    emit addProduct(p);
}
