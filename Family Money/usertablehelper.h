#ifndef USERTABLEHELPER_H
#define USERTABLEHELPER_H

#include <QVector>
#include "user.h"
#include <QObject>

namespace Ui {
class UserTableHelper;
}

class UserTableHelper
{

public:
    UserTableHelper();

    QVector<User> UserVector;
    void Pages(int p);
    int Pages();

private:
    int f_Pages = 0;
};
Q_DECLARE_METATYPE(UserTableHelper)

#endif // USERTABLEHELPER_H
