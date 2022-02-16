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
void minerMoveLeft();
void minerMoveRight();
bool isRightMovePossible(int temp_row_idx, int temp_col_idx);
bool isLeftMovePossible(int temp_row_idx, int temp_col_idx);
// Temperary Checks Varaible
string MoveRightStatus = "Alert";
string MoveLeftStatus = "Alert";
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
            minerMoveLeft();
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            minerMoveRight();
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
void minerMoveLeft()
{
    string status = "Relax"; // Variable to Store Status as is there any Wall Present at left Side
    for (int row_idx = 0; row_idx < maze_row; row_idx++)
    {
        for (int col_idx = 0; col_idx < maze_col; col_idx++)
        {

            if (maze[row_idx][col_idx] == '/')
            {
                if (maze[row_idx][col_idx - 1] == ' ')
                {
                    maze[row_idx][col_idx] = ' ';
                    gotoxy(col_idx, row_idx);
                    cout << maze[row_idx][col_idx];
                    maze[row_idx][col_idx - 1] = '/';
                    gotoxy(col_idx - 1, row_idx);
                    cout << maze[row_idx][col_idx - 1];
                }
                else
                {
                    status = "Alert";
                }
            }
            else if (maze[row_idx][col_idx] == '\\')
            {
                if (status == "Relax")
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
}
void minerMoveRight()
{
    for (int row_idx = 0; row_idx < maze_row; row_idx++)
    {
        for (int col_idx = maze_col - 1; col_idx >= 0; col_idx--)
        {
            if (maze[row_idx][col_idx] == '\\' && isRightMovePossible(row_idx, col_idx))
            {
                MoveRightStatus = "Relax";
            }
            if (MoveRightStatus == "Relax")
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
    MoveRightStatus = "Alert";
}