/*
 * Author: Zorhan Salami
 * Student Number: 153159921
 * Email: zorhan.salami@tuni.fi
 * ID: nkk362
 *
 * Description:
 * This source file implements the MainWindow class, which controls the main
 * graphical user interface (GUI) for the chess application. It defines the
 * methods for setting up the game board, handling user interactions (such as
 * selecting and moving pieces), restarting the game, and updating the UI
 * elements based on the game's state. The class also communicates with the
 * Chess game logic to process moves and determine game outcomes.
 */

#include "mainwindow.hh"
#include "chesspiece.hh"

#include <QCloseEvent>

//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}, m_selectedCoord(NULL_COORD)
{
    this->initializeWidgets();

    this->initializeLayouts();

    this->intializeNewGame();

    this->renderBoardSquares();

    this->initializeConnections();
}

//------------------------------------------------------------------------------
MainWindow::~MainWindow() {}

//------------------------------------------------------------------------------
void MainWindow::handleClicks(int row, int col)
{
    Coord clikedButton{row, col};

    // First click
    if (m_selectedCoord == NULL_COORD)
    {
        if (!isValidClick(row, col))
        {
            return;
        }

        m_selectedCoord = clikedButton;

        this->updateInfoText(InfoMessages::PIECE_SELECTED);

        this->highlightPossibleMoves(m_selectedCoord);

        return;
    }

    // Second click
    this->resetHighlight();

    if (!this->updateGame(clikedButton))
    {
        return;
    }

    m_selectedCoord = NULL_COORD;

    if (isGameFinished())
    {
        for (auto row : m_chessBoardButtons)
        {
            for (auto button : row)
            {
                button->setDisabled(true);
            }
        }

        return;
    }
}

//------------------------------------------------------------------------------
void MainWindow::restartGame(ChessColor startingPlayer)
{
    m_chessGame = make_unique<Chess>();

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (m_chessBoardButtons[row][col])
            {
                m_boardLayout->removeWidget(m_chessBoardButtons[row][col]);
                m_chessBoardButtons[row][col]->deleteLater();
                m_chessBoardButtons[row][col] = nullptr;
            }
        }
    }

    this->intializeNewGame(startingPlayer);

    this->renderBoardSquares();

    m_selectedCoord = NULL_COORD;

    if (sender() == m_restartButton)
    {
        this->updateInfoText(InfoMessages::RESTART_GAME);
    }
}

//------------------------------------------------------------------------------
void MainWindow::intializeNewGame(ChessColor startingPlayer)
{
    m_chessGame = make_unique<Chess>();
    m_chessGame->start_game(startingPlayer);
}

//------------------------------------------------------------------------------
void MainWindow::initializeWidgets()
{
    // Initialize all widgets
    m_centralWidget = new QWidget(this);
    m_boardWidget = new QWidget(this);
    m_buttonsWidget = new QWidget(this);
    m_infoWidget = new QWidget(this);

    m_closeButton = new QPushButton("Exit", this);
    m_restartButton = new QPushButton("Restart Game", this);

    m_infoLabel = new QLabel("WELCOME\n"
                             "White to move",
                             this);

    this->setCentralWidget(m_centralWidget);

    m_boardWidget->setMaximumSize(640, 640);
}

//------------------------------------------------------------------------------
void MainWindow::initializeLayouts()
{
    // Initialize all layouts
    m_centralLayout = new QGridLayout(m_centralWidget);
    m_boardLayout = new QGridLayout(m_boardWidget);
    m_buttonsLayout = new QGridLayout(m_buttonsWidget);
    m_infoLayout = new QGridLayout(m_infoWidget);

    // Add the widgets to the layouts
    m_centralLayout->addWidget(m_boardWidget, 0, 0);
    m_centralLayout->addWidget(m_buttonsWidget, 1, 0);
    m_centralLayout->addWidget(m_infoWidget, 0, 1, 2, 1);

    m_buttonsLayout->addWidget(m_restartButton, 0, 0);
    m_buttonsLayout->addWidget(m_closeButton, 0, 1);

    m_infoLayout->addWidget(m_infoLabel, 0, 0);

    m_boardLayout->setSpacing(0);
}

//------------------------------------------------------------------------------
void MainWindow::renderBoardSquares()
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            QPushButton *squareButton = createSquareButton(row, col);

            this->setChessPiece(squareButton, row, col);
        }
    }
}

//------------------------------------------------------------------------------
QPushButton *MainWindow::createSquareButton(const int row, const int col)
{
    QString imagePath = this->getImagePath(row, col);

    QPushButton *squareButton = new QPushButton(this);

    squareButton->setFlat(false);

    this->setButtonIcon(squareButton, imagePath);

    squareButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    return squareButton;
}

//------------------------------------------------------------------------------
void MainWindow::initializeConnections()
{
    connect(m_closeButton, &QPushButton::clicked, this, &QMainWindow::close);

    connect(m_restartButton, &QPushButton::clicked, this, [this]() { restartGame(); });
}

//------------------------------------------------------------------------------
void MainWindow::setButtonIcon(QPushButton *button, const QString &imagePath)
{
    QPixmap pixMap(imagePath);
    QIcon buttonIcon(pixMap);

    button->setIcon(buttonIcon);
    button->setMinimumSize(c_buttonSize);
    button->setIconSize(QSize(c_iconSize));
}

//------------------------------------------------------------------------------
QString MainWindow::getImagePath(const int row, const int col) const
{
    shared_ptr<ChessPiece> piece =
        m_chessGame->get_board().get_piece_at(row, col);

    QString squareColor = (row + col) % 2 == 0 ? "bl" : "wt";

    if (!piece)
    {
        return QString(":pieces/empty-%1.png").arg(squareColor);
    }

    QString pieceColor = piece->get_color() == ChessColor::WHITE ? "wt" : "bl";
    QString pieceName = QString::fromStdString(piece->get_name());

    return QString(":pieces/%1-%2-on-%3.png")
        .arg(pieceColor)
        .arg(pieceName)
        .arg(squareColor);
}

//------------------------------------------------------------------------------
void MainWindow::setChessPiece(QPushButton *piece, const int row, const int col)
{
    connect(piece, &QPushButton::clicked, this,
            [this, row, col]() { handleClicks(row, col); });

    this->m_chessBoardButtons[row][col] = piece;
    this->m_boardLayout->addWidget(piece, row, col);
}

//------------------------------------------------------------------------------
bool MainWindow::updateGame(Coord dest)
{
    shared_ptr<ChessPiece> selectedPiece =
        m_chessGame->get_board().get_piece_at(m_selectedCoord.row,
                                              m_selectedCoord.col);

    shared_ptr<ChessPiece> destPiece =
        m_chessGame->get_board().get_piece_at(dest.row, dest.col);

    // If same color is selected, update m_selectedCoord
    if (destPiece && selectedPiece->get_color() == destPiece->get_color())
    {
        this->updateInfoText(InfoMessages::PIECE_SELECTED_AGAIN);

        m_selectedCoord = dest;

        this->highlightPossibleMoves(m_selectedCoord);

        return false;
    }

    if (!m_chessGame->make_move(selectedPiece, dest))
    {
        m_selectedCoord = NULL_COORD;

        this->updateInfoText(InfoMessages::INVALID_MOVE);

        return false;
    }

    renderBoardSquares();

    this->updateInfoText(InfoMessages::SUCCESSFUL_MOVE);

    return true;
}

//------------------------------------------------------------------------------
void MainWindow::updateInfoText(InfoMessages message)
{
    switch (message)
    {
    case InfoMessages::CURRENT_TURN:
        m_infoLabel->setText(
            QString("%1 to move")
                .arg(this->colorToString(m_chessGame->get_current_turn())));
        break;

    case InfoMessages::PIECE_SELECTED:
        m_infoLabel->setText(
            QString("%1 has selected")
                .arg(this->colorToString(m_chessGame->get_current_turn())));
        break;

    case InfoMessages::PIECE_SELECTED_AGAIN:
        m_infoLabel->setText(
            QString("%1 has selected again")
                .arg(this->colorToString(m_chessGame->get_current_turn())));
        break;

    // String formed is opposite since this is called after move is made
    case InfoMessages::SUCCESSFUL_MOVE:
        m_infoLabel->setText(
            QString("Successful move by %1")
                .arg(m_chessGame->get_current_turn() == ChessColor::BLACK
                         ? "White"
                         : "Black"));
        break;

    case InfoMessages::INVALID_MOVE:
        m_infoLabel->setText("Invalid Move!!!");
        break;

    case InfoMessages::GAME_FINISHED:
        m_infoLabel->setText(
            QString("Congratulations, %1 won the game\n"
                    "Please start a new game")
                .arg(m_gameState == GameState::BLACK_WIN ? "Black" : "White"));
        break;

    case InfoMessages::RESTART_GAME:
        m_infoLabel->setText("New game started\n"
                             "White to move");
        break;

    default:
        m_infoLabel->setText("You shouldn't see this message!!!");
        break;
    }
}

//------------------------------------------------------------------------------
QString MainWindow::colorToString(const ChessColor &color)
{
    return color == ChessColor::BLACK ? "Black" : "White";
}

//------------------------------------------------------------------------------
void MainWindow::highlightPossibleMoves(const Coord &selectedPosition)
{
    ChessBoard board = m_chessGame->get_board();
    set<Coord> moves =
        board.get_piece_at(selectedPosition)->get_allowed_moves(board);

    for (const auto [row, col] : moves)
    {
        m_chessBoardButtons[row][col]->setStyleSheet(c_highlightSquare);
    }
}

//------------------------------------------------------------------------------
void MainWindow::resetHighlight()
{

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            m_chessBoardButtons[row][col]->setStyleSheet(c_noHighlight);
        }
    }
}

//------------------------------------------------------------------------------
bool MainWindow::isValidClick(const int row, const int col) const
{
    shared_ptr<ChessPiece> clickedPiece =
        m_chessGame->get_board().get_piece_at(row, col);

    if (!clickedPiece)
    {
        return false;
    }

    if (m_chessGame->get_current_turn() != clickedPiece->get_color())
    {
        return false;
    }

    return true;
}

//------------------------------------------------------------------------------
bool MainWindow::isGameFinished()
{
    m_gameState = m_chessGame->get_game_state();

    if (m_gameState != GameState::IN_PROGRESS)
    {
        this->updateInfoText(InfoMessages::GAME_FINISHED);

        return true;
    }

    return false;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    emit windowClosed();
    QMainWindow::closeEvent(event);
}
