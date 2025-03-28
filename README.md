# Tetris Game By Pro Programmers

This is a simple implementation of the classic Tetris game written in C++ for the console.

## Team Members

* Nirmal Nakum - 202401022
* Ayush Donga - 202401052
* Rajveersinh Gohil - 202401057

 ## Files
>> game code :- [tetris.cpp](./tetris.cpp)


## Demo Video of Game

https://github.com/user-attachments/assets/b77abd94-ce59-4845-b8a0-fce5f6e07029


## Game Controls

* **Left Arrow Key:** Move the falling tetromino to the left.
* **Right Arrow Key:** Move the falling tetromino to the right.
* **Down Arrow Key:** Soft drop - move the falling tetromino down one row.
* **Up Arrow Key:** Rotate the falling tetromino clockwise.
* **Spacebar:** Hard drop - instantly drop the falling tetromino to the lowest possible position.
* **ESC Key:** Quit the game.
* **y (or Y):** When the game ends, press 'y' to play again.
* **n (or N):** When the game ends, press 'n' to exit the application.

## Game Description

The goal of Tetris is to prevent the accumulating blocks from reaching the top of the playing field. You achieve this by strategically rotating and positioning falling blocks (tetrominoes) to create solid horizontal lines. When a line is completed, it disappears, and you earn points.

* **Tetrominoes:** The game features seven different tetromino shapes (I, O, T, L, J, S, Z) that fall randomly from the top of the screen.
* **Gameplay:** You can move the falling tetrominoes left, right, and rotate them. You can also make them fall faster using the down arrow key (soft drop) or instantly drop them using the spacebar (hard drop).
* **Scoring:** You earn points for each line you clear. Clearing multiple lines simultaneously awards more points.
* **Level:** The game has increasing levels of difficulty. As you clear more lines, the game level increases, and the tetrominoes fall at a faster speed.
* **Game Over:** The game ends when a new tetromino cannot be placed on the board because the top row is already occupied.
* **High Score:** The game keeps track of the highest score achieved during the current session.
* **Restart:** After a game over, you have the option to restart the game.

## Code Structure

The code is organized into the following main parts:

* **Includes:** Includes necessary header files for input/output, vectors, random number generation, time, and Windows-specific console functions.
* **Constants:** Defines game constants like `WIDTH`, `HEIGHT`, and `NUM_TETROMINOS`.
* **Enums:** Defines the `TetrominoType` enum to represent the different tetromino shapes.
* **`Tetromino` Class:**
    * Represents a single tetromino.
    * Stores its shape (as a 2D vector), x and y coordinates on the board.
    * Provides a `getShape()` method to define the shape of each tetromino type.
* **`gotoxy()` Function:** A Windows-specific function to move the console cursor to a specific position.
* **`hideCursor()` and `showCursor()` Functions:** Windows-specific functions to hide and show the console cursor.
* **`TetrisGame` Class:**
    * Represents the main game logic.
    * Contains the game board (a 2D vector), the current falling tetromino, score, level, lines cleared, falling speed, high score, and game over flag.
    * Includes methods for:
        * `spawnTetromino()`: Creates a new random tetromino.
        * `checkCollision()`: Checks if the current tetromino collides with the board or boundaries.
        * `placeTetromino()`: Places the current tetromino on the board.
        * `rotateTetromino()`: Rotates the current tetromino.
        * `moveTetrominoLeft()`, `moveTetrominoRight()`, `moveTetrominoDown()`: Moves the current tetromino.
        * `softDrop()`, `hardDrop()`: Controls the falling speed.
        * `clearLines()`: Checks for and clears full horizontal lines.
        * `display()`: Draws the game board and information on the console.
        * `isGameOver()`: Checks if the game has ended.
        * `handleInput()`: Reads and processes user input.
        * `run()`: The main game loop.
* **`main()` Function:**
    * Hides the cursor.
    * Creates an instance of the `TetrisGame` class.
    * Starts the game loop.
    * Shows the cursor after the game ends.
 
## How to Compile and Run

1.  **Save the code:** Save the provided C++ code as a `.cpp` file (e.g., `tetris.cpp`).
2.  **Compile:** Open a command prompt or terminal and use a C++ compiler (like g++) to compile the code. Make sure you have a C++ compiler installed on your system.

    ```bash
    g++ tetris.cpp -o tetris
    ```

    If you encounter issues related to `windows.h` and `conio.h`, ensure you are compiling on a Windows system or have a compatible environment. These headers are specific to Windows.

3.  **Run:** Execute the compiled program.

    ```bash
    ./tetris
    ```

    On Windows, you might need to run:

    ```bash
    tetris.exe
    ```

## Dependencies

This game relies on the following:

* **Standard C++ Library:** For basic functionalities like input/output, vectors, and random number generation.
* **`windows.h`:** For Windows-specific functions like `COORD`, `SetConsoleCursorPosition`, `GetStdHandle`, and `CONSOLE_CURSOR_INFO`. This header is required for cursor manipulation and the `gotoxy()` function.
* **`conio.h`:** For console input/output functions like `_kbhit()` and `_getch()`, which allow non-blocking keyboard input.

**Note:** Due to the use of `windows.h` and `conio.h`, this code is primarily intended for compilation and execution on Windows systems using a compatible compiler. To make it cross-platform, you would need to replace these Windows-specific functions with platform-independent alternatives.
