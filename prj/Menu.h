#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <string>
#include "Billable.h"
namespace seneca {
class Menu {
    private:
        std::string title;           // Tiêu đề menu (ví dụ: "Food Menu", "Drink Menu")
        std::string exitOption;      // Lựa chọn quay lại (ví dụ: "Back to Order")
        int indentations;            // Số lượng thụt đầu dòng khi hiển thị menu
        std::vector<Billable*> options;  // Danh sách các món trong menu

    public:
        // Constructor
        Menu(const std::string& title, const std::string& exitOption, int indentations);
        void addOption(Billable* option);
        Billable* operator[](int index);
        int size();
        int display() const;
        void printTitle() const;    
        void printOptions() const;
    };

}


#endif // MENU_H
