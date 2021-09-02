QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alien.cpp \
    bullet.cpp \
    drop.cpp \
    game.cpp \
    gameovermenu.cpp \
    hud.cpp \
    main.cpp \
    mainmenu.cpp \
    menubutton.cpp \
    player.cpp \
    spaceship.cpp \
    stage.cpp \
    weapon.cpp

HEADERS += \
    alien.h \
    bullet.h \
    drop.h \
    game.h \
    gameovermenu.h \
    hud.h \
    mainmenu.h \
    menubutton.h \
    player.h \
    settings.h \
    spaceship.h \
    stage.h \
    weapon.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc

LIBS += -lwinmm
