#include "edituser_window.h"
#include "ui_edituser_window.h"

edituser_window::edituser_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edituser_window)
{
    ui->setupUi(this);
}

edituser_window::~edituser_window()
{
    delete ui;
}

void edituser_window::userEditResult(User usr)
{
    editedId = usr.Id();
    ui->login_edituser->setText(usr.Login());
    ui->name_edituser->setText(usr.Name());
    ui->age_edituser->setText(QString::number(usr.Age()));
    if (usr.Gender().toInt() == 0)
        ui->gender_edituser->setCurrentIndex(0);
    else ui->gender_edituser->setCurrentIndex(1);
    this->show();
}

void edituser_window::userEdited(bool b, QString s)
{
    if (b)
    {
        ui->freespace2->setStyleSheet("color: rgb(0,255,0)");
        ui->login_edituser->clear();
        ui->password_edituser->clear();
        ui->name_edituser->clear();
        ui->age_edituser->clear();
    }

    else
        ui->freespace2->setStyleSheet("color: rgb(255,0,0");

    ui->freespace2->setText(s);
}

void edituser_window::on_cancel_Button_clicked()
{
    ui->login_edituser->clear();
    ui->password_edituser->clear();
    ui->name_edituser->clear();
    ui->age_edituser->clear();
    ui->freespace2->clear();
    this->close();
}

void edituser_window::on_editUser_Button_clicked()
{
    User user;
    user.Id(editedId);
    user.Login(ui->login_edituser->text());
    user.Password(ui->password_edituser->text());
    user.Name(ui->name_edituser->text());
    user.Age(ui->age_edituser->text().toInt());
    if (ui->gender_edituser->currentIndex() == 1)
        user.Gender(1);
    else
        user.Gender(0);
    emit editUser(user);
}
