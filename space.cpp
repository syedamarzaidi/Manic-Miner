#include<iostream>
#include<fstream>
using namespace std;
void load_screen();
void print_Screen();
char board[38][100];
int main(){


}
void load_screen(){
    string line = " ";
    int row_idx = 0;
    fstream file;
    file.open("screen.txt",ios::in);
    while(!file.eof()){
        file>>line;
        for(int col_idx = 0;col_idx<line.length();col_idx++){
        board[row_idx][col_idx] = line[col_idx];
        }
        row_idx++;
    }
    file.close();
}
void print_Screen(){
    for(int row_idx = 0;row_idx < 38){
        for(int col_idx = 0;col_idx < 100;col_idx++){
            cout << board[row_idx][col_idx];
        }
        cout << endl;
    }
}
