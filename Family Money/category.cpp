#include "category.h"

Category::Category()
{

}

void Category::Id(int i)
{
    f_Id = i;
}

int Category::Id()
{
    return f_Id;
}

void Category::Name(QString n)
{
    f_Name = n;
}

QString Category::Name()
{
    return f_Name;
}
