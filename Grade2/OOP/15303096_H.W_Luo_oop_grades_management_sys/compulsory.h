#ifndef COMPULSORY_H
#define COMPULSORY_H

class Compulsory{
public:
    Compulsory(int=0,int=0,int=0,int=0);
    ~Compulsory();
    void setID(int);
    void setEnglish(int);
    void setPolitics(int);
    void setAdvancedData(int);
    int getID();
    int getEnglish();
    int getPolitics();
    int getAdvancedData();
    int sum();
    double avg();
    void disp();
protected:
    int stID,english,politics,advancedData;
};
#endif
