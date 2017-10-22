#ifndef MYSTR_H
#define MYSTR_H

class Mystr{
public:
    Mystr(const char* = "") ;
    Mystr(char);
    Mystr(Mystr&);
    ~Mystr();

    friend std::istream& operator>>(std::istream&,Mystr&);
    friend std::ostream& operator<<(std::ostream&,Mystr&);
    friend std::ostream& operator<<(std::ostream&,Mystr*);
    friend bool operator==(Mystr&,Mystr&);
    friend bool operator!=(Mystr&,Mystr&);
    friend bool operator>(Mystr&,Mystr&);
    friend bool operator<(Mystr&,Mystr&);
    friend bool operator>=(Mystr&,Mystr&);
    friend bool operator<=(Mystr&,Mystr&);
    friend Mystr* operator/(Mystr&,char);
    friend Mystr* operator/(Mystr&,int);
public:
    Mystr& operator = (Mystr&);
    Mystr& operator = (const char*);
    Mystr& operator = (char);
    Mystr& operator +=(Mystr&);
    Mystr& operator +=(const char*);
    Mystr& operator +=(char);
    Mystr& operator *=(int);
    char operator[](int);

    int getlen();
    char* getstr();
    Mystr& setlen(int);
    Mystr& setstr(const char*);
    Mystr& display();

private:
    int len;
    char* str;

};

#endif
