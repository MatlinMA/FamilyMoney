#ifndef ADDUSER_WINDOW_H
#define ADDUSER_WINDOW_H

#include <QWidget>
#include <user.h>

namespace Ui {
class adduser_window;
}

class adduser_window : public QWidget
{
    Q_OBJECT

public:
    explicit adduser_window(QWidget *parent = 0);
    ~adduser_window();

public slots:
    void userAdded(bool, QString);

signals:
    void addUser(User);

private slots:
    void on_addUser_Button_clicked();
    void on_cancel_Button_clicked();

private:
    Ui::adduser_window *ui;
};

#endif // ADDUSER_WINDOW_H
