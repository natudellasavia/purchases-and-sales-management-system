#include <iostream>
#include <clocale>
#include "supplierMenu.h"
#include "clsPerson.h"
#include "clsSupplier.h"
#include "clsSupplierDataFile.h"
#include "generalFunctions.h"
using namespace std;

/* THESE ATTRIBUTES ARE DECLARED IN GENERAL FUNCTIONS
SUPPLIER: int supplierId; / char supplierName[50];
PERSON: char identifier[12]; / int personType; / char phoneNumber[30]; / char email[50]; */

int supplierMenu(){
    int option;
    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "------------------------------" << endl;
        cout << "       S U P P L I E R        " << endl;
        cout << "------------------------------" << endl;
        cout << " 1 - MODIFY" << endl;
        cout << " 2 - DEACTIVATE" << endl;
        cout << " 3 - LISTS" << endl;
        cout << " 4 - QUERIES" << endl << endl;
        cout << " 0 - BACK TO MAIN MENU" << endl;
        cout << "------------------------------" << endl;
        cout << " SELECT AN OPTION: ";
        cin >> option;

        system("cls");
        switch(option){
            case 1: {
                modifySupplier();
                break;
            }
            case 2:
                 deactivateSupplier();
                break;
            case 3:
                supplierLists();
                break;
            case 4:
                supplierQueries();
                break;
            case 0:
                return 0;
                break;
            default:
                cout << " ERROR: THE OPTION YOU SELECTED IS INCORRECT. PLEASE TRY AGAIN." << endl << endl;
                system("pause");
                break;
        }
    }
	return 0;
}


///     (1) M O D I F Y
int modifySupplier(){
    SuppliersDataFile suppliersFile;
    int idToModify;
    int position;

    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "-----     MODIFY A SUPPLIER     -----" << endl << endl;
        cout << " ENTER SUPPLIER ID (ENTER 0 TO GO BACK): ";
        cin >> idToModify;
        if(idToModify == 0){return 0;} // Type 0 to return

        position = suppliersFile.findPosition(idToModify);
        if (position == -1){
            cout << endl << " ERROR: THERE IS NO SUPPLIER WITH ID " << idToModify << ". PLEASE TRY AGAIN." << endl << endl;
            system("pause");
        }else if (position < -1){
            cout << " ERROR: COULD NOT OPEN THE SUPPLIER FILE. PLEASE TRY AGAIN LATER." << endl << endl;
        }else{
            correctOption = true;
        }
    }

    int option;
    correctOption = false;
    Supplier record;
    record = suppliersFile.readRecord(position);

    while(!correctOption){
        system("cls");
        cout << "-----     MODIFY A SUPPLIER     -----" << endl << endl;
        cout << " SUPPLIER ID " << idToModify << " . IDENTIFIER " << record.getIdentifier() << ". NAME '" << record.getName() << "'. PERSON TYPE " << record.getPersonType() << endl;
        cout << " PHONE NUMBER " << record.getPhoneNumber() << ". EMAIL " << record.getEmail() << endl << endl;
        cout << " 1 - PHONE NUMBER" << endl;
        cout << " 2 - EMAIL" << endl;
        cout << " 3 - REACTIVATE" << endl << endl;
        cout << " 0 - BACK TO SUPPLIER MENU" << endl;
        cout << "--------------------------" << endl;
        cout << " SELECT AN OPTION: ";
        cin >> option;
        system("cls");

        bool modified = false; // To determine whether any modifications were made

        switch(option){
            case 1:{
                cout << " -----     MODIFY SUPPLIER PHONE NUMBER     -----" << endl << endl;
                cout << " SUPPLIER ID " << idToModify << " .   IDENTIFIER " << record.getIdentifier() << ".   NAME '" << record.getName() << "'.   PHONE NUMBER " << record.getPhoneNumber() << "." << endl << endl;

                char newPhoneNumber[30];
                char existingPhoneNumber[30] = {};
                strcpy(existingPhoneNumber, record.getPhoneNumber()); // Get the record phone number

                cout << " ENTER THE NEW PHONE NUMBER (ENTER 0 TO GO BACK): ";
                newString(newPhoneNumber, sizeof(newPhoneNumber)-1);
                toUppercase(newPhoneNumber);
                if(strcmp(newPhoneNumber, "0") == 0){break;} // Type 0 to return

                if(strcmp(newPhoneNumber, existingPhoneNumber) != 0){
                    record.setPhoneNumber(newPhoneNumber); // Save the new phone number
                    modified = true; // To indicate that a modification was made
                }else{
                    cout << endl << " WARNING: THE ENTERED PHONE NUMBER IS THE SAME AS THE EXISTING ONE." << endl << endl;
                    system("pause");
                }
                break;
            }

            case 2:{
                cout << " -----     MODIFY SUPPLIER EMAIL     -----" << endl << endl;
                cout << " SUPPLIER ID " << idToModify << " .   IDENTIFIER " << record.getIdentifier() << ".   NAME '" << record.getName() << "'.   EMAIL " << record.getEmail() << endl << endl;

                char newEmail[50];
                char existingEmail[50] = {};
                strcpy(existingEmail, record.getEmail()); // Get the record email

                cout << " ENTER THE NEW EMAIL (ENTER 0 TO GO BACK): ";
                newString(newEmail, sizeof(newEmail)-1);
                toUppercase(newEmail);
                if(strcmp(newEmail, "0") == 0){break;} // Type 0 to return

                if(strcmp(newEmail, existingEmail) != 0){
                    record.setEmail(newEmail); // Save the new email
                    modified = true; // To indicate that a modification was made
                }else{
                    cout << endl << " WARNING: THE ENTERED EMAIL IS THE SAME AS THE EXISTING ONE." << endl << endl;
                    system("pause");
                }
                break;
            }

            case 3:{
                bool flag = false;
                while (!flag){
                    system("cls");
                    cout << " -----     REACTIVATE A SUPPLIER     -----" << endl << endl;
                    cout << " SUPPLIER ID " << idToModify << " . IDENTIFIER " << record.getIdentifier() << ". NAME '" << record.getName() << ". PERSON TYPE '" << record.getPersonType() << "'" << endl;
                    cout << " PHONE NUMBER " << record.getPhoneNumber() << ". EMAIL " << record.getEmail() << "." << endl << endl;

                    bool existingState = record.getState(); // Get the record state

                    if(existingState){
                        cout << " WARNING: THE SUPPLIER IS ALREADY ACTIVATED." << endl << endl;
                        system("pause");
                        break;
                    }else{
                        int option;
                        cout << " ARE YOU SURE YOU WANT TO REACTIVATE THE SUPPLIER? 1-YES / 2-NO : ";
                        cin >> option;

                        switch(option){
                            case 1: {
                                record.setState(true);
                                flag = true; // To go out of case 4 bool
                                modified = true; // To indicate that a modification was made
                                break;
                            }
                            case 2: {
                                cout << endl <<  " THE SUPPLIER HAS NOT BEEN ACTIVATED." << endl << endl;
                                flag = true;
                                system("pause");
                                break;
                            }
                            default: {
                                cout << endl << " ERROR: THE OPTION YOU SELECTED IS INCORRECT. PLEASE TRY AGAIN." << endl << endl;
                                system("pause");
                                break;
                            }
                        }
                    }
                }
                break;
            }

            case 0:{
                return 0;
                break;
            }

            default:{
                cout << endl << " ERROR: THE OPTION YOU SELECTED IS INCORRECT. PLEASE TRY AGAIN." << endl << endl;
                system("pause");
                break;
            }
        }

        if(modified){
            int modifySuccess = suppliersFile.modifyRecord(record, position);
            if(modifySuccess == 1){
                cout << endl << " THE SUPPLIER HAS BEEN MODIFIED SUCCESSFULLY." << endl << endl;
                system("pause");
            }else{
                cout << endl << " ERROR: FAILED TO MODIFY THE SUPPLIER IN THE FILE." << endl << endl;
                system("pause");
            }
        }
    }
    return 0;
}


///     (2) D E A C T I V A T E
void deactivateSupplier(){
    SuppliersDataFile suppliersFile;
    Supplier record;
    int idToDesactivate;
    int position;

    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "-----     DEACTIVATE A SUPPLIER     -----" << endl << endl;
        cout << " ENTER SUPPLIER ID (ENTER 0 TO GO BACK): ";
        cin >> idToDesactivate;
        if(idToDesactivate == 0){return;} // Type 0 to return

        position = suppliersFile.findPosition(idToDesactivate);
        if (position == -1){
            cout << endl << " ERROR: THERE IS NO SUPPLIER WITH ID " << idToDesactivate << ". PLEASE TRY AGAIN." << endl << endl;
            system("pause");
        }else if (position < -1){
            cout << endl << " ERROR: COULD NOT OPEN THE SUPPLIER FILE. PLEASE TRY AGAIN LATER." << endl << endl;
        }else{
            record = suppliersFile.readRecord(position);
            bool isActivated = record.getState();
            if(!isActivated){
                cout << endl << " WARNING: THE SUPPLIER ID " << idToDesactivate << ". IDENTIFIER " << record.getIdentifier();
                cout << ". NAME '" << record.getName() << "' IS ALREADY DEACTIVATED." << endl << endl;
                system("pause");
            }else{
                correctOption = true;
            }
        }
    }

    int option;
    correctOption = false;

    while(!correctOption){
        system("cls");
        cout << "-----     DEACTIVATE A SUPPLIER     -----" << endl << endl;
        cout << " ID " << idToDesactivate << ". IDENTIFIER " << record.getIdentifier() << ". NAME '" << record.getName() << "'." << endl << endl;

        cout << " ARE YOU SURE YOU WANT TO DEACTIVATE THE SUPPLIER? 1-YES / 2-NO : ";
        cin >> option;

        switch(option){
            case 1:{
                bool deactivated;
                 deactivated = suppliersFile.logicalDeletion(idToDesactivate); // Marked as inactive in the file
                 if(deactivated == true){
                     cout << endl << " SUPPLIER HAS BEEN DEACTIVATE SUCCESSFULLY." << endl << endl;
                 }else{
                     cout << endl << " ERROR: FAILED TO DEACTIVATE THE SUPPLIER." << endl << endl;
                 }
                 correctOption = true;
                 system("pause");
                 break;
            }
            case 2:{
                return;
                break;
            }
            default:{
                cout << endl << " ERROR: THE OPTION YOU SELECTED IS INCORRECT. PLEASE TRY AGAIN." << endl << endl;
                system("pause");
                break;
            }
        }
    }
}



///     (3) L I S T S
void supplierLists(){
    int option;
    int check = 0;
    bool correctOption = false;

    while(!correctOption){
        system("cls");
        cout << "-----     SUPPLIER LISTS     -----" << endl << endl;
        cout << " 1 - BY ID" << endl;
        cout << " 2 - BY IDENTIFIER" << endl;
        cout << " 3 - BY PERSON TYPE" << endl << endl;
        cout << " 0 - BACK TO SUPPLIER MENU" << endl;
        cout << "---------------------------------" << endl;
        cout << " SELECT AN OPTION: ";
        cin >> option;
        system("cls");
        SuppliersDataFile suppliersFile;

        switch(option){
            case 1:{
                cout << " -----     SUPPLIER LIST BY ID     -----" << endl << endl;
                check = suppliersFile.listSupplier(1);
                break;
            }

            case 2:{
                cout << " -----     SUPPLIER LIST BY IDENTIFIER     -----" << endl << endl;
                check = suppliersFile.listSupplier(2);
                break;
            }

            case 3:{
                cout << " -----     SUPPLIER LIST BY PERSON TYPE     -----" << endl << endl;
                check = suppliersFile.listSupplier(3);
                break;
            }

            case 0:{
                return;
                break;
            }
            default:{
                cout << endl << " ERROR: THE OPTION YOU SELECTED IS INCORRECT. PLEASE TRY AGAIN." << endl;
                break;
            }
        }

        if(check == -2){
            cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER."<< endl;
        }else if(check == -3){
            cout << " THERE ARE NO SUPPLIERS REGISTERED." << endl;
        }
        cout << endl;
        system("pause");
    }
}



///     (4) Q U E R I E S
void supplierQueries(){
    int option;
    int check;
    bool correctOption = false;

    while(!correctOption){
        system("cls");
        cout << "-----     SUPPLIER QUERIES     -----" << endl << endl;
        cout << " 1 - BY ID" << endl;
        cout << " 2 - BY IDENTIFIER" << endl;
        cout << " 3 - BY NAME" << endl;
        cout << " 4 - BY PERSON TYPE" << endl << endl;
        cout << " 0 - BACK TO SUPPLIER MENU" << endl;
        cout << "---------------------------------" << endl;
        cout << " SELECT AN OPTION: ";
        cin >> option;
        system("cls");
        SuppliersDataFile suppliersFile;

        switch(option){
            case 1:{
                cout << " -----     SUPPLIER QUERY BY ID     -----" << endl << endl;
                cout << " ENTER THE ID TO SEARCH: ";
                int id = readInt();
                cout << endl;

                if (id == -1){
                    cout << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl;
                    break;
                }else{
                    check = suppliersFile.querySupplier(1, id, "", "", 0);
                    switch(check){
                        case -4:{
                            cout << " THE SUPPLIER WHIT ID " << id << " IS DEACTIVATED." << endl;
                            break;
                        }

                        case -3:{
                            cout << " THERE ARE NO SUPPLIERS REGISTERED." << endl;
                            break;
                        }

                        case -2:{
                            cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER." << endl;
                            break;
                        }

                        case -1:{
                            cout << " SUPPLIER WITH THE SPECIFIED ID DOES NOT EXIST." << endl;
                            break;
                        }
                    }
                }

                break;
            }

            case 2:{
                cout << " -----     SUPPLIER QUERY BY IDENTIFIER     -----" << endl << endl;
                cout << " ENTER THE IDENTIFIER TO SEARCH: ";
                newString(identifier, sizeof(identifier)-1);
                toUppercase(identifier);
                cout << endl;

                check = suppliersFile.querySupplier(2, 0, identifier, "", 0);
                switch(check){
                    case -4:{
                        cout << " THE SUPPLIER WHIT IDENTIFIER " << identifier << " IS DEACTIVATED." << endl;
                        break;
                    }

                    case -3:{
                        cout << " THERE ARE NO SUPPLIERS REGISTERED." << endl;
                        break;
                    }

                    case -2:{
                        cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER." << endl;
                        break;
                    }

                    case -1:{
                        cout << " CUSTOMER WITH THE SPECIFIE IDENTIFIER DOES NOT EXIST." << endl;
                        break;
                    }
                }

                break;
            }

            case 3:{
                cout << " -----     SUPPLIER QUERY BY NAME     -----" << endl << endl;
                cout << " ENTER THE NAME TO SEARCH: ";
                newString(supplierName, sizeof(supplierName)-1);
                toUppercase(supplierName);
                cout << endl;

                check = suppliersFile.querySupplier(3, 0, "", supplierName, 0);
                switch(check){
                    case -3:{
                        cout << " THERE ARE NO SUPPLIERS REGISTERED." << endl;
                        break;
                    }

                    case -2:{
                        cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER." << endl;
                        break;
                    }

                    case -1:{
                        cout << " SUPPLIER WITH THE SPECIFIE NAME DOES NOT EXIST." << endl;
                        break;
                    }
                }

                break;
            }

            case 4:{
                cout << " -----     SUPPLIER QUERY BY PERSON TYPE     -----" << endl << endl;
                cout << " ENTER THE PERSON TYPE TO SEARCH: ";
                personType = readInt();
                cout << endl;

                if (personType == -1){
                    cout << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl;
                    break;
                }else{
                    if(personType == 1 || personType == 2){
                        check = suppliersFile.querySupplier(4, 0, "", "", personType);
                        switch(check){
                            case -3:{
                                cout << " THERE ARE NO SUPPLIERS REGISTERED." << endl;
                                break;
                            }

                            case -2:{
                                cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER." << endl;
                                break;
                            }

                            case -1:{
                                cout << " SUPPLIER WITH THE SPECIFIED PERSON TYPE DOES NOT EXIST." << endl;
                                break;
                            }
                        }
                    }else{
                        cout << " ERROR: THE PERSON TYPE YOU SELECTED IS INCORRECT." << endl;
                    }
                }

                break;
            }

            case 0:{
                return;
                break;
            }

            default:{
                cout << endl << " ERROR: THE OPTION YOU SELECTED IS INCORRECT. PLEASE TRY AGAIN." << endl;
                break;
            }
        }
        cout << endl;
        system("pause");
    }
}


///     O T H E R   F U N C T I O N S

///     ADD SUPPLIER
void addSupplier(){
    Supplier record;
    int option;

    bool keepDoing = true;
    while(keepDoing){
        system("cls");
        cout << "-----     ADD A SUPPLIER     -----" << endl << endl;

        cout << " IDENTIFIER: ";
        newString(identifier, sizeof(identifier)-1);
        toUppercase(identifier);
        record.setIdentifier(identifier);

        // VALIDATE THAT NO SUPPLIER EXISTS (WITH THE SAME ID)
        SuppliersDataFile suppliersFile;
        int idToCheck = suppliersFile.idSupplierExists(identifier);
        switch(idToCheck){
            case -5:{
                cout << "  ERROR: UNABLE TO OPEN THE FILE TO VERIFY IF THE SUPPLIER EXISTS. PLEASE TRY AGAIN LATER." << endl;
                break; // End of addSupplier() because it was not possible to check if the product exists
            }

            case -2:{
                // THE SUPPLIER DOES NOT EXIST - CONTINUE ADDING
                cout << " NAME: ";
                newString(supplierName, sizeof(supplierName)-1);
                toUppercase(supplierName);
                record.setName(supplierName);

                bool correctType = false;
                while(!correctType){
                    system("cls");
                    cout << "-----     ADD A SUPPLIER     -----" << endl << endl;
                    cout << " IDENTIFIER: " << identifier << endl;
                    cout << " NAME: " << supplierName << endl;
                    cout << " PERSON TYPE: ";
                    personType = readInt();

                    // VERIFY THAT THE PERSON TYPE IS 1 OR 2
                    if (personType == -1){
                        cout << endl << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl << endl;
                        system("pause");
                    }else{
                        if(personType == 1 || personType == 2){
                            correctType = true;
                            record.setPersonType(personType);

                            cout << " PHONE NUMBER: ";
                            newString(phoneNumber, sizeof(phoneNumber)-1);
                            toUppercase(phoneNumber);
                            record.setPhoneNumber(phoneNumber);

                            cout << " EMAIL: ";
                            newString(email, sizeof(email)-1);
                            toUppercase(email);
                            record.setEmail(email);

                            record.setState(true);

                            // ASK THE USER IF IS SURE ABOUT ADDING THE SUPPLIER
                            bool correctOption = false;
                            while(!correctOption){
                                system("cls");
                                cout << "-----     ADD A SUPPLIER     -----" << endl << endl;
                                displayWithoutId(record);
                                cout << endl << " ARE YOU SURE YOU WANT TO ADD THE SUPPLIER? 1-YES / 2-NO : ";
                                option = readInt();
                                switch(option){
                                    case -1:{
                                        cout << endl << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl << endl;
                                        system("pause");
                                        break;
                                    }

                                    case 1:{
                                        int added = suppliersFile.addRecord(record); // Store the result of the addRecord function to know what happened
                                        switch(added){
                                            case -5:
                                                cout << endl << "ERROR: THE FILE COULD NOT BE FOUND." << endl << endl;
                                                break;
                                            case 0:
                                                cout << endl << "ERROR: THE SUPPLIER COULD NOT BE ADDED." << endl << endl;
                                                break;
                                            case 1:
                                                cout << endl << " THE SUPPLIER WAS ADDED SUCCESSFULLY." << endl << endl;
                                                break;
                                        }
                                        correctOption = true;
                                        keepDoing = false;
                                        break;
                                    }

                                    case 2:{
                                        cout << endl;
                                        correctOption = true;
                                        keepDoing = false;
                                        break;
                                    }

                                    default:{
                                        cout <<  endl << " ERROR: THE OPTION YOU SELECTED IS INCORRECT. PLEASE TRY AGAIN." << endl << endl;
                                        system("pause");
                                        break;
                                    }
                                }
                            }
                            correctType = true;
                        }else{
                            cout << endl << " ERROR: THE PERSON TYPE YOU SELECTED IS INCORRECT. PLEASE TRY AGAIN." << endl << endl;
                            system("pause");
                        }
                    }
                }
                break;
            }

            default:{
                // THE SUPPLIER ALREADY EXISTS
                int position = suppliersFile.findPosition(idToCheck);
                Supplier recordToCompare = suppliersFile.readRecord(position);

                // VALIDATE THE STATE
                if(recordToCompare.getState()){
                    cout << endl << " ERROR: THE SUPPLIER ALREADY EXISTS." << endl << endl;
                    break; // End of addSupplier() because the product already exists and it is active
                }else{
                    bool correctOption = false;
                    while(!correctOption){
                        cout << endl;
                        displayWithId(recordToCompare);
                        cout << " THE SUPPLIER ALREADY EXISTS BUT IS DEACTIVATED. DO YOU WANT TO REACTIVATE IT? 1-YES / 2-NO : ";
                        cin >> option;
                        switch(option){
                            case 1: {
                                recordToCompare.setState(true);
                                int added = suppliersFile.modifyRecord(recordToCompare); // Store the result of the addRecord function to know what happened
                                switch(added){
                                    case -5:
                                        cout << endl << "ERROR: THE FILE COULD NOT BE FOUND." << endl << endl;
                                        break;
                                    case 0:
                                        cout << endl << "ERROR: THE SUPPLIER COULD NOT BE ADDED." << endl << endl;
                                        break;
                                    case 1:
                                        cout << endl << " THE SUPPLIER HAS BEEN REACTIVATED SUCCESSFULLY." << endl << endl;
                                        break;
                                }
                                correctOption = true; // To exit the while loop that keeps asking "Are you sure?"
                                break; // End of addSupplier() because the user said "yes" to reactivating the product
                            }
                            case 2: {
                                correctOption = true; // To exit the while loop that keeps asking "Are you sure?"
                                break; // End of addSupplier() because the user said "no" to reactivating the product
                            }
                            default:{
                                cout <<  endl << " ERROR: THE OPTION YOU SELECTED IS INCORRECT. PLEASE TRY AGAIN." << endl << endl;
                                system("pause");
                                break;
                            }
                        }
                    }
                }
                break;
            }
        }
        system("pause");
    }
}

///     DISPLAY WITH ID
void displayWithId(Supplier record){
    cout << " SUPPLIER ID: " << record.getSupplierId() << ".   IDENTIFIER: " << record.getIdentifier() << ".   NAME: '" << record.getName() << "'.   PERSON TYPE: " << record.getPersonType();
    cout << ".   PHONE NUMBER: " << record.getPhoneNumber() << ".   EMAIL: " << record.getEmail() << endl;
}

///     DISPLAY WITHOUT ID
void displayWithoutId(Supplier record){
    cout << " IDENTIFIER: " << record.getIdentifier() << endl;
    cout << " NAME: " << record.getName() << endl;
    cout << " PERSON TYPE: " << record.getPersonType() << endl;
    cout << " PHONE NUMBER: " << record.getPhoneNumber() << endl;
    cout << " EMAIL: " << record.getEmail() << endl;
}


