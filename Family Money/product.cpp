#include "product.h"

Product::Product()
{

}

void Product::Id(int id)
{
    f_Id = id;
}

int Product::Id()
{
    return f_Id;
}

void Product::Name(QString name)
{
    f_Name = name;
}

QString Product::Name()
{
    return f_Name;
}

void Product::IdCategory(int idcat)
{
    f_IdCategory = idcat;
}

int Product::IdCategory()
{
    return f_IdCategory;
}

void Product::CategoryName(QString catname)
{
    f_CategoryName = catname;
}

QString Product::CategoryName()
{
    return f_CategoryName;
}
