QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17





# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    changepassword.cpp \
    datahandler.cpp \
    history.cpp \
    main.cpp \
    mainscreen.cpp \
    mainwindow.cpp \
    register.cpp \
    safteyinspector.cpp \
    send_mail.cpp \
    userprofile.cpp \
    viewhistory.cpp \
    viewprofile.cpp

HEADERS += \
    changepassword.h \
    datahandler.h \
    history.h \
    mainscreen.h \
    mainwindow.h \
    register.h \
    safteyinspector.h \
    send_mail.h \
    userprofile.h \
    viewhistory.h \
    viewprofile.h

FORMS += \
    changepassword.ui \
    mainscreen.ui \
    mainwindow.ui \
    register.ui \
    send_mail.ui \
    userprofile.ui \
    viewhistory.ui \
    viewprofile.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target






#---------------OpenSSL--------------------------------#

win32: LIBS += -L$$PWD/libs/OpenSSL/ -llibcrypto
macx: LIBS += -L$$PWD/libs/OpenSSL/ -lcrypto

INCLUDEPATH += $$PWD/libs/OpenSSL/include
DEPENDPATH += $$PWD/libs/OpenSSL/include



win32: LIBS += -L$$PWD/libs/OpenSSL/ -llibssl
macx: LIBS += -L$$PWD/libs/OpenSSL/ -lssl



INCLUDEPATH += $$PWD/libs/OpenSSL/include
DEPENDPATH += $$PWD/libs/OpenSSL/include

#-----------------------------------------------#



win32: LIBS += -L$$PWD/libs/Yaml/ -lyaml-cppd
macx: LIBS += -L$$PWD/libs/Yaml/ -lyaml-cpp

INCLUDEPATH += $$PWD/libs/Yaml/include
DEPENDPATH += $$PWD/libs/Yaml/include


#------------------------------------------------





win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/Poco/ -lPocoFoundation
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/Poco/ -lPocoFoundationd

macx: LIBS += -L$$PWD/libs/Poco/ -lPocoFoundation

INCLUDEPATH += $$PWD/libs/Poco/Foundation/include
DEPENDPATH += $$PWD/libs/Poco/Foundation/include

#----------------------------------------



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/Poco/ -lPocoNet
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/Poco/ -lPocoNetd

macx: LIBS += -L$$PWD/libs/Poco/ -lPocoNet

INCLUDEPATH += $$PWD/libs/Poco/Net/include
DEPENDPATH += $$PWD/libs/Poco/Net/include

#-----------------------------------------------

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/Poco/ -lPocoUtil
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/Poco/ -lPocoUtild
macx: LIBS += -L$$PWD/libs/Poco/ -lPocoUtil

INCLUDEPATH += $$PWD/libs/Poco/Util/include
DEPENDPATH += $$PWD/libs/Poco/Util/include

RESOURCES += \
    Images.qrc









