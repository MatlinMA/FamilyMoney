#include "user.h"

User::User()
{

}

void User::Id(int i)
{
    f_Id = i;
}

int User::Id()
{
    return f_Id;
}

void User::Login(QString l)
{
    f_Login = l;
}

QString User::Login()
{
    return f_Login;
}

void User::Password(QString p)
{
    f_Password = p;
}

QString User::Password()
{
    return f_Password;
}

void User::Name(QString n)
{
    f_Name = n;
}

QString User::Name()
{
    return f_Name;
}

void User::Age(int a)
{
    f_Age = a;
}

int User::Age()
{
    return f_Age;
}

void User::Gender(int g)
{
    if (g == 1)
        f_Gender = "М";
    if (g ==0)
        f_Gender = "Ж";
}

QString User::Gender()
{
    return f_Gender;
}
