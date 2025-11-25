INTRODUCTION

The Restaurant Billing System is a console‑based application designed to simplify the process of managing menu items, taking customer orders, calculating bills, and maintaining sales records. The main objective of this project is to understand real‑world problem solving using the C language.

This system helps restaurant staff to:

Add, update, or delete menu items

Generate detailed customer bills

Apply discounts and GST

Store data using file handling

It provides a simple and efficient way to automate billing operations.

-----------------------------------------------------------------------------------------------------------------------------------------------


OBJECTIVES OF THE PROJECT

To implement a real‑life billing system using C.

To understand and apply file handling for data storage.

To use structures to store menu and billing information.

To create a user‑friendly menu‑driven interface.

To learn how to apply calculations (tax, discount, totals) in programming.

To implement basic inventory and menu management.

---------------------------------------------------------------------------------------------------------------------


SYSTEM FEATURES
1 ADMIN LOGIN

(I) Password‑protected entry

(II) Secures menu management section

2 MENU MANAGEMENT

(I) Add new items

(II) Delete items

UPDATE ITEM INFORMATION

(I) Search items by ID or name

(II) Sort menu by name or price

(III) Low‑stock alerts

3 BILLING MODULE

Take customer orders

Check availability and validate item ID

Calculate:

Subtotal

GST

Discounts

Generate a formatted bill

Save bill to sales file

4 FILE HANDLING

menu.txt → Stores menu data

sales.txt → Stores bill history

Ensures persistent storage

5 ADDITIONAL FUNCTIONALITIES

Dine‑in and takeaway option

Basic error handling for invalid inputs

---------------------------------------------------------------------------------------------------------------------------------------------
TECHNOLOGIES USED

C Programming Language

GCC Compiler

Text files for data handling

Console‑based interface

---------------------------------------------------------------------------------------------------------------------------------------------------------------
SYSTEM FLOW

5 WORKING PROCESS

Program starts → Admin login (if required)

User selects from main menu:

Manage menu

Generate bill

View sales

Menu items are loaded from file

User performs operation

Updated data is saved back to files

Program ends when user exits

5.2 Data Flow

Input → Processing → Output → Save to file

HOW TO RUN THE PROGRAM

Step 1: Clone the Repository

git clone https://github.com/Tara-2911/RESTAURANTE-BILLING-SYSTEM.git
cd RESTAURANTE-BILLING-SYSTEM

Step 2: Compile the Code

gcc restaurant_billing.c -o billing

Step 3: Run the Program

./billing

Step 4: Ensure Required Files Exist

menu.txt → Menu items

sales.txt → Sales history

----------------------------------------------------------------------------------------------------------------------------------------------
PROJECT STRUCTURE

📁 RESTAURANTE-BILLING-SYSTEM
│── restaurant_billing.c     # Source code
│── menu.txt                  # Menu database
│── sales.txt                 # Billing records
│── README.md                 # Documentation

==================================================================================================================================


HERE ARE THE SCREENSHOTS OF MY PROJECT.
<img width="1918" height="1079" alt="Image" src="https://github.com/user-attachments/assets/a0f93ef9-2a3d-4ac6-bd90-f824ff857427" />
<img width="1919" height="1079" alt="Image" src="https://github.com/user-attachments/assets/681bbd59-9c20-4b64-8f21-65a1ea8b2b99" />
<img width="1919" height="1079" alt="Image" src="https://github.com/user-attachments/assets/4f5ee7c6-892a-4697-8050-b4e4d4e3e331" />
<img width="1915" height="1079" alt="Image" src="https://github.com/user-attachments/assets/de212d88-195f-4688-aaaf-d5a7f5ab6c4d" />
<img width="1917" height="1077" alt="Image" src="https://github.com/user-attachments/assets/a0719012-c7f7-4ad3-831c-bde37875c387" />

-----------------------------------------------------------------------------------------------------------------------------------------------
 FUTURE ENHANCEMENT

Adding a graphical user interface

Using a database system (MySQL/SQLite)

Exporting bills as PDF

Adding multi‑user roles (Manager, Cashier)

Monthly sales report generation

-------------------------------------------------------------------------------------------------------------------------------------------------
Conclusion

The Restaurant Billing System demonstrates how core concepts of the C language—such as file handling, structures, and functions—can be used to build a practical application. This project enhances logical thinking and helps understand how real‑world billing systems operate.

It is an excellent beginner project for students learning C programming.
