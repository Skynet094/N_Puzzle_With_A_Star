#include<bits/stdc++.h>
using namespace std;

#define VECTOR vector< vector<int> >

int heuristic_N_MaxSwap(VECTOR BOARD){

    int SIZE= BOARD.size();

    vector<int> P,B;

    P.push_back(0);
    B.resize(SIZE+1);


    for(int i=0; i< SIZE; i++)
        for(int j=0; j< SIZE ; j++){
            if(BOARD[i][j]!=0)
                P.push_back(BOARD[i][j]);
            else
                P.push_back(SIZE*SIZE);
        }

    for(int i=1; i<= SIZE* SIZE ; i++){


        B[P[i]] = i;
    }


    int counter=0;

    while(1){

        for(int i=1; i<=10; i++)
            cout<<P[i]<<" ";
        cout<<endl;

        int test=1;
        for(int i=1; i<=10; i++)
            {
                if(P[i] != i){
                test=0;
                break;

            }
            }


        if(test)
            break;

            swap(P[B[(counter+1) % 11]], P[B[B[(counter+1) % 11]]]);
            swap(B[(counter+1) % 11] , B[B[(counter+1) % 11]]);




    counter++;
    }

    return counter;
}




int heuristic_function2(VECTOR BOARD){


    int Size= BOARD.size();
    int N= Size* Size;

    vector<int> current_state,B_goal, goal, B;

    current_state.push_back(0);
    B.resize(N+1);
    B_goal.resize(N+1);


    for(int i=0; i< Size; i++)
        for(int j=0; j< Size ; j++){
            if(BOARD[i][j]!=0)
                current_state.push_back(BOARD[i][j]);
            else
                current_state.push_back(N);
        }

    for(int i=1; i<= N ; i++)
        B[current_state[i]] = i;

    int counter=0;


    while(1){

    for(int i=1; i<=N ; i++)
        cout<<current_state[i]<<" ";
        cout<<endl;

    if(B[N] != B_goal[N]){
            swap(current_state[B[N]] , current_state[B[goal[B[N]]]]);  //  goal[B[9]] = what element is supposed to be at B[9]-th location ,                                                                   //
            swap(B[N] , B[goal[B[N]]]);

    }


    else{

        int flag= true;

        for(int i=1; i <N; i++){

                if(B[i] != B_goal[i]){  // if element-i is NOT  where it should be, that's a mismatch
                    swap(current_state[B[i]] , current_state[B[N]]);  // swap position with blank and mismatch item
                    swap(B[i], B[N]);
                    flag=false;
                    break;
                }
        }

        if(flag)
            break;

    }

    counter++;

    }

    return counter;

}



int main(void){

    int current_state[10]={0,7 ,2 ,4 ,6 ,3 ,1 ,8 ,9 ,5};

    int B[10];  // kon element kothay asche,

    int goal[10]={0,1 ,2, 3 ,4 ,5 ,6, 7, 8, 9};

    int B_goal[10]; // kothay kon element gulo thakar kotha


    for(int i=1; i<=9; i++){
        B[current_state[i]]=i;
        B_goal[goal[i]]=i;

    }


    int counter=0;


    while(1){

    for(int i=1; i<=9 ; i++)
        cout<<current_state[i]<<" ";
        cout<<endl;

    if(B[9] != B_goal[9]){
      //      cout<<"I AM NOT HERE"<<endl;

            swap(current_state[B[9]] , current_state[B[goal[B[9]]]]);  //  goal[B[9]] = what element is supposed to be at B[9]-th location ,
                                                                   //
            swap(B[9] , B[goal[B[9]]]);



    }


    else{
//        cout<<" I AM HERE"<<endl;

        int flag= true;

        for(int i=1; i <9; i++){
  //              cout<<" I AM HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE"<<endl;
//                cout<<B[i]<<" "<<B_goal[i]<<endl;

                if(B[i] != B_goal[i]){  // if element-i is NOT  where it should be, that's a mismatch
                    swap(current_state[B[i]] , current_state[B[9]]);  // swap position with blank and mismatch item
                    swap(B[i], B[9]);
                    flag=false;
                    break;
                }


        }


        if(flag)
            break;

    //cout<<"I AM NEVER HEEEEEEEEEREEEEEEEEEEEE NEVER NEVER"<<endl;
    }



    counter++;

    }






    cout<< counter<<endl;


    return 0;
}
