#ifndef OPERATION_H
#define OPERATION_H

#include <QObject>

class Operation
{
public:
    Operation();
    void Id(int id);
    int Id();
    void IdUser(int u);
    int IdUser();
    void IdProduct(int p);
    int IdProduct();
    void IdProductCategory(int c);
    int IdProductCategory();
    void IdIncomeCategory(int c);
    int IdIncomeCategory();
    void Sum(int s);
    int Sum();
    void Date(QString d);
    QString Date();
    void UserName(QString n);
    QString UserName();
    void ProductName(QString n);
    QString ProductName();
    void ProductCategoryName(QString n);
    QString ProductCategoryName();
    void IncomeCategoryName(QString n);
    QString IncomeCategoryName();
    void Comment(QString c);
    QString Comment();

private:
    int f_Id;
    int f_IdUser;
    int f_IdProduct;
    int f_IdProductCategory;
    int f_IdIncomeCategory;
    int f_Sum;
    QString f_Date;
    QString f_UserName;
    QString f_ProductName;
    QString f_ProductCategoryName;
    QString f_IncomeCategoryName;
    QString f_Comment;
};
Q_DECLARE_METATYPE(Operation)

#endif // OPERATION_H
