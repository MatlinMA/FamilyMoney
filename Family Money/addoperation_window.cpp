#include "addoperation_window.h"
#include "ui_addoperation_window.h"

addoperation_window::addoperation_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addoperation_window)
{
    ui->setupUi(this);
}

addoperation_window::~addoperation_window()
{
    delete ui;
}

void addoperation_window::showClear(int id)
{
    ui->incomeOperation->setChecked(true);
    this->on_incomeOperation_clicked();
    ui->sum_addOperation->clear();
    ui->product_addOperation->clear();
    ui->category_addOperation->clear();
    ui->user_addOperation->clear();
    ui->date_addOperation->setDateTime(QDateTime::currentDateTime());
    ui->comment_addOperation->clear();
    this->show();
}

void addoperation_window::on_incomeOperation_clicked()
{
    ui->label_3->show();
    ui->product_addOperation->show();
}

void addoperation_window::on_spendingOperation_clicked()
{
    ui->label_3->hide();
    ui->product_addOperation->hide();
}
