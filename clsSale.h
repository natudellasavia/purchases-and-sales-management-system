#pragma once
#include "clsDate.h"

class Sale{
    private:
        int _saleId;
        int _productId;
        int _customerId;
        float _unitPrice;
        float _totalPrice;
        int _quantity;
        Date _date;
        bool _state;

    public:
        // CONSTRUCTOR
        Sale();

        // SETTERS
        void setSaleId(int saleId);
        void setProductId(int productId);
        void setCustomerId(int customerId);
        void setUnitPrice(float unitPrice);
        void setTotalPrice(float totalPrice);
        void setQuantity(int quantity);
        void setDate(Date date);
        void setState(bool state);

        // GETTER
        int getSaleId();
        int getProductId();
        int getCustomerId();
        float getUnitPrice();
        float getTotalPrice();
        int getQuantity();
        Date getDate();
        bool getState();
};
