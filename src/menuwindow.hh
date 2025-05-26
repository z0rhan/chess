#ifndef MENUWINDOW_HH
#define MENUWINDOW_HH

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class MenuWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MenuWindow(QWidget* parent = nullptr);
    virtual ~MenuWindow();

signals:
    void startGame();

private:
    QWidget*            m_centralWidget;

    QPushButton*        m_startButton;
    QPushButton*        m_exitButton;

    QVBoxLayout*        m_centralLayout;

    void                initializeMenu();
};

#endif // MENUWINDOW_HH
