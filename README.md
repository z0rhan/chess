# Install and Run
This program has been tested and run with qt6 in Arch Linux x86_64 Linux Mint 22.1 x86_64.  
To install qt Arch Linux, run in your terminal:
```
sudo pacman -S qt6-base git
```
For Linux Mint,
```
sudo apt install qt6-base-dev
```
This will install all the qt-related libraries needed and git also if you don't have it yet.
Then run:
```
git clone https://github.com/z0rhan/chess
cd chess
mkdir build/bin build/obj
qmake6 && make
```
To run the game, run:
```
build/bin/chess
```

# ♟️ How to Play the Chess Game

## Objective
Play a classic two-player chess game where White and Black take turns moving their pieces. The goal is to capture the opponent's king, as **checkmate detection is not implemented**.

> **Important Note:**  
> The game does **not** currently detect check, checkmate, or stalemate.  
> To end the game, you must **manually capture the opponent's king**.  
> Also, it does not support pinnig, so you can still move a piece even if it **lead to check**.  
> I'll continue to improve on this after submitting what is required to the university.

## Controls & Interaction

### Selecting and Moving Pieces
- **Click** on a piece that belongs to the player whose turn it is (White starts by default).
- After selecting a piece, its **valid moves** will be highlighted.
- **Click** on one of the highlighted squares to move the piece.

### Restarting the Game
- Click the **"Restart Game"** button to reset the board.
- The game will restart with the currently selected starting color.

### Choosing a Starting Color
- Click **"Start with White"** or **"Start with Black"** to start a new game and at the same time deciding which player starts.

### Exiting the Game
- Click the **"Exit"** button to close the application.

---

## Game Flow

- Players take turns making moves.
- Game events are displayed in the info section at the right.
- When a valid move is made, the board updates and control switches to the other player.
- When a king is captured, the game ends and a message shows the winner.
- The board becomes disabled until a new game is started.

To play again, simply click **"Restart Game"**.

---

Enjoy your game!
