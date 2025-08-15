#include <iostream>
#include <clocale>
#include "saleMenu.h"
#include "clsSale.h"
#include "clsSalesDataFile.h"
#include "clsProductsDataFile.h"
#include "productMenu.h"
#include "clsCustomersDataFile.h"
#include "customerMenu.h"
#include "generalFunctions.h"
using namespace std;

/* THESE ATTRIBUTES ARE DECLARED IN GENERAL FUNCTIONS
PRODUCT: int productId;
CUSTOMER: int customerId;
SALE: float price; / int quantity; */

int saleMenu(){
    int option;
    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "------------------------" << endl;
        cout << "       S A L E S       " << endl;
        cout << "------------------------" << endl;
        cout << " 1 - ADD" << endl;
        cout << " 2 - MODIFY" << endl;
        cout << " 3 - DEACTIVATE" << endl;
        cout << " 4 - LISTS" << endl;
        cout << " 5 - QUERIES" << endl << endl;
        cout << " 0 - BACK TO MAIN MENU" << endl;
        cout << "------------------------" << endl;
        cout << " SELECT AN OPTION: ";
        cin >> option;

        system("cls");
        switch(option){
            case 1:
                addSale();
                break;
            case 2:
                modifySale();
                break;
            case 3:
                deactivateSale();
                break;
            case 4:
                saleLists();
                break;
            case 5:
                saleQueries();
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



///     (1) A D D   S A L E
void addSale(){
    Sale record;
    SalesDataFile salesFile;
    int option;

    bool keepDoing = true;
    while(keepDoing){
        system("cls");
        cout << "-----     ADD A SALE     -----" << endl << endl;
        cout << " YOU WILL NEED THE PRODUCT ID AND THE CUSTOMER ID" << endl << endl;
        cout << " 1 - ADD SALE" << endl;
        cout << " 2 - SEE PRODUCT LIST" << endl;
        cout << " 3 - SEE CUSTOMER LIST" << endl;
        cout << " 4 - ADD CUSTOMER" << endl << endl;
        cout << " 0 - BACK TO SALE MENU" << endl;
        cout << "----------------------------------" << endl;
        cout << " SELECT AN OPTION: ";
        option = readInt();

        if (option == -1){
            cout << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl << endl;
            break;
        }else{
            switch(option){
                case 1:{
                    // ADD SALE

                    productId = addSaleProductId();
                    if(productId == -2){
                        break;
                    }else{
                        record.setProductId(productId);
                    }

                    customerId = addSaleCustomerId();
                    if(customerId == -2){
                        break;
                    }else{
                        record.setCustomerId(customerId);
                    }

                    addSaleQuantity();
                    record.setQuantity(quantity);

                    addSalePrice();
                    record.setUnitPrice(unitPrice);

                    totalPrice = unitPrice * quantity;
                    record.setTotalPrice(totalPrice);

                    Date date;
                    date.Add();
                    record.setDate(date);

                    record.setState(true);

                    // ASK THE USER IF IS SURE ABOUT ADDING THE SALE
                    bool correctOption = false;
                    while(!correctOption){
                        system("cls");
                        cout << "-----     ADD A SALE     -----" << endl << endl;
                        displayWithoutId(record);
                        cout << endl << " ARE YOU SURE YOU WANT TO ADD THE SALE? 1-YES / 2-NO : ";
                        option = readInt();

                        if (option == -1){
                            cout << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl << endl;
                            break;
                        }else{
                            switch(option){
                                case 1: {
                                    int added = salesFile.addRecord(record); // Store the result of the addRecord function to know what happened
                                    switch(added){
                                        case -5:
                                            cout << endl << "ERROR: THE FILE COULD NOT BE FOUND." << endl << endl;
                                            break;
                                        case 0:
                                            cout << endl << "ERROR: THE SALE COULD NOT BE ADDED." << endl << endl;
                                            break;
                                        case 1:
                                            cout << endl << " THE SALE WAS ADDED SUCCESSFULLY." << endl << endl;

                                            // SET THE SALE PRICE AND QUANTITY OF THE PRODUCT
                                            ProductsDataFile productsFile;
                                            int productPosition = productsFile.findPosition(productId);
                                            Product recordProduct = productsFile.readRecord(productPosition);

                                            recordProduct.setSellingPrice(unitPrice);

                                            int actualQuantity = recordProduct.getQuantity(); // Get the current quantity of the product
                                            actualQuantity -= quantity; // Decrease the entered quantity to the current one.
                                            recordProduct.setQuantity(actualQuantity);

                                            productsFile.modifyRecord(recordProduct);

                                            break;
                                    }
                                    correctOption = true; // To exit the while loop that keeps asking "Are you sure?"
                                    break; // End of addSale() because the user said "yes" to adding the product
                                }

                                case 2: {
                                    cout << endl << " THE PURCHASE WAS NOT ADDED." << endl << endl;
                                    correctOption = true;  // To exit the while loop that keeps asking "Are you sure?"
                                    break; // End of addSale() because the user said "no" to adding the product
                                }

                                default: {
                                    cout << endl << " ERROR: THE OPTION YOU SELECTED IS INCORRECT. PLEASE TRY AGAIN." << endl << endl;
                                    break;
                                }
                            }
                            system("pause");
                        }
                    }
                    break;
                }

                case 2:{
                    productLists();
                    break;
                }

                case 3:{
                    customerLists();
                    break;
                }

                case 4:{
                    addCustomer();
                    break;
                }

                case 0:{
                    return;
                    break;
                }

                default:{
                    cout << " ERROR: THE OPTION YOU SELECTED IS INCORRECT. PLEASE TRY AGAIN." << endl << endl;
                    system("pause");
                    break;
                }
            }
        }
    }
}

/// ADD PRODUCT ID
int addSaleProductId(){
    int id;
    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "-----     ADD A SALE     -----" << endl << endl;
        cout << " PRODUCT ID: ";
        id = readInt();
        if (id == -1){
            cout << endl << endl << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl;
            system("pause");
        }else{
            // VALIDATE THAT THE PRODUCT EXIST
            ProductsDataFile productsFile;
            int productExists = productsFile.findPosition(id);

            if (productExists == -1){
                cout << endl  << " ERROR: THERE IS NO PRODUCT WITH ID " << id << "." << endl << endl;
                correctOption = true;
                id = -2;
                system("pause");
            }else if(productExists == -2 || productExists == -3 || productExists == -5){
                cout << endl  << " ERROR: UNABLE TO OPEN THE FILE TO VERIFY IF THE PRODUCT EXISTS. PLEASE TRY AGAIN LATER." << endl << endl;
                correctOption = true;
                id = -2;
                system("pause");
            }else{
                correctOption = true;
            }
        }
    }

    return id;
}

/// ADD CUSTOMER ID
int addSaleCustomerId(){
    int id;
    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "-----     ADD A SALE     -----" << endl << endl;
        cout << " PRODUCT ID: " << productId << endl;
        cout << " CUSTOMER ID: ";
        id = readInt();
        if (id == -1){
            cout << endl << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl;
            system("pause");
        }else{
            // VALIDATE THAT THE CUSTOMER EXIST
            CustomersDataFile customersFile;
            int customerExists = customersFile.findPosition(id);

            if (customerExists == -1){
                cout << endl << " ERROR: THERE IS NO CUSTOMER WITH ID " << id << ". PLEASE TRY AGAIN." << endl << endl;
                system("pause");
            }else if(customerExists == -2 || customerExists == -3 || customerExists == -5){
                cout << endl << " ERROR: UNABLE TO OPEN THE FILE TO VERIFY IF THE CUSTOMER EXISTS. PLEASE TRY AGAIN LATER." << endl << endl;
                correctOption = true;
                id = -2;
                system("pause");
            }else{
                correctOption = true;
            }
        }
    }
    return id;
}

/// ADD QUANTITY
void addSaleQuantity(){
    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "-----     ADD A SALE     -----" << endl << endl;
        cout << " PRODUCT ID: " << productId << endl;
        cout << " CUSTOMER ID: " << customerId << endl;
        cout << " QUANTITY: ";
        cin >> quantity;

        // VALIDATE THAT THE QUANTITY IS > 0
        if(quantity > 0){
            // VALIDATE THAT THE SALE QUANTITY IS > THAN THE ACTUAL QUANTITY
            ProductsDataFile productsFile;
            int productPosition = productsFile.findPosition(productId);
            Product recordProduct = productsFile.readRecord(productPosition);

            int actualQuantity = recordProduct.getQuantity(); // Get the current quantity of the product

            if(quantity <= actualQuantity){
                correctOption = true;
                return;
            }else{
                cout << endl << " WARNING: THE QUANTITY MUST BE EQUAL TO OR LESS THAN THE STOCK." << endl << endl;
            }
        }else{
            cout << endl << " WARNING: THE QUANTITY MUST BE GREATER THAN 0" << endl << endl;
        }
        system("pause");
    }
}

/// ADD PRICE
void addSalePrice(){
    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "-----     ADD A SALE     -----" << endl << endl;
        cout << " PRODUCT ID: " << productId << endl;
        cout << " CUSTOMER ID: " << customerId << endl;
        cout << " QUANTITY: " << quantity << endl;
        cout << " UNIT PRICE: ";
        cin >> unitPrice;

        // VALIDATE THAT THE PRICE IS > 0
        if(unitPrice > 0){
            correctOption = true;
            return;
        }else{
            cout << endl << " WARNING: THE PRICE MUST BE GREATER THAN 0" << endl;
            system("pause");
        }
    }
}


///     (2) M O D I F Y
int modifySale(){
    SalesDataFile salesFile;
    int idToModify;
    int position;

    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "-----     MODIFY A SALE     -----" << endl << endl;
        cout << " ENTER SALE ID (ENTER 0 TO GO BACK): ";
        cin >> idToModify;
        if(idToModify == 0){return 0;} // Type 0 to return

        position = salesFile.findPosition(idToModify);
        if (position == -1){
            cout << endl << " ERROR: THERE IS NO SALE WITH ID: " << idToModify << ". PLEASE TRY AGAIN." << endl << endl;
            system("pause");
        }else if (position < -1){
            cout << " ERROR: COULD NOT OPEN THE SALE FILE. PLEASE TRY AGAIN LATER." << endl << endl;
            return 0;
        }else{
            correctOption = true;
        }
    }

    int option;
    correctOption = false;

    // GET THE RECORD OF THE SALE
    Sale record;
    record = salesFile.readRecord(position);

    // GET THE RECORD OF THE PRODUCT FROM THE PURCHASE
    ProductsDataFile productsFile;
    productId = record.getProductId();
    int productPosition = productsFile.findPosition(productId);
    Product recordProduct = productsFile.readRecord(productPosition);

    // GET THE RECORD OF THE CUSTOMER FROM THE PURCHASE
    CustomersDataFile customersFile;
    customerId = record.getCustomerId();
    int customerPosition = customersFile.findPosition(customerId);
    Customer recordCustomer = customersFile.readRecord(customerPosition);

    while(!correctOption){
        system("cls");
        cout << "-----     MODIFY A SALE     -----" << endl << endl;
        cout << " SALE ID " << idToModify << "   QUANTITY: " << record.getQuantity() << "   UNIT PRICE $" << record.getUnitPrice() << "   TOTAL PRICE $" << record.getTotalPrice()  << "   DATE: ";
        Date date = record.getDate();
        date.Display();
        cout << endl;
        cout << " PRODUCT ID " << recordProduct.getProductId() << ".   PRODUCT NAME '" << recordProduct.getName() << "'.   BRAND '" << recordProduct.getBrand() << "'." << endl;
        cout << " CUSTOMER ID " << recordCustomer.getCustomerId() << ".   CUSTOMER NAME '" << recordCustomer.getName() << "'." << endl << endl;

        cout << " 1 - UNIT PRICE" << endl;
        cout << " 2 - QUANTITY" << endl << endl;
        cout << " 0 - BACK TO SALE MENU" << endl;
        cout << "-------------------------------------" << endl;
        cout << " SELECT AN OPTION: ";
        cin >> option;
        system("cls");

        bool modified = false; // To determine whether any modifications were made

        switch(option){
            case 1:{
                cout << " -----     MODIFY SALE UNIT PRICE     -----" << endl << endl;
                cout << " SALE ID " << idToModify << ".   UNIT PRICE $" << record.getUnitPrice() << endl << endl;

                float newUnitPrice;
                float existingUnitPrice = record.getUnitPrice(); // Get the record unit price

                cout << " ENTER THE NEW UNIT PRICE (ENTER 0 TO GO BACK): ";
                cin >> newUnitPrice;

                if(newUnitPrice == 0){break;} // Type 0 to return

                if(newUnitPrice > 0){
                    if(newUnitPrice != existingUnitPrice){
                        // SET THE NEW UNIT PRICE AND TOTAL PRICE OF THE SALE
                        record.setUnitPrice(newUnitPrice); // Save the new unit price
                        quantity = record.getQuantity();
                        record.setTotalPrice(quantity*newUnitPrice);
                        modified = true; // To indicate that a modification was made

                        // SET THE SALE PRICE OF THE PRODUCT
                        recordProduct.setSellingPrice(newUnitPrice); // Save the selling price of the product
                        productsFile.modifyRecord(recordProduct);
                        break;
                    }else{
                        cout << endl << " WARNING: THE ENTERED SELLING PRICE IS THE SAME AS THE EXISTING ONE." << endl << endl;
                        system("pause");
                    }
                }else{
                    cout << endl << " WARNING: THE UNIT PRICE MUST BE GREATER THAN 0." << endl << endl;
                    system("pause");
                }

                break;
            }

            case 2:{
                cout << " -----     MODIFY SALE QUANTITY     -----" << endl << endl;
                cout << " SALE ID " << idToModify << ".   QUANTITY " << record.getQuantity() << endl << endl;

                float newQuantity;
                float existingQuantity = record.getQuantity(); // Get the record quantity

                cout << " ENTER THE NEW QUANTITY (ENTER 0 TO GO BACK): ";
                newQuantity = readInt();

                if(newQuantity == -1){
                    cout << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl << endl;
                    break;
                }else if(newQuantity == 0){
                    break; // Type 0 to return
                }else if(newQuantity > 0){
                    if(newQuantity != existingQuantity){
                        // SET THE NEW QUANTITY AND TOTAL PRICE OF THE SALE
                        record.setQuantity(newQuantity); // Save the new quantity
                        unitPrice = record.getUnitPrice();
                        record.setTotalPrice(unitPrice*newQuantity);
                        modified = true; // To indicate that a modification was made

                        // SET THE QUANTITY OF THE PRODUCT
                        int productQuantity = recordProduct.getQuantity();
                        productQuantity += existingQuantity; // Add the old quantity
                        productQuantity -= newQuantity; // Subtract the new quantity
                        recordProduct.setQuantity(productQuantity);
                        productsFile.modifyRecord(recordProduct);
                        break;
                    }else{
                        cout << endl << " WARNING: THE ENTERED QUANTITY IS THE SAME AS THE EXISTING ONE." << endl << endl;
                        system("pause");
                    }
                }else{
                    cout << endl << " WARNING: THE QUANTITY MUST BE GREATER THAN 0." << endl << endl;
                    system("pause");
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
            int modifySuccess = salesFile.modifyRecord(record, position);
            if(modifySuccess == 1){
                cout << endl << " THE SALE HAS BEEN MODIFIED SUCCESSFULLY." << endl << endl;
                system("pause");
            }else{
                cout << endl << " ERROR: FAILED TO MODIFY THE SALE IN THE FILE." << endl << endl;
                system("pause");
            }
        }
    }
    return 0;
}


///     (3) D E A C T I V A T E
void deactivateSale(){
    SalesDataFile salesFile;
    Sale record;
    int idToDesactivate;
    int position;

    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "-----     DEACTIVATE A SALE     -----" << endl << endl;
        cout << " ENTER SALE ID (ENTER 0 TO GO BACK): ";
        cin >> idToDesactivate;
        if(idToDesactivate == 0){return;} // Type 0 to return

        position = salesFile.findPosition(idToDesactivate);
        if (position == -1){
            cout << endl << " ERROR: THERE IS NO SALE WITH ID: " << idToDesactivate << ". PLEASE TRY AGAIN." << endl << endl;
            system("pause");
        }else if (position < -1){
            cout << endl << " ERROR: COULD NOT OPEN THE SALE FILE. PLEASE TRY AGAIN LATER." << endl << endl;
        }else{
            record = salesFile.readRecord(position);
            bool isActivated = record.getState();
            if(!isActivated){
                cout << endl << " WARNING: THE SALE ID " << idToDesactivate << "' IS ALREADY DEACTIVATED." << endl << endl;
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
        cout << "-----     DEACTIVATE A SALE     -----" << endl << endl;
        cout << " ID " << idToDesactivate
             << ".   PRODUCT ID " << record.getProductId()
             << ".   CUSTOMER ID " << record.getCustomerId() << ". " << endl;

        cout << " QUANTITY " << record.getQuantity()
             << "   UNIT PRICE $" << record.getUnitPrice()
             << "   TOTAL PRICE $" << record.getTotalPrice() << endl << endl;

        cout << " ARE YOU SURE YOU WANT TO DEACTIVATE THE SALE? 1-YES / 2-NO : ";
        cin >> option;

        switch(option){
            case 1:{
                bool deactivated;
                 deactivated = salesFile.logicalDeletion(idToDesactivate); // Marked as inactive in the file
                 if(deactivated == true){

                    // ADD THE QUANTITY FROM THE PRODUCT
                    productId = record.getProductId();
                    ProductsDataFile productsFile;
                    int productPosition = productsFile.findPosition(productId);
                    Product recordProduct = productsFile.readRecord(productPosition);

                    int productQuantity = recordProduct.getQuantity(); // Get the product quantity
                    productQuantity += record.getQuantity(); // Add the "quantity" of the sale
                    recordProduct.setQuantity(productQuantity);
                    productsFile.modifyRecord(recordProduct);


                    // MODIFY THE UNIT PRICE IF NECESSARY
                    float lastValidPrice = 0;
                    int maxPrevId = -1;

                    int recordCount = salesFile.countRecords();

                    for (int i = 0; i < recordCount; i++) {
                        Sale prevRecord = salesFile.readRecord(i);

                        // It must be the same product, be active, and have an ID smaller than the current one
                        if (prevRecord.getProductId() == productId &&
                            prevRecord.getState() &&
                            prevRecord.getSaleId() < record.getSaleId()) {

                            // We are looking for the highest ID from the valid ones before
                            if (prevRecord.getSaleId() > maxPrevId) {
                                maxPrevId = prevRecord.getSaleId();
                                lastValidPrice = prevRecord.getUnitPrice();
                            }
                        }
                    }

                    // The product price is updated
                    recordProduct.setPurchasePrice(lastValidPrice);
                    productsFile.modifyRecord(recordProduct);

                    cout << endl << " SALE HAS BEEN DEACTIVATE SUCCESSFULLY." << endl << endl;
                 }else{
                     cout << endl << " ERROR: FAILED TO DEACTIVATE THE SALE." << endl << endl;
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


///     (4) L I S T S
void saleLists(){
    int option;
    int check = 0;
    bool correctOption = false;

    while(!correctOption){
        system("cls");
        cout << "-----     S A L E   L I S T S     -----" << endl << endl;
        cout << " 1 - BY SALE ID" << endl;
        cout << " 2 - BY PRODUCT ID" << endl;
        cout << " 3 - BY CUSTOMER ID" << endl << endl;
        cout << " 0 - BACK TO PRODUCT MENU" << endl;
        cout << "---------------------------------------" << endl;
        cout << " SELECT AN OPTION: ";
        cin >> option;
        system("cls");
        SalesDataFile salesFile;

        switch(option){
            case 1:{
                cout << " -----     SALE LIST BY PURCHASE ID     -----" << endl << endl;
                check = salesFile.listSale(1);
                break;
            }

            case 2:{
                cout << " -----     SALE LIST BY PRODUCT ID     -----" << endl << endl;
                check = salesFile.listSale(2);
                break;
            }

            case 3:{
                cout << " -----     SALE LIST BY CUSTOMER ID     -----" << endl << endl;
                check = salesFile.listSale(3);
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
            cout << " THERE ARE NO SALES REGISTERED." << endl << endl;
        }

        cout << endl;
        system("pause");
    }
}


///     (5) Q U E R I E S
void saleQueries(){
    int option;
    int check;
    bool correctOption = false;

    while(!correctOption){
        system("cls");
        cout << "-----     S A L E   Q U E R I E S     -----" << endl << endl;
        cout << " 1 - BY SALE ID" << endl;
        cout << " 2 - BY PRODUCT ID" << endl;
        cout << " 3 - BY CUSTOMER ID" << endl;
        cout << " 4 - BY DATE RANGE" << endl;
        cout << " 5 - BY PRICE RANGE" << endl << endl;
        cout << " 0 - BACK TO SALE MENU" << endl;
        cout << "-------------------------------------------" << endl;
        cout << " SELECT AN OPTION: ";
        cin >> option;
        system("cls");
        SalesDataFile salesFile;
        int id;

        switch(option){
            case 1:{
                cout << " -----     SALE QUERY BY SALE ID     -----" << endl << endl;
                cout << " ENTER THE SALE ID TO SEARCH: ";
                id = readInt();
                cout << endl;

                if (id == -1){
                    cout << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl;
                    break;
                }else{
                    check = salesFile.querySale(1, id, 0, 0);
                    switch(check){
                        case -4:{
                            cout << " THE SALE WHIT ID " << id << " WAS DELETED." << endl;
                            break;
                        }

                        case -3:{
                            cout << " THERE ARE NO SALES REGISTERED." << endl;
                            break;
                        }

                        case -2:{
                            cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER." << endl;
                            break;
                        }

                        case -1:{
                            cout << " NO SALE FOUND WITH THE SPECIFIED SALE ID." << endl;
                            break;
                        }
                    }
                }
                break;
            }

            case 2:{
                cout << " -----     SALE QUERY BY PRODUCT ID     -----" << endl << endl;
                cout << " ENTER THE PRODUCT ID TO SEARCH: ";
                id = readInt();
                cout << endl;

                if (id == -1){
                    cout << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl;
                    break;
                }else{
                    check = salesFile.querySale(2, 0, id, 0);
                    switch(check){
                        case -3:{
                            cout << " THERE ARE NO SALES REGISTERED." << endl;
                            break;
                        }

                        case -2:{
                            cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER." << endl;
                            break;
                        }

                        case -1:{
                            cout << " NO SALE FOUND WITH THE SPECIFIED PRODUCT ID." << endl;
                            break;
                        }
                    }
                }
                break;
            }

            case 3:{
                cout << " -----     SALE QUERY BY CUSTOMER ID     -----" << endl << endl;
                cout << " ENTER THE CUSTOMER ID TO SEARCH: ";
                id = readInt();
                cout << endl;

                if (id == -1){
                    cout << " ERROR: INVALID INPUT. PLEASE ENTER A VALID NUMBER." << endl;
                    break;
                }else{
                    check = salesFile.querySale(3, 0, 0, id);
                    switch(check){
                        case -3:{
                            cout << " THERE ARE NO SALES REGISTERED." << endl;
                            break;
                        }

                        case -2:{
                            cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER." << endl;
                            break;
                        }

                        case -1:{
                            cout << " NO SALE FOUND WITH THE SPECIFIED CUSTOMER ID." << endl;
                            break;
                        }
                    }
                }
                break;
            }

            case 4:{
                bool correctDate = false;
                while(!correctDate){
                    system("cls");
                    cout << " -----     SALE QUERY BY DATE RANGED     -----" << endl << endl;
                    Date fromDate, toDate;
                    cout << " FROM DATE:" << endl;

                    if(fromDate.Add() == true){
                        cout << endl << " TO DATE:" << endl;
                        if(toDate.Add() == true){
                            // VALIDATE THAT 'TO DATE' IS EQUAL OR LATER THAN 'FROM DATE'
                            if(toDate.getYear() >= fromDate.getYear() && toDate.getMonth() >= fromDate.getMonth() && toDate.getDay() >= fromDate.getDay()){
                                correctDate = true; // If it is equal or grater
                            }else{
                                cout << endl << " ERROR: 'TO DATE' MUST BE THE SAME AS OR LATER THAN 'FROM DATE'" << endl << endl;
                                system("pause");
                            }

                            system("cls");
                            cout << " -----     SALE QUERY BY DATE RANGED     -----" << endl << endl;
                            cout << " FROM DATE: ";
                            fromDate.Display();
                            cout << " TO DATE: ";
                            toDate.Display();
                            cout << endl << endl;

                            check = salesFile.querySaleDateRange(fromDate, toDate);
                            switch(check){
                                case -3:{
                                    cout << " THERE ARE NO PURCHASES REGISTERED." << endl;
                                    break;
                                }

                                case -2:{
                                    cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER."<< endl;
                                    break;
                                }

                                case -1:{
                                    cout << " NO SALE FOUND IN THE SPECIFIED DATE RANGE." << endl;
                                    break;
                                }
                            }
                        }
                    }
                }
                break;
            }

            case 5:{
                bool correctType = false;
                while(!correctType){
                    system("cls");
                    cout << " -----     SALE QUERY BY PRICE RANGE     -----" << endl << endl;
                    float fromPrice, toPrice;
                    cout << " PRICE FROM: ";
                    cin >> fromPrice;
                    if(fromPrice >= 0){
                        cout << " PRICE TO: ";
                        cin >> toPrice;
                        cout << endl;
                        if(toPrice >= fromPrice){
                            correctType = true;
                            check = salesFile.querySaleTotalPriceRange(fromPrice, toPrice);
                            switch(check){
                                case -3:{
                                    cout << " THERE ARE NO SALES REGISTERED." << endl;
                                    break;
                                }

                                case -2:{
                                    cout << " SORRY, UNABLE TO GENERATE THE LIST. PLEASE TRY AGAIN LATER." << endl;
                                    break;
                                }

                                case -1:{
                                    cout << " NO SALE FOUND IN THE SPECIFIED PRICE RANGE." << endl;
                                    break;
                                }
                            }
                        }else{
                            cout << " WARNING: 'PRICE TO' MUST BE LESS THAN OR EQUAL TO 'PRICE FROM'." << endl << endl;
                            system("pause");
                        }
                    }else{
                        cout << endl << " WARNING: THE 'PRICE FROM' MUST BE EQUAL OR GREATER THAN 0." << endl << endl;
                        system("pause");
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


///     (6) R E P O R T S
void saleReports(){
    cout << " sales reports" << endl;
}


///     O T H E R   F U N C T I O N S

///     DISPLAY WITH ID
int displayWithId(Sale record){
    Date date = record.getDate();

    cout << " SALE ID: " << record.getSaleId() << "   CUSTOMER ID: " << record.getCustomerId() << "   PRODUCT ID: " << record.getProductId();
    cout << "   QUANTITY: " << record.getQuantity() << "   UNIT PRICE: $" << record.getUnitPrice() << "   TOTAL PRICE: $" << record.getTotalPrice() << "   DATE: ";
    date.Display();
    cout << endl;
}

///     DISPLAY WITHOUT ID
int displayWithoutId(Sale record){
    Date date = record.getDate();

    cout << " CUSTOMER ID: " << record.getCustomerId() << endl;
    cout << " PRODUCT ID: " << record.getProductId() << endl;
    cout << " QUANTITY: " << record.getQuantity() << endl;
    cout << " UNIT PRICE $" << record.getUnitPrice() << endl;
    cout << " TOTAL PRICE $" << record.getTotalPrice() << endl;
    cout << " DATE: ";
    date.Display();
    cout << endl;
}






