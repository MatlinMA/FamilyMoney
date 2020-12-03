#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);   

    qRegisterMetaType<User>();
    qRegisterMetaType<QVector<Operation>>();
    qRegisterMetaType<UserTableHelper>();
    qRegisterMetaType<QVector<Category>>();
    qRegisterMetaType<QVector<Product>>();
    qRegisterMetaType<QVector<IncomeCategory>>();
    ui_addUser = new adduser_window();
    ui_editUser = new edituser_window();
    ui_addCategory = new addcategory_window();
    ui_editCategory = new editcategory_window();
    ui_addProduct = new addproduct_window();
    ui_editProduct = new editproduct_window();
    ui_addIncomeCategory = new addincomecategory_window();
    ui_editIncomeCategory = new editincomecategory_window();
    ui_addOperation = new addoperation_window();
    QThread *qt = new QThread;
    qt->start();
    db->moveToThread(qt);

    QObject::connect(&ui_Auth, SIGNAL(authSend(QString, QString)), db, SLOT(authCheck(QString, QString)),Qt::QueuedConnection); //авторизация
    QObject::connect(db, SIGNAL(loginResult(bool, int)), this, SLOT(authResult(bool, int)),Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(startProgram()), db, SLOT(dbCheck()), Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(loginError()), &ui_Auth, SLOT(uiLoginError()), Qt::QueuedConnection);

    QObject::connect(this, SIGNAL(loadUserTable()), db, SLOT(dbLoadUser()), Qt::QueuedConnection); //вкладка пользователей
    QObject::connect(db, SIGNAL(returnUserResult(UserTableHelper)), this, SLOT(userTableResult(UserTableHelper)), Qt::QueuedConnection);
    QObject::connect(ui_addUser, SIGNAL(addUser(User)), db, SLOT(dbAddUser(User)), Qt::QueuedConnection);
    QObject::connect(db, SIGNAL(returnAddUserResult(bool,QString)), ui_addUser, SLOT(userAdded(bool,QString)) ,Qt::QueuedConnection);
    QObject::connect(this, SIGNAL(loadUserInfo(QString)), db, SLOT(dbLoadEditedUser(QString)), Qt::QueuedConnection);
    QObject::connect(db, SIGNAL(returnEditedUserResult(User)), ui_editUser, SLOT(userEditResult(User)), Qt::QueuedConnection);
    QObject::connect(ui_editUser, SIGNAL(editUser(User)), db, SLOT(dbEditUser(User)), Qt::QueuedConnection);
    QObject::connect(db, SIGNAL(returnEditUserResult(bool, QString)), ui_editUser, SLOT(userEdited(bool, QString)), Qt::QueuedConnection);

    QObject::connect(this, SIGNAL(loadCategoryTable()), db, SLOT(dbLoadCategoryTable()), Qt::QueuedConnection); //вкладка категорий товаров
    QObject::connect(db, SIGNAL(returnCategoryTable(QVector<Category>)), this, SLOT(categoryTableResult(QVector<Category>)), Qt::QueuedConnection);
    QObject::connect(ui_addCategory, SIGNAL(addCategory(Category)), db, SLOT(dbAddCategory(Category)), Qt::QueuedConnection);
    QObject::connect(db, SIGNAL(returnAddCategoryResult(bool,QString)), ui_addCategory, SLOT(categoryAdded(bool,QString)) ,Qt::QueuedConnection);
    QObject::connect(ui_editCategory, SIGNAL(editCategory(Category)), db, SLOT(dbEditCategory(Category)) ,Qt::QueuedConnection);
    QObject::connect(db, SIGNAL(returnEditCategoryResult(bool,QString)), ui_editCategory, SLOT(categoryEdited(bool,QString)) ,Qt::QueuedConnection);

    QObject::connect(this, SIGNAL(loadProductTable()), db, SLOT(dbLoadProductTable()) ,Qt::QueuedConnection); //вкладка товаров
    QObject::connect(db, SIGNAL(returnProductTable(QVector<Product>)), this, SLOT(productTableResult(QVector<Product>)), Qt::QueuedConnection);
    QObject::connect(ui_addProduct, SIGNAL(loadCategoryVector()), db, SLOT(dbLoadCategoryVector()) ,Qt::QueuedConnection);
    QObject::connect(db, SIGNAL(returnCategoryVector(QVector<Category>)), ui_addProduct, SLOT(putCategories(QVector<Category>)), Qt::QueuedConnection);
    QObject::connect(ui_addProduct, SIGNAL(addProduct(Product)), db, SLOT(dbAddProduct(Product)), Qt::QueuedConnection);
    QObject::connect(db, SIGNAL(returnAddProductResult(bool,QString)), ui_addProduct, SLOT(productAdded(bool,QString)) ,Qt::QueuedConnection);
    QObject::connect(ui_editProduct, SIGNAL(loadCategoryVector()), db, SLOT(dbLoadCategoryVector()) ,Qt::QueuedConnection);
    QObject::connect(db, SIGNAL(returnCategoryVector(QVector<Category>)), ui_editProduct, SLOT(putCategories(QVector<Category>)), Qt::QueuedConnection);
    QObject::connect(ui_editProduct, SIGNAL(editProduct(Product)), db, SLOT(dbEditProduct(Product)), Qt::QueuedConnection);
    QObject::connect(db, SIGNAL(returnEditProductResult(bool,QString)), ui_editProduct, SLOT(productEdited(bool,QString)), Qt::QueuedConnection);

    QObject::connect(this, SIGNAL(loadIncomeCategoryTable()), db, SLOT(dbLoadIncomeCategoryTable()), Qt::QueuedConnection); //вкладка категорий доходов
    QObject::connect(db, SIGNAL(returnIncomeCategoryTable(QVector<IncomeCategory>)), this, SLOT(incomeCategoryTableResult(QVector<IncomeCategory>)), Qt::QueuedConnection);
    QObject::connect(ui_addIncomeCategory, SIGNAL(addIncomeCategory(IncomeCategory)), db, SLOT(dbAddIncomeCategory(IncomeCategory)), Qt::QueuedConnection);
    QObject::connect(db, SIGNAL(returnAddIncomeCategoryResult(bool,QString)), ui_addIncomeCategory, SLOT(incomeCategoryAdded(bool,QString)) ,Qt::QueuedConnection);
    QObject::connect(ui_editIncomeCategory, SIGNAL(editIncomeCategory(IncomeCategory)), db, SLOT(dbEditIncomeCategory(IncomeCategory)) ,Qt::QueuedConnection);
    QObject::connect(db, SIGNAL(returnEditIncomeCategoryResult(bool,QString)), ui_editIncomeCategory, SLOT(incomeCategoryEdited(bool,QString)) ,Qt::QueuedConnection);

    QObject::connect(this, SIGNAL(loadOperationTable(int)), db, SLOT(dbLoadOperationTable(int)), Qt::QueuedConnection);
    QObject::connect(db, SIGNAL(returnOperationTable(QVector<Operation>, int)), this, SLOT(incomeOperationTableResult(QVector<Operation>, int)), Qt::QueuedConnection);


    ui->userTable->setColumnCount(4);
    ui->userTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->userTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->categoryTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->categoryTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->productTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->productTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->incomeCategoryTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->incomeCategoryTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_currentChanged(int index) //смена страницы меню
{
    if (index == 0) //Операции
    {
        ui->operationTable->setRowCount(0);
        emit loadOperationTable(operationPage);
    }
    if (index == 1) //Пользователи
    {
        ui->userTable->setRowCount(0);
        emit loadUserTable();
    }
    if (index == 2) //Товары
    {
        ui->productTableWidget->setRowCount(0);
        emit loadProductTable();
    }
    if (index == 3) //Категории товаров
    {
        ui->categoryTableWidget->setRowCount(0);
        ui->categoryCounter->clear();
        emit loadCategoryTable();
    }
    if (index == 4) //Категории дохода
    {
        ui->incomeCategoryTableWidget->setRowCount(0);
        ui->incomeCategoryCounter->clear();
        emit loadIncomeCategoryTable();
    }
}

void MainWindow::display() //Вывод окна авторизации
{
    ui_Auth.show();
    emit startProgram();
}

void MainWindow::authResult(bool result, int id) //Проверка при авторизации
{
    if (result == true)
    {
        idCurrentUser = id;
        this->show();
        ui_Auth.close();
        emit loadOperationTable(operationPage);
    }
    else
    {
        emit loginError();
    }
}

void MainWindow::userTableResult(UserTableHelper tableHelper) //Заполнение таблицы пользователей после обновления страницы
{
    int i = 0;

    while(i < tableHelper.UserVector.length() && i < 500)
    {
        ui->userTable->setRowCount(i+1);
        for (int j = 0; j < 4; j++)
        {
            ui->userTable->setItem(i, j, new QTableWidgetItem());
        }
        ui->userTable->item(i,0)->setText(tableHelper.UserVector[i].Name());
        ui->userTable->item(i,1)->setText(QString::number(tableHelper.UserVector[i].Age()));
        ui->userTable->item(i,2)->setText(tableHelper.UserVector[i].Gender());
        ui->userTable->item(i,3)->setText(QString::number(tableHelper.UserVector[i].Id()));
        i++;
    }

    ui->userTable->setColumnHidden(3, true);
    ui->userTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->userTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->userTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    userTablePage = 0;

    QString firstPart = QString::number((userTablePage * 500) + 1);
    QString secondPart;

    if (tableHelper.UserVector.length() > (userTablePage+1)*500)
        secondPart = QString::number((userTablePage+1)*500);
    else
        secondPart = QString::number(tableHelper.UserVector.length());

    ui->pageNumberUser->setText(firstPart + " - " + secondPart);

    *userTableData = tableHelper;
}

void MainWindow::categoryTableResult(QVector<Category> v) //Заполнение таблицы категорий после обновления страницы
{
    ui->categoryTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->categoryTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    Category c;
    foreach(c, v)
    {
        ui->categoryTableWidget->setRowCount(ui->categoryTableWidget->rowCount()+1);

        ui->categoryTableWidget->setItem(ui->categoryTableWidget->rowCount()-1, 0, new QTableWidgetItem(c.Name()));
        ui->categoryTableWidget->setItem(ui->categoryTableWidget->rowCount()-1, 1, new QTableWidgetItem(QString::number(c.Id())));
    }
    ui->categoryCounter->setText("Всего категорий: " + QString::number(ui->categoryTableWidget->rowCount()));
    ui->categoryTableWidget->setColumnHidden(1, true);
}

void MainWindow::productTableResult(QVector<Product> products) //Заполнение таблицы товаров после обновления страницы
{
    ui->productTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->productTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    Product p;

    foreach(p, products)
    {
        ui->productTableWidget->setRowCount(ui->productTableWidget->rowCount()+1);

        ui->productTableWidget->setItem(ui->productTableWidget->rowCount()-1, 0, new QTableWidgetItem(p.Name()));
        ui->productTableWidget->setItem(ui->productTableWidget->rowCount()-1, 1, new QTableWidgetItem(p.CategoryName()));
        ui->productTableWidget->setItem(ui->productTableWidget->rowCount()-1, 2, new QTableWidgetItem(QString::number(p.Id())));
        ui->productTableWidget->setItem(ui->productTableWidget->rowCount()-1, 3, new QTableWidgetItem(QString::number(p.IdCategory())));
    }
    ui->productCounter->setText("Всего товаров: " + QString::number(ui->productTableWidget->rowCount()));

    ui->productTableWidget->setColumnHidden(2, true);
    ui->productTableWidget->setColumnHidden(3, true);
}

void MainWindow::incomeCategoryTableResult(QVector<IncomeCategory> v) //Заполнение таблицы категорий дохода после обновления страницы
{
    ui->incomeCategoryTableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->incomeCategoryTableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    IncomeCategory c;
    foreach(c, v)
    {
        ui->incomeCategoryTableWidget->setRowCount(ui->incomeCategoryTableWidget->rowCount()+1);

        ui->incomeCategoryTableWidget->setItem(ui->incomeCategoryTableWidget->rowCount()-1, 0, new QTableWidgetItem(c.Name()));
        ui->incomeCategoryTableWidget->setItem(ui->incomeCategoryTableWidget->rowCount()-1, 1, new QTableWidgetItem(QString::number(c.Id())));
    }
    ui->incomeCategoryCounter->setText("Всего категорий дохода: " + QString::number(ui->incomeCategoryTableWidget->rowCount()));
    ui->incomeCategoryTableWidget->setColumnHidden(1, true);
}

void MainWindow::incomeOperationTableResult(QVector<Operation> v, int p) //Заполнение таблицы операций после обновления страницы
{
    operationPage = p;

    for (int i = 0; i < 6; i++)
        ui->operationTable->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);

    Operation o;
    foreach (o, v)
    {
        ui->operationTable->setRowCount(ui->operationTable->rowCount()+1);

        ui->operationTable->setItem(ui->operationTable->rowCount()-1, 0, new QTableWidgetItem(o.Date()));
        ui->operationTable->setItem(ui->operationTable->rowCount()-1, 1, new QTableWidgetItem(QString::number(o.Sum())));
        ui->operationTable->setItem(ui->operationTable->rowCount()-1, 2, new QTableWidgetItem(o.ProductName()));
        if (o.IncomeCategoryName() == "")
            ui->operationTable->setItem(ui->operationTable->rowCount()-1, 3, new QTableWidgetItem(o.ProductCategoryName()));
        if (o.ProductCategoryName() == "")
            ui->operationTable->setItem(ui->operationTable->rowCount()-1, 3, new QTableWidgetItem(o.IncomeCategoryName()));
        ui->operationTable->setItem(ui->operationTable->rowCount()-1, 4, new QTableWidgetItem(o.UserName()));
        ui->operationTable->setItem(ui->operationTable->rowCount()-1, 5, new QTableWidgetItem(o.Comment()));
        ui->operationTable->setItem(ui->operationTable->rowCount()-1, 6, new QTableWidgetItem(QString::number(o.Id())));
        ui->operationTable->setItem(ui->operationTable->rowCount()-1, 7, new QTableWidgetItem(QString::number(o.IdUser())));
        ui->operationTable->setItem(ui->operationTable->rowCount()-1, 8, new QTableWidgetItem(QString::number(o.IdProduct())));
        ui->operationTable->setItem(ui->operationTable->rowCount()-1, 9, new QTableWidgetItem(QString::number(o.IdProductCategory())));
        ui->operationTable->setItem(ui->operationTable->rowCount()-1, 10, new QTableWidgetItem(QString::number(o.IdIncomeCategory())));
    }

    if (p == 0)
        ui->pageNumberOperation->setText("0");
    else
        ui->pageNumberOperation->setText(QString::number(p * 500 + 1) + " - " + QString::number(p * 500 + v.length()));

    for (int i = 6; i < 11; i++)
        ui->operationTable->setColumnHidden(i, true);
}

void MainWindow::on_addUser_clicked() //Вызов окна добавления пользователя
{
    ui_addUser->show();
}

void MainWindow::on_editUser_clicked() //Редактирование пользователя
{
    if (ui->userTable->item(ui->userTable->currentRow(), 3) != nullptr)
        emit loadUserInfo(ui->userTable->item(ui->userTable->currentRow(), 3)->text());
}

void MainWindow::on_deleteUser_clicked() //Удаление пользователя
{

}

void MainWindow::on_nextPageUser_clicked() //Следующая страница пользователей
{
    if (userTableData->Pages() > userTablePage)
    {
        ui->userTable->setRowCount(0);
        int i = 0;
        while(i < (userTableData->UserVector.length() - (userTablePage+1)*500) && i < 500)
        {
            ui->userTable->setRowCount(i+1);
            ui->userTable->setItem(i, 0, new QTableWidgetItem(userTableData->UserVector[i + ((userTablePage + 1) * 500)].Name()));
            ui->userTable->setItem(i, 1, new QTableWidgetItem(QString::number(userTableData->UserVector[i + ((userTablePage + 1) * 500)].Age())));
            ui->userTable->setItem(i, 2, new QTableWidgetItem(userTableData->UserVector[i + ((userTablePage + 1) * 500)].Gender()));
            ui->userTable->setItem(i, 3, new QTableWidgetItem(QString::number(userTableData->UserVector[i + ((userTablePage + 1) * 500)].Id())));
            i++;
        }
        userTablePage++;

        QString firstPart = QString::number((userTablePage * 500) + 1);
        QString secondPart;

        if (userTableData->UserVector.length() > (userTablePage+1)*500)
            secondPart = QString::number((userTablePage+1)*500);
        else
            secondPart = QString::number(userTableData->UserVector.length());

        ui->pageNumberUser->setText(firstPart + " - " + secondPart);
    }
}

void MainWindow::on_lastPageUser_clicked() //Последняя страница пользователей
{
    if (userTableData->Pages() != userTablePage)
    {
        ui->userTable->setRowCount(0);
        int i = 0;
        while(i < (userTableData->UserVector.length() - (userTableData->Pages() * 500)))
        {
            ui->userTable->setRowCount(i+1);
            ui->userTable->setItem(i, 0, new QTableWidgetItem(userTableData->UserVector[i + (userTableData->Pages() * 500)].Name()));
            ui->userTable->setItem(i, 1, new QTableWidgetItem(QString::number(userTableData->UserVector[i + (userTableData->Pages() * 500)].Age())));
            ui->userTable->setItem(i, 2, new QTableWidgetItem(userTableData->UserVector[i + (userTableData->Pages() * 500)].Gender()));
            ui->userTable->setItem(i, 3, new QTableWidgetItem(QString::number(userTableData->UserVector[i + (userTableData->Pages() * 500)].Id())));
            i++;
        }
        userTablePage = userTableData->Pages();

        QString firstPart = QString::number((userTablePage * 500) + 1);
        QString secondPart;

        if (userTableData->UserVector.length() > (userTablePage+1)*500)
            secondPart = QString::number((userTablePage+1)*500);
        else
            secondPart = QString::number(userTableData->UserVector.length());

        ui->pageNumberUser->setText(firstPart + " - " + secondPart);
    }
}

void MainWindow::on_prevPageUser_clicked() //Предыдущая страница пользователей
{
    if (userTablePage > 0)
    {
        ui->userTable->setRowCount(0);
        int i = 0;
        while (i < (userTableData->UserVector.length() - (userTablePage - 1) * 500) && i < 500)
        {
            ui->userTable->setRowCount(i+1);
            ui->userTable->setItem(i, 0, new QTableWidgetItem(userTableData->UserVector[i + ((userTablePage - 1) * 500)].Name()));
            ui->userTable->setItem(i, 1, new QTableWidgetItem(QString::number(userTableData->UserVector[i + ((userTablePage - 1) * 500)].Age())));
            ui->userTable->setItem(i, 2, new QTableWidgetItem(userTableData->UserVector[i + ((userTablePage - 1) * 500)].Gender()));
            ui->userTable->setItem(i, 3, new QTableWidgetItem(QString::number(userTableData->UserVector[i + ((userTablePage - 1) * 500)].Id())));
            i++;
        }
        userTablePage--;

        QString firstPart = QString::number((userTablePage * 500) + 1);
        QString secondPart;

        if (userTableData->UserVector.length() > (userTablePage+1)*500)
            secondPart = QString::number((userTablePage+1)*500);
        else
            secondPart = QString::number(userTableData->UserVector.length());

        ui->pageNumberUser->setText(firstPart + " - " + secondPart);
    }
}

void MainWindow::on_firstPageUser_clicked() //Первая страница пользователей
{
    if (userTablePage > 0)
    {
        ui->userTable->setRowCount(0);
        int i = 0;
        while (i < userTableData->UserVector.length() && i < 500)
        {
            ui->userTable->setRowCount(i+1);
            ui->userTable->setItem(i, 0, new QTableWidgetItem(userTableData->UserVector[i].Name()));
            ui->userTable->setItem(i, 1, new QTableWidgetItem(QString::number(userTableData->UserVector[i].Age())));
            ui->userTable->setItem(i, 2, new QTableWidgetItem(userTableData->UserVector[i].Gender()));
            ui->userTable->setItem(i, 3, new QTableWidgetItem(QString::number(userTableData->UserVector[i].Id())));
            i++;
        }
    }
    userTablePage = 0;

    QString firstPart = QString::number((userTablePage * 500) + 1);
    QString secondPart;

    if (userTableData->UserVector.length() > (userTablePage+1)*500)
        secondPart = QString::number((userTablePage+1)*500);
    else
        secondPart = QString::number(userTableData->UserVector.length());

    ui->pageNumberUser->setText(firstPart + " - " + secondPart);
}

void MainWindow::on_addCategory_clicked() //вызов окна добавление категории
{
    ui_addCategory->show();
}

void MainWindow::on_editCategory_clicked() //вызов окна редактирования категории
{
    if (ui->categoryTableWidget->currentItem() != nullptr)
    {
        Category c;
        c.Id(ui->categoryTableWidget->item(ui->categoryTableWidget->currentRow(), 1)->text().toInt());
        c.Name(ui->categoryTableWidget->item(ui->categoryTableWidget->currentRow(), 0)->text());
        ui_editCategory->showWithString(c);
    }
}

void MainWindow::on_addProduct_clicked() //вызов окна добавления товара
{
    ui_addProduct->showClear();
}

void MainWindow::on_editProduct_clicked() //вызов окна редактирования товара
{
    if (ui->productTableWidget->item(ui->productTableWidget->currentRow(), 1) != nullptr)
    {
        Product p;
        p.Name(ui->productTableWidget->item(ui->productTableWidget->currentRow(), 0)->text());
        p.CategoryName(ui->productTableWidget->item(ui->productTableWidget->currentRow(), 1)->text());
        p.Id(ui->productTableWidget->item(ui->productTableWidget->currentRow(), 2)->text().toInt());
        p.IdCategory(ui->productTableWidget->item(ui->productTableWidget->currentRow(), 3)->text().toInt());
        ui_editProduct->showPage(p);
    }
}

void MainWindow::on_addIncomeCategory_clicked() //вызов окна добавления категории дохода
{
    ui_addIncomeCategory->showClear();
}

void MainWindow::on_editIncomeCategory_clicked() //вызов окна редактирования категории дохода
{
    if (ui->incomeCategoryTableWidget->currentItem() != nullptr)
    {
        IncomeCategory c;
        c.Id(ui->incomeCategoryTableWidget->item(ui->incomeCategoryTableWidget->currentRow(), 1)->text().toInt());
        c.Name(ui->incomeCategoryTableWidget->item(ui->incomeCategoryTableWidget->currentRow(), 0)->text());
        ui_editIncomeCategory->showWithString(c);
    }
}

void MainWindow::on_nextPageOperation_clicked() //Следующая страница операций
{
    operationPage ++;
    emit loadOperationTable(operationPage);
}

void MainWindow::on_lastPageOperation_clicked() //Последняя страница
{
    operationPage = 2147483647;
    emit loadOperationTable(operationPage);
}

void MainWindow::on_prevPageOperation_clicked() //Предыдущая страница
{
    if (operationPage > 0)
        operationPage--;
    emit loadOperationTable(operationPage);
}

void MainWindow::on_firstPageOperation_clicked() //Первая страница
{
    operationPage = 0;
    emit loadOperationTable(operationPage);
}

void MainWindow::on_addOperation_clicked() //вызов окна добавления операции
{
    ui_addOperation->showClear(idCurrentUser);
}
