#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

const int totalCustomers = 100;
const int totalOrders = 100;
const int totalMenuItems = 50;

//menuItem class
class MenuItem {
    string name;
    float price;
    int availability;
    int category; // 1: Vegan, 2: Vegetarian, 3: Gluten-Free, 4: Specialty, 5: Drinks
    int itemsSold;

public:
    MenuItem() : name(""), price(0.0), availability(0), category(0), itemsSold(0) {
	}

    void displayItem() {
        cout << endl << "-------------------------------" << endl;
        cout << "- Item name: " << name << endl;
        cout << "- Price: $" << price << endl;
        cout << "- Available items: " << availability << endl;
        cout << "- Category: " << getCategoryName() << endl;
        cout << endl << "-------------------------------" << endl;
    }

    void setName(string n) { 
		name = n; 
	}
    void setPrice(float p) { 
		price = p; 
	}
    void setCategory(int cat) { 
		category = cat; 
	}
    void updateAvailability(int av) { 
		availability = av; 
	}
    void incrementItemsSold(int quantity) { 
		itemsSold += quantity; 
	}

    string getName() { 
		return name; 
	}
    float getPrice() { 
		return price; 
	}
    int getAvailability() { 
		return availability; 
	}
    int getCategory() { 
		return category; 
	}
    int getItemsSold() { 
		return itemsSold; 
	}

    string getCategoryName() {
        switch (category) {
            case 1: 
			return "Vegan";
            case 2: 
			return "Vegetarian";
            case 3: 
			return "Gluten-Free";
            case 4: 
			return "Specialty";
            case 5: 
			return "Drinks";
            default: 
			return "Unknown";
        }
    }

    void saveToFile(ofstream& file) {
        if (file.is_open()) {
            file << name << "," << price << "," << availability << ","
                 << category << "," << itemsSold << "\n";
        }
    }

    void loadFromFile(string line) {
        stringstream ss(line);
        string temp;

        getline(ss, name, ',');
        getline(ss, temp, ',');
        price = stof(temp);
        getline(ss, temp, ',');
        availability = stoi(temp);
        getline(ss, temp, ',');
        category = stoi(temp);
        getline(ss, temp, ',');
        itemsSold = stoi(temp);
    }
};

//customer class
class Customer {
    string name;
    string contact;
    int dietaryPreference; 
    int customerId;
    int loyaltyPoints;
    static int nextCustomerId;

public:
    Customer() : name(""), contact(""), dietaryPreference(0), customerId(0), loyaltyPoints(0) {
        customerId = nextCustomerId++;
    }

    void displayCustomer() {
        cout << endl << "----------------------------------------" << endl;
        cout << "Name: " << name << endl;
        cout << "Contact: " << contact << endl;
        cout << "Customer ID: " << customerId << endl;
        cout << "Dietary preference: " << getDietaryPreferenceName() << endl;
        cout << "Loyalty Points: " << loyaltyPoints << endl;
        cout << "-----------------------------------------" << endl;
    }

    void setName(string n) { 
		name = n; 
	}
    void setContact(string c) { 
		contact = c; 
	}
    void setDietaryPreference(int dp) { 
		dietaryPreference = dp; 
	}
    string getName() { 
		return name; 
	}
    string getContact() { 
		return contact; 
	}
    int getDietaryPreference() { 
		return dietaryPreference; 
	}
    int getCustomerId() { 
		return customerId; 
	}
    int getLoyaltyPoints() { 
		return loyaltyPoints; 
	}

    string getDietaryPreferenceName() {
        switch (dietaryPreference) {
            case 1: 
			return "Vegan";
            case 2: 
			return "Vegetarian";
            case 3: 
			return "Gluten-Free";
            case 4: 
			return "None";
            default: 
			return "Unknown";
        }
    }

    void addLoyaltyPoints(float amount) {
        loyaltyPoints += (int)(amount / 50);
    }

    void useLoyaltyPoints(int points) {
        if (points <= loyaltyPoints) {
            loyaltyPoints -= points;
        }
    }

    void saveToFile(ofstream& file) {
        if (file.is_open()) {
            file << customerId << "," << name << "," << contact << ","
                 << dietaryPreference << "," << loyaltyPoints << "\n";
        }
    }

    void loadFromFile(string line) {
        stringstream ss(line);
        string temp;

        getline(ss, temp, ',');
        customerId = stoi(temp);
        getline(ss, name, ',');
        getline(ss, contact, ',');
        getline(ss, temp, ',');
        dietaryPreference = stoi(temp);
        getline(ss, temp, ',');
        loyaltyPoints = stoi(temp);
    }

    static void initializeNextCustomerId() {
        ifstream file("customers.csv");
        string line;
        int maxId = 0;

        while (getline(file, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string temp;
            getline(ss, temp, ',');
            int storedId = stoi(temp);

            if (storedId > maxId) {
                maxId = storedId;
            }
        }

        nextCustomerId = maxId + 1;
        file.close();
    }
};

int Customer::nextCustomerId = 1;

//order class
class Order {
    static int nextOrderNumber;
    MenuItem items[10];
    int orderNumber;
    int customerId;
    int totalItems;
    float totalPrice;
    string date;

public:
    Order() : customerId(0), totalItems(0), totalPrice(0.0) {
        orderNumber = nextOrderNumber++;
        setDate();
    }

    void setDate() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        date = to_string(1900 + ltm->tm_year) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(ltm->tm_mday);
    }

    string getDate() { 
        return date; 
    }

    void addItem(MenuItem item, int quantity) {
        if (totalItems < 10) {
            items[totalItems] = item;
            totalItems++;
            totalPrice += item.getPrice() * quantity;
        } else {
            cout << "- Cannot add more items to this order..." << endl;
        }
    }

    void setCustomerId(int id) { 
        customerId = id; 
    }
    int getCustomerId() { 
        return customerId; 
    }
    float getTotalPrice() { 
        return totalPrice; 
    }

    void displayOrder() {
        cout << endl;
        cout << endl << "----------------------------------------" << endl;
        cout << "Order Number: " << orderNumber << endl;
        cout << "Customer ID: " << customerId << endl;
        cout << "Total Items: " << totalItems << endl;
        cout << "Total Price: $" << totalPrice << endl;
        cout << "Items Ordered:" << endl;
        for (int i = 0; i < totalItems; i++) {
            cout << "- " << items[i].getName() << " - $" << items[i].getPrice() << endl;
        }
        cout << "----------------------------------------" << endl;
    }
};

int Order::nextOrderNumber = 1;

//cafe class
class Cafe {
    MenuItem menuItems[totalMenuItems];
    int totalMenuItems;
    float dailySales;
    Customer customers[totalCustomers];
    int totalCustomers;

public:
    Cafe() : totalMenuItems(0), dailySales(0), totalCustomers(0) {
        loadMenuFromFile();
        loadCustomersFromFile();
    }

    void loadMenuFromFile() {
        ifstream file("menu.csv");
        string line;
        totalMenuItems = 0;

        while (getline(file, line) && totalMenuItems < totalMenuItems) {
            if (!line.empty()) {
                menuItems[totalMenuItems].loadFromFile(line);
                totalMenuItems++;
            }
        }
        file.close();
    }

    void loadCustomersFromFile() {
        ifstream file("customers.csv");
        string line;
        totalCustomers = 0;

        while (getline(file, line) && totalCustomers < totalCustomers) {
            if (!line.empty()) {
                customers[totalCustomers].loadFromFile(line);
                totalCustomers++;
            }
        }
        file.close();
    }

    void saveMenuToFile() {
        ofstream file("menu.csv");
        for (int i = 0; i < totalMenuItems; i++) {
            menuItems[i].saveToFile(file);
        }
        file.close();
    }

    void saveCustomersToFile() {
        ofstream file("customers.csv");
        for (int i = 0; i < totalCustomers; i++) {
            customers[i].saveToFile(file);
        }
        file.close();
    }

    void addMenuItem(string name, float price, int category, int availability) {
        if (totalMenuItems < totalMenuItems) {
            menuItems[totalMenuItems].setName(name);
            menuItems[totalMenuItems].setPrice(price);
            menuItems[totalMenuItems].setCategory(category);
            menuItems[totalMenuItems].updateAvailability(availability);
            totalMenuItems++;
            saveMenuToFile();
            cout << "Menu item added successfully!\n";
        }
    }

    void addCustomer(Customer customer) {
        if (totalCustomers < totalCustomers) {
            customers[totalCustomers] = customer;
            totalCustomers++;
            saveCustomersToFile();
            cout << "Customer added successfully!\n";
        }
    }

    Customer* getCustomer(int id) {
        for (int i = 0; i < totalCustomers; i++) {
            if (customers[i].getCustomerId() == id) {
                return &customers[i];
            }
        }
        return nullptr;
    }

    void displayMenu() {
        int choice;
        cout << endl;
        cout << "\n1. Display Whole Menu\n";
        cout << "2. Display Menu by Category\n";
        cout << "3. Display Most Popular Item\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayWholeMenu();
                break;
            case 2:
                displayMenuByCategory();
                break;
            case 3:
                displayMostPopularItem();
                break;
            default:
                cout << endl << "- Invalid choice! Please try again ... " << endl;
                break;
        }
    }

    void displayWholeMenu() {
        if (totalMenuItems == 0) {
            cout << endl << "- Menu is empty! " << endl;
            return;
        }

        cout << "\n-------------------- Complete Menu --------------------" << endl;
        for (int i = 0; i < totalMenuItems; i++) {
            cout << "\nItem " << i + 1 << ":" << endl;
            menuItems[i].displayItem();
        }
    }

    void displayMenuByCategory() {
        int category;
        cout << "\nEnter category (1: Vegan, 2: Vegetarian, 3: Gluten-Free, 4: Specialty, 5: Drinks): ";
        cin >> category;

        bool found = false;
        cout << "\n-------------------- " << getCategoryName(category) << " Menu --------------------" << endl;
        for (int i = 0; i < totalMenuItems; i++) {
            if (menuItems[i].getCategory() == category) {
                menuItems[i].displayItem();
                found = true;
            }
        }

        if (!found) {
            cout << "- No items found in category: " << getCategoryName(category) << endl;
        }
    }

    string getCategoryName(int category) {
        switch (category) {
            case 1: return "Vegan";
            case 2: return "Vegetarian";
            case 3: return "Gluten-Free";
            case 4: return "Specialty";
            case 5: return "Drinks";
            default: return "Unknown";
        }
    }

    MenuItem* getMenuItem(int index) {
        if (index >= 0 && index < totalMenuItems) {
            return &menuItems[index];
        }
        return nullptr;
    }

    int getTotalMenuItems() {
        return totalMenuItems;
    }

    void recordSale(float amount) {
        dailySales += amount;
        ofstream file("sales.txt", ios::app);
        if (file.is_open()) {
            time_t now = time(0);
            tm* ltm = localtime(&now);
            file << "Date: " << (1900 + ltm->tm_year) << "-" << (1 + ltm->tm_mon) << "-" << ltm->tm_mday << ", Sale: $" << amount << endl;
            file.close();
        } else {
            cout << endl << "- Unable to open sales file!" << endl;
        }
    }

    void showDailySales() {
        cout << "\n---------- Daily Sales ----------" << endl;
        cout << "- Total Sales: $" << dailySales << endl;
    }

    void decrementTotalMenuItems() {
        if (totalMenuItems > 0) {
            totalMenuItems--;
        }
    }

    void displayMostPopularItem() {
        int maxSold = 0;
        MenuItem* popularItem = nullptr;
        for (int i = 0; i < totalMenuItems; i++) {
            if (menuItems[i].getItemsSold() > maxSold) {
                maxSold = menuItems[i].getItemsSold();
                popularItem = &menuItems[i];
            }
        }
        if (popularItem) {
            cout << "\n---------- Most Popular Item ----------" << endl;
            popularItem->displayItem();
        } else {
            cout << endl << "- No items sold yet ... " << endl;
        }
    }
};

//function prototypes
void customerManagement(Cafe& cafe);
void menuManagement(Cafe& cafe);
void placeOrder(Cafe& cafe);
void showSalesRecord(Cafe& cafe);
void showSalesByDate();
void showSalesByMonth();
void displayBanner();

//main function
int main() {
    Cafe campusBites;
    int choice;

    do {
        system("cls");
        displayBanner();
        cout << "------------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t\t1. Customer Management\n" << endl;
        cout << "\t\t\t\t2. Menu Management\n" << endl;
        cout << "\t\t\t\t3. Place Order\n" << endl;
        cout << "\t\t\t\t4. Sales Record\n" << endl;
        cout << "\t\t\t\t5. Display Menu\n" << endl;
        cout << "-------------------------------------------------------------------------------------------------" << endl;
        cout << endl << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                customerManagement(campusBites);
                break;
            case 2:
                menuManagement(campusBites);
                break;
            case 3:
                placeOrder(campusBites);
                break;
            case 4:
                showSalesRecord(campusBites);
                break;
            case 5:
                campusBites.displayMenu();
                break;
            case 6:
                cout << endl << " GoodBye!- Thanks for using CampusBites ... " << endl;
                break;
            default:
                cout << endl << " - Invalid choice! Please try again ... " << endl;
                break;
        }
        if (choice != 6) {
            system("pause");
        }
    } while (choice != 6);

    return 0;
}

//function definitions
void displayBanner() {
    cout << "\033[33m";
    cout << R"(
   _____      __      __   __   _____   _    _   _____   ____    _____  _______ ______  _____   
  / ____|    / \\    |  \\/  | |  __ \ | |  | | / ____| | __ ) | ____ ||__   __||_____| / ____| 
 | |        / __\\   | |\\/| | | |__) || |  | |  (___   |  _ \\   | |     | |   |____    (___   
 | |       / ____\\  | |   | | |  ___/ | |  | | \\___ \\| |_) ||  | |     | |   |____| \\___ \\ 
 | |___|  / /     \\ | |   | | | |     | |__| | ____) | | |       | |     | |   |_____   ____) | 
  \_____\/_/    \\_\\|_|   |_| |_|     \\____/ |_____/  |____/  |_____|   |_|   |______| _____/  
    )" << endl;
    cout << "\033[0m";
}

void customerManagement(Cafe& cafe) {
    int option;
    cout << "\n1. Register New Customer\n";
    cout << "2. Update Customer Information\n";
    cout << "Enter your choice: ";
    cin >> option;

    if (option == 1) {
        Customer newCustomer;
        string name, contact;
        int preference;

        cout << "Enter customer name: ";
        cin.ignore();
        getline(cin, name);
        newCustomer.setName(name);

        cout << "Enter contact number: ";
        getline(cin, contact);
        newCustomer.setContact(contact);

        cout << "Enter dietary preference (1. Vegan, 2. Vegetarian, 3. Gluten-Free, 4. None): ";
        cin >> preference;
        newCustomer.setDietaryPreference(preference);

        cafe.addCustomer(newCustomer);
        cout << "- Customer registered successfully!" << endl;
        cout << "- Customer details:" << endl;
        newCustomer.displayCustomer();
    } else if (option == 2) {
        int customerId;
        cout << "Enter customer ID: ";
        cin >> customerId;

        Customer* customer = cafe.getCustomer(customerId);
        if (customer) {
            string name, contact;
            int preference;

            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, name);
            customer->setName(name);

            cout << "Enter new contact number: ";
            getline(cin, contact);
            customer->setContact(contact);

            cout << "Enter new dietary preference (1. Vegan, 2. Vegetarian, 3. Gluten-Free, 4. None): ";
            cin >> preference;
            customer->setDietaryPreference(preference);

            cout << "- Customer information updated successfully!" << endl;
            cout << "- Updated customer details:" << endl;
            customer->displayCustomer();
        } else {
            cout << "- Customer not found!" << endl;
        }
    } else {
        cout << "- Invalid option!" << endl;
    }
}

void menuManagement(Cafe& cafe) {
    int option;
    cout << "\n1. Add Menu Item\n";
    cout << "2. Delete Menu Item\n";
    cout << "3. Update Menu Item Availability\n";
    cout << "Enter your choice: ";
    cin >> option;

    if (option == 1) {
        string name;
        float price;
        int availability, category;

        cout << "Enter item name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter category (1. Vegan, 2. Vegetarian, 3. Gluten-Free, 4. Specialty, 5. Drinks): ";
        cin >> category;

        cout << "Enter price: $";
        cin >> price;

        cout << "Enter available quantity: ";
        cin >> availability;

        cafe.addMenuItem(name, price, category, availability);
        cout << "- Menu item added successfully!" << endl;
    } else if (option == 2) {
        cafe.displayMenu();
        int itemNumber;
        cout << "Enter item number to delete: ";
        cin >> itemNumber;

        if (itemNumber > 0 && itemNumber <= cafe.getTotalMenuItems()) {
            for (int i = itemNumber - 1; i < cafe.getTotalMenuItems() - 1; i++) {
                *cafe.getMenuItem(i) = *cafe.getMenuItem(i + 1);
            }
            cafe.getMenuItem(cafe.getTotalMenuItems() - 1)->setName("");
            cafe.getMenuItem(cafe.getTotalMenuItems() - 1)->setPrice(0.0);
            cafe.getMenuItem(cafe.getTotalMenuItems() - 1)->setCategory(0);
            cafe.getMenuItem(cafe.getTotalMenuItems() - 1)->updateAvailability(0);

            cafe.decrementTotalMenuItems();
            cout << "- Menu item deleted successfully!" << endl;
        } else {
            cout << "- Invalid item number!" << endl;
        }
    } else if (option == 3) {
        int itemNumber, availability;
        cout << "Enter item number to update availability: ";
        cin >> itemNumber;

        if (itemNumber > 0 && itemNumber <= cafe.getTotalMenuItems()) {
            cout << "Enter new available quantity: ";
            cin >> availability;
            cafe.getMenuItem(itemNumber - 1)->updateAvailability(availability);
            cout << "- Availability updated successfully!" << endl;
        } else {
            cout << "- Invalid item number!" << endl;
        }
    } else {
        cout << "- Invalid option!" << endl;
    }
}

void placeOrder(Cafe& cafe) {
    int customerId;
    cout << "Enter customer ID: ";
    cin >> customerId;

    Customer* customer = cafe.getCustomer(customerId);
    if (!customer) {
        cout << "- Customer not found! Registering new customer..." << endl;
        customerManagement(cafe);
        customer = cafe.getCustomer(customerId);
    }

    float totalAmount = 0.0;
    char orderMore;
    do {
        cafe.displayWholeMenu();
        int itemNumber, quantity;

        cout << "Enter item number to order: ";
        cin >> itemNumber;

        if (itemNumber > 0 && itemNumber <= cafe.getTotalMenuItems()) {
            MenuItem* item = cafe.getMenuItem(itemNumber - 1);
            cout << "Enter quantity: ";
            cin >> quantity;

            if (quantity > 0 && quantity <= item->getAvailability()) {
                item->updateAvailability(item->getAvailability() - quantity);
                item->incrementItemsSold(quantity);
                totalAmount += item->getPrice() * quantity;
            } else {
                cout << endl << "- Invalid quantity or item unavailable!" << endl;
            }
        } else {
            cout << endl << "- Invalid item number!" << endl;
        }

        cout << "Order more items? (y/n): ";
        cin >> orderMore;
    } while (orderMore == 'y' || orderMore == 'Y');

    if (customer) {
        int points = customer->getLoyaltyPoints();
        if (points > 0) {
            cout << "You have " << points << " loyalty points. Use for discount? (y/n): ";
            char usePoints;
            cin >> usePoints;

            if (usePoints == 'y' || usePoints == 'Y') {
                cout << "Enter points to use (1 point = $1): ";
                int pointsToUse;
                cin >> pointsToUse;

                if (pointsToUse <= points) {
                    customer->useLoyaltyPoints(pointsToUse);
                    totalAmount -= pointsToUse;
                }
            }
        }

        customer->addLoyaltyPoints(totalAmount);
    }

    cout << "\nTotal Amount: $" << totalAmount << endl;
    cafe.recordSale(totalAmount);
    cafe.saveMenuToFile();
}

void showSalesRecord(Cafe& cafe) {
    int option;
    cout << "\n1. Daily Sales Report\n";
    cout << "2. Monthly Sales Report\n";
    cout << "Enter your choice: ";
    cin >> option;

    if (option == 1) {
        cafe.showDailySales();
    } else if (option == 2) {
        showSalesByMonth();
    } else {
        cout << "- Invalid option!" << endl;
    }
}

void showSalesByDate() {
    string targetDate;
    cout << "Enter the date (YYYY-MM-DD): ";
    cin >> targetDate;

    ifstream file("sales.txt");
    string line;
    float total = 0.0;
    bool found = false;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line.find(targetDate) != string::npos) {
            try {
                size_t pos = line.find("Sale: $") + 7;
                total += stof(line.substr(pos));
                found = true;
            } catch (const std::invalid_argument& e) {
                cerr << "- Invalid data in sales.txt: " << line << endl;
                continue;
            }
        }
    }

    if (found) {
        cout << "Total Sales for " << targetDate << ": $" << total << endl;
    } else {
        cout << "- No sales found for " << targetDate << endl;
    }

    file.close();
}

void showSalesByMonth() {
    string targetMonth;
    cout << "Enter the month (YYYY-MM): ";
    cin >> targetMonth;

    ifstream file("sales.txt");
    string line;
    float total = 0.0;
    bool found = false;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line.find(targetMonth) != string::npos) {
            try {
                size_t pos = line.find("Sale: $") + 7;
                total += stof(line.substr(pos));
                found = true;
            } catch (const std::invalid_argument& e) {
                cerr << "- Invalid data in sales.txt: " << line << endl;
                continue;
            }
        }
    }

    if (found) {
        cout << "Total Sales for " << targetMonth << ": $" << total << endl;
    } else {
        cout << "No sales found for " << targetMonth << endl;
    }

    file.close();
}