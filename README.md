# Tic-Tac-Toe (C++)

A console-based Tic-Tac-Toe mini game written in C++. The board is redrawn after every move, wins and draws are detected automatically, and you can replay as many rounds as you like while a running score is kept.

## Features

- **Two modes:** two players, or play against the computer
- **Dynamic board:** redrawn after every move; empty cells show their number (1-9) so you always know what to type
- **Win / draw detection** after every move
- **Replay option** with a score tally (X wins, O wins, draws) across rounds
- **Input validation:** rejects letters, numbers out of range and cells that are already taken
- **Computer opponent** that wins when it can, blocks your winning move, then prefers the centre, corners and sides

## Programming concepts demonstrated

| Concept | Where it is used |
|---|---|
| Arrays | `board[9]` holds the game state; `WIN_LINES[8][3]` lists every winning combination |
| Loops | Game loop, input-retry loops, scanning lines to find a winner or a winning move |
| Conditional logic | Move validation, win/draw checks, switching players, computer strategy |
| Functions | `drawBoard`, `findWinner`, `boardFull`, `computerMove`, `playRound`, and more |

## How to play

```
     1 | 2 | 3
    ---+---+---
     4 | 5 | 6
    ---+---+---
     7 | 8 | 9
```

Players take turns typing the number of the cell they want. X always goes first. The first player to get three in a row (across, down or diagonally) wins. If all nine cells fill up with no winner, it's a draw.

## Build and run

Requires a C++ compiler such as g++.

```bash
g++ -std=c++17 tictactoe.cpp -o tictactoe
./tictactoe          # Windows: .\tictactoe.exe
```

## Project structure

```
tic-tac-toe-cpp/
├── tictactoe.cpp
├── .gitignore
└── README.md
```

## Possible extensions

Choose X or O, difficulty levels (an unbeatable computer using minimax), a bigger 4x4 board, player names.

## Author

Your Name · [GitHub](https://github.com/your-username) · [LinkedIn](https://linkedin.com/in/your-profile)
