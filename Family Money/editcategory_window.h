#ifndef EDITCATEGORY_WINDOW_H
#define EDITCATEGORY_WINDOW_H

#include <QWidget>
#include  "category.h"

namespace Ui {
class editcategory_window;
}

class editcategory_window : public QWidget
{
    Q_OBJECT

public:
    explicit editcategory_window(QWidget *parent = nullptr);
    ~editcategory_window();
    void showWithString(Category);

signals:
    void editCategory(Category);

private slots:
    void on_cancel_Button_clicked();

    void on_editCategory_Button_clicked();

    void categoryEdited(bool, QString);

private:
    Ui::editcategory_window *ui;
    Category category;
};

#endif // EDITCATEGORY_WINDOW_H
