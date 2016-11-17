#include<bits/stdc++.h>
using namespace std;


vector< vector<int> > BOARD;
int SIZE=0;


void print_board(){

    for(int i=0; i< SIZE; i++){

        for(int k=0; k< SIZE*3+1; k++){

                cout<<"-";


        }
        cout<<endl;
            cout<<"|";

        for(int j=0; j< SIZE; j++){

            if(BOARD[i][j]>9 ) //in last column
                cout<<BOARD[i][j]<<"|";
            else if(BOARD[i][j]==0)
                cout<<"  |";
            else
                cout<<" "<<BOARD[i][j]<<"|";

        }
            cout<<endl;

    }


    for(int k=0; k< SIZE*3+1; k++){

            cout<<"-";

        }

}



int main(void){


    int N;

    cin>>N;

    int sqrtN= sqrt(N+1);
    SIZE= sqrtN;

    BOARD.resize(sqrtN);


    for(int i=0; i< sqrtN; i++)
    {
        BOARD[i].resize(sqrtN);
    }


    int row , col;

    row = col = sqrtN;

    for(int i=0; i< row; i++)
        for(int j=0; j<col; j++)
            cin>>BOARD[i][j];

    print_board();


    return 0;
}
