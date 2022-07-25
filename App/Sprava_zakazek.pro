#-------------------------------------------------
#
# Project created by QtCreator 2019-06-27T20:24:04
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += testlib
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sprava_zakazek
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += debug

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    query.cpp \
    database.cpp \
    database_obj.cpp \
    item.cpp \
    state.cpp \
    user.cpp \
    test_db.cpp \
    log.cpp \
    dialogboxes.cpp \
    main_model_table.cpp \
    hover_delegate.cpp \
    main_model_user.cpp \
    user_dialog.cpp \
    user_model_user.cpp \
    item_dialog.cpp \
    item_model_item.cpp \
    virtual_dialog.cpp \
    virtual_dialog_helper.cpp \
    setting.cpp \
    search.cpp \
    password_dialog.cpp

HEADERS  += mainwindow.h \
    query.h \
    exception.h \
    database.h \
    database_obj.h \
    item.h \
    state.h \
    user.h \
    test_db.h \
    log.h \
    dialogboxes.h \
    main_model_table.h \
    hover_delegate.h \
    main_model_user.h \
    user_dialog.h \
    user_model_user.h \
    item_dialog.h \
    item_model_item.h \
    virtual_dialog.h \
    virtual_dialog_helper.h \
    setting.h \
    search.h \
    password_dialog.h

FORMS    += mainwindow.ui \
    usertab.ui \
    itemtab.ui \
    setting.ui \
    search.ui \
    state_ch.ui \
    password.ui

