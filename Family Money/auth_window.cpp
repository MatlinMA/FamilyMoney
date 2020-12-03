#include "auth_window.h"
#include "ui_auth_window.h"
#include <cstdlib>
#include <QDebug>

auth_window::auth_window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::auth_window)
{
    ui->setupUi(this);
    ui->loginError->hide();
}

auth_window::~auth_window()
{
    delete ui;
}

void auth_window::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        this->on_buttonBox_accepted();
    if (event->key() == Qt::Key_Escape)
        exit(0);
}

void auth_window::on_buttonBox_rejected()
{
    exit(0);
}

void auth_window::on_buttonBox_accepted()
{
    emit authSend(f_login, f_password);
}

void auth_window::on_login_textEdited(const QString &arg1)
{
    f_login = arg1;
}

void auth_window::on_password_textEdited(const QString &arg1)
{
    f_password = arg1;
}

void auth_window::uiLoginError()
{
    ui->loginError->show();
}
