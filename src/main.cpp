/*
 * Author: Zorhan Salami
 * Student Number: 153159921
 * Email: zorhan.salami@tuni.fi
 * ID: nkk362
 *
 * Description:
 * Entry point of the chess application. This file initializes the Qt application
 * environment, creates an instance of the MainWindow class (which handles the
 * user interface and game logic), and starts the main event loop.
 *
 * Responsibilities:
 * - Set up QApplication instance
 * - Instantiate and display the main application window
 * - Begin the Qt event loop
 */

#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
