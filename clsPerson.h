#pragma once


class Person{
    protected:
        char _identifier[12];
        char _name[50];
        int _personType; // 1 - Natural person / 2 - Legal entity
        char _phoneNumber[30];
        char _email[50];
        bool _state;

    public:
        // CONSTRUCTOR
        Person();

        // SETTERS
        void setIdentifier(const char* identifier);
        void setName(const char* name);
        void setPersonType(int personType);
        void setPhoneNumber(const char* phoneNumber);
        void setEmail(const char* email);
        void setState(bool state);

        // GETTER
        const char* getIdentifier();
        const char* getName();
        int getPersonType();
        const char* getPhoneNumber();
        const char* getEmail();
        bool getState();
};

