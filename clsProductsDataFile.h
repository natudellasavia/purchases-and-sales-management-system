#pragma once
#include "clsProduct.h"
#include "string.h"

class ProductsDataFile{
    private:
        char fileName[30];
        int recordSize;

    public:
        ProductsDataFile(const char *n="Products.dat");

        int addRecord(Product record);
        bool logicalDeletion(int productId);
        int modifyRecord(Product record, int position);
        int modifyRecord(Product updatedProduct);
        int countRecords();
        int findPosition(int productId);
        Product readRecord(int position);
        int idProductExists(const char* name, int type, const char* brand);

        int listProducts(int option);
        int queryProduct(int option, int productId, const char* name, int type, const char* brand);
};

