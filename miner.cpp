#include <iostream>
#include <fstream>
#include <windows.h>
#include <math.h>
using namespace std;
const int maze_row = 34;
const int maze_col = 105;
char maze[maze_row][maze_col];
void gotoxy(int x, int y);
void loadMaze();
void printMaze();
void ManicMoveLeft();
void ManicMoveRight();
void FindManicCurrentLocation();
void ManicJump();
void ManicFalling();
bool isManicFalling();
bool isRightMovePossible(int temp_row_idx, int temp_col_idx);
bool isLeftMovePossible(int temp_row_idx, int temp_col_idx);
// Checks Varaible on Player Movement
string MoveRightStatus = "Obstacle_Present";//Variable to keep status for moving in right Wheather there is a obstacle present at right
string MoveLeftStatus = "Obstacle_Present";//Variable to keep status for moving in Left Wheather there is a obstacle present at Left
int Manic_Current_Row = 0;
int Manic_Current_Col = 0;
string ManicFallingStatus = "NOT FALLING"
// Checks Variable Ends
int main()
{
    bool gameRunning = true;
    loadMaze();
    system("cls");
    printMaze();
    while (gameRunning)
    {
        Sleep(50);
        if (GetAsyncKeyState(VK_LEFT))
        {
            ManicMoveLeft();
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            ManicMoveRight();
        }
        else if(GetAsyncKeyState(VK_SPACE)){
            ManicJump();
        }
    }
    return 0;
}
void loadMaze()
{
    string line;
    int row_idx = 0;
    fstream file;
    file.open("maze.txt", ios::in);
    while (!file.eof())
    {
        getline(file, line);
        for (int col_idx = 0; col_idx < maze_col; col_idx++)
        {
            maze[row_idx][col_idx] = line[col_idx];
        }
        row_idx++;
    }
    file.close();
}
void printMaze()
{
    for (int row_idx = 0; row_idx < maze_row; row_idx++)
    {
        for (int col_idx = 0; col_idx < maze_col; col_idx++)
        {
            cout << maze[row_idx][col_idx];
        }
        cout << '\n';
    }
}
void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}
bool isRightMovePossible(int temp_row_idx, int temp_col_idx)
{
    int temp_count = 0;
    if (maze[temp_row_idx][temp_col_idx + 1] == ' ')
    {
        temp_count++;
    }
    if (maze[temp_row_idx + 1][temp_col_idx + 1] == ' ')
    {
        temp_count++;
    }
    if (maze[temp_row_idx + 2][temp_col_idx + 1] == ' ')
    {
        temp_count++;
    }
    if (temp_count == 3)
    {
        return true;
    }
    return false;
}
bool isLeftMovePossible(int temp_row_idx, int temp_col_idx)
{
    int temp_count = 0;
    if (maze[temp_row_idx][temp_col_idx - 1] == ' ')
    {
        temp_count++;
    }
    if (maze[temp_row_idx + 1][temp_col_idx - 1] == ' ')
    {
        temp_count++;
    }
    if (maze[temp_row_idx + 2][temp_col_idx - 1] == ' ')
    {
        temp_count++;
    }
    if (temp_count == 3)
    {
        return true;
    }
    return false;
}
void ManicMoveLeft()
{
    if(ManicFallingStatus == "NOT FALLING"){
    for (int row_idx = 0; row_idx < maze_row; row_idx++)
    {
        for (int col_idx = 0; col_idx < maze_col; col_idx++)
        {
           if(maze[row_idx][col_idx] == '/' && isLeftMovePossible(row_idx,col_idx)){
               MoveLeftStatus = "No_Obstacle";
           }
           if(MoveLeftStatus == "No_Obstacle"){
            if (maze[row_idx][col_idx] == '/')
            {
                    maze[row_idx][col_idx] = ' ';
                    gotoxy(col_idx, row_idx);
                    cout << maze[row_idx][col_idx];
                    maze[row_idx][col_idx - 1] = '/';
                    gotoxy(col_idx - 1, row_idx);
                    cout << maze[row_idx][col_idx - 1];
            }
            else if (maze[row_idx][col_idx] == '\\')
            {
                
                    maze[row_idx][col_idx] = ' ';
                    gotoxy(col_idx, row_idx);
                    cout << maze[row_idx][col_idx];
                    maze[row_idx][col_idx - 1] = '\\';
                    gotoxy(col_idx - 1, row_idx);
                    cout << maze[row_idx][col_idx - 1];
            }
           }
        }
    }
    MoveLeftStatus = "Obstacle";
    }
}
void ManicMoveRight()
{
    if(ManicFallingStatus == "NOT FALLING"){
    for (int row_idx = 0; row_idx < maze_row; row_idx++)
    {
        for (int col_idx = maze_col - 1; col_idx >= 0; col_idx--)
        {
            if (maze[row_idx][col_idx] == '\\' && isRightMovePossible(row_idx, col_idx))
            {
                MoveRightStatus = "No_Obstacle";
            }
            if (MoveRightStatus == "No_Obstacle")
            {
                if (maze[row_idx][col_idx] == '/')
                {
                    maze[row_idx][col_idx] = ' ';
                    gotoxy(col_idx, row_idx);
                    cout << maze[row_idx][col_idx];
                    maze[row_idx][col_idx + 1] = '/';
                    gotoxy(col_idx + 1, row_idx);
                    cout << maze[row_idx][col_idx + 1];
                }
                else if (maze[row_idx][col_idx] == '\\')
                {
                    maze[row_idx][col_idx] = ' ';
                    gotoxy(col_idx, row_idx);
                    cout << maze[row_idx][col_idx];
                    maze[row_idx][col_idx + 1] = '\\';
                    gotoxy(col_idx + 1, row_idx);
                    cout << maze[row_idx][col_idx + 1];
                }
            }
        }
    }
    MoveRightStatus = "Obstacle_Present";
    }
}
void FindManicCurrentLocation(){
    string isLocationFound = "NOT";
    for(int temp_row_idx = 0;temp_row_idx < maze_row;temp_row_idx++){
        for(int temp_col_idx = 0;temp_col_idx < maze_col;temp_col_idx++){
            if(maze[temp_row_idx][temp_col_idx] == '/'){
                Manic_Current_Row = temp_row_idx;
                Manic_Current_Col = temp_col_idx;
                isLocationFound = "FOUND";
                break;
            }
        }
        if(isLocationFound == "FOUND"){
            break;
        }
    }
}
void ManicJump(){

}
bool isMinnerFalling(){
   if(maze[Manic_Current_Row+3][Manic_Current_Col] == ' ' && maze[Manic_Current_Row+3][Manic_Current_Col+1] == ' '){
       ManicFallingStatus = "FALLING";
       return true;
   } 
   ManicFallingStatus = "NOT FALLING";
   return false;
}
void ManicFalling(){
if(isManicFalling())
}
