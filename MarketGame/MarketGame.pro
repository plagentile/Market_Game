QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about.cpp \
    account.cpp \
    applicationstatus.cpp \
    coordinator.cpp \
    initialaccountsetup.cpp \
    main.cpp \
    mainwindow.cpp \
    readknownsymbols.cpp \
    searchsymbol.cpp \
    signinoptionsdialog.cpp \
    singleuseqstringqueue.cpp \
    symbolbst.cpp \
    termsofservice.cpp

HEADERS += \
    about.h \
    account.h \
    applicationstatus.h \
    coordinator.h \
    initialaccountsetup.h \
    mainwindow.h \
    readknownsymbols.h \
    searchsymbol.h \
    signinoptionsdialog.h \
    singleuseqstringqueue.h \
    symbolbst.h \
    termsofservice.h

FORMS += \
    about.ui \
    account.ui \
    initialaccountsetup.ui \
    mainwindow.ui \
    searchsymbol.ui \
    signinoptionsdialog.ui \
    termsofservice.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resources.qrc
