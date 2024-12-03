#ifndef SENECA_ORDERING_H
#define SENECA_ORDERING_H
#include "Food.h"
#include "Drink.h"
#include "Billable.h"
#include "constants.h"
#include <vector>
#include "Menu.h"
#include <iostream>

namespace seneca {
    class Ordering {

      private:
        std::vector<Billable*> billItems; 
        int billNumber; 
        bool isValid;
        Menu foodMenu; 
        Menu drinkMenu; 

        void loadFoods(const char* foodFile);
        void loadDrinks(const char* drinkFile);
        size_t countRecords(const char* file) const;
        void printBillTitle(std::ostream& os) const;
        void printTotals(std::ostream& os, double totalAmount) const;
        bool validateFiles(const std::string& drinkFile, const std::string& foodFile);
    public:
        Ordering(const char* drinkFile, const char* foodFile); 
        void listFoods() const;    
        void listDrinks() const;   
        void orderFood();          
        void orderDrink();         
        void printBill(std::ostream& os) const; 
        void resetBill();          
        bool hasUnsavedBill() const; 
        size_t noOfBillItems() const; 
        operator bool() const {
            return isValid;
        }    
    };
}
#endif
