QT       += core gui sql      #подключаем язык SQL

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = catalog
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        addproduct.cpp \
        authwidget.cpp \
        catalogbuyer.cpp \
        catalogmanager.cpp \
        main.cpp \
        model/dbfacade.cpp \
        model/productdb.cpp \
        model/user.cpp \
        orderbuyer.cpp \
        ordermanagement.cpp \
        salesreport.cpp \
        users.cpp

HEADERS += \
        addproduct.h \
        authwidget.h \
        catalogbuyer.h \
        catalogmanager.h \
        model/dbfacade.h \
        model/order.h \
        model/product.h \
        model/productdb.h \
        model/soltproduct.h \
        model/user.h \
        orderbuyer.h \
        ordermanagement.h \
        salesreport.h \
        singleton.h \
        users.h

FORMS += \
        addproduct.ui \
        authwidget.ui \
        catalogbuyer.ui \
        catalogmanager.ui \
        orderbuyer.ui \
        ordermanagement.ui \
        salesreport.ui \
        users.ui
