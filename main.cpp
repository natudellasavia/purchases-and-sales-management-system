#include <iostream>
#include "productMenu.h"
#include "customerMenu.h"
#include "supplierMenu.h"
#include "purchaseMenu.h"
#include "saleMenu.h"

using namespace std;

int main(){
    int option;

    bool correctOption = false;
    while(!correctOption){
        system("cls");
        cout << "-------------------------------" << endl;
        cout << "       M A I N   M E N U       " << endl;
        cout << "-------------------------------" << endl;
        cout << " 1 - PURCHASES" << endl;
        cout << " 2 - SALES" << endl;
        cout << " 3 - PRODUCTS" << endl;
        cout << " 4 - SUPPLIER" << endl;
        cout << " 5 - CUSTOMER" << endl << endl;
        cout << " 0 - EXIT THE PROGRAM" << endl;
        cout << "-------------------------------" << endl;
        cout << " SELECT AN OPTION: ";
        cin >> option;

        system("cls");
        switch(option){
            case 1:
                purchaseMenu();
                break;
            case 2:
                saleMenu();
                break;
            case 3:
                productMenu();
                break;
            case 4:
                supplierMenu();
                break;
            case 5:
                customerMenu();
                break;
            case 0:
                cout << endl << " THE PROGRAM HAS FINISHED." << endl;
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
