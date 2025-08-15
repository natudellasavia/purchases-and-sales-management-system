#include <iostream>
#include <cstring>
#include "clsPurchase.h"
#include "clsPurchasesDataFile.h"
#include "clsProduct.h"
#include "clsSupplier.h"
#include "clsDate.h"
#include "generalFunctions.h"
using namespace std;


// CONSTRUCTOR
Purchase::Purchase(){
    _purchaseId = 0;
    _productId = 0;
    _supplierId = 0;
    _unitPrice = 0;
    _totalPrice = 0;
    _quantity = 0;
    _date;
    _state = false;
}


// SETTERS
void Purchase::setPurchaseId(int purchaseId){_purchaseId = purchaseId;}
void Purchase::setProductId(int productId){_productId = productId;}
void Purchase::setSupplierId(int supplierId){_supplierId = supplierId;}
void Purchase::setUnitPrice(float unitPrice){_unitPrice = unitPrice;}
void Purchase::setTotalPrice(float totalPrice){_totalPrice = totalPrice;}
void Purchase::setQuantity(int quantity){_quantity = quantity;}
void Purchase::setDate(Date date){_date = date;}
void Purchase::setState(bool state){_state = state;}


// GETTER
int Purchase::getPurchaseId(){return _purchaseId;}
int Purchase::getProductId(){return _productId;}
int Purchase::getSupplierId(){return _supplierId;}
float Purchase::getUnitPrice(){return _unitPrice;}
float Purchase::getTotalPrice(){return _totalPrice;}
int Purchase::getQuantity(){return _quantity;}
Date Purchase::getDate(){return _date;}
bool Purchase::getState(){return _state;}


