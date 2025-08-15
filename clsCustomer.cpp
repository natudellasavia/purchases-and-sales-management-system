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
/// ME DEJO ESTO POR ACÁ

int Customer::AddClsCustomer() {
    // Llamar al método de la clase base para cargar datos de persona
    AddClsPerson();

    // Ahora agregar el dato específico de Customer
    cout << "Ingrese el ID de cliente: ";
    cin >> _customerId;

    return 1; // O cualquier valor de control que uses
}

Si en tu clase Customer tienes un método AddClsCustomer()
y quieres reutilizar el método AddClsPerson() de la clase base (Person) para cargar los datos heredados,
podés simplemente llamarlo desde dentro de AddClsCustomer()

Ya que Customer hereda públicamente de Person, todos los métodos public (como AddClsPerson())
están disponibles directamente desde la clase hija.

*/
