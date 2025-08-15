#include <iostream>
#include <clocale>
#include <cerrno>
#include "clsCustomer.h"
#include "clsCustomersDataFile.h"
#include "customerMenu.h"
using namespace std;


CustomersDataFile::CustomersDataFile(const char *n){
    strcpy(fileName, n);
    recordSize = sizeof(Customer);

    FILE *pDataFile = fopen(fileName, "rb");
    if (pDataFile == nullptr && errno == ENOENT) {
        // File does not exist, create empty
        pDataFile = fopen(fileName, "wb");
        if (pDataFile != nullptr) {
            fclose(pDataFile);
        }
    }
}


int CustomersDataFile::addRecord(Customer record){
    FILE *pDataFile = fopen(fileName, "ab");
    if(pDataFile == nullptr){return -5;} // Could not open the file

    // Auto-incrementing ID:
    if (fseek(pDataFile, 0, SEEK_END) != 0) { // Move to the end of the file to find the last ID
        fclose(pDataFile);
        return -3; // Could not move to the correct position
    }

    int pointerPosition = ftell(pDataFile);
    int customerId = (pointerPosition/recordSize) + 1; // Get the ID of the last record and increment it by 1
    record.setCustomerId(customerId); // Assign the auto-incremented ID to the record to be added

    int hasWrittenRecords = fwrite(&record, recordSize, 1, pDataFile);
    fclose(pDataFile);
    return hasWrittenRecords; // 1 if data was written, 0 if not
}


bool CustomersDataFile::logicalDeletion(int customerId){
    Customer record;
    CustomersDataFile customersFile;

    int position = customersFile.findPosition(customerId);
    if(position < 0){
        return false; // Could not find the position
    }

    record = customersFile.readRecord(position); // Getting the record data
    if(record.getCustomerId() == 0){
        return false;
    }
    record.setState(false); // We perform a logical deletion by setting the status to false

    return customersFile.modifyRecord(record, position); // We overwrite the record
}


int CustomersDataFile::modifyRecord(Customer record, int position){
    FILE *pDataFile = fopen(fileName, "rb+");
    if (pDataFile == nullptr){return -5;} // Could not open the file

    if (fseek(pDataFile, position * recordSize, SEEK_SET) != 0) { // Set the position to the desired record
        fclose(pDataFile);
        return -3; // Could not move to the correct position
    }

    int hasWrittenRecords = fwrite(&record, recordSize, 1, pDataFile);
    fclose(pDataFile);
    return hasWrittenRecords; // 1 if data was written, 0 if not
}


int CustomersDataFile::modifyRecord(Customer updatedCustomer){
    FILE *pDataFile = fopen(fileName, "rb+");
    if (pDataFile == nullptr) {return -5;} // Could not open the file

    Customer record;
    int position = 0;
    while (fread(&record, recordSize, 1, pDataFile)) {
        if (record.getCustomerId() == updatedCustomer.getCustomerId()) {
            fseek(pDataFile, position * recordSize, SEEK_SET);
            fwrite(&updatedCustomer, recordSize, 1, pDataFile);
            fclose(pDataFile);
            return 1;
        }
        position++;
    }

    fclose(pDataFile);
    return -1; // The customer was not found
}


int CustomersDataFile::countRecords(){
    FILE *pDataFile = fopen(fileName, "rb");
    if(pDataFile == nullptr){return -5;} // Could not open the file

    if (fseek(pDataFile, 0, SEEK_END) != 0) { // Set the position to the end of the data file
        fclose(pDataFile);
        return -3; // Could not move to the correct position
    }

    int dataFileSize = ftell(pDataFile); // Number of bytes from the beginning of the file to the pointer
    fclose(pDataFile);

    int recordCount = dataFileSize/recordSize;
    return recordCount;
}


int CustomersDataFile::findPosition(int customerId){
    FILE *pDataFile = fopen(fileName, "rb");
    if (pDataFile == nullptr){return -5;} // Could not open the file

    int recordCount = countRecords();
    Customer record;

    for (int i = 0; i < recordCount; i++) {
        if (fseek(pDataFile, i * recordSize, SEEK_SET) != 0) { // Set the position to the desired record
            fclose(pDataFile);
            return -3; // Could not move to the correct position
        }

        if (fread(&record, recordSize, 1, pDataFile) != 1) {
            fclose(pDataFile);
            return -2; // Could not read the file
        }
        if (record.getCustomerId() == customerId) {
            fclose(pDataFile);
            return i; // If found, return the position
        }
    }

    fclose(pDataFile);
    return -1; // The ID was not found in the file
}


Customer CustomersDataFile::readRecord(int position){
    Customer record;
    FILE *pDataFile = fopen(fileName, "rb");
    if (pDataFile == nullptr){return record;} // Return the object's attributes initialized by the constructor

    if (fseek(pDataFile, position * recordSize, SEEK_SET) != 0) { // Set the position to the desired record
        fclose(pDataFile);
        return record; // Could not move to the correct position. Return the object's attributes initialized by the constructor
    }

    if (fread(&record, recordSize, 1, pDataFile) != 1) {
        fclose(pDataFile);
        return record; // Could not read the file. Return the object's attributes initialized by the constructor
    }

    fclose(pDataFile);
    return record;
}


int CustomersDataFile::idCustomerExists(const char* identifier){
    Customer record;

    int recordCount = countRecords();
    if (recordCount == -5) {return -5;} // Could not open the file

    // Loop through the customer file
    for (int i = 0; i < recordCount; i++){
        record = readRecord(i);

        if (strcmp(record.getIdentifier(), identifier) == 0){
            int id = record.getCustomerId();
            return id; // All fields match (the customer already exists) and get the id
        }
    }

    return -2; // No match, can be added
}



/// ------------------------- L I S T S -------------------------

int CustomersDataFile::listCustomers(int option){
    CustomersDataFile customersFile;

    int recordCount = customersFile.countRecords();
    if (recordCount < 0) {
        return -2; // Unable to generate the list
    } else if (recordCount == 0){
        return -3; // There are no customers registered
    }

    Customer* vec = new Customer[recordCount]; // We create a dynamic array of objects to sort by id
    int dynamicMemorySize = 0; // Stores the total number of records in dynamic memory

    for (int i = 0; i < recordCount; i++) {
        Customer record = customersFile.readRecord(i);
        // CHECK THAT THE CUSTOMER IS ACTIVE
        if (record.getState()) {
            vec[dynamicMemorySize] = record; // The record is saved only if it is active
            dynamicMemorySize++;
        }
    }

    // i -> Position of the record / x -> Next record position
    for (int i = 0; i < dynamicMemorySize - 1; i++) {
        // Traverse the vector by moving to the next record
        for (int x = i + 1; x < dynamicMemorySize; x++) {
            // Swap them if the first record is greater
            switch(option){
                case 1:{ // BY ID
                    if (vec[i].getCustomerId() > vec[x].getCustomerId()) {
                        Customer auxiliary = vec[i];
                        vec[i] = vec[x];
                        vec[x] = auxiliary;
                    }
                    break;
                }

                case 2:{ // BY IDENTIFIER
                    if (strcmp(vec[i].getIdentifier(), vec[x].getIdentifier()) > 0) { // If > 0, the first string is bigger than the second
                        Customer auxiliary = vec[i];
                        vec[i] = vec[x];
                        vec[x] = auxiliary;
                    }
                }

                case 3:{ // BY PERSON TYPE
                    if (vec[i].getPersonType() > vec[x].getPersonType()) {
                        Customer auxiliary = vec[i];
                        vec[i] = vec[x];
                        vec[x] = auxiliary;
                    }
                }
            }
        }
    }

    // All file records are displayed
    for (int i = 0; i < dynamicMemorySize; i++) {
        displayWithId(vec[i]);
    }

    delete[] vec; // Memory is freed
    return 0; // Operation successful
}



/// ------------------------- Q U E R I E S -------------------------

int CustomersDataFile::queryCustomer(int option, int customerId, const char* identifier, const char* name, int personType){
    CustomersDataFile customersFile;
    Customer record;
    int result = -1;

    int recordCount = customersFile.countRecords();
    if (recordCount < 0) {
        return -2; // Unable to generate the list
    } else if (recordCount == 0){
        return -3; // There are no customers registered
    }

    for(int i = 0; i < recordCount; i++){
        record = customersFile.readRecord(i);
        // Iterates over the customers file and shows the record
        switch(option){
            case 1:{ // BY ID
                if(record.getCustomerId() == customerId){
                    if(record.getState()){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }else{
                        return -4; // The customer is deactivated
                    }
                }
                break;
            }

            case 2:{ // BY IDENTIFIER
                if(strcmp(record.getIdentifier(), identifier) == 0){
                    if(record.getState()){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }else{
                        return -4; // The customer is deactivated
                    }
                }
                break;
            }

            case 3:{ // BY NAME
                if(strcmp(record.getName(), name) == 0){
                    if(record.getState()){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }
                }
                break;
            }

            case 4:{ // BY PERSON TYPE
                if(record.getPersonType() == personType){
                    if(record.getState()){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }
                }
                break;
            }
        }
    }

    return result; // Returns -1 if no record was found
}
