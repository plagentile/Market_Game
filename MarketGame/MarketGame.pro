QT += charts
QT += core gui
QT += concurrent
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
INCLUDEPATH += C:/OpenSSL-Win64/include/


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    account.cpp \
    chartbuilder.cpp \
    coordinator.cpp \
    initialaccountsetup.cpp \
    main.cpp \
    mainwindow.cpp \
    networkhandler.cpp \
    requestencapsulator.cpp \
    signinoptionsdialog.cpp \
    symbolternarysearchtree.cpp \
    termsofservice.cpp \
    tradehandler.cpp \
    updatehandler.cpp

HEADERS += \
    about.h \
    account.h \
    chartbuilder.h \
    coordinator.h \
    initialaccountsetup.h \
    mainwindow.h \
    networkhandler.h \
    requestencapsulator.h \
    signinoptionsdialog.h \
    symbolternarysearchtree.h \
    termsofservice.h \
    tradehandler.h \
    updatehandler.h

FORMS += \
    about.ui \
    account.ui \
    initialaccountsetup.ui \
    mainwindow.ui \
    signinoptionsdialog.ui \
    termsofservice.ui \
    tradehandler.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
