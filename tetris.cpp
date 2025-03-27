#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>    // For _kbhit(), _getch(), and gotoxy()

using namespace std;

// Game Constants
const int WIDTH = 10;
const int HEIGHT = 20;
const int NUM_TETROMINOS = 7;

// Tetromino Types
enum TetrominoType { I, O, T, L, J, S, Z };

// Tetromino Shape Structure
class Tetromino {
public:
    vector<vector<int>> shape;
    int x, y;

    Tetromino(TetrominoType type) {
        x = WIDTH / 2 - 2; // Start at the center of the screen
        y = 0;
        shape = getShape(type);
    }

    vector<vector<int>> getShape(TetrominoType type) {
        switch (type) {
        case I:
            return {{1, 1, 1, 1}};
        case O:
            return {{1, 1}, {1, 1}};
        case T:
            return {{0, 1, 0}, {1, 1, 1}};
        case L:
            return {{1, 0, 0}, {1, 1, 1}};
        case J:
            return {{0, 0, 1}, {1, 1, 1}};
        case S:
            return {{0, 1, 1}, {1, 1, 0}};
        case Z:
            return {{1, 1, 0}, {0, 1, 1}};
        }
        return {}; // Default case
    }
};

// Gotoxy function declaration
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Hide cursor
void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Show cursor
void showCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Main Game Class
class TetrisGame {
private:
    vector<vector<int>> board;
    Tetromino* currentTetromino;
    int score, level, linesCleared, fallingSpeed,highScore;
    bool gameOver;

public:
    TetrisGame() {
        board = vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 0));
        srand(time(0));
        score = 0;
        level = 1;
        linesCleared = 0;
        fallingSpeed = 500; // 500ms between drops initially
        gameOver = false;
        highScore = 0;
        spawnTetromino();
    }

    // Spawn a random Tetromino
    void spawnTetromino() {
        TetrominoType type = static_cast<TetrominoType>(rand() % NUM_TETROMINOS);
        currentTetromino = new Tetromino(type);
    }

    // Check for collision of the tetromino
    bool checkCollision() {
        for (int i = 0; i < currentTetromino->shape.size(); ++i) {
            for (int j = 0; j < currentTetromino->shape[i].size(); ++j) {
                if (currentTetromino->shape[i][j]) {
                    int newX = currentTetromino->x + j;
                    int newY = currentTetromino->y + i;
                    if (newX < 0 || newX >= WIDTH || newY >= HEIGHT || (newY >= 0 && board[newY][newX])) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    // Place the tetromino on the board
    void placeTetromino() {
        for (int i = 0; i < currentTetromino->shape.size(); ++i) {
            for (int j = 0; j < currentTetromino->shape[i].size(); ++j) {
                if (currentTetromino->shape[i][j]) {
                    board[currentTetromino->y + i][currentTetromino->x + j] = 1;
                }
            }
        }
        spawnTetromino();
        clearLines();
    }

    // Rotate the current tetromino
    void rotateTetromino() {
        vector<vector<int>> originalShape = currentTetromino->shape;
        int originalX = currentTetromino->x;
        int originalY = currentTetromino->y;

        int rows = currentTetromino->shape.size();
        int cols = currentTetromino->shape[0].size();
        vector<vector<int>> rotated(cols, vector<int>(rows));

        // Rotate the matrix 90 degrees clockwise
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                rotated[j][rows - 1 - i] = currentTetromino->shape[i][j];
            }
        }

        currentTetromino->shape = rotated;

        if (checkCollision()) {
            currentTetromino->shape = originalShape;
            currentTetromino->x = originalX;
            currentTetromino->y = originalY;
        }
    }

    // Move the tetromino left
    void moveTetrominoLeft() {
        currentTetromino->x--;
        if (checkCollision()) {
            currentTetromino->x++;
        }
    }

    // Move the tetromino right
    void moveTetrominoRight() {
        currentTetromino->x++;
        if (checkCollision()) {
            currentTetromino->x--;
        }
    }

    // Move the tetromino down
    void moveTetrominoDown() {
        currentTetromino->y++;
        if (checkCollision()) {
            currentTetromino->y--;
            placeTetromino();
        }
    }

    // Soft drop
    void softDrop() {
        moveTetrominoDown();
    }

    // Hard drop (sudden drop)
    void hardDrop() {
        while (!checkCollision()) {
            currentTetromino->y++;
        }
        currentTetromino->y--;
        placeTetromino();
    }

    // Clear full lines
    void clearLines() {
        for (int i = HEIGHT - 1; i >= 0; --i) {
            bool fullLine = true;
            for (int j = 0; j < WIDTH; ++j) {
                if (board[i][j] == 0) {
                    fullLine = false;
                    break;
                }
            }
            if (fullLine) {
                for (int k = i; k >= 1; --k) {
                    for (int j = 0; j < WIDTH; ++j) {
                        board[k][j] = board[k - 1][j];
                    }
                }
                for (int j = 0; j < WIDTH; ++j) {
                    board[0][j] = 0;
                }

                linesCleared++;
                score += 10; // Award 10 points for clearing a line

                // Increase level and speed after every 10 lines cleared
                if (linesCleared % 5 == 0) {
                    level++;
                    fallingSpeed -= 50; // Decrease the delay to increase speed
                }
            }
        }
    }

    // Display the game board
    void display() {

        gotoxy(0, 0);  // Move cursor to the top-left corner
        
        cout<<"             =>>   Tetris GAME   <<=  "<<endl;
        cout << "Press ESC to quit, Arrow keys to move the tetromino." <<endl<< endl;

        for (int i = 0; i < HEIGHT; ++i) {
            cout << "#";  // Left border
            for (int j = 0; j < WIDTH; ++j) {
                bool isTetrominoPart = false;
                for (int tY = 0; tY < currentTetromino->shape.size(); ++tY) {
                    for (int tX = 0; tX < currentTetromino->shape[tY].size(); ++tX) {
                        if (currentTetromino->shape[tY][tX] && currentTetromino->x + tX == j && currentTetromino->y + tY == i) {
                            isTetrominoPart = true;
                            break;
                        }
                    }
                    if (isTetrominoPart) break;
                }

                if (board[i][j] || isTetrominoPart) {
                    cout << "[]";  // Part of tetromino or filled cell
                } else {
                    cout << "  ";  // Empty space
                }
            }
            cout << "#";  // Right border
            cout << endl;
        }

        // Display score and level at the bottom of the board
        gotoxy(0, HEIGHT + 1);  // Move cursor to the line below the board
        cout <<endl <<endl << endl<< "--> Score: " << score << " || Level: " << level <<"    "<< endl;
    }

    // Check for game over
    bool isGameOver() {
        for (int j = 0; j < WIDTH; ++j) {
            if (board[0][j] != 0) {  // If the top row is occupied, game over
                return true;
            }
        }
        return false;
    }

    // Handle user input
    void handleInput() {
        if (_kbhit()) {
            char ch = _getch(); // Get the pressed key
            if (ch == 27) { // ESC key to quit
                gameOver = true;
            } else if (ch == 75) { // Left arrow key
                moveTetrominoLeft();
            } else if (ch == 77) { // Right arrow key
                moveTetrominoRight();
            } else if (ch == 80) { // Down arrow key
                softDrop();
            } else if (ch == 72) { // Up arrow key
                rotateTetromino();
            } else if (ch == 32) { // Spacebar for hard drop
                hardDrop();
            }
        }
    }

    // Main game loop
    void run() {
        while (true) {
            while (!gameOver) {
                handleInput();
                display();
                moveTetrominoDown();
                if (isGameOver()) {
                    gameOver = true;
                    if(score > highScore){
                        highScore = score;
                    }
                }
                Sleep(fallingSpeed); // Adjust falling speed based on the level
            }

            // Don't print the "Game Over" and restart prompt if the user chooses to restart
            char restartChoice;
            if (gameOver) {
                cout <<endl<< "Do you want to play again? (y/n): ";
                cin >> restartChoice;

                if (restartChoice == 'y' || restartChoice == 'Y') {
                    // Reset the game
                    board = vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 0));
                    score = 0;
                    level = 1;
                    linesCleared = 0;
                    fallingSpeed = 500;
                    gameOver = false;
                    spawnTetromino();
                } else {
                    cout<<endl<<"[^_^] Thank You For Playing !!!"<<endl ;
                    cout<<"--> HighScore : "<<highScore<< endl;
                    break; // Exit the game
                }
            }
        }
    }
};

int main() {
    hideCursor(); // Hide cursor at the start
    TetrisGame game;
    game.run();
    showCursor(); // Show cursor at the end
    return 0;
}