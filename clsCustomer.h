#pragma once
#include "clsPerson.h"

class Customer : public Person{
    private:
        int _customerId;

    public:
        // CONSTRUCTOR
        Customer();

        // SETTERS
        void setCustomerId(int customerId);

        // GETTER
        int getCustomerId();
};
