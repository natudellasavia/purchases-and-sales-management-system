#include <iostream>
#include <cstring>
#include "clsProduct.h"
#include "clsProductsDataFile.h"
#include "generalFunctions.h"
using namespace std;


// CONSTRUCTOR
Product::Product(){
    _productId = 0;
    strcpy(_name, "");
    _type = 0;
    strcpy(_brand, "");
    _purchasePrice = 0;
    _sellingPrice = 0;
    _quantity = 0;
    _state = true;
}


// SETTERS
void Product::setProductId(int productId){_productId = productId;}
void Product::setName(const char* name){strcpy(_name, name);}
void Product::setType(int type){_type = type;}
void Product::setBrand(const char* brand){strcpy(_brand, brand);}
void Product::setPurchasePrice(float purchasePrice){_purchasePrice = purchasePrice;}
void Product::setSellingPrice(float sellingPrice){_sellingPrice = sellingPrice;}
void Product::setQuantity(int quantity){_quantity = quantity;}
void Product::setState(bool state){_state = state;}


// GETTER
int Product::getProductId(){return _productId;}
const char* Product::getName(){return _name;}
int Product::getType(){return _type;}
const char* Product::getBrand(){return _brand;}
float Product::getPurchasePrice(){return _purchasePrice;}
float Product::getSellingPrice(){return _sellingPrice;}
int Product::getQuantity(){return _quantity;}
bool Product::getState(){return _state;}




