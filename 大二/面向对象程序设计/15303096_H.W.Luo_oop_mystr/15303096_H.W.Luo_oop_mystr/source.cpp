#include <iostream>
#include "mystr.h"

using namespace std;

int main(){
    Mystr a("H.W. Luo");
    Mystr b;
    Mystr c(a);
    //constructed function
    Mystr* cc=NULL;
    cout<<a<<endl<<b<<endl<<c<<endl<<endl;         //check operator<<
    
    b+='o';
    cout<<b<<endl;                           //check operator+=
    cout<<"Please input string of var_b:";
    cin>>b;                                  //check operator>>
    cout<<b<<endl;
    b*=4;                                    //check operator*=
    cout<<b<<endl;
    cc=b/4;                                  //check operator/int
    cout<<cc<<endl;
    cc=b/5;                                  //check operator/int
    cout<<cc<<endl;
    b="-1997-5---20";
    cc=b/'-';                                //check operator/char
    cout<<cc<<endl;
    cc=b/5;                                  //check operator/int
    cout<<cc<<endl<<endl;
    
    cout<<(a==c)<<endl<<(a!=c)<<endl<<(a>c)<<endl<<(a<c)<<endl<<(a>=c)<<endl<<(a<=c)<<endl;
    b="Y.C. Li";
    c=b;                                     //check opeartor =
    cout<<a<<endl<<b<<endl<<c<<endl<<endl;
    cout<<(a==c)<<endl<<(a!=c)<<endl<<(a>c)<<endl<<(a<c)<<endl<<(a>=c)<<endl<<(a<=c)<<endl;
    //check operator of cmp
    
    int i=0;
    while(a[i])cout<<a[i++];
    i=0;
    while(b[i])cout<<b[i++];
    cout<<endl;
    //check operator []
    
    a+=" and ";
    cout<<a<<endl;
    a+=b;
    cout<<b<<endl<<a<<endl;
    //check operator +=
    
    return 0;
}
