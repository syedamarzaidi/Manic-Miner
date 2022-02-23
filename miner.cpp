#include <iostream>
#include <fstream>
#include <windows.h>
#include <math.h>
using namespace std;
const int maze_row = 34;
const int maze_col = 105;
char maze[maze_row][maze_col];
void gotoxy(int x, int y);      // This Function is created to move th cursor
void loadMaze();                // This function is used to load maze from maze.txt file
void printMaze();               // This function is used to print maze from maze.txt file
bool ManicMoveLeft();           // This function is used to move manic at left side
bool ManicMoveRight();          // This function is used to Move manic at right
bool ManicMoveDown();           // This Function is used to move manic at down side
bool ManicMoveUp();             // This function is used to manic at upper side
void SetManicCurrentLocation(); // To Store the Manic Row and Column position in Manic_Current_Row and Manic_Current_Col Variables
bool JumpManic();               // This function is used to Jump the manic according to settled manic jump limit variable
bool FellTheManic();            // This function is used to fell manic when there is no solid material at the feet of manic
bool isManicFalling();          // This function is used to return true if manic is falling
bool isRightMovePossible(int temp_row_idx, int temp_col_idx);
bool isLeftMovePossible(int temp_row_idx, int temp_col_idx);
bool isDownMovePossible(int temp_row_idx, int temp_col_idx);
bool isUpHurdlePresent(int temp_row_idx, int temp_col_idx);
void MoveEnemy1Horizontal();
bool isRightEnemy1Possible(int temp_row_idx, int temp_col_idx);
bool isLeftEnemy1Possible(int temp_row_idx, int temp_col_idx);
void MoveEnemy1Right();
void MoveEnemy1Left();
bool isClimbUpPossible(string &LeftKey, string &RightKey);
bool isClimbDownPossible(string &LeftKey, string &RightKey);
void ClimbUp(string &step1, string &step2, int &ladder_count, string &ManicClimbing, int temp_x, int temp_y, string &LeftKey, string &RightKey);
void ClimbDown(string &step1, string &step2, int &ladder_count, string &ManicClimbing, int temp_x, int temp_y, string &LeftKey, string &RightKey);
void ManicClimb(string &step1, string &step2, int &ladder_count, string &ManicClimbing, int temp_x, int temp_y, string &LeftKey, string &RightKey,string &LadderPosition);
string isClimbPosition(string &LeftKey, string &RightKey);
void CompleteBrokenLadder();//This Function is used to Complete Ladder because it will be broken when manic will come down with ladder
// isClimbPosition() Function is used to find wheather ladder is in front of Manic or manic is at the position to come down from ladder
void RemoveManic();
void UpdateManicLadderPositionUp(int temp_x, int temp_y); // This will update manic to upper ladder position according to temp_x,temp_y coordinates
void CalculateLives(int &lives);
void PrintLives(int &lives);
void CalculateKeys();
void PrintKeys();
void ResetLevel1(int &position_X, int &position_Y); // This Function is used to Reset Maze When Manic is Touched with enemy
void crawl_manic();
bool isCrawlPositionPossible();          // This function is used to check wheather manic can crawl or not on certain location
void CrawlMoveRight();                   // This function is used to move right while manic is crawling
void ManicLayDown(string &isManicLayed); // This function is used to lay down manic
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
string isManicFrozen = "NOT FROZEN"; // This variable will be freeze manic and manic can not move right or left when he is freeze
// Checks Variable Ends
int main()
{
    string LadderPosition = "NOTHING"; //This Variable is used to store status of ladder position as RIGHT OR LEFT OF MANIC
    string isManicLayed = "NOT LAYED"; // This variable to check whather manic is layeed down to ground or not
    string RightKey = "UNLOCKED";      // Right and left keys can be locaked or unlocked according to hurdles at front positions
    string LeftKey = "UNLOCKED";
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
    string ClimbingStatus = "END"; // This variable is used to store the status of climbing wheather the manic has started climbing or not
    bool gameRunning = true;
    loadMaze();
    system("cls");
    printMaze();
    bool Temp_Manic_Falling_Status;
    int temp_x = 0; // Temperary VAriables to perform different functions on manic location
    int temp_y = 0;
    for (int total_turns = lives; total_turns != 0; total_turns--)
    {
        while (gameRunning)
        {
            Sleep(100);
            MoveEnemy1Horizontal();
            Temp_Manic_Falling_Status = isManicFalling();
            if (!isClimbUpPossible(LeftKey, RightKey) && LeftKey == "UNLOCKED")
            { // The left key will be only pressed when there will be no ladder in front of manic to climb
                // cin >>Temp_Manic_Falling_Status;
                if (GetAsyncKeyState(VK_LEFT))
                {
                    gameRunning = ManicMoveLeft();
                }
            }
            // cin >> Temp_Manic_Falling_Status;
            if (GetAsyncKeyState(VK_RIGHT))
            {
                if (!isClimbUpPossible(LeftKey, RightKey) || RightKey == "UNLOCKED") // Fix Required at  ||
                {
                    gameRunning = ManicMoveRight();
                }
            }
            if (ManicFallingStatus == "FALLING" && ManicJumpingStatus == "NOT JUMPING" && isManicClimbing == "NOT CLIMBING")
            {
                FellTheManic();
            }
            if (ManicJumpingStatus == "NOT JUMPING" && ManicFallingStatus == "NOT FALLING")
            {
                if (GetAsyncKeyState(VK_SPACE))
                {
                    if(isManicFrozen == "NOT FROZEN"){ //While Manic is Frozen User cannot jump
                    gameRunning = JumpManic();
                    ManicJumpCount++;
                    ManicJumpingStatus = "JUMPING";
                    }
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
            if (GetAsyncKeyState(VK_NUMPAD0))
            {
                if ((isClimbUpPossible(LeftKey, RightKey) || isClimbDownPossible(LeftKey,RightKey)) && isManicClimbing == "NOT CLIMBING")
                {
                    LadderPosition = isClimbPosition(LeftKey,RightKey);
                    
                    SetManicCurrentLocation();
                    temp_x = Manic_Current_Row;
                    temp_y = Manic_Current_Col;
                }
               ManicClimb(step1, step2, ladder_count, isManicClimbing, temp_x, temp_y,LeftKey,RightKey,LadderPosition);
            }
            if (isManicLayed == "NOT LAYED")
            {
                if (GetAsyncKeyState(VK_NUMPAD5))
                {
                    isManicLayed = "LAYED";
                    ManicLayDown(isManicLayed);
                }
            }
            if (GetAsyncKeyState(VK_ESCAPE))
            {
                cout << "Game Over";
                gameRunning = false;
            }
            PrintLives(lives);
            PrintKeys();
            if (isManicLayed == "LAYED")
            {
                CrawlMoveRight();
            }
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
        if (isManicFrozen == "NOT FROZEN")
        { // If manic is not on the ladder then hw is not freezed and he can move right
            return true;
        }
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
        if (isManicFrozen == "NOT FROZEN")
        { // If manic is not on ladder then he can move at left and he is in NOT FROZEN P
            return true;
        }
    }
    return false;
}
bool isDownMovePossible(int temp_row_idx, int temp_col_idx)
{
    if (maze[temp_row_idx + 1][temp_col_idx] == ' ' || maze[temp_row_idx + 1][temp_col_idx] == '0' || maze[temp_row_idx + 1][temp_col_idx + 1] == '+' || maze[temp_row_idx + 1][temp_col_idx + 1] == '!' || maze[temp_row_idx + 1][temp_col_idx + 1] == '_') // This If condition require editing in changing in condition when it will meet up with enemy
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
                MoveDownStatus = "No_Obstacle"; //Area is cleared so further processing is possible
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
bool isClimbUpPossible(string &LeftKey, string &RightKey)
{
    RightKey = "UNLOCKED";
    LeftKey = "UNLOCKED";
    SetManicCurrentLocation();
    // This Condition is used to check wheather there is a ladder present at the front of manic to climb
    if (maze[Manic_Current_Row][Manic_Current_Col - 1] == '|' && maze[Manic_Current_Row][Manic_Current_Col - 2] == '_' && maze[Manic_Current_Row][Manic_Current_Col-3] == '_')
    {
        LeftKey = "LOCKED"; // User cannot move left if left key is locked
        RightKey = "UNLOCKED";
        return true;
    }
    else if (maze[Manic_Current_Row][Manic_Current_Col + 2] == '|' && maze[Manic_Current_Row][Manic_Current_Col + 3] == '_' && maze[Manic_Current_Row][Manic_Current_Col+4] == '_')
    {
        RightKey = "LOCKED";
        LeftKey = "UNLOCKED";
        return true;
    }
    return false;
}
bool isClimbDownPossible(string &LeftKey,string &RightKey)
{
    // This function is used to check wheather manic can climb down or not
    SetManicCurrentLocation();
    if (maze[Manic_Current_Row + 4][Manic_Current_Col - 2] == '_' || maze[Manic_Current_Row + 4][Manic_Current_Col - 1] == '_')
    {
        return true;
    }
    return false;
}
void RemoveManic()
{ // Removing Manic From the ladder Upper Position
 
 for(int i = 0;i<maze_row;i++){
     for(int a = 0;a<maze_col;a++){
         if(maze[i][a] == '/' || maze[i][a] == '\\'){
             maze[i][a] = ' ';
             gotoxy(a,i);
             cout << ' ';
         }
     }
 }
}
void UpdateManicLadderPositionUp(int temp_x, int temp_y)
{                  // This Function is Used to Lift the Manic To Upper Side From Ladder For Level 1
    RemoveManic(); // It will remove manic from the ladder and then manic will be shown outside of the ladder
    maze[temp_x - 7][temp_y] = '/';
    gotoxy(temp_y, temp_x - 7);
    cout << '/';
    maze[temp_x - 7][temp_y + 1] = '\\';
    gotoxy(temp_y + 1, temp_x - 7);
    cout << '\\';
    maze[temp_x - 6][temp_y] = '\\';
    gotoxy(temp_y, temp_x - 6);
    cout << '\\';
    maze[temp_x - 6][temp_y + 1] = '/';
    gotoxy(temp_y + 1, temp_x - 6);
    cout << '/';
    maze[temp_x - 5][temp_y] = '/';
    gotoxy(temp_y, temp_x - 5);
    cout << '/';
    maze[temp_x - 5][temp_y + 1] = '\\';
    gotoxy(temp_y + 1, temp_x - 5);
    cout << '\\';
}
void UpdateManicLadderPositionDown(int temp_x, int temp_y)
{
    RemoveManic(); // Removing manic from the ladder
    // Starting snippet of code to help manic to move out of the ladder
    maze[temp_x + 7][temp_y] = '/';
    gotoxy(temp_y, temp_x + 7);
    cout << '/';
    maze[temp_x + 7][temp_y + 1] = '\\';
    gotoxy(temp_y + 1, temp_x + 7);
    cout << '\\';
    maze[temp_x + 8][temp_y] = '\\';
    gotoxy(temp_y, temp_x + 8);
    cout << '\\';
    maze[temp_x + 8][temp_y + 1] = '/';
    gotoxy(temp_y + 1, temp_x + 8);
    cout << '/';
    maze[temp_x + 9][temp_y] = '/';
    gotoxy(temp_y, temp_x + 9);
    cout << '/';
    maze[temp_x + 9][temp_y + 1] = '\\';
    gotoxy(temp_y + 1, temp_x + 9);
    cout << '\\';
    // Ending snippet code
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
void ManicLayDown(string &isManicLayed)
{
    if (isCrawlPositionPossible())
    {
        SetManicCurrentLocation();
        for (int x = Manic_Current_Row; x < Manic_Current_Row + 3; x++)
        {
            for (int y = Manic_Current_Col; y < Manic_Current_Col + 2; y++)
            {
                maze[x][y] = ' ';
                gotoxy(y, x);
                cout << ' ';
            }
        }
        isManicLayed = "LAYED";
    }
    int x = Manic_Current_Row + 2; // Choosen location for manic to be lay down
    int y = Manic_Current_Col + 2;
    maze[x][y + 2] = '/';
    maze[x][y + 3] = '\\';
    gotoxy(y + 2, x);
    cout << '/';
    gotoxy(y + 3, x);
    cout << '\\';
}
void CrawlMoveRight()
{
    // bool temp_found_status = false;
    for (int x = 0; x < maze_row; x++)
    {
        for (int y = maze_col - 1; y != 0; y--)
        {
            if (maze[x][y] == '\\')
            { // This will match the head of manic when he is at crawling position and will move one step right
                maze[x][y] = ' ';
                gotoxy(y, x);
                cout << ' ';
                maze[x][y + 1] = '\\';
                gotoxy(y + 1, x);
                cout << '\\';
            }
            else if (maze[x][y] == '/')
            {
                maze[x][y] = ' ';
                gotoxy(y, x);
                cout << ' ';
                maze[x][y + 1] = '/';
                gotoxy(y + 1, x);
                cout << '/';
            }
        }
    }
}
void ClimbUp(string &step1, string &step2, int &ladder_count, string &ManicClimbing, int temp_x, int temp_y,string &LeftKey,string &RightKey)
{
    char PreviousItem1 = '|';
    char PreviousItem2 = '_';
    ladder_count++;
     ManicClimbing = "CLIMBING";
    if (ladder_count < 4)
    {
        step1 = "START";
    }
    else
    {
        step1 = "STOP";
    }
    if (ladder_count >= 4)
    {
        step2 = "START";
       // ManicClimbing = "CLIMBING";
    }
    else
    {
        step2 = "STOP";
    }
    if (step1 == "START")
    {
        ManicMoveLeft();
       
        if (ladder_count == 3)
        {
            isManicFrozen = "FROZEN";
            SetManicCurrentLocation();
            for (int temp_row = Manic_Current_Row; temp_row <= Manic_Current_Row+2; temp_row++)
            {
                maze[temp_row][Manic_Current_Col+2] = PreviousItem1;
                gotoxy(Manic_Current_Col+2, temp_row);
                cout << PreviousItem1;
                step1 = "STOP";
            }
        }
    }
    else if (step2 == "START")
    {
        ManicMoveUp();
        if (ladder_count > 4)
        {
            SetManicCurrentLocation();
            maze[Manic_Current_Row+3][Manic_Current_Col] = '_';
            maze[Manic_Current_Row+3][Manic_Current_Col+1] = '_';
            gotoxy(Manic_Current_Col, Manic_Current_Row + 3);
            cout << '_';
            gotoxy(Manic_Current_Col + 1, Manic_Current_Row + 3);
            cout << '_';
            if (ladder_count == 9)
            {
                ladder_count = 0;
                UpdateManicLadderPositionUp(temp_x, temp_y); // Putting Manic to Upper side after removing manic from ladder
                ManicClimbing = "NOT CLIMBING";
                isManicFrozen = "NOT FROZEN";
            }
        }
    }
     
}
void ManicClimb(string &step1, string &step2, int &ladder_count, string &ManicClimbing, int temp_x, int temp_y, string &LeftKey, string &RightKey,string &LadderPosition)
{
    // This Function will climb manic at up or down position according to ladder position
    if (LadderPosition == "UP") // Manic will move Climb up to ladder
    {
        ClimbUp(step1, step2, ladder_count, ManicClimbing, temp_x, temp_y, LeftKey, RightKey);
    }
    else if (LadderPosition == "DOWN")
    {
        ClimbDown(step1, step2, ladder_count, ManicClimbing, temp_x, temp_y, LeftKey, RightKey);
    }
}
string isClimbPosition(string &LeftKey, string &RightKey)
{                                     // This Function is used to check manic should climb up or climb down
    string temp_position = "NOTHING"; // By Default there is nothing means that ladder is not present near manic to climb up or climb down
    if (isClimbUpPossible(LeftKey, RightKey))
    {
        temp_position = "UP"; // UP means ladder is set to move up
    }
    else if (isClimbDownPossible(LeftKey, RightKey))
    {
        temp_position = "DOWN"; // DOWN means that ladder is set at position that manic can move down
    }
    return temp_position;
}
string ManicClimbDownDirection()
{ // This Function is used to check wheather ladder is at right or left side of the manic
    string temp_status = "NOTHING";
    SetManicCurrentLocation();
    if (maze[Manic_Current_Row + 4][Manic_Current_Col - 1] == '_' || maze[Manic_Current_Row + 4][Manic_Current_Col - 2] == '_')
    {
        temp_status = "LEFT"; // ladder is at the left side of MAnic
    }
    else if (maze[Manic_Current_Row + 4][Manic_Current_Col + 2] == '_' || maze[Manic_Current_Row + 4][Manic_Current_Col + 3] == '_')
    {
        temp_status = "RIGHT"; // Ladder is at the right side of the Manic
    }
    return temp_status; // Returning the location of the ladder with respect to MAnic
}
void ClimbDown(string &step1, string &step2, int &ladder_count, string &isManicClimbing, int temp_x, int temp_y, string &LeftKey, string &RightKey)
{ //ClimbDown Function is used to Come DOwn From ladder 
    char PreviousItem1 = '|';
    char PreviousItem2 = '_';
    isManicClimbing = "CLIMBING";
    ladder_count++;
    if (ladder_count < 4)
    {
        step1 = "START"; // Step1 is started in which manic will move Left to go down at next step
    }
    else
    {
        step1 = "STOP";
    }
    if (ladder_count >= 4)
    {
        step2 = "START";
    }
    else
    {
        step2 = "STOP";
    }
    if (ladder_count == 4)
    {
        isManicFrozen = "FROZEN"; // Manic is Frozen and cannot Move right or left when he is coming down from ladder
    }
    if (step1 == "START")
    {
        if (ManicClimbDownDirection() == "LEFT") // Instead of Functions there will be variables in future to avoid bugs
        {
            ManicMoveLeft();
        }
        else if (ManicClimbDownDirection() == "RIGHT")
        {
            ManicMoveRight();
        }
    }   
    else if (step2 == "START")
    {
        ManicMoveDown();
        if (ladder_count >= 8)
        {
            SetManicCurrentLocation();
            maze[Manic_Current_Row-1][Manic_Current_Col] = '_'; //This snippet is displaying __ when manic is going down
            gotoxy(Manic_Current_Col, Manic_Current_Row - 1);
            cout << '_';
            maze[Manic_Current_Row-1][Manic_Current_Col+1] = '_';
            gotoxy(Manic_Current_Col + 1, Manic_Current_Row - 1);
            cout << '_';
        }
        if (ladder_count == 10)
        {   
            // Move Manic out of the ladder
            ladder_count = 0;
            CompleteBrokenLadder();
            UpdateManicLadderPositionDown(temp_x, temp_y);
            isManicClimbing = "NOT CLIMBING";
            isManicFrozen = "NOT FROZEN";
        }
    }
    
}
void CompleteBrokenLadder(){
    //This Function will complete the ladder when manic will come out of the ladder
    SetManicCurrentLocation();
    int x = Manic_Current_Row;
    int y = Manic_Current_Col;
    maze[x][y] ='_';
    maze[x][y+1] = '_';
    maze[x+1][y]= '_';
    maze[x+1][y+1]='_';
    gotoxy(y,x);
    cout << '_';
    gotoxy(y+1,x);
    cout << '_';
    gotoxy(y,x+1);
    cout << '_';
    gotoxy(y+1,x+1);
    cout << '_';
}