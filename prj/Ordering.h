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
        std::vector<Billable*> billItems; // Danh sách các món
        int billNumber; // Số thứ tự hóa đơn
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
        Ordering(const char* drinkFile, const char* foodFile); // Hàm khởi tạo
        void listFoods() const;    // Hiển thị danh sách đồ ăn
        void listDrinks() const;   // Hiển thị danh sách đồ uống
        void orderFood();          // Đặt đồ ăn
        void orderDrink();         // Đặt đồ uống
        void printBill(std::ostream& os) const; // In hóa đơn
        void resetBill();          // Reset hóa đơn
        bool hasUnsavedBill() const; // Kiểm tra hóa đơn chưa lưu
        size_t noOfBillItems() const; // Số lượng món trong hóa đơn
        operator bool() const {
            return isValid;
        }    
    };
}
#endif
