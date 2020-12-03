#ifndef EDITUSER_WINDOW_H
#define EDITUSER_WINDOW_H

#include <QWidget>
#include "user.h"

namespace Ui {
class edituser_window;
}

class edituser_window : public QWidget
{
    Q_OBJECT

public:
    explicit edituser_window(QWidget *parent = nullptr);
    ~edituser_window();

public slots:
    void userEditResult(User);
    void userEdited(bool, QString);

private slots:
    void on_cancel_Button_clicked();

    void on_editUser_Button_clicked();

signals:
    void editUser(User);

private:
    Ui::edituser_window *ui;
    int editedId;
};

#endif // EDITUSER_WINDOW_H
