PERSONAL PROJECT

Purchases and Sales Management System

This personal project was made to show knowledge of object-oriented programming (classes, composition, inheritance, and more) and file handling.

The system can manage purchases and sales in a business. It has a main menu and sub-menus. These menus are the graphical interface to manage products, purchases, sales, suppliers, and customers.

Products are registered with an auto-increment ID as a unique identifier. The combination of name, product type (the business has its own number classification), and brand is used to check the product authenticity. The system also stores purchase price, sales price, and quantity.
The system can list the information by ID, product type, and brand. It can also search for products by ID, name, product type, and brand.

Suppliers and customers share the same information: identifier (must be unique), name, type of person, phone number, and email. But each one has its own ID: supplier ID or customer ID.
In both cases, the system lists the information by ID, identifier, and type of person. It can also filter by the same criteria plus the name.

Purchases have an auto-increment ID, supplier ID, product ID, unit price, total price, quantity, and date. The system lists purchases by ID, product ID, and supplier ID.
You can search purchases by the same criteria plus date range and amount range.

Sales are similar to purchases, but they have a customer ID instead of a supplier ID.
