#pragma once

class Date{
    private:
        int _day;
        int _month;
        int _year;

    public:
        // CONSTRUCTOR
        Date(int d=0, int m=0, int y=0000);

        // SETTERS
        void setDay(int d);
        void setMonth(int m);
        void setYear(int y);

        // GETTERS
        int getDay();
        int getMonth();
        int getYear();

        // METHODS
        bool Add();
        void Display();
};
