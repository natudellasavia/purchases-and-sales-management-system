#pragma once
#include "string.h"
#include "clsPurchase.h"

class PurchasesDataFile{
    private:
        char fileName[30];
        int recordSize;

    public:
        PurchasesDataFile(const char *n="Purchases.dat");

        int addRecord(Purchase record);
        bool logicalDeletion(int purchaseId);
        int modifyRecord(Purchase record, int position);
        int modifyRecord(Purchase updatedPurchase);
        int countRecords();
        int findPosition(int purchaseId);
        Purchase readRecord(int position);
        int idPurchaseExists(int purchaseId);
        int getLastId();

        int listPurchase(int option); // by purchaseId, productId, supplierId and date;
        int queryPurchase(int option, int purchaseId, int productId, int supplierId);
        int queryPurchaseTotalPriceRange(float fromPrice, float toPrice);
        int queryPurchaseDateRange(Date fromDate, Date toDate);
};

