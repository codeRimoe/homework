#include <iostream>
using namespace std;

#include "pubProperty.h"
#include "husband.h"
#include "wife.h"
#include "child.h"

int main(){
    Child c(1000000,200000,300000,100);
    cout<<c.balance<<endl<<endl;
    c.disp();
    c.getAll();
    c.disp();
    return 0;
}
