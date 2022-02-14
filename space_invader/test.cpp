#include<iostream>
#include<fstream>
#include<windows.h>
using namespace std;
const int board_row = 28;
const int board_col = 80;
int Cannon_UpperTip_x = 25;
int Cannon_UpperTip_y = 29;
int Cannon_LeftTip_x = 26;
int Cannon_LeftTip_y = 28;
int Cannon_MidTip_x = 26;
int Cannon_MidTip_y = 29;
int Cannon_RightTip_x = 26;
int Cannon_RightTip_y = 30;
char board[board_row][board_col];
void loadScreen();
void printScreen();
void gotoxy(int x,int y);
int main(){
    system("cls");
loadScreen();
printScreen();
bool gameRunning = true;
void CannonMoveLeft();
void CannonMoveRight();
while(gameRunning){
    Sleep(100);
if(GetAsyncKeyState(VK_LEFT)){
CannonMoveLeft();
}
else if(GetAsyncKeyState(VK_RIGHT)){
    CannonMoveRight();
}
else if(GetAsyncKeyState(VK_ESCAPE)){
    cout << "Game Over "<<endl;
    gameRunning = false;
}
}
return 0;
}
void loadScreen(){
    string line;
    int row_idx = 0;
    fstream file;
    file.open("screen.txt",ios::in);
    while(!file.eof()){
getline(file,line);
for (int col_idx = 0;line[col_idx] != '\0';col_idx++){
    board[row_idx][col_idx] = line[col_idx];
}
row_idx++;
    }
    file.close();
}
void printScreen(){
    for(int row_idx = 0;row_idx < board_row ;row_idx++){
        for(int col_idx = 0;col_idx<board_col;col_idx++){
            cout << board[row_idx][col_idx];
        }
        cout << endl;
    }
}
void CannonMoveLeft(){
    board[Cannon_UpperTip_x][Cannon_UpperTip_y] = ' ';
    gotoxy(Cannon_UpperTip_y,Cannon_UpperTip_x);
    cout << ' ';
    board[Cannon_LeftTip_x][Cannon_LeftTip_y] = ' ';
 gotoxy(Cannon_LeftTip_y,Cannon_LeftTip_x);
 cout << ' ';
    board[Cannon_MidTip_x][Cannon_MidTip_y] = ' ';
   gotoxy(Cannon_MidTip_y,Cannon_MidTip_x);
   cout << ' ';
   board[Cannon_RightTip_x][Cannon_RightTip_y] = ' ';
gotoxy(Cannon_RightTip_y,Cannon_RightTip_x);
cout << ' ';
Cannon_UpperTip_y--;
 Cannon_LeftTip_y--;
 Cannon_MidTip_y--;
  Cannon_RightTip_y--;
board[Cannon_UpperTip_x][Cannon_UpperTip_y] = '^';
 gotoxy(Cannon_UpperTip_y,Cannon_UpperTip_x);
 cout << '^';
  board[Cannon_LeftTip_x][Cannon_LeftTip_y] = '^';
   gotoxy(Cannon_LeftTip_y,Cannon_LeftTip_x);
   cout << '^'; 
    board[Cannon_MidTip_x][Cannon_MidTip_y] = '^';
   gotoxy(Cannon_MidTip_y,Cannon_MidTip_x);
   cout << '^';
board[Cannon_RightTip_x][Cannon_RightTip_y] = '^';
gotoxy(Cannon_RightTip_y,Cannon_RightTip_x);
cout << '^';
}
void CannonMoveRight(){
 board[Cannon_UpperTip_x][Cannon_UpperTip_y] = ' ';
    gotoxy(Cannon_UpperTip_y,Cannon_UpperTip_x);
    cout << ' ';
     board[Cannon_LeftTip_x][Cannon_LeftTip_y] = ' ';
 gotoxy(Cannon_LeftTip_y,Cannon_LeftTip_x);
 cout << ' ';
  board[Cannon_MidTip_x][Cannon_MidTip_y] = ' ';
   gotoxy(Cannon_MidTip_y,Cannon_MidTip_x);
   cout << ' ';
   board[Cannon_RightTip_x][Cannon_RightTip_y] = ' ';
gotoxy(Cannon_RightTip_y,Cannon_RightTip_x);
cout << ' ';
 Cannon_LeftTip_y++;
 Cannon_UpperTip_y++;
  Cannon_MidTip_y++;
   Cannon_RightTip_y++;
   board[Cannon_UpperTip_x][Cannon_UpperTip_y] = '^';
 gotoxy(Cannon_UpperTip_y,Cannon_UpperTip_x);
 cout << '^';
  board[Cannon_LeftTip_x][Cannon_LeftTip_y] = '^';
   gotoxy(Cannon_LeftTip_y,Cannon_LeftTip_x);
   cout << '^';
    board[Cannon_MidTip_x][Cannon_MidTip_y] = '^';
   gotoxy(Cannon_MidTip_y,Cannon_MidTip_x);
   cout << '^';
board[Cannon_RightTip_x][Cannon_RightTip_y] = '^';
gotoxy(Cannon_RightTip_y,Cannon_RightTip_x);
cout << '^';
}
void gotoxy(int x,int y){
COORD coordinates;
coordinates.X = x;
coordinates.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinates);
}