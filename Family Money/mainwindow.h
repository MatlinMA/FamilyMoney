#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "auth_window.h"
#include <QString>
#include <QtDebug>
#include "dbhelper.h"
#include <QVector>
#include "usertablehelper.h"
#include "adduser_window.h"
#include "edituser_window.h"
#include "addcategory_window.h"
#include "editcategory_window.h"
#include "addproduct_window.h"
#include "editproduct_window.h"
#include "addincomecategory_window.h"
#include "editincomecategory_window.h"
#include "addoperation_window.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void display();

private:
    Ui::MainWindow *ui;
    auth_window ui_Auth; //окно авторизации
    adduser_window *ui_addUser; //окно добавления пользователя
    edituser_window *ui_editUser; //окно редактирования пользователя
    editcategory_window *ui_editCategory; //окно редактирования категории
    dbHelper *db = new dbHelper(); //помощник для работы с БД в отдельном потоке
    int userTablePage = 0; //текущая страница в таблице пользователей
    addcategory_window *ui_addCategory; //окно добавления категории
    addproduct_window *ui_addProduct; //окно добавления товара
    editproduct_window *ui_editProduct; //окно редактирования товара
    addincomecategory_window *ui_addIncomeCategory; //окно добавления категории дохода
    editincomecategory_window *ui_editIncomeCategory; //окно редактирования категории дохода
    addoperation_window *ui_addOperation; // окно добавления операции
    UserTableHelper *userTableData = new UserTableHelper();
    int idCurrentUser;
    int operationPage = 0;

public slots:
    void authResult(bool, int);
    void userTableResult(UserTableHelper); //Заполнение таблицы пользователей
    void categoryTableResult(QVector<Category> v); //Заполнение таблицы категориями
    void productTableResult(QVector<Product> v); //Заполнение таблицы продуктами
    void incomeCategoryTableResult(QVector<IncomeCategory> v); //Заполнение таблицы категорий доходов
    void incomeOperationTableResult(QVector<Operation>, int); //Заполнение таблицы операций

signals:
    void startProgram();
    void loginError();
    void loadUserTable();
    void loadUserInfo(QString);
    void loadCategoryTable();
    void loadProductTable();
    void loadIncomeCategoryTable();

    //сигналы таблицы операций
    void loadOperationTable(int);

private slots:
    void on_addUser_clicked();
    void on_editUser_clicked();
    void on_deleteUser_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_nextPageUser_clicked();
    void on_lastPageUser_clicked();
    void on_prevPageUser_clicked();
    void on_firstPageUser_clicked();
    void on_addCategory_clicked();
    void on_editCategory_clicked();
    void on_addProduct_clicked();
    void on_editProduct_clicked();
    void on_addIncomeCategory_clicked();
    void on_editIncomeCategory_clicked();
    void on_nextPageOperation_clicked();
    void on_lastPageOperation_clicked();
    void on_prevPageOperation_clicked();
    void on_firstPageOperation_clicked();
    void on_addOperation_clicked();
};

#endif // MAINWINDOW_H
