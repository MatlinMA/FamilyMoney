#ifndef CATEGORIES_H
#define CATEGORIES_H

#include <QObject>

class Category
{
public:
    Category();
    void Id(int i);
    int Id();
    void Name(QString n);
    QString Name();

private:
    int f_Id;
    QString f_Name;

};
Q_DECLARE_METATYPE(Category)

#endif // CATEGORIES_H
