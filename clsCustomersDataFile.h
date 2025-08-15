#pragma once
#include "clsCustomer.h"
#include "string.h"


class CustomersDataFile{
    private:
        char fileName[30];
        int recordSize;

    public:
        CustomersDataFile(const char *n="Customers.dat");
        int addRecord(Customer record);
        bool logicalDeletion(int customerId);
        int modifyRecord(Customer record, int position);
        int modifyRecord(Customer updatedCustomer);
        int countRecords();
        int findPosition(int customerId);
        Customer readRecord(int position);
        int idCustomerExists(const char* identifier);

        int listCustomers(int option);
        int queryCustomer(int option, int customerId, const char* identifier, const char* name, int personType);
};

