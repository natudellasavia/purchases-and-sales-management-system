#include <iostream>
#include <cstring>
#include "clsCustomer.h"
#include "clsCustomersDataFile.h"
using namespace std;


// CONSTRUCTOR
Customer::Customer() : Person() {
    _customerId = 0;
}


// SETTERS
void Customer::setCustomerId(int customerId){_customerId = customerId;}


// GETTER
int Customer::getCustomerId(){return _customerId;}



/*
/// ME DEJO ESTO POR AC�

int Customer::AddClsCustomer() {
    // Llamar al m�todo de la clase base para cargar datos de persona
    AddClsPerson();

    // Ahora agregar el dato espec�fico de Customer
    cout << "Ingrese el ID de cliente: ";
    cin >> _customerId;

    return 1; // O cualquier valor de control que uses
}

Si en tu clase Customer tienes un m�todo AddClsCustomer()
y quieres reutilizar el m�todo AddClsPerson() de la clase base (Person) para cargar los datos heredados,
pod�s simplemente llamarlo desde dentro de AddClsCustomer()

Ya que Customer hereda p�blicamente de Person, todos los m�todos public (como AddClsPerson())
est�n disponibles directamente desde la clase hija.

*/
