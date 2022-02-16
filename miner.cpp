#include<iostream>
#include<fstream>
#include<windows.h>
#include<math.h>
using namespace std;
const int maze_row = 34;
const int maze_col = 105;
char maze[maze_row][maze_col];
void gotoxy(int x,int y);
void loadMaze();
void printMaze();
void minerMoveLeft();
int main(){
    bool gameRunning = true;
     loadMaze();
     system("cls");
    printMaze();
    while(gameRunning){
        Sleep(100);
        if(GetAsyncKeyState(VK_LEFT)){
            minerMoveLeft();
        }
    }
    return 0;
}
void loadMaze(){
    string line;
    int row_idx = 0;
    fstream file;
    file.open("maze.txt",ios::in);
    while(!file.eof()){
        getline(file,line);
        for(int col_idx =0;col_idx<maze_col;col_idx++){
            maze[row_idx][col_idx]=line[col_idx];
        }
        row_idx++;
    }
    file.close();
}
void printMaze(){
    for(int row_idx = 0;row_idx<maze_row;row_idx++){
        for(int col_idx = 0;col_idx < maze_col;col_idx++){
            cout <<maze[row_idx][col_idx];
        }
        cout << '\n';
    }
}
void gotoxy(int x,int y){
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}
void minerMoveLeft(){
    for(int row_idx = 0;row_idx<maze_row;row_idx++){
        for(int col_idx = 0; col_idx < maze_col;col_idx++){
            if(maze[row_idx][col_idx] == '/'){
                maze[row_idx][col_idx] = ' ';
                gotoxy(col_idx,row_idx);
                cout << maze[row_idx][col_idx];
                maze[row_idx][col_idx-1] = '/';
                gotoxy(col_idx-1,row_idx);
                cout << maze[row_idx][col_idx-1];
            }
            else if(maze[row_idx][col_idx] == '\\'){
                maze[row_idx][col_idx] = ' ';
                gotoxy(col_idx,row_idx);
                cout << maze[row_idx][col_idx];
                maze[row_idx][col_idx-1] = '\\';
                gotoxy(col_idx-1,row_idx);
                cout << maze[row_idx][col_idx-1];
            }
        }
    }
}
