#ifndef ADDPRODUCT_WINDOW_H
#define ADDPRODUCT_WINDOW_H

#include <QWidget>
#include "product.h"
#include "category.h"

namespace Ui {
class addproduct_window;
}

class addproduct_window : public QWidget
{
    Q_OBJECT

public:
    explicit addproduct_window(QWidget *parent = nullptr);
    ~addproduct_window();
    void showClear();

public slots:
    void putCategories(QVector<Category>);
    void productAdded(bool,QString);

signals:
    void loadCategoryVector();
    void addProduct(Product);

private slots:
    void on_addProduct_Button_clicked();

private:
    Ui::addproduct_window *ui;
    QVector<Category> *categoriesVector;
};

#endif // ADDPRODUCT_WINDOW_H
