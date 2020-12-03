#ifndef EDITINCOMECATEGORY_WINDOW_H
#define EDITINCOMECATEGORY_WINDOW_H

#include <QWidget>
#include "incomecategory.h"

namespace Ui {
class editincomecategory_window;
}

class editincomecategory_window : public QWidget
{
    Q_OBJECT

public:
    explicit editincomecategory_window(QWidget *parent = 0);
    ~editincomecategory_window();
    void showWithString(IncomeCategory);

signals:
    void editIncomeCategory(IncomeCategory);

private slots:
    void on_cancel_Button_clicked();

    void on_editIncomeCategory_Button_clicked();

    void incomeCategoryEdited(bool, QString);

private:
    Ui::editincomecategory_window *ui;
    IncomeCategory incomeCategory;
};

#endif // EDITINCOMECATEGORY_WINDOW_H
