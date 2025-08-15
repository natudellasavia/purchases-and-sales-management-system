#include <iostream>
#include "clsDate.h"
using namespace std;


// CONSTRUCTOR
Date::Date(int d, int m, int y){
    _day = d;
    _month = m;
    _year = y;
}


// SETTERS
void Date::setDay(int d){_day = d;}
void Date::setMonth(int m){_month = m;}
void Date::setYear(int y){_year = y;}


// GETTERS
int Date::getDay(){return _day;}
int Date::getMonth(){return _month;}
int Date::getYear(){return _year;}


// METHODS
bool Date::Add(){
    int d, m, y;

        cout << " DAY: ";
        cin >> d;
        if(d > 0 && d <= 31){
            _day = d;
            cout << " MONTH: ";
            cin >> m;
            if(m > 0 && m <= 12){
                _month = m;
                cout << " YEAR: ";
                cin >> y;
                if(y > 0){
                    _year = y;
                    return true;
                }else{
                    cout << " ERROR: INVALID DATE." << endl << endl;
                    system("pause");
                    system("cls");
                    return false;
                }
            }else{
                cout << " ERROR: INVALID DATE." << endl << endl;
                system("pause");
                system("cls");
                return false;
            }
        }else{
            cout << " ERROR: INVALID DATE." << endl << endl;
            system("pause");
            system("cls");
            return false;
        }
}

void Date::Display(){
    cout << _day << "/" << _month << "/" << _year;
}
