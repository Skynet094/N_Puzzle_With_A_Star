#include<bits/stdc++.h>
using namespace std;

struct X{
    int a;
    X(){

    }

    X(int a){
        this->a = a;
    }
};


struct comp{


    bool operator()(const X &a, const X& b){
        return a.a > b.a;

    }

};

int main(void){


    priority_queue<X, vector<X> ,comp> Q;


    Q.push(X(5));
    Q.push(X(10));
    Q.push(X(423));
    Q.push(X(534));
    Q.push(X(65));
    Q.push(X(45));
    Q.push(X(578));
    Q.push(X(523));
    Q.push(X(645));

    for(; Q.empty() != true ;)
        {

            cout<< Q.top().a <<endl;
            Q.pop();
        }





    return 0;
}
