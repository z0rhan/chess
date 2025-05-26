TEMPLATE = app
TARGET = chess
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Set output directory for the final binary
DESTDIR = $$PWD/build/bin

# Set output directory for object files and MOC files
OBJECTS_DIR = $$PWD/build/obj
MOC_DIR = $$PWD/build/obj

# Set the directory for resource .cpp file generated from .qrc
RCC_DIR = $$PWD/build/obj

# Add source and header files
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
    src/rook.cpp \
    src/mainwindow.cpp \
    src/move_utils.cpp \
    src/menuwindow.cpp

HEADERS += \
    src/bishop.hh \
    src/chess.hh \
    src/chessboard.hh \
    src/chesspiece.hh \
    src/knight.hh \
    src/pawn.hh \
    src/king.hh \
    src/queen.hh \
    src/rook.hh \
    src/mainwindow.hh \
    src/move_utils.hh \
    src/menuwindow.hh

# Add the resource file
RESOURCES += chess_icons.qrc

