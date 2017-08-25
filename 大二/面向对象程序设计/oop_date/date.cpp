#include <iostream>
using std::cout;using std::endl;using std::cin;

#include "Date.h"

Date::Date(int yyy, int mmm, int ddd){
    set(yyy,mmm,ddd);
}

int Date::getYear(){
	return year;
}

int Date::getMonth(){
	return month;
}

int Date::getDay(){
	return day;
}

void Date::setYear(int yyy){
    year=yyy;
    if(year==0)year=2000;
}

void Date::setMonth(int mmm){
    month=mmm;
    if(month>12)month=12;
    else if (month<1)month=1;
}

void Date::setDay(int ddd){
    day=ddd;
    if(day>dIM())day=dIM();
    else if(day<1)day=1;
}

void Date::set(int yyy,int mmm,int ddd){
    setYear(yyy);
    setMonth(mmm);
    setDay(ddd);
}

void Date::increment(){
    day++;
    if(day>dIM())day=1,month++;
    if(month>12)month=1,year++;
}

void Date::decrement(){
    day--;
    if(day==0){
        month--;
        if(month==0)month=12,year--;
        day=dIM();
    }
}

void Date::print(){
	std::cout<<"Date:"<<year<<"/"<<month<<"/"<<day<<std::endl;
}

int Date::dIM(){            //private function for returning max day in a month
    int dim=30;
    if(((month<8)&&(month%2))||((month>7)&&(month%2==0)))dim=31;    //set day in month except feb.
    if(month==2){
        dim=28;
        if(year%4==0)dim=29;
        if((year%100==0)&&(year%400!=0))dim=28;    //set feb 28 or 29
    }
    return dim;
}
