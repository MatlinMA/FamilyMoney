#ifndef ADDCATEGORY_WINDOW_H
#define ADDCATEGORY_WINDOW_H

#include <QWidget>
#include "category.h"

namespace Ui {
class addcategory_window;
}

class addcategory_window : public QWidget
{
    Q_OBJECT

public:
    explicit addcategory_window(QWidget *parent = nullptr);
    ~addcategory_window();
    void showClear();

public slots:
    void categoryAdded(bool, QString);

private slots:
    void on_addCategory_Button_clicked();

    void on_cancel_Button_clicked();

signals:
    void addCategory(Category);

private:
    Ui::addcategory_window *ui;
};

#endif // ADDCATEGORY_WINDOW_H
