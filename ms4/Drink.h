#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H

#include "Billable.h"  
#include <iostream>
#include <string>
#include <fstream>

namespace seneca {

  class Drink : public Billable {
    private:
        char m_size; 
    
    public:
        Drink();
        Drink(const Drink& other); 
        Drink& operator=(const Drink& other); 
        virtual ~Drink();
        Billable* clone() const override;
        virtual double price() const override; 
        virtual ostream& print(ostream& ostr = cout) const override; 
        virtual bool order() override; 
        virtual bool ordered() const override; 
        virtual ifstream& read(ifstream& file) override; 
        void setSize(char size); 
    };
} 

#endif 
