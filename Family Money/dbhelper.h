#ifndef DBHELPER_H
#define DBHELPER_H

#include <QtSql/QtSql>
#include "usertablehelper.h"
#include "user.h"
#include "category.h"
#include "product.h"
#include "incomecategory.h"
#include "operation.h"

namespace Ui {
class dbHelper;
}

class dbHelper : public QObject
{
    Q_OBJECT

public:
    dbHelper();
    void dbConnect();
    void dbCreate();

private :
    QSqlDatabase db;
    const QString dbPath = QCoreApplication::applicationDirPath() + "/DB.db";

public slots:
    void authCheck(QString, QString);
    void dbCheck();
    void dbLoadUser();
    void dbAddUser(User);
    void dbLoadEditedUser(QString);
    void dbEditUser(User);
    void dbLoadCategoryTable();
    void dbAddCategory(Category);
    void dbEditCategory(Category);
    void dbLoadProductTable();
    void dbLoadCategoryVector();
    void dbAddProduct(Product);
    void dbEditProduct(Product);
    void dbLoadIncomeCategoryTable();
    void dbAddIncomeCategory(IncomeCategory);
    void dbEditIncomeCategory(IncomeCategory);
    void dbLoadOperationTable(int);

signals:
    void loginResult(bool, int);
    void returnUserResult(UserTableHelper);
    void returnAddUserResult(bool, QString);
    void returnEditedUserResult(User);
    void returnEditUserResult(bool, QString);
    void returnCategoryTable(QVector<Category>);
    void returnAddCategoryResult(bool, QString);
    void returnEditCategoryResult(bool, QString);
    void returnProductTable(QVector<Product>);
    void returnCategoryVector(QVector<Category>);
    void returnAddProductResult(bool, QString);
    void returnEditProductResult(bool, QString);
    void returnIncomeCategoryTable(QVector<IncomeCategory>);
    void returnAddIncomeCategoryResult(bool, QString);
    void returnEditIncomeCategoryResult(bool,QString);
    void returnOperationTable(QVector<Operation>, int);
};

#endif // DBHELPER_H
