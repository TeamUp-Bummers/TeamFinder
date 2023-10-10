QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
LIBS += -L"C:/Qt/Tools/OpenSSLv3/Win_x64/lib/" -llibcrypto -llibssl

INCLUDEPATH +=C:/Qt/Tools/OpenSSLv3/Win_x64/include

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changepassword.cpp \
    databaseQuery.cpp \
    main.cpp \
    mainscreen.cpp \
    mainwindow.cpp \
    register.cpp \
    safteyinspector.cpp \
    userprofile.cpp

HEADERS += \
    changepassword.h \
    databaseQuery.h \
    mainscreen.h \
    mainwindow.h \
    register.h \
    safteyinspector.h \
    userprofile.h

FORMS += \
    changepassword.ui \
    mainscreen.ui \
    mainwindow.ui \
    register.ui \
    userprofile.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
