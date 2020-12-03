#-------------------------------------------------
#
# Project created by QtCreator 2020-10-05T16:24:46
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    addcategory_window.cpp \
    addproduct_window.cpp \
    category.cpp \
    editcategory_window.cpp \
    editproduct_window.cpp \
    edituser_window.cpp \
        mainwindow.cpp \
    auth_window.cpp \
    dbhelper.cpp \
    product.cpp \
    user.cpp \
    usertablehelper.cpp \
    adduser_window.cpp \
    incomecategory.cpp \
    addincomecategory_window.cpp \
    editincomecategory_window.cpp \
    operation.cpp \
    addoperation_window.cpp

HEADERS  += mainwindow.h \
    addcategory_window.h \
    addproduct_window.h \
    auth_window.h \
    category.h \
    dbhelper.h \
    editcategory_window.h \
    editproduct_window.h \
    edituser_window.h \
    product.h \
    user.h \
    usertablehelper.h \
    adduser_window.h \
    incomecategory.h \
    addincomecategory_window.h \
    editincomecategory_window.h \
    operation.h \
    addoperation_window.h

FORMS    += mainwindow.ui \
    addcategory_window.ui \
    addproduct_window.ui \
    auth_window.ui \
    adduser_window.ui \
    editcategory_window.ui \
    editproduct_window.ui \
    edituser_window.ui \
    addincomecategory_window.ui \
    editincomecategory_window.ui \
    addoperation_window.ui
