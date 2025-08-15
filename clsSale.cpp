#include <iostream>
#include <cstring>
#include "clsSale.h"
#include "clsSalesDataFile.h"
#include "clsProduct.h"
#include "clsCustomer.h"
#include "clsDate.h"
#include "generalFunctions.h"
using namespace std;


// CONSTRUCTOR
Sale::Sale(){
    _saleId = 0;
    _productId = 0;
    _customerId = 0;
    _unitPrice = 0;
    _totalPrice = 0;
    _quantity = 0;
    _date;
    _state = false;
}


// SETTERS
void Sale::setSaleId(int saleId){_saleId = saleId;}
void Sale::setProductId(int productId){_productId = productId;}
void Sale::setCustomerId(int customerId){_customerId = customerId;}
void Sale::setUnitPrice(float unitPrice){_unitPrice = unitPrice;}
void Sale::setTotalPrice(float totalPrice){_totalPrice = totalPrice;}
void Sale::setQuantity(int quantity){_quantity = quantity;}
void Sale::setDate(Date date){_date = date;}
void Sale::setState(bool state){_state = state;}


// GETTER
int Sale::getSaleId(){return _saleId;}
int Sale::getProductId(){return _productId;}
int Sale::getCustomerId(){return _customerId;}
float Sale::getUnitPrice(){return _unitPrice;}
float Sale::getTotalPrice(){return _totalPrice;}
int Sale::getQuantity(){return _quantity;}
Date Sale::getDate(){return _date;}
bool Sale::getState(){return _state;}


