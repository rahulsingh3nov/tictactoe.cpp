// Tic-Tac-Toe (C++11 or newer)
// Build: g++ -std=c++17 tictactoe.cpp -o tictactoe      Run: ./tictactoe   (Windows: .\tictactoe.exe)
//
// Core concepts shown: arrays (the board and the winning lines), loops (game loop,
// input loop, checks), and conditional logic (move validation, win/draw detection).
// Modes: two players, or play against the computer. Scores are kept across replays.

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

const int CELLS = 9;

// The 8 ways to win: 3 rows, 3 columns, 2 diagonals (cell positions 0-8).
const int WIN_LINES[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},   // rows
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},   // columns
    {0, 4, 8}, {2, 4, 6}               // diagonals
};

// ---------------------------------------------------------------- board
// An empty cell shows its number ('1'-'9'), so players can see what to type.
void resetBoard(char board[]) {
    for (int i = 0; i < CELLS; i++) board[i] = static_cast<char>('1' + i);
}

bool isFree(const char board[], int cell) {
    return board[cell] != 'X' && board[cell] != 'O';
}

void drawBoard(const char board[]) {
    std::cout << "\n";
    for (int row = 0; row < 3; row++) {
        std::cout << "     " << board[row * 3] << " | " << board[row * 3 + 1] << " | "
                  << board[row * 3 + 2] << "\n";
        if (row < 2) std::cout << "    ---+---+---\n";
    }
    std::cout << "\n";
}

// Returns 'X' or 'O' if that player has three in a row, otherwise ' '.
char findWinner(const char board[]) {
    for (int i = 0; i < 8; i++) {
        char a = board[WIN_LINES[i][0]];
        char b = board[WIN_LINES[i][1]];
        char c = board[WIN_LINES[i][2]];
        if (a == b && b == c) return a;
    }
    return ' ';
}

bool boardFull(const char board[]) {
    for (int i = 0; i < CELLS; i++)
        if (isFree(board, i)) return false;
    return true;
}

// ---------------------------------------------------------------- computer player
// Finds a free cell that completes a line for `player`; returns -1 if none.
int winningMoveFor(const char board[], char player) {
    for (int i = 0; i < 8; i++) {
        int mine = 0, freeCell = -1;
        for (int j = 0; j < 3; j++) {
            int cell = WIN_LINES[i][j];
            if (board[cell] == player) mine++;
            else if (isFree(board, cell)) freeCell = cell;
        }
        if (mine == 2 && freeCell != -1) return freeCell;
    }
    return -1;
}

// Strategy: win if possible, block the opponent, then centre, corners, sides.
int computerMove(const char board[], char me, char opponent) {
    int move = winningMoveFor(board, me);
    if (move != -1) return move;
    move = winningMoveFor(board, opponent);
    if (move != -1) return move;
    if (isFree(board, 4)) return 4;

    const int corners[4] = {0, 2, 6, 8};
    const int sides[4] = {1, 3, 5, 7};
    std::vector<int> options;
    for (int i = 0; i < 4; i++)
        if (isFree(board, corners[i])) options.push_back(corners[i]);
    if (options.empty())
        for (int i = 0; i < 4; i++)
            if (isFree(board, sides[i])) options.push_back(sides[i]);
    return options[std::rand() % options.size()];
}

// ---------------------------------------------------------------- input
// Reads a line. Returns false if the input has ended (Ctrl+Z / Ctrl+D).
bool readLine(const std::string& prompt, std::string& line) {
    std::cout << prompt << std::flush;
    return static_cast<bool>(std::getline(std::cin, line));
}

// Asks the player for a cell until a valid, free one is chosen. Returns -1 on end of input.
int askForMove(const char board[], char player) {
    std::string line;
    while (true) {
        if (!readLine(std::string("Player ") + player + ", choose a cell (1-9): ", line))
            return -1;
        if (line.size() == 1 && line[0] >= '1' && line[0] <= '9') {
            int cell = line[0] - '1';
            if (isFree(board, cell)) return cell;
            std::cout << "That cell is already taken. Try another.\n";
        } else {
            std::cout << "Please type a single number from 1 to 9.\n";
        }
    }
}

bool askYesNo(const std::string& prompt, bool& answer) {
    std::string line;
    while (true) {
        if (!readLine(prompt, line)) return false;
        if (!line.empty() && (line[0] == 'y' || line[0] == 'Y')) { answer = true; return true; }
        if (!line.empty() && (line[0] == 'n' || line[0] == 'N')) { answer = false; return true; }
        std::cout << "Please answer y or n.\n";
    }
}

// ---------------------------------------------------------------- one round
// Plays one game. Returns 'X', 'O', 'D' (draw) or 'Q' (input ended).
char playRound(bool vsComputer) {
    char board[CELLS];
    resetBoard(board);
    char current = 'X';

    drawBoard(board);
    while (true) {
        int cell;
        if (vsComputer && current == 'O') {
            cell = computerMove(board, 'O', 'X');
            std::cout << "Computer plays cell " << cell + 1 << ".\n";
        } else {
            cell = askForMove(board, current);
            if (cell == -1) return 'Q';
        }
        board[cell] = current;
        drawBoard(board);

        char winner = findWinner(board);
        if (winner != ' ') return winner;
        if (boardFull(board)) return 'D';

        current = (current == 'X') ? 'O' : 'X';
    }
}

// ---------------------------------------------------------------- main
int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::cout << "=============================\n"
              << "      TIC-TAC-TOE (C++)\n"
              << "=============================\n";

    std::string choice;
    bool vsComputer = false;
    while (true) {
        std::cout << "\n1. Two players\n2. Play against the computer\n";
        if (!readLine("Choose a mode (1 or 2): ", choice)) return 0;
        if (choice == "1") { vsComputer = false; break; }
        if (choice == "2") { vsComputer = true; break; }
        std::cout << "Please enter 1 or 2.\n";
    }
    if (vsComputer) std::cout << "You are X and go first. The computer is O.\n";

    int xWins = 0, oWins = 0, draws = 0;
    bool again = true;
    while (again) {
        char result = playRound(vsComputer);
        if (result == 'Q') break;

        if (result == 'X') {
            xWins++;
            std::cout << (vsComputer ? "You win! Well played.\n" : "Player X wins!\n");
        } else if (result == 'O') {
            oWins++;
            std::cout << (vsComputer ? "The computer wins. Better luck next time!\n"
                                     : "Player O wins!\n");
        } else {
            draws++;
            std::cout << "It's a draw!\n";
        }

        std::cout << "\nScore -> X: " << xWins << "   O: " << oWins << "   Draws: " << draws
                  << "\n";
        if (!askYesNo("Play again? (y/n): ", again)) break;
    }

    std::cout << "\nThanks for playing! Final score -> X: " << xWins << "  O: " << oWins
              << "  Draws: " << draws << "\n";
    return 0;
}
