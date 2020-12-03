#ifndef USER_H
#define USER_H

#include <QString>
#include <QObject>

namespace Ui {
class User;
}

class User
{

public:
    User();
    void Id(int i);
    int Id();
    void Login(QString l);
    QString Login();
    void Password(QString p);
    QString Password();
    void Name(QString n);
    QString Name();
    void Age(int a);
    int Age();
    void Gender(int g);
    QString Gender();

private:
    int f_Id;
    QString f_Login;
    QString f_Password;
    QString f_Name;
    int f_Age;
    QString f_Gender;
};
Q_DECLARE_METATYPE(User)

#endif // USER_H
