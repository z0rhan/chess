QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/bishop.cpp \
    src/chess.cpp \
    src/chessboard.cpp \
    src/chesspiece.cpp \
    src/knight.cpp \
    src/main.cpp \
    src/pawn.cpp \
    src/king.cpp \
    src/queen.cpp \
    src/rook.cpp

HEADERS += \
    include/bishop.hh \
    include/chess.hh \
    include/chessboard.hh \
    include/chesspiece.hh \
    include/knight.hh \
    include/pawn.hh \
    include/king.hh \
    include/queen.hh \
    include/rook.hh

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    chess_icons.qrc
