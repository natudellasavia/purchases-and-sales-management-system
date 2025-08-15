#include <iostream>
#include <cstring>
#include "clsPerson.h"
#include "generalFunctions.h"
using namespace std;


// CONSTRUCTOR
Person::Person(){
    strcpy(_identifier, "");
    strcpy(_name, "");
    _personType = 0;
    strcpy(_phoneNumber, "");
    strcpy(_email, "");
    _state = true;
}


// SETTERS
void Person::setIdentifier(const char* identifier){strcpy(_identifier, identifier);}
void Person::setName(const char* name){strcpy(_name, name);}
void Person::setPersonType(int personType){_personType = personType;}
void Person::setPhoneNumber(const char* phoneNumber){strcpy(_phoneNumber, phoneNumber);}
void Person::setEmail(const char* email){strcpy(_email, email);}
void Person::setState(bool state){_state = state;}


// GETTER
const char* Person::getIdentifier(){return _identifier;}
const char* Person::getName(){return _name;}
int Person::getPersonType(){return _personType;}
const char* Person::getPhoneNumber(){return _phoneNumber;}
const char* Person::getEmail(){return _email;}
bool Person::getState(){return _state;}






























