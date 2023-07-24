#include <iostream>
#include <vector>
using namespace std;

const int Rows = 6;
const int Cols = 7;

enum class Player { RED, BLUE, NONE };

class Connect4 {
private:
    vector<vector<Player>> board;
    Player currentPlayer;

public:
    Connect4()
        : board(Rows, vector<Player>(Cols, Player::NONE)),
        currentPlayer(Player::RED) {}

    void Play() {
        bool gameFinished = false;
        while (!gameFinished) {
            drawBoard();
            int column = chooseColumn();
            if (isValidMove(column)) {
                int row = dropPiece(column);
                if (checkWin(row, column)) {
                    drawBoard();
                    cout << "Player " << currentPlayerToString() << " wins!\n";
                    gameFinished = true;
                }
                else if (checkDraw()) {
                    drawBoard();
                    cout << "It's a draw!\n";
                    gameFinished = true;
                }
                else {
                    switchPlayer();
                }
            }
            else {
                cout << "Invalid move! Please try again.\n";
            }
        }
    }

private:
    void drawBoard() {
        // cout << "\n";
        cout << " ";
        for (int j = 0; j < Cols; j++) {
            cout << "+---";
        }
        cout << "+\n";

        for (int i = 0; i < Rows; i++) {
            cout << " | ";
            for (int j = 0; j < Cols; j++) {
                switch (board[i][j]) {
                case Player::NONE:
                    cout << "  ";
                    break;
                case Player::RED:
                    cout << "\033[1;31mR \033[0m";
                    break;
                case Player::BLUE:
                    cout << "\033[1;34mB \033[0m";
                    break;
                }
                cout << "| ";
            }
            cout << "\n";

            cout << " ";
            for (int j = 0; j < Cols; j++) {
                cout << "+---";
            }
            cout << "+\n";
        }

        cout << "  ";
        for (int j = 0; j < Cols; j++) {
            cout << " " << j << "  ";
        }
        cout << "\n\n\n";
    }

    int chooseColumn() {
        int column;
        cout << "Player " << currentPlayerToString() << ", choose a column: ";
        cin >> column;
        return column;
    }

    bool isValidMove(int column) {
        return column >= 0 && column < Cols && board[0][column] == Player::NONE;
    }

    int dropPiece(int column) {
        int row = Rows - 1;
        while (board[row][column] != Player::NONE) {
            row--;
        }
        board[row][column] = currentPlayer;
        return row;
    }

    bool checkWin(int row, int column) {
        Player player = currentPlayer;
        // Check horizontal
        int count = 0;
        for (int j = 0; j < Cols; j++) {
            if (board[row][j] == player) {
                count++;
                if (count == 4) {
                    return true;
                }
            }
            else {
                count = 0;
            }
        }

        // Check vertical
        count = 0;
        for (int i = 0; i < Rows; i++) {
            if (board[i][column] == player) {
                count++;
                if (count == 4) {
                    return true;
                }
            }
            else {
                count = 0;
            }
        }

        // Check diagonal (top-left to bottom-right)
        int startRow = row - min(row, column);
        int startCol = column - min(row, column);
        count = 0;
        for (int i = startRow, j = startCol; i < Rows && j < Cols; i++, j++) {
            if (board[i][j] == player) {
                count++;
                if (count == 4) {
                    return true;
                }
            }
            else {
                count = 0;
            }
        }

        // Check diagonal (bottom-left to top-right)
        startRow = row + min(Rows - row - 1, column);
        startCol = column - min(Rows - row - 1, column);
        count = 0;
        for (int i = startRow, j = startCol; i >= 0 && j < Cols; i--, j++) {
            if (board[i][j] == player) {
                count++;
                if (count == 4) {
                    return true;
                }
            }
            else {
                count = 0;
            }
        }
        return false;
    }

    bool checkDraw() {
        for (int j = 0; j < Cols; j++) {
            if (board[0][j] == Player::NONE) {
                return false;
            }
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == Player::RED) ? Player::BLUE : Player::RED;
    }

    string currentPlayerToString() {
        return (currentPlayer == Player::RED) ? "RED" : "BLUE";
    }
};
class GameIntro : public Connect4 {
public:
    void GameProfile() {
        cout << "            +-------------------------------+" << endl;
        cout << "            |   WELCOME TO CONNECT-4 GAME   |" << endl;
        cout << "            +-------------------------------+" << endl;
        cout << endl;
        cout << "RULES:" << endl;
        cout << " 1. Two-playe Red(R) & Blue(B) game." << endl;
        cout << " 2. Board Size is 6 rows & 7 columns." << endl;
        cout << " 3. A player wins, if he/she is able to connect 4 letters" << endl;
        cout << "    horizontally, vertically or diagonally" << endl;
        cout << " 4. Game Draw when matrix is fully filled." << endl;
        cout << endl;
        cout << "HOW TO PLAY:" << endl;
        cout << " 1. Game always starts with player- 1 i.e. Red(R)." << endl;
        cout << " 2. In each step choose the column number in which you" << endl;
        cout << "    want to drop the letter." << endl;
        cout << " 3. Rows will be filled from bottom to top in any column " << endl;
        cout << endl;
        cout << "          GAME STARTS " << endl;
    }
};

int main() {
    Connect4 game;
    GameIntro title;
    title.GameProfile();
    game.Play();
    return 0;
}