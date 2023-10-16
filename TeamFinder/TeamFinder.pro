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
    send_mail.cpp \
    userprofile.cpp \
    viewprofile.cpp

HEADERS += \
    changepassword.h \
    databaseQuery.h \
    mainscreen.h \
    mainwindow.h \
    register.h \
    safteyinspector.h \
    send_mail.h \
    userprofile.h \
    viewprofile.h

FORMS += \
    changepassword.ui \
    mainscreen.ui \
    mainwindow.ui \
    register.ui \
    send_mail.ui \
    userprofile.ui \
    viewprofile.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../Qt/Tools/Pocco/ -lPocoFoundation
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../Qt/Tools/Pocco/ -lPocoFoundationd

INCLUDEPATH += $$PWD/../../../../../Qt/Tools/Pocco/Foundation/include
DEPENDPATH += $$PWD/../../../../../Qt/Tools/Pocco/Foundation/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../Qt/Tools/Pocco/ -lPocoNet
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../Qt/Tools/Pocco/ -lPocoNetd

INCLUDEPATH += $$PWD/../../../../../Qt/Tools/Pocco/Net/include
DEPENDPATH += $$PWD/../../../../../Qt/Tools/Pocco/Net/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../Qt/Tools/Pocco/ -lPocoUtil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../Qt/Tools/Pocco/ -lPocoUtild
else:unix: LIBS += -L$$PWD/../../../../../Qt/Tools/Pocco/ -lPocoUtil

INCLUDEPATH += $$PWD/../../../../../Qt/Tools/Pocco/Util/include
DEPENDPATH += $$PWD/../../../../../Qt/Tools/Pocco/Util/include
