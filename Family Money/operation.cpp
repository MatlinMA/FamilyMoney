#include "operation.h"

Operation::Operation()
{

}

void Operation::Id(int id)
{
    f_Id = id;
}

int Operation::Id()
{
    return f_Id;
}

void Operation::IdUser(int u)
{
    f_IdUser = u;
}

int Operation::IdUser()
{
    return f_IdUser;
}

void Operation::IdProduct(int p)
{
    f_IdProduct = p;
}

int Operation::IdProduct()
{
    return f_IdProduct;
}

void Operation::IdProductCategory(int c)
{
    f_IdProductCategory = c;
}

int Operation::IdProductCategory()
{
    return f_IdProductCategory;
}

void Operation::IdIncomeCategory(int c)
{
    f_IdIncomeCategory = c;
}

int Operation::IdIncomeCategory()
{
    return f_IdIncomeCategory;
}

void Operation::Sum(int s)
{
    f_Sum = s;
}

int Operation::Sum()
{
    return f_Sum;
}

void Operation::Date(QString d)
{
    f_Date = d;
}

QString Operation::Date()
{
    return f_Date;
}

void Operation::UserName(QString n)
{
    f_UserName = n;
}

QString Operation::UserName()
{
    return f_UserName;
}

void Operation::ProductName(QString n)
{
    f_ProductName = n;
}

QString Operation::ProductName()
{
    return f_ProductName;
}

void Operation::ProductCategoryName(QString n)
{
    f_ProductCategoryName = n;
}

QString Operation::ProductCategoryName()
{
    return f_ProductCategoryName;
}

void Operation::IncomeCategoryName(QString n)
{
    f_IncomeCategoryName = n;
}

QString Operation::IncomeCategoryName()
{
    return f_IncomeCategoryName;
}

void Operation::Comment(QString c)
{
    f_Comment = c;
}

QString Operation::Comment()
{
    return f_Comment;
}
