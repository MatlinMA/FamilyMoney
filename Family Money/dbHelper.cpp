#include "dbhelper.h"
#include <QtDebug>
#include <QDebug>

dbHelper::dbHelper()
{}

void dbHelper::dbConnect()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);
    db.open();
}

void dbHelper::dbCreate()
{
    dbConnect();

    QSqlQuery query;
    //тут запросы в sql
    query.exec("CREATE TABLE User ("
               "Id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
               "Login TEXT NOT NULL UNIQUE,"
               "Password TEXT NOT NULL,"
               "Name TEXT NOT NULL,"
               "Age INTEGER NOT NULL,"
               "Gender INTEGER NOT NULL," //0 - Женщина, 1 - Мужчина
               "Status INTEGER NOT NULL);"); //0 - Пользователь удалён, 1 - Пользователь активен

    query.exec("CREATE TABLE ProductCategory ("
               "Id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
               "Name Text NOT NULL,"
               "Status INTEGER NOT NULL);"); //0 - Категория удалена, 1 - Категория активна

    query.exec("CREATE TABLE Product ("
               "Id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
               "IdCategory INTEGER NOT NULL,"
               "Name TEXT NOT NULL,"
               "Status INTEGER NOT NULL," //0 - Товар удалён, 1 - Товар активен
               "FOREIGN KEY (IdCategory) REFERENCES ProductCategory(Id));");

    query.exec("CREATE TABLE IncomeCategory ("
               "Id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
               "Name Text NOT NULL,"
               "Status INTEGER NOT NULL);"); //0 - Категория удалена, 1 - Категория активна

    query.exec("CREATE TABLE Operation ("
               "Id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
               "IdUser INTEGER NOT NULL,"
               "IdProduct INTEGER CHECK(IdIncomeCategory IS NULL),"
               "IdProductCategory INTEGER CHECK(IdIncomeCategory IS NULL),"
               "IdIncomeCategory INTEGER CHECK(IdProductCategory IS NULL),"
               "Sum INTEGER NOT NULL,"
               "Date TEXT NOT NULL,"
               "Comment TEXT,"
               "Status INTEGER NOT NULL,"
               "FOREIGN KEY (IdUser) REFERENCES User(Id),"
               "FOREIGN KEY (IdProduct) REFERENCES Product(Id),"
               "FOREIGN KEY (IdIncomeCategory) REFERENCES IncomeCategory(Id));");

    query.exec("INSERT INTO User (Login, Password, Name, Age, Gender, Status) "
               "VALUES ('admin', 'admin', 'admin', 1, 1, 1);");

    for(int i = 0; i < 505; i++)
    query.exec("INSERT INTO User (Login, Password, Name, Age, Gender, Status) "
               "VALUES ('" + QString::number(i) + "admin', 'admin', '" + QString::number(i) + "admin', 1, 1, 1);");

    for(int i = 0; i < 50; i++)
    query.exec("INSERT INTO ProductCategory (Name, Status) "
               "VALUES ('" + QString::number(i) + "TestCategory', 1);");

    for(int i = 0; i < 10; i++)
    query.exec("INSERT INTO Operation (IdUser, IdCategory, Date, Status) "
               "VALUES (0, 0, 1, 1);");
}

void dbHelper::dbCheck()
{
    if (QFile(dbPath).exists())
    {
        dbConnect();
    }
    else
    {
        dbCreate();   
    }
}

void dbHelper::authCheck(QString login, QString password)
{
    QSqlQuery query(db);
    if (query.exec("SELECT EXISTS(SELECT Login, Password FROM User WHERE Login = '" + login + "' AND Password = '" + password + "' LIMIT 1);"))
    {
        query.next();
        if (query.record().value(0).toInt() == 1)
            if (query.exec("SELECT Id FROM User WHERE Login = '" + login + "';"))
            {
                query.next();
                emit loginResult(true, query.value(0).toInt());
            }
        else
            emit loginResult(false, 0);
    }
}

void dbHelper::dbLoadUser()
{
    QSqlQuery query;
    if (query.exec("SELECT Id, Name, Age, Gender FROM User WHERE Status = 1 ORDER BY Name;"))
    {
        UserTableHelper *userTable = new UserTableHelper();
        User tempUser;
        while(query.next())
        {
            tempUser.Id(query.value(0).toInt());//Id
            tempUser.Name(query.value(1).toString());//Name
            tempUser.Age(query.value(2).toInt());//Age
            tempUser.Gender(query.value(3).toInt());//Gender
            userTable->UserVector.append(tempUser);
        }
        userTable->Pages(userTable->UserVector.length()/500);
        emit returnUserResult(*userTable);
        delete userTable;
    }
}

void dbHelper::dbAddUser(User user)
{
    QSqlQuery query;
    if (query.exec("SELECT EXISTS(SELECT Login, Password FROM User WHERE Login = '" + user.Login() + "' LIMIT 1);"))
    {
        query.next();
        if (query.record().value(0).toInt() == 1)
            emit returnAddUserResult(false, "Пользователь с таким логином уже существует!"); //ошибка повторяющегося логина

        else
        {
            int gender;
            if (user.Gender() == "М")
                gender = 1;
            if (user.Gender() == "Ж")
                gender = 0;

            QString usrCreating = "INSERT INTO User (Login, Password, Name, Age, Gender, Status) "
                                  "VALUES ('" + user.Login() + "', '" + user.Password() + "', '" + user.Name() + "', " + QString::number(user.Age()) + ", " + QString::number(gender) + ", 1);";

            if (query.exec(usrCreating))
                emit returnAddUserResult(true, "Пользователь успешно создан!"); //успешное создание пользователя

            else
                emit returnAddUserResult(false, "Ошибка создания пользователя в БД!"); //ошибка запроса в БД
        }
    }
}

void dbHelper::dbLoadEditedUser(QString id)
{
    QSqlQuery query;
    if (query.exec("SELECT Id, Login, Name, Age, Gender FROM User WHERE Id = " + id))
    {
        User tempUser;
        while(query.next())
        {
            tempUser.Id(query.value(0).toInt());//Id
            tempUser.Login(query.value(1).toString());//Login
            tempUser.Name(query.value(2).toString());//Name
            tempUser.Age(query.value(3).toInt());//Age
            tempUser.Gender(query.value(4).toInt());//Gender
        }
        emit returnEditedUserResult(tempUser);
    }
}

void dbHelper::dbEditUser(User usr)
{
    QSqlQuery query;

    int gender;
    if (usr.Gender() == "М")
        gender = 1;
    if (usr.Gender() == "Ж")
        gender = 0;

    QString usrEditing = "UPDATE User SET Login = '" + usr.Login() + "', Password = '" + usr.Password() + "', Name = '" + usr.Name() + "',"
                         " Age = " + QString::number(usr.Age()) + ", Gender = " + QString::number(gender) + ", Status = 1 "
                         "WHERE Id = " + QString::number(usr.Id());

    if (query.exec(usrEditing))
        emit returnEditUserResult(true, "Пользователь успешно изменён!"); //успешное изменение пользователя

    else
        emit returnEditUserResult(false, "Ошибка изменения пользователя в БД!"); //ошибка запроса в БД
}

void dbHelper::dbLoadCategoryTable()
{
    QVector<Category> categories;

    QSqlQuery query;
    if (query.exec("SELECT Id, Name FROM ProductCategory WHERE Status = 1 ORDER BY Name"))
    {
        Category tempCategory;
        while(query.next())
        {
            tempCategory.Id(query.value(0).toInt());
            tempCategory.Name(query.value(1).toString());
            categories.append(tempCategory);
        }
        emit returnCategoryTable(categories);
    }
}

void dbHelper::dbAddCategory(Category c)
{
    QSqlQuery query;
    if (query.exec("SELECT EXISTS(SELECT Name FROM ProductCategory WHERE Name = '" + c.Name() + "' LIMIT 1);"))
    {
        query.next();
        if (query.record().value(0).toInt() == 1)
            emit returnAddCategoryResult(false, "Категория с таким названием уже существует!"); //ошибка повторяющегося названия

        else
        {
            QString categoryCreating = "INSERT INTO ProductCategory (Name, Status) "
                                  "VALUES ('" + c.Name() + "', 1);";

            if (query.exec(categoryCreating))
                emit returnAddCategoryResult(true, "Категория успешно создана!"); //успешное создание категории

            else
                emit returnAddCategoryResult(false, "Ошибка создания категории в БД!"); //ошибка запроса в БД
        }
    }
}

void dbHelper::dbEditCategory(Category c)
{
    QSqlQuery query;

    QString categoryEditing = "UPDATE ProductCategory SET Name = '" + c.Name() + "', Status = 1 WHERE Id = " + QString::number(c.Id());

    if (query.exec(categoryEditing))
        emit returnEditCategoryResult(true, "Категория успешно изменена!"); //успешное изменение пользователя

    else
        emit returnEditCategoryResult(false, "Ошибка изменения категории в БД!"); //ошибка запроса в БД
}

void dbHelper::dbLoadProductTable()
{
    QVector<Product> products;

    QSqlQuery query;
    if (query.exec("SELECT Product.Id, IdCategory, Product.Name, ProductCategory.Name "
                   "FROM Product, ProductCategory WHERE ProductCategory.Id = IdCategory AND Product.Status = 1 "
                   "ORDER BY Product.Name"))
    {
        Product tempProduct;
        while(query.next())
        {
            tempProduct.Id(query.value(0).toInt());
            tempProduct.IdCategory(query.value(1).toInt());
            tempProduct.Name(query.value(2).toString());
            tempProduct.CategoryName(query.value(3).toString());
            products.append(tempProduct);
        }
        emit returnProductTable(products);
    }
}

void dbHelper::dbLoadCategoryVector()
{
    QVector<Category> categories;

    QSqlQuery query;

    if (query.exec("SELECT Id, Name FROM ProductCategory WHERE Status = 1 ORDER BY Name"))
    {

        Category tempCategory;

        while(query.next())
        {
            tempCategory.Id(query.value(0).toInt());
            tempCategory.Name(query.value(1).toString());
            categories.append(tempCategory);
        }

    emit returnCategoryVector(categories);
    }
}

void dbHelper::dbAddProduct(Product p)
{
    QSqlQuery query;
    if (query.exec("SELECT EXISTS(SELECT Name FROM Product WHERE Name = '" + p.Name() + "' LIMIT 1);"))
    {
        query.next();
        if (query.record().value(0).toInt() == 1)
            emit returnAddProductResult(false, "Товар с таким названием уже существует!"); //ошибка повторяющегося названия

        else
        {
            QString productCreating = "INSERT INTO Product (Name, IdCategory, Status) "
                                  "VALUES ('" + p.Name() + "', " + QString::number(p.IdCategory()) + " , 1);";

            if (query.exec(productCreating))
                emit returnAddProductResult(true, "Товар успешно создан!"); //успешное создание категории

            else
                emit returnAddProductResult(false, "Ошибка создания товара в БД!"); //ошибка запроса в БД
        }
    }
}

void dbHelper::dbEditProduct(Product p)
{
    QSqlQuery query;

    QString productEditing = "UPDATE Product SET Name = '" + p.Name() + "', IdCategory = " + QString::number(p.IdCategory()) + " WHERE Id = " + QString::number(p.Id());

    if (query.exec(productEditing))
        emit returnEditProductResult(true, "Товар успешно изменен!"); //успешное изменение пользователя

    else
        emit returnEditProductResult(false, "Ошибка изменения товара в БД!"); //ошибка запроса в БД
}

void dbHelper::dbLoadIncomeCategoryTable()
{
    QVector<IncomeCategory> incomeCategories;

    QSqlQuery query;
    if (query.exec("SELECT Id, Name FROM IncomeCategory WHERE Status = 1 ORDER BY Name"))
    {
        IncomeCategory tempIncomeCategory;
        while(query.next())
        {
            tempIncomeCategory.Id(query.value(0).toInt());
            tempIncomeCategory.Name(query.value(1).toString());
            incomeCategories.append(tempIncomeCategory);
        }
        emit returnIncomeCategoryTable(incomeCategories);
    }
}

void dbHelper::dbAddIncomeCategory(IncomeCategory c)
{
    QSqlQuery query;
    if (query.exec("SELECT EXISTS(SELECT Name FROM IncomeCategory WHERE Name = '" + c.Name() + "' LIMIT 1);"))
    {
        query.next();
        if (query.record().value(0).toInt() == 1)
            emit returnAddIncomeCategoryResult(false, "Категория дохода с таким названием уже существует!"); //ошибка повторяющегося названия

        else
        {
            QString categoryCreating = "INSERT INTO IncomeCategory (Name, Status) "
                                  "VALUES ('" + c.Name() + "', 1);";

            if (query.exec(categoryCreating))
                emit returnAddIncomeCategoryResult(true, "Категория дохода успешно создана!"); //успешное создание категории

            else
                emit returnAddIncomeCategoryResult(false, "Ошибка создания категории дохода в БД!"); //ошибка запроса в БД
        }
    }
}

void dbHelper::dbEditIncomeCategory(IncomeCategory c)
{
    QSqlQuery query;

    QString incomeCategoryEditing = "UPDATE IncomeCategory SET Name = '" + c.Name() + "', Status = 1 WHERE Id = " + QString::number(c.Id());

    if (query.exec(incomeCategoryEditing))
        emit returnEditIncomeCategoryResult(true, "Категория успешно изменена!"); //успешное изменение пользователя

    else
        emit returnEditIncomeCategoryResult(false, "Ошибка изменения категории в БД!"); //ошибка запроса в БД
}

void dbHelper::dbLoadOperationTable(int page)
{
    QSqlQuery query;

    if (query.exec("SELECT COUNT(*) FROM Operation WHERE Status = 1"))
    {

        query.next();

        QVector<Operation> Operations;
        Operation tempOperation;

        if ((query.value(0).toInt() / 500) < page)
            page = query.value(0).toInt() / 500;

        if (query.exec("SELECT Operation.Id, Operation.IdUser, Operation.IdProduct, Operation.IdProductCategory, "
                       "Operation.IdIncomeCategory, Operation.Sum, Operation.Date, User.Name, Product.Name, "
                       "ProductCategory.Name, IncomeCategory.Name, Operation.Comment "
                       "FROM Operation, User, Product, ProductCategory, IncomeCategory "
                       "WHERE (Operation.Status = 1) AND (User.Id = Operation.IdUser) AND (Product.Id = Operation.IdProduct) AND "
                       "(((Operation.IdProductCategory = ProductCategory.Id) AND (Operation.IdIncomeCategory = NULL)) OR "
                       "((Operation.IdIncomeCategory = IncomeCategory.Id) AND (Operation.IdProductCategory = NULL)))"
                       "ORDER BY Operation.Date DESC "
                       "LIMIT 500 OFFSET " + QString::number(page * 500)))
        {
            while(query.next())
            {
                tempOperation.Id(query.value(0).toInt());
                tempOperation.IdUser(query.value(1).toInt());
                tempOperation.IdProduct(query.value(2).toInt());
                tempOperation.IdProductCategory(query.value(3).toInt());
                tempOperation.IdIncomeCategory(query.value(4).toInt());
                tempOperation.Sum(query.value(5).toInt());
                tempOperation.Date(query.value(6).toString());
                tempOperation.UserName(query.value(7).toString());
                tempOperation.ProductName(query.value(8).toString());
                tempOperation.ProductCategoryName(query.value(9).toString());
                tempOperation.IncomeCategoryName(query.value(10).toString());
                tempOperation.Comment(query.value(11).toString());
                Operations.append(tempOperation);
            }
            emit returnOperationTable(Operations, page);
        }
    }
}
