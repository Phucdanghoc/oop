#include "Drink.h"
#include <iostream>
#include <iomanip> 
#include <fstream> 
using namespace std;
namespace seneca {
    Drink::Drink() : m_size('\0') {
        m_name = nullptr;
        m_price = 0.0;
    }

   
    Drink::Drink(const Drink& other) : Billable(other), m_size(other.m_size) {}

   
    Drink& Drink::operator=(const Drink& other) {
        if (this != &other) {
            Billable::operator=(other); 
            m_size = other.m_size; 
        }
        return *this;
    }

   
    Drink::~Drink() {}

   
    double Drink::price() const {
        double adjustedPrice = m_price;

       
        switch (m_size) {
            case 'S': adjustedPrice /= 2; break; 
            case 'M': adjustedPrice *= 0.75; break; 
            case 'L': break; 
            case 'X': adjustedPrice *= 1.5; break; 
            default: break;
        }

        return adjustedPrice;
    }

   
    ostream& Drink::print(ostream& ostr) const {
        ostr << left << setw(28) << setfill('.') << m_name << " | ";

       
        switch (m_size) {
            case 'S': ostr << "SML.."; break;
            case 'M': ostr << "MID.."; break;
            case 'L': ostr << "LRG.."; break;
            case 'X': ostr << "XLR.."; break;
            default: ostr << "....."; break;
        }

        ostr << " | " << right << setw(7) << setfill(' ') << fixed << setprecision(2) << price() << endl;
        return ostr;
    }

   
    bool Drink::order() {
        cout << "Drink Size Selection\n";
        cout << "   1- Small\n";
        cout << "   2- Medium\n";
        cout << "   3- Large\n";
        cout << "   4- Extra Large\n";
        cout << "   0- Back\n";
        cout << ">";
        
        int choice;
        cin >> choice;

        switch (choice) {
            case 1: setSize('S'); break;
            case 2: setSize('M'); break;
            case 3: setSize('L'); break;
            case 4: setSize('X'); break;
            case 0: return false;
            default: cout << "Invalid choice, try again!" << endl; return false;
        }

        return true;
    }
   
    bool Drink::ordered() const {
        return m_size != ' ';
    }
   
    ifstream& Drink::read(ifstream& file) {
        if (file) {
            char temp[100];
            file.getline(temp, 100, ','); 
            name(temp);
            
            file >> m_price; 
            file.ignore(); 

            m_size = ' '; 

            return file;
        }
        return file;
    }
    Billable* Drink::clone() const {
        return new Drink(*this);
    }
   
    void Drink::setSize(char size) {
        m_size = size;
    }
}
