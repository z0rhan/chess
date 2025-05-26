#include "menuwindow.hh"

MenuWindow::MenuWindow(QWidget* parent):
    QMainWindow(parent)
{
    initializeMenu();
}

MenuWindow::~MenuWindow()
{
}

void MenuWindow::initializeMenu()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    m_startButton = new QPushButton("Start Game", this);
    m_exitButton = new QPushButton("Exit", this);

    m_centralLayout = new QVBoxLayout(m_centralWidget);

    m_centralLayout->addWidget(m_startButton);
    m_centralLayout->addWidget(m_exitButton);

    connect(m_startButton, &QPushButton::clicked, this, &MenuWindow::startGame);
    connect(m_exitButton, &QPushButton::clicked, this, &QWidget::close);
}
