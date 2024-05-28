#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <stdexcept>

using namespace std;

// Class representing a product with a name and price
class Product {
public:
    string name;
    float price;

    Product(string name, float price) : name(name), price(price) {}
};

// Class representing a category of products
class Category {
public:
    string name;
    vector<Product> products;

    Category(string name) : name(name) {}

    // Add a product to the category
    void addProduct(const Product& product) {
        products.push_back(product);
    }

    // Edit a product in the category
    void editProduct(size_t index, const Product& product) {
        if (index < products.size()) {
            products[index] = product;
        }
    }

    // Delete a product from the category
    void deleteProduct(size_t index) {
        if (index < products.size()) {
            products.erase(products.begin() + index);
        }
    }

    // Display all products in the category
    void displayProducts() const {
        for (size_t i = 0; i < products.size(); ++i) {
            cout << i + 1 << ". " << products[i].name << " (Rs. " << products[i].price << ")\n";
        }
    }

    // Allow customer to select products from the category and add to bill
    float selectProduct() const {
        int choice;
        float bill = 0;
        char cont;

        system("cls");
        system("color 70");

        cout << "\n" << name << ":\n";
        displayProducts();

        while (true) {
            cout << "\nYour Choice: ";
            cin >> choice;
            if (cin.fail() || choice < 1 || choice > products.size()) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid input. Please try again.\n";
            } else {
                bill += products[choice - 1].price;
                cout << "Added to cart! Press 'Y' to add another item: ";
                cin >> cont;
                if (cont != 'y' && cont != 'Y') {
                    break;
                }
            }
        }

        return bill;
    }
};

// Main store class managing categories and operations
class Store {
private:
    vector<Category> categories; // List of product categories
    float cart; // Current cart total
    double revenue; // Total store revenue
    string adminPassword; // Admin password

public:
    Store() : cart(0), revenue(196564.61), adminPassword("Raad") {}

    // Add a category to the store
    void addCategory(const Category& category) {
        categories.push_back(category);
    }

    // Display all categories and allow customer to choose products
    void displayCategories() {
        int choice;

        while (true) {
            system("cls");
            system("color B0");

            cout << "-------------------------------------- CATEGORIES --------------------------------------\n";
            for (size_t i = 0; i < categories.size(); ++i) {
                cout << "Press " << i << " for " << categories[i].name << "\n";
            }

            cout << "\nYour Choice: ";
            cin >> choice;

            if (cin.fail() || choice < 0 || choice >= categories.size()) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid input, please enter a valid category number.\n";
                Sleep(1000);
            } else {
                cart += categories[choice].selectProduct();
                revenue += cart;
                cout << "\nYour Total Bill = Rs. " << cart;
                char cont;
                cout << "\nPress 'Y' to add more items from categories: ";
                cin >> cont;
                if (cont != 'y' && cont != 'Y') {
                    break;
                }
            }
        }
    }

    // Display loading screen animation
    void displayLoadingScreen() {
        char x = 219;
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t\t\t\t\tL O A D I N G " << endl;
        cout << "\t\t\t\t\t";
        for (int i = 0; i < 69; i++) {
            cout << x;
            Sleep(20);
        }
        cout << endl << endl << endl << endl;
    }

    // Save delivery information to a file
    void saveDeliveryInfo() {
        string name, address;
        long int num;

        cout << "Enter Your Mobile Phone Number: ";
        cin >> num;
        cout << "Enter Your Address: ";
        cin.ignore();
        getline(cin, address);
        cout << "Enter Your First Name: ";
        getline(cin, name);

        ofstream file("record.csv", ios::app);
        if (file.is_open()) {
            file << name << "," << address << "," << num << "," << cart << "\n";
            file.close();
        } else {
            cerr << "Error opening file.\n";
        }

        cout << "Your Total Bill: Rs. " << cart << endl;
        cout << "You will receive your order at your doorstep in 30 minutes\n";
    }

    // Search for a product by name
    void searchProduct() const {
        string searchQuery;
        cout << "Enter product name to search: ";
        cin.ignore();
        getline(cin, searchQuery);

        bool found = false;
        for (const auto& category : categories) {
            for (const auto& product : category.products) {
                if (product.name.find(searchQuery) != string::npos) {
                    cout << "Found " << product.name << " in " << category.name << " category, Price: Rs. " << product.price << "\n";
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "Product not found.\n";
        }
    }

    // Admin menu for managing products and viewing customer info
    void adminMenu() {
        while (true) {
            int choice;
            cout << "\nAdmin Menu:\n";
            cout << "1. Add Product\n";
            cout << "2. Edit Product\n";
            cout << "3. Delete Product\n";
            cout << "4. View Customer Information\n";
            cout << "5. Change Password\n";
            cout << "6. Exit Admin Menu\n";
            cout << "Your Choice: ";
            cin >> choice;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                cout << "Invalid input. Please try again.\n";
            } else {
                switch (choice) {
                    case 1:
                        addProduct();
                        break;
                    case 2:
                        editProduct();
                        break;
                    case 3:
                        deleteProduct();
                        break;
                    case 4:
                        viewCustomerInformation();
                        break;
                    case 5:
                        changePassword();
                        break;
                    case 6:
                        return;
                    default:
                        cout << "Invalid choice. Please try again.\n";
                }
            }
        }
    }

    // Add a new product to a category
    void addProduct() {
        int categoryIndex;
        string productName;
        float productPrice;

        cout << "Enter the category index to add a product: ";
        cin >> categoryIndex;
        if (categoryIndex < 0 || categoryIndex >= categories.size()) {
            cout << "Invalid category index.\n";
            return;
        }

        cout << "Enter the product name: ";
        cin.ignore();
        getline(cin, productName);
        cout << "Enter the product price: ";
        cin >> productPrice;

        categories[categoryIndex].addProduct(Product(productName, productPrice));
        cout << "Product added successfully.\n";
    }

    // Edit an existing product in a category
    void editProduct() {
        int categoryIndex, productIndex;
        string productName;
        float productPrice;

        cout << "Enter the category index to edit a product: ";
        cin >> categoryIndex;
        if (categoryIndex < 0 || categoryIndex >= categories.size()) {
            cout << "Invalid category index.\n";
            return;
        }

        cout << "Enter the product index to edit: ";
        cin >> productIndex;
        if (productIndex < 1 || productIndex > categories[categoryIndex].products.size()) {
            cout << "Invalid product index.\n";
            return;
        }

        cout << "Enter the new product name: ";
        cin.ignore();
        getline(cin, productName);
        cout << "Enter the new product price: ";
        cin >> productPrice;

        categories[categoryIndex].editProduct(productIndex - 1, Product(productName, productPrice));
        cout << "Product edited successfully.\n";
    }

    // Delete a product from a category
    void deleteProduct() {
        int categoryIndex, productIndex;

        cout << "Enter the category index to delete a product: ";
        cin >> categoryIndex;
        if (categoryIndex < 0 || categoryIndex >= categories.size()) {
            cout << "Invalid category index.\n";
            return;
        }

        cout << "Enter the product index to delete: ";
        cin >> productIndex;
        if (productIndex < 1 || productIndex > categories[categoryIndex].products.size()) {
            cout << "Invalid product index.\n";
            return;
        }

        categories[categoryIndex].deleteProduct(productIndex - 1);
        cout << "Product deleted successfully.\n";
    }

    // View customer information from the file
    void viewCustomerInformation() {
        ifstream file("record.csv");
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                cout << line << "\n";
            }
            file.close();
        } else {
            cerr << "Error opening file.\n";
        }
    }

    // Change admin password with a security question
    void changePassword() {
        string answer;

        cout << "What is the dog's name? ";
        cin >> answer;
        if (answer == "Isreal") {
            cout << "Enter new password: ";
            cin >> adminPassword;
            cout << "Password changed successfully.\n";
        } else {
            cout << "Incorrect answer.\n";
        }
    }

    // Authenticate admin with password
    bool authenticateAdmin() {
        string password;

        cout << "Enter admin password: ";
        cin >> password;
        return password == adminPassword;
    }
};

int main() {
    Store store;

    // Initialize categories and products
    Category instantFood("Instant Food");
    instantFood.addProduct(Product("Kolson Noodles", 40.0));
    instantFood.addProduct(Product("Knorr Noodles", 41.0));
    instantFood.addProduct(Product("Samyang", 270.0));
    instantFood.addProduct(Product("National Vermicelli", 32.0));
    instantFood.addProduct(Product("Kolson Large Elbow", 124.0));
    instantFood.addProduct(Product("Kolson Spaghetti", 135.0));
    instantFood.addProduct(Product("Lays Masala", 50.0));
    instantFood.addProduct(Product("Pringles", 300.0));
    instantFood.addProduct(Product("Lites", 20.0));
    store.addCategory(instantFood);

    Category freshMeat("Fresh Meat");
    freshMeat.addProduct(Product("Chicken Mince", 530.0));
    freshMeat.addProduct(Product("Karahi Cut", 360.0));
    freshMeat.addProduct(Product("Boneless Chicken", 520.0));
    freshMeat.addProduct(Product("Mutton Mince", 1500.0));
    freshMeat.addProduct(Product("Shoulder/Dusti", 1500.0));
    freshMeat.addProduct(Product("Boneless Mutton", 2100.0));
    freshMeat.addProduct(Product("Beef Mince", 1000.0));
    freshMeat.addProduct(Product("Beef Shoulder/Dusti", 1500.0));
    freshMeat.addProduct(Product("Boneless Beef", 1700.0));
    store.addCategory(freshMeat);

    Category fishSeafood("Fish & Seafood");
    fishSeafood.addProduct(Product("Tilapia Fish Fillets", 1100.0));
    fishSeafood.addProduct(Product("Rahu Fish", 1500.0));
    fishSeafood.addProduct(Product("Tuna Fish", 1700.0));
    fishSeafood.addProduct(Product("Surmai Fish", 2200.0));
    fishSeafood.addProduct(Product("Tilapia", 1000.0));
    fishSeafood.addProduct(Product("Tiger Jumbo Prawn", 3000.0));
    fishSeafood.addProduct(Product("Mud Crab", 1700.0));
    store.addCategory(fishSeafood);

    Category grocery("Grocery");
    grocery.addProduct(Product("Red Chilli Powder", 137.0));
    grocery.addProduct(Product("National Iodized Pink Salt", 55.0));
    grocery.addProduct(Product("Sugar", 110.0));
    grocery.addProduct(Product("Vinegar", 120.0));
    grocery.addProduct(Product("National Kheer mix", 100.0));
    grocery.addProduct(Product("National Ice Cream Powder", 100.0));
    grocery.addProduct(Product("Rafhan Custard Powder", 100.0));
    grocery.addProduct(Product("Shan Jelly mix", 80.0));
    grocery.addProduct(Product("Mitchell's Orange Marmalade Jam", 100.0));
    grocery.addProduct(Product("Marhaba Herbal Honey", 193.0));
    grocery.addProduct(Product("Chicken Mayonnaise Spread", 380.0));
    store.addCategory(grocery);

    Category personalCare("Personal Care");
    personalCare.addProduct(Product("Nivea Men Black Body Spray", 500.0));
    personalCare.addProduct(Product("Gillette Mach 3 Shaving Form", 400.0));
    personalCare.addProduct(Product("Dari Mooch Beard Growth Oil", 1100.0));
    personalCare.addProduct(Product("Colgate Pro-relief Toothbrush", 171.0));
    personalCare.addProduct(Product("Sensodyne Toothpaste", 245.0));
    personalCare.addProduct(Product("Listerine Mouthwash", 320.0));
    personalCare.addProduct(Product("Medora Nail Enamel", 175.0));
    personalCare.addProduct(Product("CVB Skin Foundation", 420.0));
    personalCare.addProduct(Product("PinkFlash Waterproof Mascara", 238.0));
    store.addCategory(personalCare);

    Category dryFruitsNuts("Dry Fruits & Nuts");
    dryFruitsNuts.addProduct(Product("Almond White", 2000.0));
    dryFruitsNuts.addProduct(Product("Ajwa Dates", 310.0));
    dryFruitsNuts.addProduct(Product("Walnuts", 2500.0));
    store.addCategory(dryFruitsNuts);

    Category homeCare("Home Care");
    homeCare.addProduct(Product("Ariel Surf", 330.0));
    homeCare.addProduct(Product("Floral Scent Bar", 45.0));
    homeCare.addProduct(Product("Mortein Insect Killer Spray", 278.0));
    homeCare.addProduct(Product("Trash Bags", 270.0));
    homeCare.addProduct(Product("Crown Fancy Wiper", 250.0));
    homeCare.addProduct(Product("Broom", 190.0));
    homeCare.addProduct(Product("Scotch Brite", 64.0));
    homeCare.addProduct(Product("Lemon Max Dish Washing Bar", 48.0));
    homeCare.addProduct(Product("Kite Matchbox", 40.0));
    store.addCategory(homeCare);

    Category babyCare("Baby Care");
    babyCare.addProduct(Product("Johnson's Baby Wipes", 340.0));
    babyCare.addProduct(Product("Pampers Diaper", 255.0));
    babyCare.addProduct(Product("Nestle Nangrow Optipro3", 2560.0));
    babyCare.addProduct(Product("Nestle Nido Shield", 1120.0));
    babyCare.addProduct(Product("Nestle Cerelac", 278.0));
    babyCare.addProduct(Product("Johnson's Baby Lotion", 360.0));
    babyCare.addProduct(Product("Johnson's Baby Powder", 450.0));
    babyCare.addProduct(Product("Johnson's Baby Shampoo", 738.0));
    store.addCategory(babyCare);

    Category bakeryDairy("Bakery Dairy");
    bakeryDairy.addProduct(Product("Olpers 1 Liter carton", 1099.0));
    bakeryDairy.addProduct(Product("Nupur milk", 217.0));
    bakeryDairy.addProduct(Product("Nestle Everydays Liquid Tea Whitener", 20.0));
    bakeryDairy.addProduct(Product("Nurpur Unsalted Butter", 289.0));
    bakeryDairy.addProduct(Product("Nurpur Cheddar Cheese", 390.0));
    bakeryDairy.addProduct(Product("Adam's Single Mozzarella Cheese slices", 430.0));
    bakeryDairy.addProduct(Product("Classic Eggs Farm Fresh", 204.0));
    bakeryDairy.addProduct(Product("Sb Eggs Super", 199.0));
    bakeryDairy.addProduct(Product("Desi Kukkari Eggs", 149.0));
    store.addCategory(bakeryDairy);

    Category beverages("Beverages");
    beverages.addProduct(Product("Lipton Yellow Label Pouch", 1045.0));
    beverages.addProduct(Product("Tapal Green Tea", 99.0));
    beverages.addProduct(Product("Tapal Danedar Teabags", 270.0));
    beverages.addProduct(Product("Fanta Orange Flavour", 45.0));
    beverages.addProduct(Product("Coke Tin Can", 60.0));
    beverages.addProduct(Product("Seven up Diet", 34.0));
    beverages.addProduct(Product("Nestle Fruta Vitals", 180.0));
    beverages.addProduct(Product("Shezan Mango Juice", 20.0));
    beverages.addProduct(Product("Cappy Pulpy Orange Juice", 65.0));
    store.addCategory(beverages);

    // Display loading screen
    store.displayLoadingScreen();

    char accessType;
    cout << "Select access type (c for customer, a for admin): ";
    cin >> accessType;

    if (accessType == 'a' || accessType == 'A') {
        // Authenticate and show admin menu if access type is admin
        if (store.authenticateAdmin()) {
            store.adminMenu();
        } else {
            cout << "Authentication failed.\n";
        }
    } else {
        // Show categories and allow customer to shop if access type is customer
        store.displayCategories();
        char searchChoice;
        cout << "Do you want to search for a product? (y/n): ";
        cin >> searchChoice;
        if (searchChoice == 'y' || searchChoice == 'Y') {
            store.searchProduct();
        }
        store.saveDeliveryInfo();
    }

    _getch();
    return 0;
}
