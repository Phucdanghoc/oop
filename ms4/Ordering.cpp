#define _CRT_SECURE_NO_WARNINGS
#include "Drink.h"
#include "Food.h"
#include "Billable.h"
#include "Ordering.h"
#include "constants.h"
#include "Menu.h"
#include <cstdio>
#include <limits>
#include <iomanip>  
#include <fstream>
#include <string>
#include "Utils.h"
using namespace std;

namespace seneca {

    Ordering::Ordering(const char* drinkFile, const char* foodFile)
        : billNumber(1), drinkMenu("Drink Menu", "Back to Order", 2), foodMenu("Food Menu", "Back to Order", 2) {
        isValid = validateFiles(drinkFile, foodFile);
        loadDrinks(drinkFile);
        loadFoods(foodFile);


    }
    bool Ordering::validateFiles(const std::string& drinkFile, const std::string& foodFile) {
        std::ifstream drink(drinkFile);
        std::ifstream food(foodFile);
        return drink.good() && food.good();
    }


    size_t Ordering::countRecords(const char* fileName) const {
        std::ifstream file(fileName);
        if (!file) {
            return 0;
        }
        size_t count = 0;
        std::string line;
        while (std::getline(file, line)) {
            count++;
        }
        return count;
    }
    void Ordering::loadDrinks(const char* drinkFile) {
        std::ifstream file(drinkFile);
        if (file) {
            while (!file.eof()) {
                Drink* drink = new Drink();
                drink->read(file);
                drinkMenu.addOption(drink);
            }
        }
    }
    void Ordering::loadFoods(const char* foodFile) {
        std::ifstream file(foodFile);
        if (file) {
            std::string name, category;
            double price;
            while (!file.eof()) {
                Food* food = new Food();
                food->read(file);
                foodMenu.addOption(food);
            }
        }
    }

    void Ordering::listFoods() const {
        foodMenu.display();
    }

    void Ordering::listDrinks() const {
        drinkMenu.display();
    }

    void Ordering::orderFood() {
        int selection = foodMenu.display();
        if (selection > 0 && selection <= foodMenu.size()) {
            Billable* selectedFood = this->foodMenu[selection - 1]->clone(); 

            if (selectedFood != nullptr) {
                if (selectedFood->order()) {
                    billItems.push_back(selectedFood);
                    std::cout << "Order successful.\n";
                } else {
                    delete selectedFood;
                    std::cout << "Order failed.\n";
                }
            }
        } else if (selection == 0) {
            std::cout << "Back to main menu.\n";
        }
    }
    void Ordering::orderDrink() {
        int selection = drinkMenu.display();
        if (selection > 0 && selection <= drinkMenu.size()) {
            Billable* selectedDrink = this->drinkMenu[selection - 1]->clone(); 
            if (selectedDrink != nullptr) {
                if (selectedDrink->order()) {
                    billItems.push_back(selectedDrink);
                    std::cout << "Order successful.\n";
                } else {
                    delete selectedDrink;
                    std::cout << "Order failed.\n";
                }
            }
        } else if (selection == 0) {
            std::cout << "Back to main menu.\n";
        }
    }

    void Ordering::printBill(std::ostream& os) const {
        double totalPrice = 0.0;
        printBillTitle(os);
        int numBillItems = static_cast<int>(billItems.size());
        for (int i = 0; i < numBillItems; ++i) {
            Billable* item = billItems[i];
            if (item) {
               
                item->print(os);  
                totalPrice += item->price(); 
            }
        }
        printTotals(os, totalPrice);
    }

    void Ordering::resetBill() {
        char filename[21];
        Utils utils;
        utils.makeBillFileName(filename, billNumber);
        std::ofstream outFile(filename);
        if (!outFile) {
            std::cerr << "Error: Cannot open file " << filename << " for writing." << std::endl;
            return;
        }
        printBill(outFile);
        std::cout << "Saved bill number " << billNumber << std::endl;
        std::cout << "Starting bill number " << (billNumber + 1) << std::endl;
        size_t numBillItems = billItems.size();
        for (size_t i = 0; i < numBillItems; ++i) {
            delete billItems[i];
        }
        billItems.clear();
        ++billNumber;
    }


    bool Ordering::hasUnsavedBill() const {
        return !billItems.empty();
    }

    size_t Ordering::noOfBillItems() const {
        return billItems.size();
    }
    void Ordering::printBillTitle(std::ostream& os) const {
        os << "Bill # " << std::setw(3) << std::setfill('0') << billNumber 
        << " =============================" << std::endl;
    }

    void Ordering::printTotals(std::ostream& os, double totalAmount) const {
    double tax = totalAmount * Tax;  
    double totalWithTax = totalAmount + tax;
    os << "                     Total:        " << std::fixed << std::setprecision(2) << totalAmount << std::endl;
    os << "                     Tax:           " << std::fixed << std::setprecision(2) << tax << std::endl;
    os << "                     Total+Tax:    " << std::fixed << std::setprecision(2) << totalWithTax << std::endl;
    os << "========================================" << std::endl;
}

}
