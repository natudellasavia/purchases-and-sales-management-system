#pragma once

class Product{
    private:
        int _productId;
        char _name[50];
        int _type;
        char _brand[50];
        float _purchasePrice;
        float _sellingPrice;
        int _quantity;
        bool _state;

    public:
        // CONSTRUCTOR
        Product();

        // SETTERS
        void setProductId(int productId);
        void setName(const char* name);
        void setType(int type);
        void setBrand(const char* brand);
        void setPurchasePrice(float purchasePrice);
        void setSellingPrice(float sellingPrice);
        void setQuantity(int quantity);
        void setState(bool state);

        // GETTER
        int getProductId();
        const char* getName();
        int getType();
        const char* getBrand();
        float getPurchasePrice();
        float getSellingPrice();
        int getQuantity();
        bool getState();
};
