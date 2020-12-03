#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class auth_window;
}

class auth_window : public QWidget
{
    Q_OBJECT

public:
    explicit auth_window(QWidget *parent = nullptr);
    ~auth_window();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_login_textEdited(const QString &arg1);

    void on_password_textEdited(const QString &arg1);

    void uiLoginError();

signals:
    void authSend(QString, QString);

private:
    Ui::auth_window *ui;

    QString f_login;
    QString f_password;
};

#endif // AUTH_WINDOW_H
