#pragma once
#include "clsDate.h"

class Purchase{
    private:
        int _purchaseId;
        int _productId;
        int _supplierId;
        float _unitPrice;
        float _totalPrice;
        int _quantity;
        Date _date;
        bool _state;

    public:
        // CONSTRUCTOR
        Purchase();

        // SETTERS
        void setPurchaseId(int purchaseId);
        void setProductId(int productId);
        void setSupplierId(int supplierId);
        void setUnitPrice(float unitPrice);
        void setTotalPrice(float totalPrice);
        void setQuantity(int quantity);
        void setDate(Date date);
        void setState(bool state);

        // GETTER
        int getPurchaseId();
        int getProductId();
        int getSupplierId();
        float getUnitPrice();
        float getTotalPrice();
        int getQuantity();
        Date getDate();
        bool getState();
};
