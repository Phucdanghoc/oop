#include "Food.h"
using namespace std;
#include <cstring> 
#include <iomanip>

namespace seneca {
    Food::Food() : m_ordered(false), m_child(false), m_customize(nullptr) {
        m_name = nullptr;
        m_price = 0.0;
    }

    Food::Food(const Food& other) : Billable(other), m_ordered(other.m_ordered), m_child(other.m_child) {
        if (other.m_customize) {
            m_customize = new char[strlen(other.m_customize) + 1];
            strcpy(m_customize, other.m_customize);
        } else {
            m_customize = nullptr;
        }
    }

    
    Food& Food::operator=(const Food& other) {
        if (this != &other) {
            Billable::operator=(other);  
            m_ordered = other.m_ordered;
            m_child = other.m_child;

            
            if (other.m_customize) {
                m_customize = new char[strlen(other.m_customize) + 1];
                strcpy(m_customize, other.m_customize);
            } else {
                m_customize = nullptr;
            }
        }
        return *this;
    }
    Billable* Food::clone() const {
        return new Food(*this);
    }
    
    Food::~Food() {
        delete[] m_customize;
    }

    
    double Food::price() const {
        double adjustedPrice = m_price;

        
        if (m_child) {
            adjustedPrice /= 2;
        }

        return adjustedPrice;
    }

    
    ostream& Food::print(ostream& ostr) const {
        ostr << left << setw(28) << setfill('.') << m_name << " | ";

        
        if (ordered() && m_child) {
            ostr << "Child";
        } else {
            ostr << ".....";
        }

        ostr << " | " << right << setw(7) << setfill(' ') << fixed << setprecision(2) << price();

        
        if (m_customize && &ostr == &cout) {
            ostr << " >> " << m_customize;
        }

        ostr << endl;
        return ostr;
    }

    
    bool Food::order() {
        cout << "Food Size Selection\n";
        cout << "   1- Adult\n";
        cout << "   2- Child\n";
        cout << "   0- Back\n";
        cout << ">";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: setChild(false); break;
            case 2: setChild(true); break;
            case 0: return false;
            default: cout << "Invalid choice, try again!" << endl; return false;
        }

        m_ordered = true;

        
        cout << "Special instructions\n";
        cin.ignore();
        char buffer[256];
        cin.getline(buffer, 256);
        if (strlen(buffer) > 0) {
            setCustomization(buffer);
        } else {
            delete[] m_customize;
            m_customize = nullptr;
        }

        return true;
    }

    
    bool Food::ordered() const {
        return m_ordered;
    }

    
    ifstream& Food::read(ifstream& file) {
        if (file) {
            char temp[100];
            file.getline(temp, 100, ',');  
            name(temp);

            file >> m_price;  
            file.ignore();  

            m_child = false;  
            m_ordered = false;  
            delete[] m_customize;
            m_customize = nullptr;

            return file;
        }
        
        return file;
    }

    
    void Food::setChild(bool child) {
        m_child = child;
    }

    
    void Food::setCustomization(const char* customization) {
        if (customization) {
            m_customize = new char[strlen(customization) + 1];
            strcpy(m_customize, customization);
        } else {
            m_customize = nullptr;
        }
    }

} 
