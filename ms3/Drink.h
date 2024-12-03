#ifndef SENECA_DRINK_H
#define SENECA_DRINK_H

#include "Billable.h"   // Bao gồm lớp Billable để kế thừa
#include <iostream>
#include <string>
#include <fstream>

namespace seneca {

  class Drink : public Billable {
    private:
        char m_size; 
    
    public:
        Drink();
        Drink(const Drink& other);  // Copy constructor
        Drink& operator=(const Drink& other);  // Assignment operator
        virtual ~Drink();
        virtual double price() const override;  // Tính giá đồ uống dựa trên kích thước
        virtual ostream& print(ostream& ostr = cout) const override;  // In thông tin đồ uống
        virtual bool order() override;  // Đặt đồ uống
        virtual bool ordered() const override;  // Kiểm tra đồ uống đã được đặt chưa
        virtual ifstream& read(ifstream& file) override;  // Đọc thông tin đồ uống từ file
        void setSize(char size);  // Thiết lập kích thước đồ uống
    };
} 

#endif  // SENECA_DRINK_H
