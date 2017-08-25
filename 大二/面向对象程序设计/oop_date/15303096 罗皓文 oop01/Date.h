#ifndef DATE_H
#define DATE_H
class Date{
public:
    Date(int=2000,int=1,int=1);
    
	int getYear();
	int getMonth();
	int getDay();
    
	void setYear();
	void setMonth();
	void setDay();
    void set();

	void increment();
	void decrement();
	void print();
private:
	int year,month,day;
    int dIM();
};
#endif

