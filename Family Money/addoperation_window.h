#ifndef ADDOPERATION_WINDOW_H
#define ADDOPERATION_WINDOW_H

#include <QWidget>

namespace Ui {
class addoperation_window;
}

class addoperation_window : public QWidget
{
    Q_OBJECT

public:
    explicit addoperation_window(QWidget *parent = 0);
    ~addoperation_window();

    void showClear(int);

private slots:
    void on_incomeOperation_clicked();

    void on_spendingOperation_clicked();

private:
    Ui::addoperation_window *ui;
};

#endif // ADDOPERATION_WINDOW_H
