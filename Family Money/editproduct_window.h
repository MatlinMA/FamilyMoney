#ifndef EDITPRODUCT_WINDOW_H
#define EDITPRODUCT_WINDOW_H

#include <QWidget>
#include "product.h"
#include "category.h"

namespace Ui {
class editproduct_window;
}

class editproduct_window : public QWidget
{
    Q_OBJECT

public:
    explicit editproduct_window(QWidget *parent = nullptr);
    ~editproduct_window();

    void showPage(Product);

signals:
    void loadCategoryVector();
    void editProduct(Product);

public slots:
    void putCategories(QVector<Category>);
    void productEdited(bool, QString);

private slots:
    void on_cancel_Button_clicked();
    void on_editProduct_Button_clicked();

private:
    Ui::editproduct_window *ui;
    Product editedProduct;
    QVector<Category> *categoriesVector;
};

#endif // EDITPRODUCT_WINDOW_H
