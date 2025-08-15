#pragma once
#include "clsSupplier.h"
#include "string.h"


class SuppliersDataFile{
    private:
        char fileName[30];
        int recordSize;

    public:
        SuppliersDataFile(const char *n="Suppliers.dat");
        int addRecord(Supplier record);
        bool logicalDeletion(int supplierId);
        int modifyRecord(Supplier record, int position);
        int modifyRecord(Supplier updatedSupplier);
        int countRecords();
        int findPosition(int supplierId);
        Supplier readRecord(int position);
        int idSupplierExists(const char* identifier);

        int listSupplier(int option);
        int querySupplier(int option, int supplierId, const char* identifier, const char* name, int personType);
};

