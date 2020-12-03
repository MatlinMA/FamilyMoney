#include "incomecategory.h"

IncomeCategory::IncomeCategory()
{

}

void IncomeCategory::Id(int id)
{
    f_Id = id;
}

int IncomeCategory::Id()
{
    return f_Id;
}

void IncomeCategory::Name(QString n)
{
    f_Name = n;
}

QString IncomeCategory::Name()
{
    return f_Name;
}
