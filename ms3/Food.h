#ifndef SENECA_FOOD_H
#define SENECA_FOOD_H

#include "Billable.h"
#include <iostream>
#include <fstream>
#include <string>  // Để sử dụng std::getline

namespace seneca {

    class Food : public Billable {
        private:
            bool m_ordered;       // Kiểm tra món ăn đã được đặt chưa
            bool m_child;         // Kiểm tra món ăn là phần trẻ em hay không
            char* m_customize;    // Lưu trữ các yêu cầu tùy chỉnh món ăn

        public:
            // Constructor và Destructor
            Food();
            Food(const Food& other);  // Copy constructor
            Food& operator=(const Food& other);  // Assignment operator
            virtual ~Food();
            // Phương thức ảo kế thừa từ Billable
            virtual double price() const override;  // Tính giá món ăn
            virtual ostream& print(ostream& ostr = cout) const override;  // In thông tin món ăn
            virtual bool order() override;  // Đặt món ăn
            virtual bool ordered() const override;  // Kiểm tra món ăn đã được đặt chưa
            virtual ifstream& read(ifstream& file) override;  // Đọc thông tin món ăn từ file
            void setChild(bool child);  // Thiết lập món ăn là phần trẻ em hay không
            void setCustomization(const char* customization);  // Thiết lập tùy chỉnh món ăn
        };
} // namespace seneca

#endif // SENECA_FOOD_H
