#ifndef PRODUCT_H
#define PRODUCT_H

#include <QObject>

class Product
{
public:
    Product();
    void Id(int id);
    int Id();
    void Name(QString name);
    QString Name();
    void IdCategory(int idcat);
    int IdCategory();
    void CategoryName(QString catname);
    QString CategoryName();

private:
    int f_Id;
    QString f_Name;
    int f_IdCategory;
    QString f_CategoryName;
};
Q_DECLARE_METATYPE(Product)

#endif // PRODUCT_H
