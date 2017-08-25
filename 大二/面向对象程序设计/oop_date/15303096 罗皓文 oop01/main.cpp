#include <iostream>
using namespace std;
#include "date.h"
int main(){
    int operate=-1;
    Date date;
    while(operate!=0){                //keep running for test,exit when input 0
        cout<<"1.set\n2.increment\n3.decrement\n4.print\n0.exit\ninput:";
        cin>>operate;
        if(operate==1){
            cout<<"please input the date(type:yyyy mm dd)";
            cin>>yyy>>mmm>>ddd;
            date.set(yyy,mmm,ddd);
        }
        else if(operate==2)date.increment();
        else if(operate==3)date.decrement();
        date.print();
    }
    return 0;
}
