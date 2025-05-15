cmake_minimum_required(VERSION 3.16)
cmake_policy(SET CMP0100 NEW)

project(chess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
    src/bishop.cpp
    src/chess.cpp
    src/chessboard.cpp
    src/chesspiece.cpp
    src/knight.cpp
    src/main.cpp
    src/pawn.cpp
    src/king.cpp
    src/queen.cpp
    src/rook.cpp
    src/mainwindow.cpp
    src/move_utils.cpp
)

qt_add_resources(RESOURCES chess_icons.qrc)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_link_libraries(chess PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_sources(${PROJECT_NAME} PRIVATE ${RESOURCES})

install(TARGETS chess
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
