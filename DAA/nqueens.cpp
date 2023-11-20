#include <bits/stdc++.h>
using namespace std;

//function for printing the board
void print(vector <vector <int>> &board, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout<< board[i][j]<< " ";
        }
        cout<<endl;
    }
}

bool isSafe(int row, int col,int n, vector<vector <int>> &board){
    for(int i = 0; i < row; i++){
        if(board[i][col] != 0){
            return false;
        }
    }

    int i = row, j = col;
    while(i >=0 && j >= 0){
        if(board[i][j] != 0){
            return false;
        }
        i--;
        j--;
    }

    i = row, j = col;
    while(i >= 0 && j < n){
        if(board[i][j] !=0){
            return false;
        }
        i--;
        j++;
    }
    return true; 
}

//placing the queen 
bool nqueen(int row, int col, int n, vector<vector<int>> &board){
    if(row == n){
        cout<<"\nFinal board is "<<endl;
        print(board, n);
        cout<<endl;
        return true;
    }
    for(int i =0;i<n;i++){
        if(isSafe(row,i,n,board)){
            board[row][i] = row+1;
            cout<<endl;
            print(board,n);
            if(nqueen(row+1,col,n,board)){
                return true;
            }
            board[row][i] = 0;
        }
    }
    cout << "\nUnable to place queen\n";
    cout << endl;
    print(board, n);
    return false;
}

//for n>8
bool nqueens(int row, int col, int n, vector <vector <int>> &board){
    if(row == n){
        cout<<"\nFinal board is :";
        print(board,n);
        cout<<endl;
        return true;
    }

    for(int i = 0; i<n;i++){
        if(isSafe(row,i,n,board)){
            board[row][i] = row+1;
            if(nqueens(row+1,col,n,board)){
                return true;
            }
            board[row][i]= 0;
        }
    }
    return false;
}

int main(){
    int n;

    cout << "\nN-QUEENS PROBLEM (USING BACKTRACKING)" << endl;
    cout << "\nEnter the size of board: ";
    cin >> n;
    if (n < 4)
    {
        cout << "Number of Queens must be greater than 3.";
        return 0;
    }
    vector<vector<int>> board;
    for(int i =0; i<n;i++){
        vector<int> temp;
        for(int j = 0;j<n; j++){
            temp.push_back(0);
        }
        board.push_back(temp);
    }
     if (n > 8)
    {
        nqueens(0, 0, n, board);
    }
    else
    {
        nqueen(0, 0, n, board);
    }
    return 0;
}
