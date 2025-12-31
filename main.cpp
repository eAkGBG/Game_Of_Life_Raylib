// A simple raylib test app.

#include "raylib.h"
#include "raymath.h"
#include <string>
#include <iostream>

const int SCREEN_SIZE = 500;
//Calculate play feild grid.
const int GRID_COLS = 50;
const int GRID_ROWS = 50;
const int CELL_SIZE = SCREEN_SIZE/50;


enum class LifeForm : bool {
    Dead = false,
    Alive = true
};
struct Cell {
    LifeForm state = LifeForm::Dead; //current status
    int liveNeighbors = 0;
};

class GameBoard{
    public:
        // Constructor – initialise board with random states
        GameBoard() {
            std::srand(static_cast<unsigned>(std::time(nullptr))); // seed RNG once
            for (int r = 0; r < GRID_ROWS; ++r) {
                for (int c = 0; c < GRID_COLS; ++c) {
                    board[r][c].state = (std::rand() % 2 == 0) ? LifeForm::Dead : LifeForm::Alive;
                    board[r][c].liveNeighbors = 0;
                }
            }
        }
        void render_parsed(){
            for (int r = 0; r < GRID_ROWS; ++r){
                for (int c = 0; c < GRID_COLS; ++c){
                    if (board[r][c].state == LifeForm::Alive){
                        DrawRectangle(r * CELL_SIZE, c * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
                    }
                    //if (board[r][c].state == LifeForm::Dead){
                        //DrawRectangle(r + CELL_SIZE, c + CELL_SIZE, CELL_SIZE, CELL_SIZE, RAYWHITE);
                    //}
                    board[r][c].liveNeighbors = 0;
                }
            }
        }
        void parse(){
            for (int r = 0; r < GRID_ROWS; ++r){
                for (int c = 0; c < GRID_COLS; ++c){
                    if(r > 0 && r < GRID_ROWS -1 ){
                        if (board[r -1][c - 1].state == LifeForm::Alive) board[r][c].liveNeighbors++;
                        if (board[r -1][c + 1].state == LifeForm::Alive) board[r][c].liveNeighbors++;
                        if (board[r -1][c].state == LifeForm::Alive) board[r][c].liveNeighbors++;
                        if (board[r +1][c - 1].state == LifeForm::Alive) board[r][c].liveNeighbors++;
                        if (board[r +1][c + 1].state == LifeForm::Alive) board[r][c].liveNeighbors++;
                        if (board[r +1][c].state == LifeForm::Alive) board[r][c].liveNeighbors++;
                        
                    }
                    if(c > 0 && c < GRID_COLS -1){
                        if (board[r][c - 1].state == LifeForm::Alive) board[r][c].liveNeighbors++;
                        if (board[r][c + 1].state == LifeForm::Alive) board[r][c].liveNeighbors++;
                        
                    }
                    //board[r][c].state = LifeForm::Alive;
                    //std::string msg = "you are in a cell: " + std::to_string(r) + "," + std::to_string(c);
                    //DrawText(msg.c_str() , 20,20,20, BLACK);
                    //std::cout << "You are in a cell: " << r << "," << c << "and lifeform state is:" << static_cast<int>(board[r][c].state) << std::endl;
                }
            }
            for (int r = 0; r < GRID_ROWS; ++r){
                for (int c = 0; c < GRID_COLS; ++c){
                    if(board[r][c].state == LifeForm::Alive){
                        if(board[r][c].liveNeighbors < 2) board[r][c].state = LifeForm::Dead;
                        if(board[r][c].liveNeighbors == 2 || board[r][c].liveNeighbors == 3) board[r][c].state = LifeForm::Alive;
                        if(board[r][c].liveNeighbors > 3) board[r][c].state = LifeForm::Dead;
                        
                    }
                    if(board[r][c].state == LifeForm::Dead){
                        if (board[r][c].liveNeighbors == 3) board[r][c].state = LifeForm::Alive;
                    }
                }
            }
        }
    private:
        Cell board[GRID_ROWS][GRID_COLS];
};

void DrawGrid(int cols, int rows, int cellSize){
    //draw vertical lines
    for (int i = 0; i <= cols; ++i){
        int x = i * cellSize;
        DrawLine(x,0,x, rows*cellSize, LIGHTGRAY);
    }
    //draw horizontal lines
    for (int j = 0; j <= rows; ++j){
        int y = j * cellSize;
        DrawLine(0,y,cols*cellSize,y,LIGHTGRAY);
    }
}

void game_render(){

}

int main(void)
{
    const int screenWidth  = SCREEN_SIZE;
    const int screenHeight = SCREEN_SIZE;
    InitWindow(screenWidth, screenHeight, "raylib basic window"); //Important to call init window before doing calculations on font and probably other stuff!
    SetTargetFPS(60);
    
    
    int textWidth = MeasureText("Congrats! You created your first window!",20); //20 fontsize
    int textStartX = (SCREEN_SIZE - textWidth) / 2;
    std::string debug_textStartX = std::to_string(textStartX);
    std::string debug_textWidth = std::to_string(textWidth);
    GameBoard game;

    float elapsedTime = 0.0; //keep track of time!

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
        elapsedTime +=dt;

        BeginDrawing();
            ClearBackground(RAYWHITE);
            //play feild
            DrawGrid(GRID_COLS,GRID_ROWS,CELL_SIZE);
            if(elapsedTime >= 0.2){
                game.parse();
                elapsedTime = 0.0;
            }
            game.render_parsed();
            DrawText("Congrats! You created your first window!", textStartX, 250, 20, DARKPURPLE);
            //DrawText(debug_textStartX.c_str(), 10,20,20,BLACK);
            //DrawText(debug_textWidth.c_str(), 10,45,20,BLACK);
            
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
