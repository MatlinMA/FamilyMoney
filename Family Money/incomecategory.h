#ifndef INCOMECATEGORY_H
#define INCOMECATEGORY_H

#include <QObject>

class IncomeCategory
{
public:
    IncomeCategory();
    void Id(int id);
    int Id();
    void Name(QString n);
    QString Name();

private:
    int f_Id;
    QString f_Name;
};
Q_DECLARE_METATYPE(IncomeCategory)

#endif // INCOMECATEGORY_H
