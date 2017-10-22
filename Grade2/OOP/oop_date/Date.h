#ifndef DATE_H
#define DATE_H
class Date{
public:
    Date(int=2000,int=1,int=1);
    
	int getYear();
	int getMonth();
	int getDay();
    
	void setYear(int=2000);
	void setMonth(int=1);
	void setDay(int=1);
    void set(int=2000,int=1,int=1);

	void increment();
	void decrement();
	void print();
private:
	int year,month,day;
    int dIM();
};
#endif

