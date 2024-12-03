#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <string>
#include "Billable.h"
namespace seneca {
class Menu {
    private:
        std::string title;         
        std::string exitOption;    
        int indentations;          
        std::vector<Billable*> options;

    public:
      
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
