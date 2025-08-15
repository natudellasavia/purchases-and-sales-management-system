#pragma once
#include "string.h"
#include "clsSale.h"

class SalesDataFile{
    private:
        char fileName[30];
        int recordSize;

    public:
        SalesDataFile(const char *n="Sales.dat");

        int addRecord(Sale record);
        bool logicalDeletion(int saleId);
        int modifyRecord(Sale record, int position);
        int modifyRecord(Sale updatedSale);
        int countRecords();
        int findPosition(int saleId);
        Sale readRecord(int position);
        int idSaleExists(int saleId);
        int getLastId();

        int listSale(int option); // by saleId, productId, customerId;
        int querySale(int option, int saleId, int productId, int customerId);
        int querySaleTotalPriceRange(float fromPrice, float toPrice);
        int querySaleDateRange(Date fromDate, Date toDate);
};

