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
bool ManicMoveLeft();
bool ManicMoveRight();
bool ManicMoveDown();
bool ManicMoveUp();
void SetManicCurrentLocation(); // To Store the Manic Row and Column position in Manic_Current_Row and Manic_Current_Col Variables
bool JumpManic();
bool FellTheManic();
bool isManicFalling();
bool isRightMovePossible(int temp_row_idx, int temp_col_idx);
bool isLeftMovePossible(int temp_row_idx, int temp_col_idx);
bool isDownMovePossible(int temp_row_idx, int temp_col_idx);
bool isUpHurdlePresent(int temp_row_idx, int temp_col_idx);
void MoveEnemy1Horizontal();
bool isRightEnemy1Possible(int temp_row_idx, int temp_col_idx);
bool isLeftEnemy1Possible(int temp_row_idx, int temp_col_idx);
void MoveEnemy1Right();
void MoveEnemy1Left();
bool isClimbPossibleLevel1();
void ClimbLevel1();
string isEnemyStuck = "NOT STUCK";
int laddder_X = 14; // The Left HEad of Manic should be Equal to this to climb
int ladder_Y = 6;
// Checks Varaible on Player Movement
string MoveRightStatus = "Obstacle_Present"; // Variable to keep status for moving in right Wheather there is a obstacle present at right
string MoveLeftStatus = "Obstacle_Present";  // Variable to keep status for moving in Left Wheather there is a obstacle present at Left
string MoveDownStatus = "Obstacle_Present";  // Variable to keep status for moving down wheather there is a obstacle present at down
string MoveUpStatus = "Obstacle_Present";    // Variable to keep Status for moving Up wheather there is a obstacle present at up
int ManicJumpCount = 0;
int ManicJumpLimit = 5;               // Manic Can jum 5 rows up
string ManicShould = "NOT FALL";      // To Choose wheather manic should Move Left or He Should fall
string ManicRightJumpStatus = "FALL"; // To Choose wheather manic should Move Right or He Should fall
// int ManicRightJumpLimit = 0;
// int ManicLeftJumpLimit = 0;
int Manic_Current_Row = 0;                 // To Store Manic Current Row position
int Manic_Current_Col = 0;                 // To Store Manic Current Column Position
string ManicFallingStatus = "NOT FALLING"; // Variable to Store Status of Manic Wheather Manic is Falling or Not
string ManicJumpingStatus = "NOT JUMPING";
// Checks Variable Ends
int main()
{
    string left_pressed = "NOT PRESSED";
    string right_pressed = "NOT PRESSED";
    bool gameRunning = true;
    loadMaze();
    system("cls");
    printMaze();
    bool Temp_Manic_Falling_Status;
    while (gameRunning)
    {
        Sleep(50);
        MoveEnemy1Horizontal();
        Temp_Manic_Falling_Status = isManicFalling();
        if (GetAsyncKeyState(VK_LEFT))
        {
           gameRunning= ManicMoveLeft();
        }
        else if (GetAsyncKeyState(VK_RIGHT))
        {
            gameRunning = ManicMoveRight();
        }
        if (ManicFallingStatus == "FALLING" && ManicJumpingStatus == "NOT JUMPING")
        {
            FellTheManic();
        }
        if (ManicJumpingStatus == "NOT JUMPING" && ManicFallingStatus == "NOT FALLING")
        {
            if (GetAsyncKeyState(VK_SPACE))
            {
                gameRunning = JumpManic();
                ManicJumpCount++;
                ManicJumpingStatus = "JUMPING";
            }
        }
        if (ManicJumpingStatus == "JUMPING")
        {
            if (ManicJumpCount == ManicJumpLimit)
            {
                ManicJumpingStatus = "NOT JUMPING";
                ManicJumpCount = 0;
            }
            else
            {
                gameRunning = JumpManic();
                ManicJumpCount++;
            }
        }
        if(GetAsyncKeyState(VK_NUMPAD5)){

        }

        if(GetAsyncKeyState(VK_ESCAPE)){
            cout << "Game Over";
            gameRunning = false;
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
    if (maze[temp_row_idx][temp_col_idx + 1] == ' ' || maze[temp_row_idx][temp_col_idx + 1] == '0' || maze[temp_row_idx][temp_col_idx + 1] == '+')
    {
        temp_count++;
    }
    if (maze[temp_row_idx + 1][temp_col_idx + 1] == ' ' || maze[temp_row_idx + 1][temp_col_idx + 1] == '0' || maze[temp_row_idx + 1][temp_col_idx + 1] == '+')
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
    if (maze[temp_row_idx][temp_col_idx - 1] == ' ' || maze[temp_row_idx][temp_col_idx - 1] == '0' || maze[temp_row_idx][temp_col_idx - 1] == '+' || maze[temp_row_idx][temp_col_idx - 1] == '|')
    {
        temp_count++;
    }
    if (maze[temp_row_idx + 1][temp_col_idx - 1] == ' ' || maze[temp_row_idx + 1][temp_col_idx - 1] == '0' || maze[temp_row_idx + 1][temp_col_idx - 1] == '+' || maze[temp_row_idx + 1][temp_col_idx - 1] == '|')
    {
        temp_count++;
    }
    if (maze[temp_row_idx + 2][temp_col_idx - 1] == ' ' || maze[temp_row_idx + 2][temp_col_idx - 1] == '0' || maze[temp_row_idx + 2][temp_col_idx - 1] == '+' || maze[temp_row_idx + 2][temp_col_idx - 1] == '|')
    {
        temp_count++;
    }
    if (temp_count == 3)
    {
        return true;
    }
    return false;
}
bool isDownMovePossible(int temp_row_idx, int temp_col_idx)
{
    if (maze[temp_row_idx + 1][temp_col_idx] == ' ' || maze[temp_row_idx + 1][temp_col_idx] == '0' || maze[temp_row_idx + 1][temp_col_idx + 1] == '+')
    {
        return true;
    }
    return false;
}
bool isUpHurdlePresent(int temp_row_idx, int temp_col_idx)
{
    if (maze[temp_row_idx - 1][temp_col_idx] == ' ' && maze[temp_row_idx - 1][temp_col_idx + 1] == ' ')
    {
        return false;
    }
    return true;
}

bool ManicMoveLeft()
{
    for (int row_idx = 0; row_idx < maze_row; row_idx++)
    {
        for (int col_idx = 0; col_idx < maze_col; col_idx++)
        {
            if (maze[row_idx][col_idx] == '/' && isLeftMovePossible(row_idx, col_idx))
            {
                if(maze[row_idx+1][col_idx-1] == '0' || maze[row_idx+1][col_idx-1] == '+' || maze[row_idx+2][col_idx-1] == '0' || maze[row_idx+2][col_idx-1] == '+' || maze[row_idx][col_idx-1] =='0' || maze[row_idx][col_idx-1] == '+'){
                    return false;
                }
                MoveLeftStatus = "No_Obstacle";
            }
            if (MoveLeftStatus == "No_Obstacle")
            {
                if (maze[row_idx][col_idx] == '/')
                {
                    maze[row_idx][col_idx] = ' ';
                    gotoxy(col_idx, row_idx);
                    cout << ' ';
                    maze[row_idx][col_idx - 1] = '/';
                    gotoxy(col_idx - 1, row_idx);
                    cout << maze[row_idx][col_idx - 1];
                }
                else if (maze[row_idx][col_idx] == '\\')
                {
                    maze[row_idx][col_idx] = ' ';
                    gotoxy(col_idx, row_idx);
                    cout << ' ';
                    maze[row_idx][col_idx - 1] = '\\';
                    gotoxy(col_idx - 1, row_idx);
                    cout << maze[row_idx][col_idx - 1];
                }
                
            }
        }
    }
    MoveLeftStatus = "Obstacle";
    return true;
}
bool ManicMoveRight()
{
    if (ManicFallingStatus == "NOT FALLING" || ManicJumpingStatus == "JUMPING")
    {
        for (int row_idx = 0; row_idx < maze_row; row_idx++)
        {
            for (int col_idx = maze_col - 1; col_idx >= 0; col_idx--)
            {
                if (maze[row_idx][col_idx] == '\\' && isRightMovePossible(row_idx, col_idx))
                {
                     if(maze[row_idx+1][col_idx+1] == '0' || maze[row_idx+1][col_idx+1] == '+' || maze[row_idx+2][col_idx+1] == '0' || maze[row_idx+2][col_idx+1] == '+' || maze[row_idx][col_idx+1] == '0' || maze[row_idx][col_idx+1] == '+'){
                        return false;
                    }
                    MoveRightStatus = "No_Obstacle";
                }
                if (MoveRightStatus == "No_Obstacle")
                {
                    if (maze[row_idx][col_idx] == '/')
                    {
                        maze[row_idx][col_idx] = ' ';
                        gotoxy(col_idx, row_idx);
                        cout << ' ';
                        maze[row_idx][col_idx + 1] = '/';
                        gotoxy(col_idx + 1, row_idx);
                        cout << maze[row_idx][col_idx + 1];
                    }
                    else if (maze[row_idx][col_idx] == '\\')
                    {
                        maze[row_idx][col_idx] = ' ';
                        gotoxy(col_idx, row_idx);
                        cout << ' ';
                        maze[row_idx][col_idx + 1] = '\\';
                        gotoxy(col_idx + 1, row_idx);
                        cout << maze[row_idx][col_idx + 1];
                    }
                   
                }
            }
        }
        MoveRightStatus = "Obstacle_Present";
    }
    return true;
}
bool ManicMoveDown()
{
    SetManicCurrentLocation();
    for (int temp_row = Manic_Current_Row + 2; temp_row >= Manic_Current_Row; temp_row--)
    {
        for (int temp_col = Manic_Current_Col; temp_col < Manic_Current_Col + 2; temp_col++)
        {
            if (isDownMovePossible(temp_row, temp_col))
            {
                 if(maze[temp_row+3][temp_col] == '0' || maze[temp_row+3][temp_col] == '+'){
                    return false;
                }
                MoveDownStatus = "No_Obstacle";
            }
            if (MoveDownStatus == "No_Obstacle")
            {
                if (maze[temp_row][temp_col] == '/')
                {
                    maze[temp_row][temp_col] = ' ';
                    gotoxy(temp_col, temp_row);
                    cout << ' ';
                    maze[temp_row + 1][temp_col] = '/';
                    gotoxy(temp_col, temp_row + 1);
                    cout << maze[temp_row + 1][temp_col];
                }
                else if (maze[temp_row][temp_col] == '\\')
                {
                    maze[temp_row][temp_col] = ' ';
                    gotoxy(temp_col, temp_row);
                    cout << ' ';
                    maze[temp_row + 1][temp_col] = '\\';
                    gotoxy(temp_col, temp_row + 1);
                    cout << maze[temp_row + 1][temp_col];
                }
               
            }
        }
    }
    MoveDownStatus = "Obstacle_Present";
    return true;
}
bool ManicMoveUp()
{
    SetManicCurrentLocation();
    for (int temp_row = Manic_Current_Row; temp_row < Manic_Current_Row + 3; temp_row++)
    {
        for (int temp_col = Manic_Current_Col; temp_col < Manic_Current_Col + 2; temp_col++)
        {
            if (!isUpHurdlePresent(temp_row, temp_col))
            {
                MoveUpStatus = "No_Obstacle";
            }
            if (MoveUpStatus == "No_Obstacle")
            {
                if (maze[temp_row][temp_col] == '/')
                {
                    maze[temp_row][temp_col] = ' ';
                    gotoxy(temp_col, temp_row);
                    cout << ' ';
                    maze[temp_row - 1][temp_col] = '/';
                    gotoxy(temp_col, temp_row - 1);
                    cout << '/';
                }
                else if (maze[temp_row][temp_col] == '\\')
                {
                    maze[temp_row][temp_col] = ' ';
                    gotoxy(temp_col, temp_row);
                    cout << ' ';
                    maze[temp_row - 1][temp_col] = '\\';
                    gotoxy(temp_col, temp_row - 1);
                    cout << '\\';
                }
            }
        }
    }
    MoveUpStatus = "Obstacle_Present";
return true;
}
void SetManicCurrentLocation()
{
    string isLocationFound = "NOT";
    for (int temp_row_idx = 0; temp_row_idx < maze_row; temp_row_idx++)
    {
        for (int temp_col_idx = 0; temp_col_idx < maze_col; temp_col_idx++)
        {
            if (maze[temp_row_idx][temp_col_idx] == '/')
            {
                Manic_Current_Row = temp_row_idx;
                Manic_Current_Col = temp_col_idx;
                isLocationFound = "FOUND";
                break;
            }
        }
        if (isLocationFound == "FOUND")
        {
            break;
        }
    }
}
bool JumpManic()
{
    bool temp_flag = true;
    temp_flag = ManicMoveUp();
return temp_flag;
}
bool isManicFalling()
{
    SetManicCurrentLocation();
    if (maze[Manic_Current_Row + 3][Manic_Current_Col] == ' ' && maze[Manic_Current_Row + 3][Manic_Current_Col + 1] == ' ')
    {
        ManicFallingStatus = "FALLING";
        return true;
    }
    ManicFallingStatus = "NOT FALLING";
    return false;
}
bool FellTheManic()
{
    bool temp_flag = true;
    if (isManicFalling())
    {
        temp_flag = ManicMoveDown();
    }
    return temp_flag;
}
bool isRightEnemy1Possible(int temp_row_idx, int temp_col_idx)
{
    if (maze[temp_row_idx + 2][temp_col_idx + 2] == ' ')
    {
        return true;
    }
    return false;
}
bool isLeftEnemy1Possible(int temp_row_idx, int temp_col_idx)
{
    if (maze[temp_row_idx + 3][temp_col_idx - 2] == ' ')
    {
        return false;
    }
    return true;
}
void MoveEnemy1Right()
{
    string EnemyRightStatus = "Obstacle";
    for (int row_idx = 0; row_idx < maze_row; row_idx++)
    {
        for (int col_idx = 0; col_idx < maze_col; col_idx++)
        {
            if (maze[row_idx][col_idx] == '0')
            {
                if (isRightEnemy1Possible(row_idx, col_idx))
                {
                    EnemyRightStatus = "No Obstacle";
                }
                else{
                    isEnemyStuck = "STUCK";
                }
            }
            if (EnemyRightStatus == "No Obstacle")
            {
                if (maze[row_idx][col_idx] == '0')
                { // Moving the Head of Enemy
                    maze[row_idx][col_idx] = ' ';
                    gotoxy(col_idx, row_idx);
                    cout << ' ';
                    maze[row_idx][col_idx + 1] = '0';
                    gotoxy(col_idx + 1, row_idx);
                    cout << '0';
                    break;
                }
                if (maze[row_idx][col_idx] == '+')
                { // Moving the Body of Enemy
                    maze[row_idx][col_idx] = ' ';
                    gotoxy(col_idx, row_idx);
                    cout << ' ';
                    maze[row_idx][col_idx + 1] = '+';
                    gotoxy(col_idx + 1, row_idx);
                    cout << '+';
                    col_idx = col_idx + 1;
                    // cin >> temp_flag;
                }
                // cin >> temp_flag;
            }
        }
    }
}
void MoveEnemy1Left()
{
    string EnemyLeftStatus = "Obstacle";
    for (int row_idx = 0; row_idx < maze_row; row_idx++)
    {
        for (int col_idx = 0; col_idx < maze_col; col_idx++)
        {
            if (maze[row_idx][col_idx] == '0')
            {
                if (isLeftEnemy1Possible(row_idx, col_idx))
                {
                    EnemyLeftStatus = "No Obstacle";
                }
                else{
                    isEnemyStuck = "NOT STUCK";
                }
            }
            if (EnemyLeftStatus == "No Obstacle")
            {
                if (maze[row_idx][col_idx] == '0')
                { // Moving the Head of Enemy
                    maze[row_idx][col_idx] = ' ';
                    gotoxy(col_idx, row_idx);
                    cout << ' ';
                    maze[row_idx][col_idx - 1] = '0';
                    gotoxy(col_idx - 1, row_idx);
                    cout << '0';
                    break;
                }
                if (maze[row_idx][col_idx] == '+')
                { // Moving the Body of Enemy
                    maze[row_idx][col_idx] = ' ';
                    gotoxy(col_idx, row_idx);
                    cout << ' ';
                    maze[row_idx][col_idx - 1] = '+';
                    gotoxy(col_idx - 1, row_idx);
                    cout << '+';
                    col_idx = col_idx - 1;
                }
            }
        }
    }
}
void MoveEnemy1Horizontal(){
    if(isEnemyStuck == "STUCK"){
        MoveEnemy1Left();
    }
    else if(isEnemyStuck == "NOT STUCK"){
        MoveEnemy1Right();
    }
}
bool isClimbPossibleLevel1(){
    SetManicCurrentLocation();
    if(Manic_Current_Row == 14 && Manic_Current_Col == 6){
        return true;
    }
    return false;
}
void ClimbLevel1(){
    
}