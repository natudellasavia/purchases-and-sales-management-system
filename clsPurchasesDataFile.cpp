#include <iostream>
#include <cstring>
#include <cerrno>
#include "clsPurchase.h"
#include "clsPurchasesDataFile.h"
#include "purchaseMenu.h"
#include "generalFunctions.h"
using namespace std;


PurchasesDataFile::PurchasesDataFile(const char *n){
    strcpy(fileName, n);
    recordSize = sizeof(Purchase);

    FILE *pDataFile = fopen(fileName, "rb");
    if (pDataFile == nullptr && errno == ENOENT) {
        // File does not exist, create empty
        pDataFile = fopen(fileName, "wb");
        if (pDataFile != nullptr) {
            fclose(pDataFile);
        }
    }
}


int PurchasesDataFile::addRecord(Purchase record){
    FILE *pDataFile = fopen(fileName, "ab");
    if(pDataFile == nullptr){return -5;} // Could not open the file

    // Auto-incrementing ID:
    if (fseek(pDataFile, 0, SEEK_END) != 0) { // Move to the end of the file to find the last ID
        fclose(pDataFile);
        return -3; // Could not move to the correct position
    }

    int pointerPosition = ftell(pDataFile);
    int purchaseId = (pointerPosition/recordSize) + 1; // Get the ID of the last record and increment it by 1
    record.setPurchaseId(purchaseId); // Assign the auto-incremented ID to the record to be added

    int hasWrittenRecords = fwrite(&record, recordSize, 1, pDataFile);
    fclose(pDataFile);
    return hasWrittenRecords; // 1 if data was written, 0 if not
}


bool PurchasesDataFile::logicalDeletion(int purchaseId){
    Purchase record;
    PurchasesDataFile purchasesFile;

    int position = purchasesFile.findPosition(purchaseId);
    if(position < 0){
        return false; // Could not find the position
    }

    record = purchasesFile.readRecord(position); // Getting the record data
    if(record.getPurchaseId() == 0){
        return false;
    }
    record.setState(false); // Perform a logical deletion by setting the status to false

    return purchasesFile.modifyRecord(record, position); // We overwrite the record
}


int PurchasesDataFile::modifyRecord(Purchase record, int position){
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


int PurchasesDataFile::modifyRecord(Purchase updatedPurchase){
    FILE *pDataFile = fopen(fileName, "rb+");
    if (pDataFile == nullptr) {return -5;} // Could not open the file

    Purchase record;
    int position = 0;
    while (fread(&record, recordSize, 1, pDataFile)) {
        if (record.getPurchaseId() == updatedPurchase.getPurchaseId()) {
            fseek(pDataFile, position * recordSize, SEEK_SET);
            fwrite(&updatedPurchase, recordSize, 1, pDataFile);
            fclose(pDataFile);
            return 1;
        }
        position++;
    }

    fclose(pDataFile);
    return -1; // The purchase was not found
}


int PurchasesDataFile::countRecords(){
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


int PurchasesDataFile::findPosition(int purchaseId){
    FILE *pDataFile = fopen(fileName, "rb");
    if (pDataFile == nullptr){return -5;} // Could not open the file

    int recordCount = countRecords();
    Purchase record;

    for (int i = 0; i < recordCount; i++) {
        if (fseek(pDataFile, i * recordSize, SEEK_SET) != 0) { // Set the position to the desired record
            fclose(pDataFile);
            return -3; // Could not move to the correct position
        }

        if (fread(&record, recordSize, 1, pDataFile) != 1) {
            fclose(pDataFile);
            return -2; // Could not read the file
        }
        if (record.getPurchaseId() == purchaseId) {
            fclose(pDataFile);
            return i; // If found, return the position
        }
    }

    fclose(pDataFile);
    return -1; // The ID was not found in the file
}


Purchase PurchasesDataFile::readRecord(int position){
    Purchase record;
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


int PurchasesDataFile::idPurchaseExists(int purchaseId){
    Purchase record;

    int recordCount = countRecords();
    if (recordCount == -5) {return -5;} // Could not open the file

    // Loop through the product file
    for (int i = 0; i < recordCount; i++){
        record = readRecord(i);

        if (record.getPurchaseId() == purchaseId){
            int id = record.getPurchaseId();
            return id; // All fields match (the purchase already exists) and get the id
        }
    }

    return -2; // No match, can be added
}


int PurchasesDataFile::getLastId(){
    FILE *pDataFile = fopen(fileName, "rb");
    if(pDataFile == nullptr){return -5;} // Could not open the file

    Purchase record;
    int maxId = 0;

    while (fread(&record, sizeof(Purchase), 1, pDataFile) == 1) {
        int currentId = record.getPurchaseId();
        if (currentId > maxId) {
            maxId = currentId;
        }
    }

    fclose(pDataFile);
    return maxId; // The biggest ID found -> last ID
}



/// ------------------------- L I S T S -------------------------

int PurchasesDataFile::listPurchase(int option){
    PurchasesDataFile purchasesFile;

    int recordCount = purchasesFile.countRecords();
    if (recordCount < 0) {
        return -2; // Unable to generate the list
    } else if (recordCount == 0){
        return -3; // There are no purchases registered
    }

    Purchase* vec = new Purchase[recordCount]; // We create a dynamic array of objects to 'sort by'
    int dynamicMemorySize = 0; // Stores the total number of records in dynamic memory

    for (int i = 0; i < recordCount; i++) {
        Purchase record = purchasesFile.readRecord(i);
        // CHECK THAT THE PURCHASE IS ACTIVE
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
                case 1:{ // BY PURCHASE ID
                    if (vec[i].getPurchaseId() > vec[x].getPurchaseId()) {
                        Purchase auxiliary = vec[i];
                        vec[i] = vec[x];
                        vec[x] = auxiliary;
                    }
                    break;
                }

                case 2:{ // BY PRODUCT ID
                    if (vec[i].getProductId() > vec[x].getProductId()) {
                        Purchase auxiliary = vec[i];
                        vec[i] = vec[x];
                        vec[x] = auxiliary;
                    }
                    break;
                }

                case 3:{ // BY SUPPLIER ID
                    if (vec[i].getSupplierId() > vec[x].getSupplierId()){
                        Purchase auxiliary = vec[i];
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

int PurchasesDataFile::queryPurchase(int option, int purchaseId, int productId, int supplierId){
    PurchasesDataFile purchasesFile;
    Purchase record;
    int result = -1;

    int recordCount = purchasesFile.countRecords();
    if (recordCount < 0) {
        return -2; // Unable to generate the list
    } else if (recordCount == 0){
        return -3; // There are no purchases registered
    }

    for(int i = 0; i < recordCount; i++){
        record = purchasesFile.readRecord(i);

        // Iterates over the purchase file and shows the record
        switch(option){
            case 1:{ // BY PURCHASE ID
                if(record.getPurchaseId() == purchaseId){
                    if(record.getState()){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }else{
                        return -4; // The purchase is deactivated
                    }
                }
                break;
            }

            case 2:{ // BY PRODUCT ID
                if(record.getProductId() == productId){
                    if(record.getState()){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }
                }
                break;
            }

            case 3:{ // BY SUPPLIER ID
                if(record.getSupplierId() == supplierId){
                    if(record.getState()){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }
                }
                break;
            }
        }
    }

    return result;
}


int PurchasesDataFile::queryPurchaseTotalPriceRange(float fromPrice, float toPrice){
    Purchase record;
    PurchasesDataFile purchasesFile;
    int result = -1;

    // Check the purchase file to see if the price in the record is between the two entered from the keyboard
    int recordCount = purchasesFile.countRecords();
    if (recordCount <= 0) {return -2;} // There are no products loaded

    for(int i = 0; i < recordCount; i++){
        record = purchasesFile.readRecord(i);
        if(record.getState()){
            if(fromPrice <= record.getTotalPrice() && record.getTotalPrice() <= toPrice){
                displayWithId(record);
                result++; // Adds +1 to indicate that a record was found before returning
            }
        }
    }

    return result; // Returns -1 if no record was found
}


int PurchasesDataFile::queryPurchaseDateRange(Date fromDate, Date toDate){
    Purchase record;
    PurchasesDataFile purchasesFile;
    int result = -1;

    // Check the purchase file to see if the date in the record is between the two entered from the keyboard
    int recordCount = purchasesFile.countRecords();
    if (recordCount <= 0) {return -2;} // There are no products loaded

    for(int i = 0; i < recordCount; i++){
        record = purchasesFile.readRecord(i);
        Date dateRecord = record.getDate();

        // Validate that the record date is greater than or equal to the start date and less than or equal to the end date
        if(dateGreaterThanOrEqual(dateRecord, fromDate) && dateLessThanOrEqual(dateRecord, toDate)){
            displayWithId(record);
            result++; // Adds +1 to indicate that a record was found before returning
        }
    }

    return result; // Returns -1 if no record was found
}




