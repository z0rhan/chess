/*
 * Author: Zorhan Salami
 * Student Number: 153159921
 * Email: zorhan.salami@tuni.fi
 * ID: nkk362
 *
 * Description:
 * This header file declares the MainWindow class, which serves as the main
 * GUI controller for the chess application. It is responsible for setting up 
 * the chessboard interface, handling user interactions (such as piece selection, 
 * move execution, and restarting the game), updating the board view based on 
 * game logic, and managing UI elements such as buttons, labels, and highlighting.
 *
 * Key Features:
 * - Initializes and manages all main widgets and layouts
 * - Handles user input and interactions with the chessboard
 * - Supports starting the game with either white or black
 * - Displays information messages and move highlights
 * - Coordinates with the Chess logic class to process moves
 */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "chesspiece.hh"
#include "chess.hh"

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QIcon>

enum class InfoMessages {
    CURRENT_TURN,
    PIECE_SELECTED,
    PIECE_SELECTED_AGAIN,
    SUCCESSFUL_MOVE,
    INVALID_MOVE,
    GAME_FINISHED,
    RESTART_GAME
};

const QSize c_buttonSize(80, 80);
const QSize c_iconSize(75, 75);
const QString c_highlightSquare = "background-color: red; border: 5px solid red";
const QString c_noHighlight = "";

using boardButtons = std::array<std::array<QPushButton*, BOARD_SIZE>, BOARD_SIZE>;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

signals:
    void windowClosed();

private slots:
    /**
     * @brief Slot to handle click events on the m_chessBoardButtons
     * @param int row
     * @param int col
     */
    void handleClicks(int row, int col);

    /**
     * @brief Slot to start the game from the startg agian
     *        Deletes the current instance of Chess and makes a new one
     *        Deletes all the current buttons and calls setupBoardSquares
     * @param ChessColor startingPlayer: the starting color for next game
     */
    void restartGame(ChessColor startingPlayer = WHITE);

    void closeEvent(QCloseEvent* event);


signals:

private:
    // Widgets
    QWidget*			m_centralWidget;
    QWidget*			m_boardWidget;
    QWidget*			m_buttonsWidget;
    QWidget*			m_infoWidget;

    // Layouts
    QGridLayout*		m_centralLayout;
    QGridLayout*		m_boardLayout;
    QGridLayout*		m_buttonsLayout;
    QGridLayout*		m_infoLayout;

    // Buttons
    QPushButton* 		m_closeButton;
    QPushButton* 		m_restartButton;
    QPushButton* 		m_whiteStart;
    QPushButton* 		m_blackStart;

    // Labels
    QLabel* 			m_infoLabel;

    // Game interface
    boardButtons 		m_chessBoardButtons;
    Coord 				m_selectedCoord;
    unique_ptr<Chess>	m_chessGame;
    GameState			m_gameState;

    /**
     * @brief Creates a new instance of Chess
     * @param ChessColor startingPlayer
     */
    void 				intializeNewGame(ChessColor startingPlayer = WHITE);

    /**
     * @brief Creates and setups all necessary Widgets
     */
    void 				initializeWidgets();

    /**
     * @brief Creates and setups all necessary Layouts
     */
    void 				initializeLayouts();

    /**
     * @brief Creates and setups 64 buttons to act as the chessboard
     */
    void 				renderBoardSquares();

    /**
     * @brief Creates and setups 64 buttons to act as the chessboard
     */
    QPushButton* 		createSquareButton(const int row,const int col);

    /**
     * @brief Setups all necessary connections between signals and slots
     */
    void 				initializeConnections();

    /**
     * @brief Set the icon for the 64 buttons from setupBoardSquares according
     *        to their postion in the Layout
     * @param QPushButton* button
     * @param const QString& imagePath 
     */
    void 				setButtonIcon(QPushButton* button,
                                      const QString &imagePath);

    /**
     * @brief Creates the imagePath according to the Coord given
     * @param const int row
     * @param const int col
     * @return Qstring as the imagePath
     */
    QString 			getImagePath(const int row, const int col) const;

    /**
     * @brief Adds the 64 buttons from setupBoardSquares to the proper location
     *        in the m_boardLayout and adds it to m_chessBoardButtons
     *        Also, connects the clicked signal to handleCliks() slot
     * @param QPushButton* piece: pointer to the button
     * @param const int row
     * @param const int col
     */
    void 				setChessPiece(QPushButton* piece,
                                      const int row, const int col);

    /**
     * @brief Calls Chess::make_move() to make a move in the game
     *        If the move is sucessfull, calls setButtonIcon() to update
     *        the button icon
     *        Otherwise, displays error message
     * @param QPushButton* firstButton  : selected button
     * @param QPushButton* secondButton : destination button
     * @param Coord dest                : destination Coord
     */
    bool            	updateGame(Coord dest);
    /**
     * @brief Function to update the info message in m_infoLabel
     * @param InfoMessages message
     */
    void 				updateInfoText(InfoMessages message);

    /**
     * @brief Funcion to convert ChessColor to its appropriate string
     * @param ChessColor& color
     */
    QString         	colorToString(const ChessColor& color);

    /**
     * @brief Function to highlight all possible moves of the piece that the
     *        user has selected
     * @param const Coord& selectedPosition
     */
    void            	highlightPossibleMoves(const Coord& selectedPosition);

    /**
     * @brief Function to remove highlight for possible moves
     */
    void 				resetHighlight();

    /**
     * @brief Funcion to check if the selected button is valid or not
     * @param const int row
     * @param const int col
     * @return false if the there is no piece or if the selected color
     *         is not the the current turn, true otherwise
     */
    bool 				isValidClick(const int row, const int col) const;

    /**
     * @brief Function to check if the game is finished or not
     * @return true if either ChessColor wins the game, false otherwise
     */
    bool 				isGameFinished();

};

#endif
