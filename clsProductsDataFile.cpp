#include <iostream>
#include <cstring>
#include <cerrno>
#include "clsProduct.h"
#include "clsProductsDataFile.h"
#include "productMenu.h"
using namespace std;


ProductsDataFile::ProductsDataFile(const char *n){
    strcpy(fileName, n);
    recordSize = sizeof(Product);

    FILE *pDataFile = fopen(fileName, "rb");
    if (pDataFile == nullptr && errno == ENOENT) {
        // File does not exist, create empty
        pDataFile = fopen(fileName, "wb");
        if (pDataFile != nullptr) {
            fclose(pDataFile);
        }
    }
}


int ProductsDataFile::addRecord(Product record){
    FILE *pDataFile = fopen(fileName, "ab");
    if(pDataFile == nullptr){return -5;} // Could not open the file

    // Auto-incrementing ID:
    if (fseek(pDataFile, 0, SEEK_END) != 0) { // Move to the end of the file to find the last ID
        fclose(pDataFile);
        return -3; // Could not move to the correct position
    }

    int pointerPosition = ftell(pDataFile);
    int productId = (pointerPosition/recordSize) + 1; // Get the ID of the last record and increment it by 1
    record.setProductId(productId); // Assign the auto-incremented ID to the record to be added

    int hasWrittenRecords = fwrite(&record, recordSize, 1, pDataFile);
    fclose(pDataFile);
    return hasWrittenRecords; // 1 if data was written, 0 if not
}


bool ProductsDataFile::logicalDeletion(int productId){
    Product record;
    ProductsDataFile productsFile;

    int position = productsFile.findPosition(productId);
    if(position < 0){
        return false; // Could not find the position
    }

    record = productsFile.readRecord(position); // Getting the record data
    if(record.getProductId() == 0){
        return false;
    }
    record.setState(false); // We perform a logical deletion by setting the status to false

    return productsFile.modifyRecord(record, position); // We overwrite the record
}


int ProductsDataFile::modifyRecord(Product record, int position){
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


int ProductsDataFile::modifyRecord(Product updatedProduct){
    FILE *pDataFile = fopen(fileName, "rb+");
    if (pDataFile == nullptr) {return -5;} // Could not open the file

    Product record;
    int position = 0;
    while (fread(&record, recordSize, 1, pDataFile)) {
        if (record.getProductId() == updatedProduct.getProductId()) {
            fseek(pDataFile, position * recordSize, SEEK_SET);
            fwrite(&updatedProduct, recordSize, 1, pDataFile);
            fclose(pDataFile);
            return 1;
        }
        position++;
    }

    fclose(pDataFile);
    return -1; // The product was not found
}


int ProductsDataFile::countRecords(){
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


int ProductsDataFile::findPosition(int productId){
    FILE *pDataFile = fopen(fileName, "rb");
    if (pDataFile == nullptr){return -5;} // Could not open the file

    int recordCount = countRecords();
    Product record;

    for (int i = 0; i < recordCount; i++) {
        if (fseek(pDataFile, i * recordSize, SEEK_SET) != 0) { // Set the position to the desired record
            fclose(pDataFile);
            return -3; // Could not move to the correct position
        }

        if (fread(&record, recordSize, 1, pDataFile) != 1) {
            fclose(pDataFile);
            return -2; // Could not read the file
        }
        if (record.getProductId() == productId) {
            fclose(pDataFile);
            return i; // If found, return the position
        }
    }

    fclose(pDataFile);
    return -1; // The ID was not found in the file
}


Product ProductsDataFile::readRecord(int position){
    Product record;
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


int ProductsDataFile::idProductExists(const char* name, int type, const char* brand){
    Product record;

    int recordCount = countRecords();
    if (recordCount == -5) {return -5;} // Could not open the file

    // Loop through the product file
    for (int i = 0; i < recordCount; i++){
        record = readRecord(i);

        if (strcmp(record.getName(), name) == 0 && record.getType() == type && strcmp(record.getBrand(), brand) == 0){
            int id = record.getProductId();
            return id; // All fields match (the product already exists) and get the id
        }
    }

    return -2; // No match, can be added
}



/// ------------------------- L I S T S -------------------------

int ProductsDataFile::listProducts(int option){
    ProductsDataFile productsFile;

    int recordCount = productsFile.countRecords();
    if (recordCount < 0) {
        return -2; // Unable to generate the list
    } else if (recordCount == 0){
        return -3; // There are no products registered
    }

    Product* vec = new Product[recordCount]; // We create a dynamic array of objects to 'sort by'
    int dynamicMemorySize = 0; // Stores the total number of records in dynamic memory

    for (int i = 0; i < recordCount; i++) {
        Product record = productsFile.readRecord(i);
        // CHECK THAT THE PRODUCT IS ACTIVE
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
                    if (vec[i].getProductId() > vec[x].getProductId()) {
                        Product auxiliary = vec[i];
                        vec[i] = vec[x];
                        vec[x] = auxiliary;
                    }
                    break;
                }

                case 2:{ // BY TYPE
                    if (vec[i].getType() > vec[x].getType()) {
                        Product auxiliary = vec[i];
                        vec[i] = vec[x];
                        vec[x] = auxiliary;
                    }
                    break;
                }

                case 3:{ // BY BRAND
                    if (strcmp(vec[i].getBrand(), vec[x].getBrand()) > 0){ // If > 0, the first string is bigger than the second
                        Product auxiliary = vec[i];
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

int ProductsDataFile::queryProduct(int option, int productId, const char* name, int type, const char* brand){
    Product record;
    ProductsDataFile productsFile;
    int result = -1;


    int recordCount = productsFile.countRecords();
    if (recordCount < 0) {
        return -2; // Unable to generate the list
    } else if (recordCount == 0){
        return -3; // There are no products registered
    }

    for(int i = 0; i < recordCount; i++){
        record = productsFile.readRecord(i);

        // Iterates over the product file and shows the record
        switch(option){
            case 1:{ // BY ID
                if(record.getProductId() == productId){
                    if(record.getState()){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }else{
                        return -4;  // The product is deactivated
                    }
                }
                break;
            }

            case 2:{ // BY NAME
                if(strcmp(record.getName(), name) == 0){
                    if(record.getState()){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }
                }
                break;
            }

            case 3:{ // BY TYPE
                if(record.getType() == type){
                    if(record.getState()){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }
                }
                break;
            }

            case 4:{ // BY BRAND
                if(strcmp(record.getBrand(), brand) == 0){
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

