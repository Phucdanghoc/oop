#include "Menu.h"
#include <iostream>
#include <iomanip> 
#include "Billable.h"

namespace seneca {
    Menu::Menu(const std::string& title, const std::string& exitOption, int indentations)
        : title(title), exitOption(exitOption), indentations(indentations) {}
    int Menu::size() {
        return options.size();
    }
    Billable* Menu::operator[](int index) {
        if (index >= 0 && index < options.size()) { 
            return options[index];
        }
        return nullptr; 
    }
    
    void Menu::addOption(Billable* option) {
        options.push_back(option);
    }
    int Menu::display() const {
        printTitle();
        printOptions();
        std::cout << std::string(indentations, ' ') << "Please select an option: ";
        int selection;
        std::cin >> selection;

        
        if (selection == 0) {
            std::cout << std::string(indentations, ' ') << exitOption << std::endl;
        }
        return selection;
    }

    
    void Menu::printTitle() const {
        std::cout << std::string(indentations, ' ') << title << std::endl;
        std::cout << std::string(indentations, ' ') << "========================================" << std::endl;
    }

    
    
   void Menu::printOptions() const {
        int targetWidth = 50;
        for (size_t i = 0; i < options.size() -1; ++i) {
            std::string name = options[i]->name();
            double price = options[i]->price();
            std::cout << std::string(indentations, ' ') << (i + 1) << ". " 
                    << std::left << name;
            int dotsNeeded = targetWidth - name.length() - std::to_string(price).length() - 1; 
            if (dotsNeeded < 1) dotsNeeded = 1; 
            std::cout << std::string(dotsNeeded, '.');
            std::cout << std::fixed << std::setprecision(2) << price << std::endl;
        }

        std::cout << std::string(indentations, ' ') << "0. " << exitOption << std::endl;
    }
   
}
