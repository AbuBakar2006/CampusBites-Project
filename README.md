# ☕ CampusBites Cafe Management System

A comprehensive **Console-Based Cafe Management System** implemented in C++. This project simulates real-world cafe operations including menu management, customer loyalty programs, order processing, and automated sales reporting. It uses **File Handling** (`.csv` and `.txt`) to persist data across sessions.

## 🚀 Features

* **Menu Management:**
    * Add, delete, and update menu items.
    * Categorization: Vegan, Vegetarian, Gluten-Free, Specialty, Drinks.
    * Real-time stock tracking (Inventory decrements upon ordering).
* **Customer CRM & Loyalty System:**
    * Register and update customer details.
    * **Loyalty Points:** Earn 1 point for every $50 spent.
    * **Redemption:** Redeem points for discounts (1 point = $1).
* **Order Processing:**
    * Cart system with stock validation.
    * Generates invoices with dates.
* **Sales Reporting:**
    * Tracks daily revenue.
    * Filters sales records by specific dates or months.
* **Data Persistence:**
    * Automatically saves and loads data for Menu, Customers, and Sales history.

## 🛠️ Object-Oriented Structure

The system is built using modular classes to ensure code maintainability:

| Class | Responsibility |
| :--- | :--- |
| **`MenuItem`** | Manages individual item details (Price, Category, Stock). |
| **`Customer`** | Manages personal info and Loyalty Points logic. |
| **`Order`** | Handles cart items, total calculation, and date stamping. |
| **`Cafe`** | The controller class managing the Menu, Customer database, and Sales files. |

## 📂 File Handling

The program uses the following files to store data permanently:

1.  **`menu.csv`**: Stores item Name, Price, Stock, Category, and Items Sold.
2.  **`customers.csv`**: Stores Customer ID, Name, Contact, Diet Preference, and Points.
3.  **`sales.txt`**: A log of every transaction with timestamps.

## 💻 How to Run

### 1. Compile
Run the following command in your terminal:

```bash
g++ main.cpp -o CampusBites
```
### 2. Run
Execute the compiled program
```bash
CampusBites.cpp
```
### 3. Navigation
Use the numeric keypad to navigate the main menu
```text
 _____       __      __   __   _____    _    _    _____   _____     _____   _______   ______     _____
/ ____|     /  \     |  \/  | |  __  \ | |  | | /   ___| |      \  |_   _| |__   __| |  ____|  /  ____|   
| |        / /\ \    | \  / | | |__)  || |  | | |  (___  |  |_)  |   | |      | |    | |__    |  (____    
| |       / /  \ \   | |\/| | |  ____/ | |  | |  \___  \ |     {     | |      | |    |  __|    \___   \   
| |___   / /    \ \  | |  | | | |      | |__| |  ____)  ||  |_)  |  _| |_     | |    | |____   ____)   |
\_____| /_/      \_\ |_|  |_| |_|       \____/  |______/ |______/  |_____|	  |_|    |______| |_______/  

------------------------------------------------------------------------------------------------
				1. Customer Management
				2. Menu Management
				3. Place Order
				4. Sales Record
				5. Display Menu
-------------------------------------------------------------------------------------------------
Enter your choice:
```

## 📝 Example Usage

####Scenario: Ordering with Loyalty Points
**Menu Path:** 3. Place Order
```text
Enter customer ID: 101
-------------------- Complete Menu --------------------
Item 1:
- Item name: Latte
- Price: $5
- Available items: 50
...

Enter item number to order: 1
Enter quantity: 2
Order more items? (y/n): n

You have 10 loyalty points. Use for discount? (y/n): y
Enter points to use (1 point = $1): 5

Total Amount: $5
```

#### Scenario: Checking Sales
**Menu Path:** 4. Sales Record -> 2. Monthly Sales Report
```text
Enter the month (YYYY-MM): 2024-11
Total Sales for 2024-11: $150.50
```

## ⚠️ Requirements
* **C++ Compiler** (GCC, MinGW, Clang, or MSVC).
* **Standard Library** (Uses <fstream>, <vector>, <ctime> for file and time management).
