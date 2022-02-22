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
void ClimbLevel1(string &step1, string &step2, int &ladder_count, string &ManicClimbing);
void RemoveManic();
void UpdateManicLadderPosition();
void CalculateLives(int &lives);
void PrintLives(int &lives);
void CalculateKeys();
void PrintKeys();
void ResetLevel1(int &position_X, int &position_Y); // This Function is used to Reset Maze When Manic is Touched with enemy
void crawl_manic();
bool isCrawlPositionPossible(); // This function is used to check wheather manic can crawl or not on certain location
void crawMoveRight();           // This function is used to move right while manic is crawling
bool isRightCrawPossible();     // This Function is used to crawl
void ManicLayDown();            //This function is used to lay down manic
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
int keys_captured = 0;                // This Variable will store the currently captured keys by Manic
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
    int ManicInitialPosition_X = 29;
    int ManicInitialPosition_Y = 6;
    int lives = 3;
    string isManicClimbing = "NOT CLIMBING";
    string step1 = "STOP"; // first go near ladder
    string step2 = "STOP"; // in Secind Step manic will start climbing up
    string step3 = "STOP"; // step3 will be move right when at the upperend of the ladder
    int ladder_count = 0;
    string left_pressed = "NOT PRESSED";
    string right_pressed = "NOT PRESSED";
    bool gameRunning = true;
    loadMaze();
    system("cls");
    printMaze();
    bool Temp_Manic_Falling_Status;
    for (int total_turns = lives; total_turns != 0; total_turns--)
    {
        while (gameRunning)
        {
            Sleep(50);
            MoveEnemy1Horizontal();
            Temp_Manic_Falling_Status = isManicFalling();
            if (GetAsyncKeyState(VK_LEFT))
            {
                gameRunning = ManicMoveLeft();
            }
            else if (GetAsyncKeyState(VK_RIGHT))
            {
                gameRunning = ManicMoveRight();
            }
            if (ManicFallingStatus == "FALLING" && ManicJumpingStatus == "NOT JUMPING" && isManicClimbing == "NOT CLIMBING")
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
            if (GetAsyncKeyState(VK_RETURN))
            {
                ClimbLevel1(step1, step2, ladder_count, isManicClimbing);
            }
            if(GetAsyncKeyState(VK_NUMPAD5)){
                ManicLayDown();
            }

            if (GetAsyncKeyState(VK_ESCAPE))
            {
                cout << "Game Over";
                gameRunning = false;
            }
            PrintLives(lives);
            PrintKeys();
        }

        CalculateLives(lives);
        PrintLives(lives); // When live will be minus it have to remove last location
        ResetLevel1(ManicInitialPosition_X, ManicInitialPosition_Y);
        gameRunning = true;
    }
    return 0;
}
void CalculateLives(int &lives)
{
    lives = lives - 1;
}
void PrintLives(int &lives)
{
    for (int temp_lives = lives, temp_count = 10; temp_lives != 0; temp_lives--, temp_count += 3)
    {
        gotoxy(temp_count, 39);
        cout << "/\\";
        gotoxy(3, 40);
        cout << "Lives: ";
        gotoxy(temp_count, 40);
        cout << "\\/";
        gotoxy(temp_count, 41);
        cout << "/\\";
        cout << '\t';
    }
}
void CalculateKeys(int &key_captured)
{
    key_captured += 1;
}
void PrintKeys()
{
    gotoxy(40, 40);
    cout << "Keys :\t";
    for (int temp_idx = keys_captured; temp_idx != 0; temp_idx--)
    {
        cout << " ! ";
    }
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
void ResetLevel1(int &position_X, int &position_Y)
{
    RemoveManic();
    maze[position_X][position_Y] = '/';
    maze[position_X][position_Y + 1] = '\\';
    maze[position_X + 1][position_Y] = '\\';
    maze[position_X + 1][position_Y + 1] = '/';
    maze[position_X + 2][position_Y] = '/';
    maze[position_X + 2][position_Y + 1] = '\\';
    gotoxy(position_Y, position_X);
    cout << '/';
    gotoxy(position_Y + 1, position_X);
    cout << '\\';
    gotoxy(position_Y, position_X + 1);
    cout << '\\';
    gotoxy(position_Y + 1, position_X + 1);
    cout << '/';
    gotoxy(position_Y, position_X + 2);
    cout << '/';
    gotoxy(position_Y + 1, position_X + 2);
    cout << '\\';
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
    if (maze[temp_row_idx][temp_col_idx + 1] == ' ' || maze[temp_row_idx][temp_col_idx + 1] == '0' || maze[temp_row_idx][temp_col_idx + 1] == '+' || maze[temp_row_idx][temp_col_idx + 1] == '!')
    {
        temp_count++;
    }
    if (maze[temp_row_idx + 1][temp_col_idx + 1] == ' ' || maze[temp_row_idx + 1][temp_col_idx + 1] == '0' || maze[temp_row_idx + 1][temp_col_idx + 1] == '+' || maze[temp_row_idx + 1][temp_col_idx + 1] == '!')
    {
        temp_count++;
    }
    if (maze[temp_row_idx + 2][temp_col_idx + 1] == ' ' || maze[temp_row_idx + 2][temp_col_idx + 1] == '0' || maze[temp_row_idx + 2][temp_col_idx + 1] == '+' || maze[temp_row_idx + 2][temp_col_idx + 1] == '!')
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
    if (maze[temp_row_idx][temp_col_idx - 1] == ' ' || maze[temp_row_idx][temp_col_idx - 1] == '0' || maze[temp_row_idx][temp_col_idx - 1] == '+' || maze[temp_row_idx][temp_col_idx - 1] == '|' || maze[temp_row_idx][temp_col_idx - 1] == '_' || maze[temp_row_idx][temp_col_idx - 1] == '!')
    {
        temp_count++;
    }
    if (maze[temp_row_idx + 1][temp_col_idx - 1] == ' ' || maze[temp_row_idx + 1][temp_col_idx - 1] == '0' || maze[temp_row_idx + 1][temp_col_idx - 1] == '+' || maze[temp_row_idx + 1][temp_col_idx - 1] == '|' || maze[temp_row_idx + 1][temp_col_idx - 1] == '_' || maze[temp_row_idx + 1][temp_col_idx - 1] == '!')
    {
        temp_count++;
    }
    if (maze[temp_row_idx + 2][temp_col_idx - 1] == ' ' || maze[temp_row_idx + 2][temp_col_idx - 1] == '0' || maze[temp_row_idx + 2][temp_col_idx - 1] == '+' || maze[temp_row_idx + 2][temp_col_idx - 1] == '|' || maze[temp_row_idx + 2][temp_col_idx - 1] == '_' || maze[temp_row_idx + 2][temp_col_idx - 1] == '!')
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
    if (maze[temp_row_idx + 1][temp_col_idx] == ' ' || maze[temp_row_idx + 1][temp_col_idx] == '0' || maze[temp_row_idx + 1][temp_col_idx + 1] == '+' || maze[temp_row_idx + 1][temp_col_idx + 1] == '!') // This If condition require editing in changing in condition when it will meet up with enemy
    {
        return true;
    }
    return false;
}
bool isUpHurdlePresent(int temp_row_idx, int temp_col_idx)
{
    if ((maze[temp_row_idx - 1][temp_col_idx] == ' ' && maze[temp_row_idx - 1][temp_col_idx + 1] == ' ') || (maze[temp_row_idx - 1][temp_col_idx] == '_' || maze[temp_row_idx - 1][temp_col_idx + 1] == '_') || (maze[temp_row_idx - 1][temp_col_idx] == '!' || maze[temp_row_idx - 1][temp_col_idx + 1] == '!'))
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
                if (maze[row_idx + 1][col_idx - 1] == '0' || maze[row_idx + 1][col_idx - 1] == '+' || maze[row_idx + 2][col_idx - 1] == '0' || maze[row_idx + 2][col_idx - 1] == '+' || maze[row_idx][col_idx - 1] == '0' || maze[row_idx][col_idx - 1] == '+')
                {
                    return false;
                }
                if (maze[row_idx + 1][col_idx - 1] == '!' || maze[row_idx + 1][col_idx - 1] == '!' || maze[row_idx + 2][col_idx - 1] == '!' || maze[row_idx + 2][col_idx - 1] == '!' || maze[row_idx][col_idx - 1] == '!' || maze[row_idx][col_idx - 1] == '!')
                {
                    keys_captured += 1; // This if condition is checking if there is a key in left then it will update the keys_captured variable
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
                    if (maze[row_idx + 1][col_idx + 1] == '0' || maze[row_idx + 1][col_idx + 1] == '+' || maze[row_idx + 2][col_idx + 1] == '0' || maze[row_idx + 2][col_idx + 1] == '+' || maze[row_idx][col_idx + 1] == '0' || maze[row_idx][col_idx + 1] == '+')
                    {
                        return false;
                    }
                    if (maze[row_idx + 1][col_idx + 1] == '!' || maze[row_idx + 1][col_idx + 1] == '!' || maze[row_idx + 2][col_idx + 1] == '!' || maze[row_idx + 2][col_idx + 1] == '!' || maze[row_idx][col_idx + 1] == '!' || maze[row_idx][col_idx + 1] == '!')
                    {
                        keys_captured += 1;
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
                if (maze[temp_row + 3][temp_col] == '0' || maze[temp_row + 3][temp_col] == '+' || maze[temp_row + 3][temp_col + 1] == '0' || maze[temp_row + 3][temp_col + 1] == '+')
                {
                    return false;
                }
                if (maze[temp_row + 3][temp_col] == '!' || maze[temp_row + 3][temp_col] == '!' || maze[temp_row + 3][temp_col + 1] == '!' || maze[temp_row + 3][temp_col + 1] == '!')
                {
                    keys_captured += 1;
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
            if (maze[Manic_Current_Row - 1][Manic_Current_Col] == '!' || maze[Manic_Current_Row - 1][Manic_Current_Col + 1] == '!')
            {
                keys_captured += 1;
            }
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
                else
                {
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
                else
                {
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
void MoveEnemy1Horizontal()
{
    if (isEnemyStuck == "STUCK")
    {
        MoveEnemy1Left();
    }
    else if (isEnemyStuck == "NOT STUCK")
    {
        MoveEnemy1Right();
    }
}
bool isClimbPossibleLevel1()
{
    SetManicCurrentLocation();
    if (Manic_Current_Row == 14 && Manic_Current_Col == 6)
    {
        return true;
    }
    return false;
}
void RemoveManic()
{ // Removing Manic From the ladder Upper Position
    SetManicCurrentLocation();
    maze[Manic_Current_Row][Manic_Current_Col] = ' ';
    gotoxy(Manic_Current_Col, Manic_Current_Row);
    cout << ' ';
    maze[Manic_Current_Row][Manic_Current_Col + 1] = ' ';
    gotoxy(Manic_Current_Col + 1, Manic_Current_Row);
    cout << ' ';
    maze[Manic_Current_Row + 1][Manic_Current_Col] = ' ';
    gotoxy(Manic_Current_Col, Manic_Current_Row + 1);
    cout << ' ';
    maze[Manic_Current_Row + 1][Manic_Current_Col + 1] = ' ';
    gotoxy(Manic_Current_Col + 1, Manic_Current_Row + 1);
    cout << ' ';
    maze[Manic_Current_Row + 2][Manic_Current_Col] = ' ';
    gotoxy(Manic_Current_Col, Manic_Current_Row + 2);
    cout << ' ';
    maze[Manic_Current_Row + 2][Manic_Current_Col + 1] = ' ';
    gotoxy(Manic_Current_Col + 1, Manic_Current_Row + 2);
    cout << ' ';
}
void UpdateManicLadderPosition()
{ // This Function is Used to Lift the Manic To Upper Side From Ladder For Level 1
    maze[7][6] = '/';
    gotoxy(6, 7);
    cout << '/';
    maze[7][7] = '\\';
    gotoxy(7, 7);
    cout << '\\';
    maze[8][6] = '\\';
    gotoxy(6, 8);
    cout << '\\';
    maze[8][7] = '/';
    gotoxy(7, 8);
    cout << '/';
    maze[9][6] = '/';
    gotoxy(6, 9);
    cout << '/';
    maze[9][7] = '\\';
    gotoxy(7, 9);
    cout << '\\';
}
bool isCrawlPositionPossible() // This Function is used to check wheather manic can come into a crawling position
{
    int temp_count = 0;
    SetManicCurrentLocation();
    for (int i = 2; i <= 5; i++)
    {
        if (maze[Manic_Current_Row + 2][Manic_Current_Col + i] == ' ' && maze[Manic_Current_Row + 1][Manic_Current_Col + i]) // This if condition is used to check wheather at the next location he can lay down to crawl
        {
            temp_count++;
        }
    }
    if (temp_count == 4)
    {
        return true;
    }
    return false;
}
void ManicLayDown(){
    if(isCrawlPositionPossible()){
        SetManicCurrentLocation();
        for(int x = Manic_Current_Row;x<Manic_Current_Row+3;x++){
            for(int y= Manic_Current_Col;y<Manic_Current_Col+2;y++){
                maze[x][y]=' ';
                gotoxy(y,x);
                cout << ' ';
            }
        }
    }
    int x = Manic_Current_Row+2; //Choosen location for manic to be lay down
    int y = Manic_Current_Col+2;
    maze[x][y]='_';
    maze[x][y+1]='_';
    maze[x][y+2]='/';
    maze[x][y+3]='\\';
    gotoxy(y,x);
    cout << '_';
    gotoxy(y+1,x);
    cout << '_';
    gotoxy(y+2,x);
    cout << '/';
    gotoxy(y+3,x);
    cout << '\\';
}
void ClimbLevel1(string &step1, string &step2, int &ladder_count, string &ManicClimbing)
{
    char PreviousItem1 = '|';
    char PreviousItem2 = '_';
    char PreviousItem3 = '|';
    if (ladder_count < 3)
    {
        step1 = "START";
    }
    else
    {
        step1 = "STOP";
    }
    if (ladder_count >= 3 && ladder_count < 9)
    {
        step2 = "START";
        ManicClimbing = "CLIMBING";
    }
    else
    {
        step2 = "STOP";
    }
    if (step1 == "START")
    {
        ManicMoveLeft();
        ladder_count++;
        if (ladder_count == 3)
        {
            int temp_col = 5;
            for (int temp_row = 14; temp_row < 17; temp_row++)
            {
                gotoxy(temp_col, temp_row);
                cout << PreviousItem1;
                step1 = "STOP";
            }
        }
    }
    else if (step2 == "START")
    {
        ManicMoveUp();
        ladder_count++;
        if (ladder_count > 4)
        {
            SetManicCurrentLocation();
            gotoxy(Manic_Current_Col, Manic_Current_Row + 3);
            cout << '_';
            gotoxy(Manic_Current_Col + 1, Manic_Current_Row + 3);
            cout << '_';
            if (ladder_count == 9)
            {
                RemoveManic();               // Removing Manic from ladder
                UpdateManicLadderPosition(); // Putting Manic to Upper side after removing manic from ladder
                ManicClimbing = "NOT CLIMBING";
            }
        }
    }
}