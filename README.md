# Tetris Game By Pro Programmers  

This is a **console-based Tetris game** implemented in **C++**. The game follows the classic Tetris mechanics where players stack tetrominoes to complete full lines and score points. The difficulty increases as the level progresses, making the game more challenging over time.

## Members  

- **Nirmal Nakum** => 202401022  
- **Ayush Donga** => 202401052  
- **Rajveersinh Gohil** => 202401057  

## Requirements  

- A **C++ compiler** (e.g., GCC, MSVC)  
- **Windows operating system** (due to usage of `conio.h` and `windows.h`)  

## Files  

- Game code: [`tetris.cpp`](./tetris.cpp)  

## How to Play  

1. **Controls**:  
   - **← Left Arrow** → Move the tetromino left  
   - **→ Right Arrow** → Move the tetromino right  
   - **↓ Down Arrow** → Soft drop (move tetromino down faster)  
   - **↑ Up Arrow** → Rotate the tetromino  
   - **Spacebar** → Hard drop (instantly places the tetromino)  
   - **ESC** → Quit the game  

2. **Objective**:  
   - Stack the falling tetrominoes to complete full lines.  
   - When a line is fully filled, it disappears, and the score increases.  
   - The game speed increases every time 5 lines are cleared.  

3. **Game Over**:  
   - If the tetrominoes stack to the top of the screen, the game ends.  
   - The player is given an option to restart or exit.  

## Features  

✅ **Classic Tetris Mechanics** – Rotate, move, and drop tetrominoes.  
✅ **Line Clearing** – Full rows disappear, increasing the score.  
✅ **Level & Speed Increase** – The game speeds up as more lines are cleared.  
✅ **Restart & High Score Tracking** – Save your best score and try again.  
✅ **Console-Based Interface** – Runs directly in the terminal.  

## Code Overview  

### Classes and Methods  

- **`Tetromino` class** – Handles individual tetromino shapes and rotations.  
- **`TetrisGame` class** – Manages the game logic, including:  
  - `spawnTetromino()` → Generates a random tetromino.  
  - `checkCollision()` → Checks if a tetromino is hitting a wall or another block.  
  - `placeTetromino()` → Places a tetromino when it reaches the bottom.  
  - `clearLines()` → Removes completed lines and increases the score.  
  - `moveTetrominoLeft()`, `moveTetrominoRight()`, `moveTetrominoDown()` → Controls movement.  
  - `rotateTetromino()` → Rotates the tetromino.  
  - `display()` → Renders the game board.  
  - `handleInput()` → Captures user input (arrow keys, spacebar, etc.).  
  - `run()` → Runs the game loop.  

### Special Functions  

- **`gotoxy(x, y)`** → Moves the cursor to a specific position in the console.  
- **`hideCursor()` / `showCursor()`** → Hides/shows the cursor for a clean interface.  

## How to Compile & Run  

### **Windows (MSVC or MinGW)**  

1. Open **Command Prompt** or **PowerShell**.  
2. Navigate to the directory containing `tetris.cpp`.  
3. Compile the code using **GCC**:  
   ```bash
   g++ tetris.cpp -o TetrisGame
