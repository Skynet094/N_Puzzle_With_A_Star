#include<bits/stdc++.h>
using namespace std;
#define VECTOR vector< vector<int> >

VECTOR start_BOARD, goal_BOARD;
vector<int> position_in_row, position_in_col, goal, B_goal;
map< VECTOR , bool > visited;
map< VECTOR, VECTOR > parent;


int SIZE=0;

bool visit(VECTOR state){

        if( visited[state] == true)
            return true;
        return false;

}





int heuristic_function2(VECTOR BOARD){


    int Size= BOARD.size();
    int N= Size* Size;

    vector<int> current_state, B;

    current_state.push_back(0);
    B.resize(N+1);



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
//
//    for(int i=1; i<=N ; i++)
//        cout<<current_state[i]<<" ";
//        cout<<endl;

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





int heuristic_function( VECTOR start_BOARD){  // OUT OF ROW, OUT OF COLUMN
    int value=0;

    for(int i=0; i<SIZE ; i ++)
    for(int j=0; j<SIZE; j++){
        int current_item= start_BOARD[i][j];
        if(current_item==0)
            continue;
        if((i - position_in_row[current_item]) !=0)
            value++;
        if((j - position_in_col[current_item]) !=0)
            value++;
    }

    return value;

}

bool goal_test(VECTOR start_BOARD){

    for(int i=0; i<SIZE; i++)
        for(int j=0; j<SIZE; j++)
            if(start_BOARD[i][j] != goal_BOARD[i][j])
                return false;

    return true;

}


bool isInsideBoard(int row, int col){

    if(row>=0 && row<SIZE && col>=0 && col<SIZE)
        return true;
    return false;


}

typedef pair< VECTOR , int > NODE;

//changing,  direction X , direction Y of the black space , if we move the blank in the upper direction, we will have to swap the upper tile
// with the blank, get new position for the blank space by (position+x + dx, position + dy)
int dx[]= {0, 0, -1 , 1};   //up , down ,  left , right
int dy[]= {-1, 1, 0 , 0};

struct compare{

        bool operator()(NODE& X , NODE& Y){

                int h1 = heuristic_function2(X.first);
                int h2= heuristic_function2(Y.first);
         //       cout<<"Heuristic values: "<<h1<<" "<<h2<<endl;
                int g1= X.second;
                int g2= Y.second;
                int cost1= h1+ g1;
                int cost2= h2+ g2;

                return cost1 > cost2;

        }

};


void print_board(VECTOR BOARD){

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
    cout<<endl;
}

void path_print(VECTOR current_state){


    if(parent.count(current_state))
        path_print(parent[current_state]);


    print_board(current_state);
    return;
}

void print_number_of_moves(VECTOR current_state){

    queue<VECTOR> Q;

    while(parent.count(current_state)){

        Q.push(parent[current_state]);
        current_state= parent[current_state];
    }
    cout<<"Number of moves required: " <<Q.size() <<endl;
}

void A_star( VECTOR start_BOARD){

    visited[start_BOARD] = true; //visited is the closed set

    priority_queue< NODE, vector<NODE> , compare> Queue;

    NODE current_node = NODE(start_BOARD, 0); // state , cost

    Queue.push(current_node);  // Q is the open set

    int number_of_nodes=0;
    //cout<<"HELLO"<<endl;


    while(! Queue.empty()){
//        cout<<number_of_steps<<endl;
        number_of_nodes++;
        current_node= Queue.top(); Queue.pop();
        //print_board(current_node.first);

        if(goal_test(current_node.first))
          {
          //    path_print(current_node.first);
              print_number_of_moves(current_node.first);
             break;

          }


        // find the blank space
        int pos_x, pos_y;



        for(int i=0; i<SIZE; i++){

            for(int j=0; j<SIZE; j++){

                if(current_node.first[i][j]==0){

                    pos_x=i, pos_y=j;
                    break;
                }
            }
        }



        // generate neighbors

        for(int i=0; i<4; i++){

            int new_pos_x= pos_x + dx[i];
            int new_pos_y= pos_y+ dy[i];



            if(isInsideBoard(new_pos_x, new_pos_y)){
                NODE temp_node = NODE(current_node);  // using current node as reference state for neighbor generation !

                int hold = temp_node.first[new_pos_x][new_pos_y];
                temp_node.first[new_pos_x][new_pos_y]= temp_node.first[pos_x][pos_y];
                temp_node.first[pos_x][pos_y] = hold;

                temp_node.second= current_node.second+1;



                if(visited[temp_node.first]!= true)
                    {
                        Queue.push(temp_node);
                        parent[temp_node.first]=current_node.first;
                        visited[temp_node.first]= true;
                    }

               // temp_node.first.clear();

            }



        }
       //current_node.first.clear();


    }

    cout<<"Required number of nodes explored: "<<number_of_nodes<<endl;

}


int main(void){
    //freopen("Input.txt", "r", stdin);
    int N;

    cin>>N;

    int sqrtN= sqrt(N+1);
    SIZE= sqrtN;

    start_BOARD.resize(sqrtN);
    goal_BOARD.resize(sqrtN);

    for(int i=0; i< sqrtN; i++)
    {
        start_BOARD[i].resize(sqrtN);
        goal_BOARD[i].resize(sqrtN);
    }

    position_in_col.resize(N+1);
    position_in_row.resize(N+1);

    int row , col;

    row = col = sqrtN;

    for(int i=0; i< row; i++)
        for(int j=0; j<col; j++)
            cin>>start_BOARD[i][j];

    for(int i=0; i< row; i++)
        for(int j=0; j<col; j++)
            {

                cin>>goal_BOARD[i][j];
                position_in_col[goal_BOARD[i][j]]=j;
                position_in_row[goal_BOARD[i][j]]=i;

            }

    // inflating goal state for N-MaxSwap heuristic

       goal.push_back(0);
       B_goal.resize(row*col+1);


       for(int i=0; i< row; i++)
        for(int j=0; j< col ; j++){
            if(goal_BOARD[i][j]!=0)
                goal.push_back(goal_BOARD[i][j]);
            else
                goal.push_back(row*col);
        }


    for(int i=1; i<= row*col ; i++)
        B_goal[goal[i]] = i;

      //     print_heuristic_function2(start_BOARD);
   cout<<heuristic_function2(start_BOARD)<<endl;
    A_star(start_BOARD);

    return 0;
}
