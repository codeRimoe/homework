#include <iostream>
using namespace std;

#include "mystr.h"

Mystr::Mystr(const char* lll){
    len=0;
    str=NULL;
    *this=lll;
}

Mystr::Mystr(char ccc){
    len=1;
    str=new char[2];
    str[0]=ccc,str[1]=0;
}
    
Mystr::Mystr(Mystr& other){
   len=0;
   str=NULL;
   *this=other;
}

Mystr::~Mystr(){
    if (str!=NULL)
        delete []str;
}

Mystr& Mystr::operator=(Mystr& other){
    *this = other.getstr();
    return *this;
}

Mystr& Mystr::operator=(const char* lll){
    setstr(lll);
    return *this;
}

Mystr& Mystr::operator=(char ccc){
    Mystr temp(ccc);
    *this=temp;
    return *this;
}

Mystr& Mystr::operator+=(Mystr& other){
    *this+=other.str;
    return *this;
}

Mystr& Mystr::operator+=(const char* lll){
    char* temp=NULL;
    len+=strlen(lll);
    temp=new char[len+1];
    strcpy(temp,str);
    strcat(temp,lll);
    if (str)
        delete []str;
    str=temp;
    return *this;
}

Mystr& Mystr::operator+=(char ccc){
    Mystr temp(ccc);
    *this+=temp;
    return *this;
}

Mystr& Mystr::operator *=(int xxx){
    Mystr temp(*this);
    for (int i=1;i<xxx;i++)
        *this+=temp;
    return *this;
}

char Mystr::operator[](int x){
    return str[x];
}

int Mystr::getlen(){
    return len;
}

char* Mystr::getstr(){
    return str;
}

Mystr& Mystr::setlen(int xxx){
    len=xxx;
    return *this;
}

Mystr& Mystr::setstr(const char* lll){
    if (str!=NULL)
        delete []str;
    len=strlen(lll);
    str=new char[len+1];
    strcpy(str,lll);
    return *this;
}

Mystr& Mystr::display(){
    cout<<*this<<endl;
    return *this;
}

istream& operator>>(istream& ins,Mystr& str){
    char ccc;
    str="";
    while(1){
        cin.get(ccc);
        if(ccc==10)
            break;
        else
            str+=ccc;
    };   
    return ins;
}

ostream& operator<<(ostream& outs,Mystr& str){
    char* p=str.getstr();
    while(*p){
        cout<<*p;
        p++;
    }
    return outs;
}

ostream& operator<<(ostream& outs,Mystr* ppp){
    int lll=ppp[0].getlen();
    cout<<"[ ";
    for(int i=1;i<=lll;i++)
        cout<<ppp[i]<<" ";
    cout<<"]";
    return outs;
}

bool operator==(Mystr& aaa,Mystr& bbb){
    if (strcmp(aaa.getstr(),bbb.getstr())==0)
        return 1;
    return 0;
}

bool operator!=(Mystr& aaa,Mystr& bbb){
    return !(aaa==bbb);
}

bool operator>(Mystr& aaa,Mystr& bbb){
    if (strcmp(aaa.getstr(),bbb.getstr())>0)
        return 1;
    return 0;
}

bool operator<(Mystr& aaa,Mystr& bbb){
    return !(aaa>=bbb);
}

bool operator>=(Mystr& aaa,Mystr& bbb){
    return (aaa>bbb)||(aaa==bbb);
}

bool operator<=(Mystr& aaa,Mystr& bbb){
    return !(aaa>bbb);
}

Mystr* operator/(Mystr& str,int xxx){
    Mystr* result=NULL;
    char* temp=str.getstr();
    int lll=str.getlen();
    if(lll%xxx==0)
        lll/=xxx;
    else
        lll/=xxx,lll++;
    result=new Mystr[lll+1];
    for(int i=1;i<=lll;i++){
        result[i]="";
        for (int j=0;j<xxx&&*temp!=0;j++,temp++)
            result[i]+=*temp;
    }
    result[0]="";
    delete []result[0].getstr();
    result[0].setlen(lll);
    return result;
}

Mystr* operator/(Mystr& str,char ccc){
    Mystr* result=NULL;
    char* temp=str.getstr();
    int cont=0,lll=str.getlen();
    for(int i=0;i<lll;i++){
        while(*temp==ccc)
            temp++;
        if(*temp!=0){
            cont++;
            while(*temp!=ccc&&*temp!=0)
                temp++;
        }
    }
    result=new Mystr[cont+1];
    temp=str.getstr();
    for(int i=1;i<=cont;i++){
        result[i]="";
        while(*temp==ccc)
            temp++;
        for(int j=0;*temp!=ccc&&*temp!=0;j++,temp++)
            result[i]+=*temp;
    }
    result[0]="";
    delete []result[0].getstr();
    result[0].setlen(cont);
    return result;
}
