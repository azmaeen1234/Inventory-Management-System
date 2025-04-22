# Inventory-Management-System

Project Report of
Programming Language I Lab (CSE115.11) 
Submitted to 
Rejuana Islam 
Lab Instructor
North South University
Department of Electrical and Computer Engineering

Submitted by


Name: Mohammod Azmaeen Mahtab		
ID: 2511014042


Date of Submission: 21/04/2025

Title: Inventory Management System
1.Introduction
This project is a command-line Inventory Management System developed by C. It provides a basic framework for managing products, suppliers and orders, along with user management and data persistence. The system aims to streamline inventory control processes for small businesses.
2.Background
Many small businesses rely on manual methods or simple spreadsheets for inventory management, which can lead to inefficiencies and errors. This project aims to provide a more structured and automated solution using C programming. The system is designed to be a foundational tool that can be expanded upon. The core technology used is C  programming language. 
3.Purpose and Benefits
The primary objectives of this project are:
To create a functional inventory management system using C.
To manage products, suppliers and orders efficiently.
To provide user authentication and role-based access control.
To persist data between program executions.
The benefits of this system includes:
Organized Data: Products, suppliers and orders are stored in a structured format.
Efficient Operations: Streamlined functions for adding, updating, deleting and listing inventory items.
User Authentication: Secure login system with admin and user roles.
4.System Features
The inventory management system offers the following functionalities:
Product Management: 
i.Add new products with details like name, price, quantity, category and supplier
ii.Update existing product, delete products from the system.
iii.List all products.
iv.Search for products with name and category.

Supplier Management:
i.Add new supplier with contact information.
ii.Update supplier details.
iii.Delete suppliers.
iv.List all suppliers.
Order Management:
i.Create new orders, specifying the product and quantity.
ii.Update the status of an order.
iii.List all orders.
iv.Generate order reports, including total orders, pending orders, total revenue, and average order value.
User Management:
i.Add new users with usernames, passwords and roles.(admin or user)(Admins only)
ii.List all users.(Admin only)
iii.Change the current user’s password.
Login and Authentication: User can login with their username and password.
5.User Stories
Here is a user story illustrating the system’s functionalities:
User Story 1: As an inventory manager (admin), I want to add a new product to the system so that I can track its stock and include it in orders.
i.Use case:
Login as an admin.
Navigate to the Product Management menu.
Select “Add Products”.
Enter the product details. (Name, price, quantity, category and supplier ID)
6.Advantages
    ·  Organized Structure: The system provides a structured way to manage inventory data, reducing the risk of errors.
  ·  Role-Based Access Control: The admin role has access to user management functions, enhancing security.
·  Basic Reporting: The system provides basic order reports, offering insights into sales and order status.
  ·  Clear Menus: The menu-driven interface makes the system relatively easy to navigate.
7.Limitations
    ·  Basic User Interface: The command-line interface is not as user-friendly as a graphical interface.
  ·  Limited Error Handling: The system has basic error handling but could be improved with more robust input validation and file operation checks.
  ·  Simple Search: The product search function only supports basic substring matching.
  ·  No Customer Management: The system does not include functionality for managing customer information.
  ·  No Advanced Reporting: The reporting features are limited to basic order statistics.
  ·  Password Security: Passwords are stored in plain text, which is a security risk.
  ·  No Sorting: The system lacks the ability to sort data (e.g., products, suppliers, orders).
No Data Persistence: The system is unable to store data in files.

8.Topics Covered
Structures
Arrays
Pointers
Functions
String manipulation
Conditional statements
Loops
Menu-driven program design   

9.Future Works
The following are some potential future improvements and functionalities:
Implement a graphical user interface (GUI) for improved user experience. 
Add more robust error handling and input validation.
Implement more advanced search and sorting capabilities.
Integrate customer management features.
Addition of logout system.
Data persistence for file saving.
Adding more than one users.
Develop more comprehensive reporting features, such as sales reports and low-stock alerts.
Secure password storage using hashing.
Implement functionality for managing multiple order items per order.
Add the ability to generate reports and export data to files.
Improve data validation.
