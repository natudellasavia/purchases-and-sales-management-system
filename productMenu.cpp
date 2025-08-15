#include <iostream>
#include <clocale>
#include "productMenu.h"
#include "clsProduct.h"
#include "clsProductsDataFile.h"
#include "generalFunctions.h"
using namespace std;

/* THESE ATTRIBUTES ARE DECLARED IN GENERAL FUNCTIONS
PRODUCT: char productName[50]; / char brand[50]; / int productType; / float purchasePrice; / float sellingPrice; */

int productMenu(){
    int option;
    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "------------------------------" << endl;
        cout << "       P R O D U C T S        " << endl;
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
            case 1:
                modifyProduct();
                break;
            case 2:
                deactivateProduct();
                break;
            case 3:
                productLists();
                break;
            case 4:
                productQueries();
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
int modifyProduct(){
    ProductsDataFile productsFile;
    int idToModify;
    int position;

    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "-----     MODIFY A PRODUCT     -----" << endl << endl;
        cout << " ENTER PRODUCT ID (ENTER 0 TO GO BACK): ";
        cin >> idToModify;
        if(idToModify == 0){return 0;} // Type 0 to return

        position = productsFile.findPosition(idToModify);
        if (position == -1){
            cout << endl << " ERROR: THERE IS NO PRODUCT WITH ID: " << idToModify << ". PLEASE TRY AGAIN." << endl << endl;
            system("pause");
        }else if (position < -1){
            cout << " ERROR: COULD NOT OPEN THE PRODUCT FILE. PLEASE TRY AGAIN LATER." << endl << endl;
        }else{
            correctOption = true;
        }
    }

    int option;
    correctOption = false;
    Product record;
    record = productsFile.readRecord(position);

    while(!correctOption){
        system("cls");
        cout << "-----     MODIFY A PRODUCT     -----" << endl << endl;
        cout << " ID " << idToModify << ". NAME '" << record.getName() << ". TYPE " << record.getType() << ". BRAND '" << record.getBrand() << "'." << endl;
        cout << " PURCHASE PRICE $"<< record.getPurchasePrice() << ". SELLING PRICE $" << record.getSellingPrice() << ". QUANTITY " << record.getQuantity() << ". "<< endl << endl;
        cout << " 1 - NAME" << endl;
        cout << " 2 - BRAND" << endl;
        cout << " 3 - SELLING PRICE" << endl;
        cout << " 4 - REACTIVATE" << endl << endl;
        cout << " 0 - BACK TO PRODUCT MENU" << endl;
        cout << "------------------------------------" << endl;
        cout << " SELECT AN OPTION: ";
        cin >> option;
        system("cls");

        bool modified = false; // To determine whether any modifications were made

        switch(option){
            case 1:{
                cout << " -----     MODIFY PRODUCT NAME     -----" << endl << endl;
                cout << " ID " << idToModify << ". NAME '" << record.getName() << "'. TYPE " << record.getType() << ". BRAND '" << record.getBrand() << "'." << endl << endl;

                char newName[50];
                char existingName[50] = {};
                strcpy(existingName, record.getName()); // Get the record name

                cout << " ENTER THE NEW NAME (ENTER 0 TO GO BACK): ";
                newString(newName, sizeof(newName)-1);
                toUppercase(newName);
                if(strcmp(newName, "0") == 0){break;} // Type 0 to return

                if(strcmp(newName, existingName) != 0){
                    record.setName(newName); // Save the new name
                    modified = true; // To indicate that a modification was made
                }else{
                    cout << endl << " WARNING: THE ENTERED NAME IS THE SAME AS THE EXISTING ONE." << endl << endl;
                    system("pause");
                }
                break;
            }

            case 2:{
                cout << " -----     MODIFY PRODUCT BRAND     -----" << endl << endl;
                cout << " ID " << idToModify << ". NAME '" << record.getName() << ". TYPE " << record.getType() << ". BRAND '" << record.getBrand() << "'." << endl << endl;

                char newBrand[50];
                char existingBrand[50] = {};
                strcpy(existingBrand, record.getBrand()); // Get the record brand

                cout << " ENTER THE NEW BRAND (ENTER 0 TO GO BACK): ";
                newString(newBrand, sizeof(newBrand)-1);
                toUppercase(newBrand);
                if(strcmp(newBrand, "0") == 0){break;} // Type 0 to return

                if(strcmp(newBrand, existingBrand) != 0){
                    record.setBrand(newBrand); // Save the new brand
                    modified = true; // To indicate that a modification was made
                }else{
                    cout << endl << " WARNING: THE ENTERED BRAND IS THE SAME AS THE EXISTING ONE." << endl << endl;
                    system("pause");
                }
                break;
            }

            case 3:{
                cout << " -----     MODIFY PRODUCT SELLING PRICE     -----" << endl << endl;
                cout << " ID " << idToModify << ". NAME '" << record.getName() << ". TYPE " << record.getType() << ". BRAND '" << record.getBrand() << "'." << endl;
                cout << " PURCHASE PRICE $"<< record.getPurchasePrice() << ". SELLING PRICE $" << record.getSellingPrice() << endl << endl;

                float newSellingPrice;
                float existingSellingPrice = record.getSellingPrice(); // Get the record purchase price

                cout << " ENTER THE NEW SELLING PRICE (ENTER 0 TO GO BACK): ";
                cin >> newSellingPrice;
                if(newSellingPrice == 0){break;} // Type 0 to return

                // VALIDATE THAT THE PRICE IS GREATER THAN 0
                if(newSellingPrice > 0){
                    if(newSellingPrice != existingSellingPrice){
                        record.setSellingPrice(newSellingPrice); // Save the new selling price
                        modified = true; // To indicate that a modification was made
                    }else{
                        cout << endl << " WARNING: THE ENTERED SELLING PRICE IS THE SAME AS THE EXISTING ONE." << endl << endl;
                        system("pause");
                    }
                }else{
                    cout << endl << " WARNING: THE SELLING PRICE MUST BE GREATER THAN 0." << endl << endl;
                    system("pause");
                }

                break;
            }

            case 4:{
                bool flag = false;
                while (!flag){
                    system("cls");
                    cout << " -----     REACTIVATE A PRODUCT     -----" << endl << endl;
                    cout << " ID " << idToModify << ". NAME '" << record.getName() << ". TYPE " << record.getType() << ". BRAND '" << record.getBrand() << "'." << endl;

                    bool existingState = record.getState(); // Get the record state

                    if(existingState){
                        cout << endl << " WARNING: THE PRODUCT IS ALREADY ACTIVATED." << endl << endl;
                        system("pause");
                        break;
                    }else{
                        int option;
                        cout << endl << " ARE YOU SURE YOU WANT TO REACTIVATE THE PRODUCT? 1-YES / 2-NO : ";
                        cin >> option;

                        switch(option){
                            case 1: {
                                record.setState(true);
                                flag = true; // To go out of case 4 bool
                                modified = true; // To indicate that a modification was made
                                break;
                            }
                            case 2: {
                                cout << endl <<  " THE PRODUCT HAS NOT BEEN ACTIVATED." << endl << endl;
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
            int modifySuccess = productsFile.modifyRecord(record, position);
            if(modifySuccess == 1){
                cout << endl << " THE PRODUCT HAS BEEN MODIFIED SUCCESSFULLY." << endl << endl;
                system("pause");
            }else{
                cout << endl << " ERROR: FAILED TO MODIFY THE PRODUCT IN THE FILE." << endl << endl;
                system("pause");
            }
        }
    }
    return 0;
}


///     (2) D E A C T I V A T E
void deactivateProduct(){
    ProductsDataFile productsFile;
    Product record;
    int idToDesactivate;
    int position;

    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "-----     DEACTIVATE A PRODUCT     -----" << endl << endl;
        cout << " ENTER PRODUCT ID (ENTER 0 TO GO BACK): ";
        cin >> idToDesactivate;
        if(idToDesactivate == 0){return;} // Type 0 to return

        position = productsFile.findPosition(idToDesactivate);
        if (position == -1){
            cout << endl << " ERROR: THERE IS NO PRODUCT WITH ID: " << idToDesactivate << ". PLEASE TRY AGAIN." << endl << endl;
            system("pause");
        }else if (position < -1){
            cout << endl << " ERROR: COULD NOT OPEN THE PRODUCT FILE. PLEASE TRY AGAIN LATER." << endl << endl;
        }else{
            record = productsFile.readRecord(position);
            bool isActivated = record.getState();
            if(!isActivated){
                cout << endl << " WARNING: THE PRODUCT ID " << idToDesactivate << ". NAME '" << record.getName() << "'. BRAND '" << record.getBrand() << "' IS ALREADY DEACTIVATED." << endl << endl;
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
        cout << "-----     DEACTIVATE A PRODUCT     -----" << endl << endl;
        cout << " ID " << idToDesactivate << ". NAME '" << record.getName() << ". TYPE " << record.getType() << ". BRAND '" << record.getBrand() << "'." << endl << endl;

        cout << " ARE YOU SURE YOU WANT TO DEACTIVATE THE PRODUCT? 1-YES / 2-NO : ";
        cin >> option;

        switch(option){
            case 1:{
                bool deactivated;
                 deactivated = productsFile.logicalDeletion(idToDesactivate); // Marked as inactive in the file
                 if(deactivated == true){
                     cout << endl << " PRODUCT HAS BEEN DEACTIVATE SUCCESSFULLY." << endl << endl;
                 }else{
                     cout << endl << " ERROR: FAILED TO DEACTIVATE THE PRODUCT." << endl << endl;
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
void productLists(){
    int option;
    int check = 0;
    bool correctOption = false;

    while(!correctOption){
        system("cls");
        cout << "-----     PRODUCT LISTS     -----" << endl << endl;
        cout << " 1 - BY ID" << endl;
        cout << " 2 - BY TYPE" << endl;
        cout << " 3 - BY BRAND" << endl << endl;
        cout << " 0 - GO BACK" << endl;
        cout << "---------------------------------" << endl;
        cout << " SELECT AN OPTION: ";
        cin >> option;
        system("cls");
        ProductsDataFile productsFile;

        switch(option){
            case 1:{
                cout << " -----     PRODUCT LIST BY ID     -----" << endl << endl;
                check = productsFile.listProducts(1);
                break;
            }

            case 2:{
                cout << " -----     PRODUCT LIST BY TYPE     -----" << endl << endl;
                check = productsFile.listProducts(2);
                break;
            }

            case 3:{
                cout << " -----     PRODUCT LIST BY BRAND     -----" << endl << endl;
                check = productsFile.listProducts(3);
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
            cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER." << endl;
        }else if(check == -3){
            cout << " THERE ARE NO PRODUCTOS REGISTERED." << endl;
        }

        cout << endl;
        system("pause");
    }
}


///     (4) Q U E R I E S
void productQueries(){
    int option;
    int check;
    bool correctOption = false;

    while(!correctOption){
        system("cls");
        cout << "-----     PRODUCT QUERIES     -----" << endl << endl;
        cout << " 1 - BY ID" << endl;
        cout << " 2 - BY NAME" << endl;
        cout << " 3 - BY TYPE" << endl;
        cout << " 4 - BY BRAND" << endl << endl;
        cout << " 0 - BACK TO PRODUCT MENU" << endl;
        cout << "---------------------------------" << endl;
        cout << " SELECT AN OPTION: ";
        cin >> option;
        system("cls");
        ProductsDataFile productsFile;

        switch(option){
            case 1:{
                cout << " -----     PRODUCT QUERY BY ID     -----" << endl << endl;
                cout << " ENTER THE ID TO SEARCH: ";
                int id = readInt();
                cout << endl;

                if (id == -1){
                    cout << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl;
                    break;
                }else{
                    check = productsFile.queryProduct(1, id, "", 0, "");
                    switch(check){
                        case -4:{
                            cout << " THE PRODUCT WHIT ID " << id << " IS DEACTIVATED." << endl;
                            break;
                        }

                        case -3:{
                            cout << " THERE ARE NO PRODUCTS REGISTERED." << endl;
                            break;
                        }

                        case -2:{
                            cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER." << endl;
                            break;
                        }

                        case -1:{
                            cout << " PRODUCT WITH THE SPECIFIED ID DOES NOT EXIST." << endl;
                            break;
                        }
                    }
                }
                break;
            }

            case 2:{
                cout << " -----     PRODUCT QUERY BY NAME     -----" << endl << endl;
                cout << " ENTER THE NAME TO SEARCH: ";
                newString(productName, sizeof(productName)-1);
                toUppercase(productName);
                cout << endl;

                check = productsFile.queryProduct(2, 0, productName, 0, "");
                switch(check){
                    case -3:{
                        cout << " THERE ARE NO PRODUCTS REGISTERED." << endl;
                        break;
                    }

                    case -2:{
                        cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER." << endl;
                        break;
                    }

                    case -1:{
                        cout << " PRODUCT WITH THE NAME '"<< productName <<"' DOES NOT EXIST." << endl;
                        break;
                    }
                }
                break;
            }

            case 3:{
                bool correctType = false;
                while(!correctType){
                    system("cls");
                    cout << " -----     PRODUCT QUERY BY TYPE     -----" << endl << endl;
                    cout << " ENTER THE TYPE TO SEARCH: ";
                    productType = readInt();
                    cout << endl;

                    if (productType == -1){
                        cout << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl;
                        break;
                    }else if(productType == 1 || productType == 2) {
                        correctType = true;

                        check = productsFile.queryProduct(3, 0, "", productType, "");

                        switch(check){
                            case -3:{
                                cout << " THERE ARE NO PRODUCTS REGISTERED." << endl;
                                break;
                            }

                            case -2:{
                                cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER." << endl;
                                break;
                            }

                            case -1:{
                                cout << " PRODUCT WITH THE SPECIFIED TYPE DOES NOT EXIST." << endl;
                                break;
                            }
                        }
                    }else{
                        cout << " THE TYPE ENTERED IS NOT VALID" << endl << endl;
                        system("pause");
                    }
                }
                break;
            }

            case 4:{
                cout << " -----     PRODUCT QUERY BY BRAND     -----" << endl << endl;
                cout << " ENTER THE BRAND TO SEARCH: ";
                newString(brand, sizeof(brand)-1);
                toUppercase(brand);
                cout << endl;

                check = productsFile.queryProduct(4, 0, "", 0, brand);
                switch(check){
                    case -3:{
                        cout << " THERE ARE NO PRODUCTS REGISTERED." << endl;
                        break;
                    }

                    case -2:{
                        cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER." << endl;
                        break;
                    }

                    case -1:{
                        cout << " THERE IS NO BRAND CALLED '" << brand << "'." << endl;
                        break;
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


/// O T H E R   F U N C T I O N S

void addProduct(){
    Product record;
    int option;

    bool keepDoing = true;
    while(keepDoing){
        system("cls");
        cout << "-----     ADD A PRODUCT     -----" << endl << endl;
        cout << " PRODUCT NAME: ";
        newString(productName, sizeof(productName)-1);
        toUppercase(productName);
        record.setName(productName);

        cout << " PRODUCT TYPE: "; /// (+) VALIDAR EL TYPE CUANDO ESTÉ LA CLASE HECHA
        productType = readInt();
        if (productType == -1){
            cout << endl << endl <<  " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl;
            break;
        }else{
            record.setType(productType);
            keepDoing = false;
            cout << " BRAND: ";
            newString(brand, sizeof(brand)-1);
            toUppercase(brand);
            record.setBrand(brand);

            // VALIDATE THAT NO PRODUCT EXIST (WITH THE SAME NAME, TYPE AND BRAND)
            ProductsDataFile productsFile;
            int idToCheck = productsFile.idProductExists(productName, productType, brand);
            switch(idToCheck){
                case -5:{
                    cout << endl <<  " ERROR: UNABLE TO OPEN THE FILE TO VERIFY IF THE PRODUCT EXISTS. PLEASE TRY AGAIN LATER." << endl;
                    break;  // End of addProduct() because it was not possible to check if the product exists
                }

                case -2:{
                    // THE PRODUCT DOES NOT EXIST - CONTINUE ADDING
                    record.setPurchasePrice(0); // Purchase price is provided by the user only during the purchase entry
                    record.setSellingPrice(0); // Selling price is provided by the user only during the selling entry
                    record.setQuantity(0); // Quantity is provided by the user only during the purchase entry
                    record.setState(true);

                    // ASK THE USER IF IS SURE ABOUT ADDING THE PRODUCT
                    bool correctOption = false;
                    while(!correctOption){
                        system("cls");
                        cout << "-----     ADD A PRODUCT     -----" << endl << endl;
                        displayWithoutId(record);
                        cout << endl << " ARE YOU SURE YOU WANT TO ADD THE PRODUCT? 1-YES / 2-NO : ";
                        cin >> option;
                        switch(option){
                            case 1: {
                                int added = productsFile.addRecord(record); // Store the result of the addRecord function to know what happened
                                switch(added){
                                    case -5:
                                        cout << endl << "ERROR: THE FILE COULD NOT BE FOUND." << endl << endl;
                                        break;
                                    case 0:
                                        cout << endl << "ERROR: THE PRODUCT COULD NOT BE ADDED." << endl << endl;
                                        break;
                                    case 1:
                                        cout << endl << " THE PRODUCT WAS ADDED SUCCESSFULLY." << endl << endl;
                                        break;
                                }
                                correctOption = true; // To exit the while loop that keeps asking "Are you sure?"
                                break; // End of addProduct() because the user said "yes" to adding the product
                            }

                            case 2: {
                                cout << endl << " THE PRODUCT WAS NOT ADDED." << endl << endl;
                                correctOption = true;  // To exit the while loop that keeps asking "Are you sure?"
                                break; // End of addProduct() because the user said "no" to adding the product
                            }

                            default: {
                                cout << endl << " ERROR: THE OPTION YOU SELECTED IS INCORRECT. PLEASE TRY AGAIN." << endl << endl;
                                system("pause");
                                break;
                            }
                        }
                    }
                    break;
                }

                default:{
                    // THE PRODUCT ALREADY EXISTS
                    int position = productsFile.findPosition(idToCheck);
                    Product recordToCompare = productsFile.readRecord(position);

                    // VALIDATE THE STATE
                    if(recordToCompare.getState()){
                        cout << endl << " ERROR: THE PRODUCT ALREADY EXISTS." << endl << endl;
                        break; // End of addProduct() because the product already exists and it is active
                    }else{
                        bool correctOption = false;
                        while(!correctOption){
                            system("cls");
                            displayWithId(recordToCompare);
                            cout << " ERROR: THE PRODUCT ALREADY EXISTS BUT IS DEACTIVATED. DO YOU WANT TO REACTIVATE IT? 1-YES / 2-NO : ";
                            cin >> option;
                            switch(option){
                                case 1: {
                                    recordToCompare.setState(true);
                                    int added = productsFile.modifyRecord(recordToCompare); // Store the result of the addRecord function to know what happened
                                    switch(added){
                                        case -5:
                                            cout << endl << "ERROR: THE FILE COULD NOT BE FOUND." << endl << endl;
                                            break;
                                        case 0:
                                            cout << endl << "ERROR: THE PRODUCT COULD NOT BE ADDED." << endl << endl;
                                            break;
                                        case 1:
                                            cout << endl << " THE PRODUCT HAS BEEN REACTIVATED SUCCESSFULLY." << endl << endl;
                                            break;
                                    }
                                    correctOption = true; // To exit the while loop that keeps asking "Are you sure?"
                                    break; // End of addProduct() because the user said "yes" to reactivating the product
                                }
                                case 2: {
                                    correctOption = true; // To exit the while loop that keeps asking "Are you sure?"
                                    break; // End of addProduct() because the user said "no" to reactivating the product
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
            break;
        }
    }
}


int displayWithId(Product record){
    cout << " PRODUCT ID: " << record.getProductId() << ".   PRODUCT NAME: " << record.getName() << ".   PRODUCT TYPE: " << record.getType() << ".   BRAND: " << record.getBrand();
    cout << ".   PURCHASE PRICE $" << record.getPurchasePrice() << ".   SELLING PRICE $" << record.getSellingPrice() << ".   QUANTITY: " << record.getQuantity() << "." << endl;
}


int displayWithoutId(Product record){
    cout << " PRODUCT NAME: " << record.getName() << endl;
    cout << " PRODUCT TYPE: " << record.getType() << endl;
    cout << " BRAND: " << record.getBrand() << endl;
    cout << " PURCHASE PRICE: " << record.getPurchasePrice() << endl;
    cout << " SELLING PRICE: " << record.getSellingPrice() << endl;
    cout << " QUANTITY: " << record.getQuantity() << endl;
}
