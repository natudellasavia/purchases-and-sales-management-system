#include <iostream>
#include <cstring>
#include "clsSupplier.h"
#include "clsSupplierDataFile.h"
using namespace std;


// CONSTRUCTOR
Supplier::Supplier() : Person() {
    _supplierId = 0;
}


// SETTERS
void Supplier::setSupplierId(int supplierId){_supplierId = supplierId;}


// GETTER
int Supplier::getSupplierId(){return _supplierId;}

