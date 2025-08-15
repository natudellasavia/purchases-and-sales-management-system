#pragma once
#include "clsPerson.h"

class Supplier : public Person{
    private:
        int _supplierId;

    public:
        // CONSTRUCTOR
        Supplier();

        // SETTERS
        void setSupplierId(int supplierId);

        // GETTER
        int getSupplierId();
};
