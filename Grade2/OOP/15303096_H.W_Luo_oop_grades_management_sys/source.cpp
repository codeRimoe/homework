#include <iostream>
using namespace std;

#include "compulsory.h"
#include "accounting.h"
#include "gis.h"

int main(){
    int a,b,c,d,e,f;
    cout<<"input:\n"<<"studentID English Politics Advanced_Data Accounting Economics\n";
    cin>>a>>b>>c>>d>>e>>f;
    Accounting st1(a,b,c,d,e,f);
    st1.disp();
    cout<<"input:\n"<<"studentID English Politics Advanced_Data Spatial_Analysis Remote_Sencing\n";
    cin>>a>>b>>c>>d>>e>>f;
    Gis st2(a,b,c,d,e,f);
    st2.disp();
    return 0;
}
