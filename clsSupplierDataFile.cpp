#include <iostream>
#include <clocale>
#include <cerrno>
#include "clsSupplier.h"
#include "clsSupplierDataFile.h"
#include "supplierMenu.h"
using namespace std;


SuppliersDataFile::SuppliersDataFile(const char *n){
    strcpy(fileName, n);
    recordSize = sizeof(Supplier);

    FILE *pDataFile = fopen(fileName, "rb");
    if (pDataFile == nullptr && errno == ENOENT) {
        // File does not exist, create empty
        pDataFile = fopen(fileName, "wb");
        if (pDataFile != nullptr) {
            fclose(pDataFile);
        }
    }
}


int SuppliersDataFile::addRecord(Supplier record){
    FILE *pDataFile = fopen(fileName, "ab");
    if(pDataFile == nullptr){return -5;} // Could not open the file

    // Auto-incrementing ID:
    if (fseek(pDataFile, 0, SEEK_END) != 0) { // Move to the end of the file to find the last ID
        fclose(pDataFile);
        return -3; // Could not move to the correct position
    }

    int pointerPosition = ftell(pDataFile);
    int supplierId = (pointerPosition/recordSize) + 1; // Get the ID of the last record and increment it by 1
    record.setSupplierId(supplierId); // Assign the auto-incremented ID to the record to be added

    int hasWrittenRecords = fwrite(&record, recordSize, 1, pDataFile);
    fclose(pDataFile);
    return hasWrittenRecords; // 1 if data was written, 0 if not
}


bool SuppliersDataFile::logicalDeletion(int supplierId){
    Supplier record;
    SuppliersDataFile suppliersFile;

    int position = suppliersFile.findPosition(supplierId);
    if(position < 0){
        return false; // Could not find the position
    }

    record = suppliersFile.readRecord(position); // Getting the record data
    if(record.getSupplierId() == 0){
        return false;
    }
    record.setState(false); // We perform a logical deletion by setting the status to false

    return suppliersFile.modifyRecord(record, position); // We overwrite the record
}


int SuppliersDataFile::modifyRecord(Supplier record, int position){
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


int SuppliersDataFile::modifyRecord(Supplier updatedSupplier){
    FILE *pDataFile = fopen(fileName, "rb+");
    if (pDataFile == nullptr) {return -5;} // Could not open the file

    Supplier record;
    int position = 0;
    while (fread(&record, recordSize, 1, pDataFile)) {
        if (record.getSupplierId() == updatedSupplier.getSupplierId()) {
            fseek(pDataFile, position * recordSize, SEEK_SET);
            fwrite(&updatedSupplier, recordSize, 1, pDataFile);
            fclose(pDataFile);
            return 1;
        }
        position++;
    }

    fclose(pDataFile);
    return -1; // The supplier was not found
}


int SuppliersDataFile::countRecords(){
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


int SuppliersDataFile::findPosition(int supplierId){
    FILE *pDataFile = fopen(fileName, "rb");
    if (pDataFile == nullptr){return -5;} // Could not open the file

    int recordCount = countRecords();
    Supplier record;

    for (int i = 0; i < recordCount; i++) {
        if (fseek(pDataFile, i * recordSize, SEEK_SET) != 0) { // Set the position to the desired record
            fclose(pDataFile);
            return -3; // Could not move to the correct position
        }

        if (fread(&record, recordSize, 1, pDataFile) != 1) {
            fclose(pDataFile);
            return -2; // Could not read the file
        }
        if (record.getSupplierId() == supplierId) {
            fclose(pDataFile);
            return i; // If found, return the position
        }
    }

    fclose(pDataFile);
    return -1; // The ID was not found in the file
}


Supplier SuppliersDataFile::readRecord(int position){
    Supplier record;
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


int SuppliersDataFile::idSupplierExists(const char* identifier){
    Supplier record;

    int recordCount = countRecords();
    if (recordCount == -5) {return -5;} // Could not open the file

    // Loop through the supplier file
    for (int i = 0; i < recordCount; i++){
        record = readRecord(i);

        if (strcmp(record.getIdentifier(), identifier) == 0){
            int id = record.getSupplierId();
            return id; // All fields match (the supplier already exists) and get the id
        }
    }

    return -2; // No match, can be added
}



/// ------------------------- L I S T S -------------------------

int SuppliersDataFile::listSupplier(int option){
    SuppliersDataFile suppliersFile;

    int recordCount = suppliersFile.countRecords();
    if (recordCount < 0) {
        return -2; // Unable to generate the list
    } else if (recordCount == 0){
        return -3; // There are no suppliers registered
    }

    Supplier* vec = new Supplier[recordCount]; // We create a dynamic array of objects to 'sort by'
    int dynamicMemorySize = 0; // Stores the total number of records in dynamic memory

    for (int i = 0; i < recordCount; i++) {
        Supplier record = suppliersFile.readRecord(i);
        // CHECK THAT THE SUPPLIER IS ACTIVE
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
                    if (vec[i].getSupplierId() > vec[x].getSupplierId()) {
                        Supplier auxiliary = vec[i];
                        vec[i] = vec[x];
                        vec[x] = auxiliary;
                    }
                    break;
                }

                case 2:{ // BY IDENTIFIER
                    if (strcmp(vec[i].getIdentifier(), vec[x].getIdentifier()) > 0) { // If > 0, the first string is bigger than the second
                        Supplier auxiliary = vec[i];
                        vec[i] = vec[x];
                        vec[x] = auxiliary;
                    }
                }

                case 3:{ // BY PERSON TYPE
                    if (vec[i].getPersonType() > vec[x].getPersonType()) {
                        Supplier auxiliary = vec[i];
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

int SuppliersDataFile::querySupplier(int option, int supplierId, const char* identifier, const char* name, int personType){
    SuppliersDataFile suppliersFile;
    Supplier record;
    int result = -1;

    int recordCount = suppliersFile.countRecords();
    if (recordCount < 0) {
        return -2; // Unable to generate the list
    } else if (recordCount == 0){
        return -3; // There are no suppliers registered
    }

    for(int i = 0; i < recordCount; i++){
        record = suppliersFile.readRecord(i);

        // Iterates over the suppliers file and shows the record
        switch(option){
            case 1:{ // BY ID
                if(record.getSupplierId() == supplierId){
                    if(record.getState()){
                        displayWithId(record);
                        result++; // Adds +1 to indicate that a record was found before returning
                    }else{
                        return -4; // The supplier is deactivated
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
                        return -4; // The supplier is deactivated
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

