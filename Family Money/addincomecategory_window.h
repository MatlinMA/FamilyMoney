#ifndef ADDINCOMECATEGORY_WINDOW_H
#define ADDINCOMECATEGORY_WINDOW_H

#include <QWidget>
#include "incomecategory.h"

namespace Ui {
class addincomecategory_window;
}

class addincomecategory_window : public QWidget
{
    Q_OBJECT

public:
    explicit addincomecategory_window(QWidget *parent = 0);
    ~addincomecategory_window();
    void showClear();

public slots:
    void incomeCategoryAdded(bool, QString);

signals:
    void addIncomeCategory(IncomeCategory);

private slots:
    void on_addIncomeCategory_Button_clicked();

    void on_cancel_Button_clicked();

private:
    Ui::addincomecategory_window *ui;
};

#endif // ADDINCOMECATEGORY_WINDOW_H
