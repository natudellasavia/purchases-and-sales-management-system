#include <iostream>
#include <cstring>
#include <cerrno>
#include "clsSale.h"
#include "clsSalesDataFile.h"
#include "saleMenu.h"
#include "generalFunctions.h"
using namespace std;


SalesDataFile::SalesDataFile(const char *n){
    strcpy(fileName, n);
    recordSize = sizeof(Sale);

    FILE *pDataFile = fopen(fileName, "rb");
    if (pDataFile == nullptr && errno == ENOENT) {
        // File does not exist, create empty
        pDataFile = fopen(fileName, "wb");
        if (pDataFile != nullptr) {
            fclose(pDataFile);
        }
    }
}


int SalesDataFile::addRecord(Sale record){
    FILE *pDataFile = fopen(fileName, "ab");
    if(pDataFile == nullptr){return -5;} // Could not open the file

    // Auto-incrementing ID:
    if (fseek(pDataFile, 0, SEEK_END) != 0) { // Move to the end of the file to find the last ID
        fclose(pDataFile);
        return -3; // Could not move to the correct position
    }

    int pointerPosition = ftell(pDataFile);
    int saleId = (pointerPosition/recordSize) + 1; // Get the ID of the last record and increment it by 1
    record.setSaleId(saleId); // Assign the auto-incremented ID to the record to be added

    int hasWrittenRecords = fwrite(&record, recordSize, 1, pDataFile);
    fclose(pDataFile);
    return hasWrittenRecords; // 1 if data was written, 0 if not
}


bool SalesDataFile::logicalDeletion(int saleId){
    Sale record;
    SalesDataFile salesFile;

    int position = salesFile.findPosition(saleId);
    if(position < 0){
        return false; // Could not find the position
    }

    record = salesFile.readRecord(position); // Getting the record data
    if(record.getSaleId() == 0){
        return false;
    }
    record.setState(false); // Perform a logical deletion by setting the status to false

    return salesFile.modifyRecord(record, position); // We overwrite the record
}


int SalesDataFile::modifyRecord(Sale record, int position){
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


int SalesDataFile::modifyRecord(Sale updatedSale){
    FILE *pDataFile = fopen(fileName, "rb+");
    if (pDataFile == nullptr) {return -5;} // Could not open the file

    Sale record;
    int position = 0;
    while (fread(&record, recordSize, 1, pDataFile)) {
        if (record.getSaleId() == updatedSale.getSaleId()) {
            fseek(pDataFile, position * recordSize, SEEK_SET);
            fwrite(&updatedSale, recordSize, 1, pDataFile);
            fclose(pDataFile);
            return 1;
        }
        position++;
    }

    fclose(pDataFile);
    return -1; // The sale was not found
}


int SalesDataFile::countRecords(){
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


int SalesDataFile::findPosition(int saleId){
    FILE *pDataFile = fopen(fileName, "rb");
    if (pDataFile == nullptr){return -5;} // Could not open the file

    int recordCount = countRecords();
    Sale record;

    for (int i = 0; i < recordCount; i++) {
        if (fseek(pDataFile, i * recordSize, SEEK_SET) != 0) { // Set the position to the desired record
            fclose(pDataFile);
            return -3; // Could not move to the correct position
        }

        if (fread(&record, recordSize, 1, pDataFile) != 1) {
            fclose(pDataFile);
            return -2; // Could not read the file
        }
        if (record.getSaleId() == saleId) {
            fclose(pDataFile);
            return i; // If found, return the position
        }
    }

    fclose(pDataFile);
    return -1; // The ID was not found in the file
}


Sale SalesDataFile::readRecord(int position){
    Sale record;
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


int SalesDataFile::idSaleExists(int saleId){
    Sale record;

    int recordCount = countRecords();
    if (recordCount == -5) {return -5;} // Could not open the file

    // Loop through the product file
    for (int i = 0; i < recordCount; i++){
        record = readRecord(i);

        if (record.getSaleId() == saleId){
            int id = record.getSaleId();
            return id; // All fields match (the purchase already exists) and get the id
        }
    }

    return -2; // No match, can be added
}


int SalesDataFile::getLastId(){
    FILE *pDataFile = fopen(fileName, "rb");
    if(pDataFile == nullptr){return -5;} // Could not open the file

    Sale record;
    int maxId = 0;

    while (fread(&record, sizeof(Sale), 1, pDataFile) == 1) {
        int currentId = record.getSaleId();
        if (currentId > maxId) {
            maxId = currentId;
        }
    }

    fclose(pDataFile);
    return maxId; // The biggest ID found -> last ID
}



/// ------------------------- L I S T S -------------------------

int SalesDataFile::listSale(int option){
    SalesDataFile salesFile;

    int recordCount = salesFile.countRecords();
    if (recordCount < 0) {
        return -2; // Unable to generate the list
    } else if (recordCount == 0){
        return -3; // There are no sales registered
    }

    Sale* vec = new Sale[recordCount]; // We create a dynamic array of objects to 'sort by'
    int dynamicMemorySize = 0; // Stores the total number of records in dynamic memory

    for (int i = 0; i < recordCount; i++) {
        Sale record = salesFile.readRecord(i);
        // CHECK THAT THE SALE IS ACTIVE
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
                case 1:{ // BY SALE ID
                    if (vec[i].getSaleId() > vec[x].getSaleId()) {
                        Sale auxiliary = vec[i];
                        vec[i] = vec[x];
                        vec[x] = auxiliary;
                    }
                    break;
                }

                case 2:{ // BY PRODUCT ID
                    if (vec[i].getProductId() > vec[x].getProductId()) {
                        Sale auxiliary = vec[i];
                        vec[i] = vec[x];
                        vec[x] = auxiliary;
                    }
                    break;
                }

                case 3:{ // BY CUSTOMER ID
                    if (vec[i].getCustomerId() > vec[x].getCustomerId()){
                        Sale auxiliary = vec[i];
                        vec[i] = vec[x];
                        vec[x] = auxiliary;
                    }
                    break;
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

int SalesDataFile::querySale(int option, int saleId, int productId, int customerId){
    SalesDataFile salesFile;
    Sale record;
    int result = -1;

    int recordCount = salesFile.countRecords();
    if (recordCount < 0) {
        return -2; // Unable to generate the list
    } else if (recordCount == 0){
        return -3; // There are no sales registered
    }

    for(int i = 0; i < recordCount; i++){
        record = salesFile.readRecord(i);
        if(record.getState()){
            // Iterates over the sale file and shows the record
            switch(option){
                case 1:{ // BY SALE ID
                    if(record.getSaleId() == saleId){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }
                    break;
                }

                case 2:{ // BY PRODUCT ID
                    if(record.getProductId() == productId){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }
                    break;
                }

                case 3:{ // BY CUSTOMER ID
                    if(record.getCustomerId() == customerId){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }
                    break;
                }
            }
        }else{
            result = -3; // The sale is inactive
        }
    }

    return result; // Returns -1 if no record was found / -3 if the sale is inactive
}


int SalesDataFile::querySaleTotalPriceRange(float fromPrice, float toPrice){
    Sale record;
    SalesDataFile salesFile;
    int result = -1;

    // Check the sale file to see if the price in the record is between the two entered from the keyboard
    int recordCount = salesFile.countRecords();
    if (recordCount <= 0) {return -2;} // There are no products loaded

    for(int i = 0; i < recordCount; i++){
        record = salesFile.readRecord(i);
        if(record.getState()){
            if(fromPrice <= record.getTotalPrice() && record.getTotalPrice() <= toPrice){
                displayWithId(record);
                result++; // Adds +1 to indicate that a record was found before returning
            }
        }
    }

    return result; // Returns -1 if no record was found
}


int SalesDataFile::querySaleDateRange(Date fromDate, Date toDate){
    Sale record;
    SalesDataFile salesFile;
    int result = -1;

    // Check the sale file to see if the date in the record is between the two entered from the keyboard
    int recordCount = salesFile.countRecords();
    if (recordCount <= 0) {return -2;} // There are no products loaded

    for(int i = 0; i < recordCount; i++){
        record = salesFile.readRecord(i);
        Date dateRecord = record.getDate();

        // Validate that the record date is greater than or equal to the start date and less than or equal to the end date
        if(dateGreaterThanOrEqual(dateRecord, fromDate) && dateLessThanOrEqual(dateRecord, toDate)){
            displayWithId(record);
            result++; // Adds +1 to indicate that a record was found before returning
        }
    }

    return result; // Returns -1 if no record was found
}




