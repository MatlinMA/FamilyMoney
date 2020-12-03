#include "adduser_window.h"
#include "ui_adduser_window.h"

adduser_window::adduser_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adduser_window)
{
    ui->setupUi(this);
}

adduser_window::~adduser_window()
{
    delete ui;
}

void adduser_window::userAdded(bool b, QString s)
{
    if (b)
        ui->freespace2->setStyleSheet("color: rgb(0,255,0)");
    else
        ui->freespace2->setStyleSheet("color: rgb(255,0,0");

    ui->freespace2->setText(s);

    ui->login_adduser->clear();
    ui->password_adduser->clear();
    ui->name_adduser->clear();
    ui->age_adduser->clear();
}

void adduser_window::on_addUser_Button_clicked()
{
    User user;
    user.Login(ui->login_adduser->text());
    user.Password(ui->password_adduser->text());
    user.Name(ui->name_adduser->text());
    user.Age(ui->age_adduser->text().toInt());
    if (ui->gender_adduser->currentIndex() == 1)
        user.Gender(1);
    else
        user.Gender(0);
    emit addUser(user);
}

void adduser_window::on_cancel_Button_clicked()
{
    ui->login_adduser->clear();
    ui->password_adduser->clear();
    ui->name_adduser->clear();
    ui->age_adduser->clear();
    ui->freespace2->clear();
    this->close();
}
